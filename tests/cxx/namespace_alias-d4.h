//===--- namespace_alias-d4.h - test input file for iwyu ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D4_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D4_H_

#include "tests/cxx/namespace_alias-d3.h"

// Alias a namespace defined in another file
namespace i4_ns = i3_ns1::i3_ns2;

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_NAMESPACE_ALIAS_D4_H_
