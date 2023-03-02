//===--- iwyu_namespace.h - namespace tracking for includes ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_IWYU_NAMESPACE_H_
#define INCLUDE_WHAT_YOU_USE_IWYU_NAMESPACE_H_

// Forward declarations
namespace clang {
class NamedDecl;
class NamespaceDecl;
}  // namespace clang

namespace include_what_you_use {
void RecordDeclNamespaces(const clang::NamedDecl *decl);

const clang::NamespaceDecl *GetBestNamespaceDecl(
    const clang::NamespaceDecl *ns);
}  // namespace include_what_you_use

#endif  // INCLUDE_WHAT_YOU_USE_IWYU_NAMESPACE_H_
