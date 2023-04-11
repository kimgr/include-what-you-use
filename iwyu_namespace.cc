//===--- iwyu_namespace.cc - namespace tracking for includes --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "iwyu_namespace.h"

#include <map>     // for map
#include <string>  // for string
#include <vector>  // for vector

#include "iwyu_ast_util.h"       // for DynCastFrom, IsForwardDecl
#include "iwyu_location_util.h"  // for GetFilePath, GetLineNumber
#include "iwyu_verrs.h"          // for VERRS
#include "clang/AST/Decl.h"      // for NamespaceDecl, NamedDecl
#include "clang/AST/DeclBase.h"  // for DeclContext
#include "llvm/Support/Casting.h"  // for isa, dyn_cast

// This translation unit contains helpers to track how namespaces are
// used. In particular it tries to suggest the best #include when a
// namespace is used.
//
// This works as follows:
//
// * Keep a map<qualified namespace identifier, list of files>
//
// * Note the NamespaceDecl's for every declaration. The way clang
//   works, the Decl's in the DeclContext of the Declaration will
//   identify the correct file (rather than the initial NamespaceDecl).
//
// * To identify the best NamespaceDecl count how many full-decl's are
//   in each NamespaceDecl. Note that we count per file, as we don't
//   care if there are multiple NamespaceDecl within a file.
//
// * A given qualified namespace identifier will fall into one of
//   three categories:
//
//   - Only one file has full-decl's for the namespace. This is the
//     ideal case, in which case we suggest this file to satisfy the
//     namespace uses.
//
//   - No file has full-decl's for the namespace. For now suggest the
//     initial NamespaceDecl. TODO: If we keep the actual Decl for
//     declarations, can we find the NamespaceDecl for the forward
//     declarations actually being used? We should already be
//     suggesting the relevant header for the forward declaration, so
//     maybe we should not suggest anything?
//
//   - More than one file has full-decl's for the namespace. Avoid
//     pulling in an include for the namespace, and rely on the
//     symbols being used from the namespace to get an appropriate
//     header.

using clang::BlockDecl;
using clang::DeclContext;
using clang::FunctionDecl;
using clang::NamedDecl;
using clang::NamespaceDecl;
using clang::TagDecl;
using llvm::isa;
using llvm::dyn_cast;
using std::map;
using std::string;
using std::vector;

namespace {
class IwyuNsFileInfo {
  const NamespaceDecl* decl;
  unsigned full_decl_count;

 public:
  IwyuNsFileInfo(const NamespaceDecl* decl)
      : decl(decl) {
  }

  const NamespaceDecl* GetNamespaceDecl() const {
    return decl;
  };
  unsigned GetFullDeclCount() const {
    return full_decl_count;
  };
  void AddFullDecl() {
    full_decl_count++;
  };
};
}  // namespace

namespace include_what_you_use {

static map<string, map<string, IwyuNsFileInfo*>> nsfileinfo;

static IwyuNsFileInfo* getNsFileInfo(const NamespaceDecl* ns, string ns_ident,
                                     string filepath) {
  IwyuNsFileInfo* fileinfo = nullptr;

  // Get the intermediate map, creating it if necessary
  map<string, IwyuNsFileInfo*>& m = nsfileinfo[ns_ident];

  if (auto pair = m.find(filepath); pair != m.end()) {
    fileinfo = pair->second;
  } else {
    // filepath not known for this namespace. Create an
    // IwyuNsFileInfo for it
    fileinfo = new IwyuNsFileInfo(ns);
    m[filepath] = fileinfo;
  }

  return fileinfo;
}

static const NamespaceDecl* getBestNamespaceDecl(const NamespaceDecl* ns) {
  string ns_ident = string(ns->getQualifiedNameAsString());
  auto m = nsfileinfo[ns_ident];

  const NamespaceDecl* best_decl = nullptr;
  const NamespaceDecl* decl = nullptr;
  int full_decl_count = 0;
  bool have_full_decls = false;
  bool multiple_files = false;

  for (auto& [filepath, fileinfo] : m) {
    decl = fileinfo->GetNamespaceDecl();
    unsigned count = fileinfo->GetFullDeclCount();

    if (count > 0) {
      if (!have_full_decls) {
        have_full_decls = true;
        full_decl_count = count;
        best_decl = decl;
      } else {
        multiple_files = true;
        full_decl_count += count;
        best_decl = nullptr;
      }
    }
  }

  if (have_full_decls && !multiple_files) {
    int line = GetLineNumber(best_decl->getBeginLoc());
    VERRS(7) << "Single namespace for " << ns_ident << " "
             << GetFilePath(best_decl) << " line " << line << " with "
             << full_decl_count << " full decls\n";
    return best_decl;
  }

  if (decl == nullptr) {
    // No declarations recorded at all. Return the input NamespaceDecl
    int line = GetLineNumber(ns->getBeginLoc());
    VERRS(7) << "No declarations in namespace " << ns_ident << " "
             << GetFilePath(ns) << " line " << line << "\n";
    return ns;
  }

  if (!have_full_decls) {
    // No full declarations. Return the input NamespaceDecl
    int line = GetLineNumber(ns->getBeginLoc());
    VERRS(7) << "No namespace with a full decl for " << ns_ident << " "
             << GetFilePath(ns) << " line " << line << "\n";
    return ns;
  }

  VERRS(7) << "Multiple namespace decls for " << ns_ident << " with "
           << full_decl_count << " full decls. Ignoring namespace use\n";
  return nullptr;
}

void RecordDeclNamespaces(const NamedDecl* decl) {
  const NamespaceDecl* ns;

  // Ignore declarations of sub-namespaces i.e. don't count them as a
  // forward decl or full decl.
  if (isa<NamespaceDecl>(decl))
    return;

  const DeclContext* decl_context = decl->getDeclContext();

  if (IsForwardDecl(decl))
    return;

  for (; decl_context; decl_context = decl_context->getParent()) {
    // Stop traversing up the context - function arguments, structure
    // members and variables in block scope don't need to be recorded,
    // as the function/structure will be.
    //
    // TODO: others?
    if (isa<FunctionDecl, TagDecl, BlockDecl>(decl_context)) {
      break;
    }

    if ((ns = DynCastFrom(decl_context))) {
      // This is the namespace within which the used symbol is declared

      // Get full namespace string...
      string ns_ident = ns->getQualifiedNameAsString();
      string filepath = GetFilePath(ns);

      VERRS(7) << "Recording declaration in namespace " << ns_ident << " for "
               << decl->getName() << " in filepath " << filepath << "\n";

      // Get or create file_info and increment count
      IwyuNsFileInfo* fileinfo = getNsFileInfo(ns, ns_ident, filepath);
      fileinfo->AddFullDecl();

      // TODO: should we count declarations in nested namespaces? I
      // feel like we should

      // TODO: should we record the Decl?
    }
  }
}

const NamespaceDecl* GetBestNamespaceDecl(const NamespaceDecl* ns) {
  return getBestNamespaceDecl(ns);
}

}  // namespace include_what_you_use
