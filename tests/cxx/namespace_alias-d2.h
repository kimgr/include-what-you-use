//===--- namespace_alias-d2.h - test input file for iwyu ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D2_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D2_H_

#include "tests/cxx/namespace_alias-d1.h"

// Alias a namespace defined in another file
namespace i2_ns = i1_ns1::i1_ns2;

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D2_H_
