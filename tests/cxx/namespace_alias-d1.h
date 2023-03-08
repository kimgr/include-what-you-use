//===--- namespace_alias-d1.h - test input file for iwyu ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D1_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D1_H_

// Just declare something in a namespace. Nested for good measure.
namespace i1_ns1 {
namespace i1_ns2 {
void function1();
}
}  // namespace i1_ns1

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D1_H_
