//===--- multiple_decl_namespace-d2.h - test input file for iwyu ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "tests/cxx/multiple_decl_namespace-d1.h"  // for Flags

namespace test::ns2 {
void function2a(test::ns1::Flags f);
void function2b();
}  // namespace test::ns2
