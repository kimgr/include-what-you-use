//===--- multiple_decl_namespace.cc - test input file for iwyu ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I .

// Tests that we handle multiply declared namespaces correctly.
//
// Where declarations of a namespace occur in multiple headers (either
// because forward declarations were needed or otherwise), iwyu should
// avoid recommending to include a header which is otherwise unused
// when it sees a using directive.
//
// A namespaces' declarations can be scattered around multiple files,
// so there may not be a canonical file to include to satisfy a using
// directive. iwyu should already identify a relevant header to
// include for the namespaced identifier(s) that are being used from
// the namespace.
//
// Where a single file provides all used declarations, iwyu can add
// the namespace to the list of identifiers being provided by the file
// (to be added to the include comment).
//
// Where multiple files provide used declarations, avoid adding the
// namespace to any file.

#include "tests/cxx/multiple_decl_namespace-d2.h"
#include "tests/cxx/multiple_decl_namespace-d3.h"

using namespace test::ns2;
using namespace test::ns3;

void uses() {
  // Use an ns3 identifier declared in d3.h
  function3b();

  // Use an identifier declared in d2.h. d2.h includes d1.h that
  // forward declares ns3.
  function2b();

  // The first declaration of ns3 is seen in d1.h, but the
  // declaration that we are using is in d3.h. We should _not_
  // recommend including d1.h for ns3.
}

/**** IWYU_SUMMARY

(tests/cxx/multiple_decl_namespace.cc has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
