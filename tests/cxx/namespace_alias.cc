//===--- namespace_alias.cc - test input file for iwyu --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I .

// Check that using a namespace alias requires an appropriate include

#include "tests/cxx/namespace_alias-d1.h"
#include "tests/cxx/namespace_alias-d2.h"
#include "tests/cxx/namespace_alias-i1.h"

void func() {
  // i1_ns1::i1_ns2::function1() from namespace_alias-d1.h
  // i2_ns from namespace_alias-d2.h
  i2_ns::function1();

  // i3_ns1::i3_ns2::function1() from namespace_alias-d3.h
  // i4_ns from namespace_alias-d4.h
  // IWYU: i3_ns1::i3_ns2::function1 is...*namespace_alias-d3.h
  // IWYU: i4_ns is defined in...*namespace_alias-d4.h
  i4_ns::function1();
}

/**** IWYU_SUMMARY

tests/cxx/namespace_alias.cc should add these lines:
#include "tests/cxx/namespace_alias-d3.h"
#include "tests/cxx/namespace_alias-d4.h"

tests/cxx/namespace_alias.cc should remove these lines:
- #include "tests/cxx/namespace_alias-i1.h"  // lines XX-XX

The full include-list for tests/cxx/namespace_alias.cc:
#include "tests/cxx/namespace_alias-d1.h"  // for function1
#include "tests/cxx/namespace_alias-d2.h"  // for i2_ns
#include "tests/cxx/namespace_alias-d3.h"  // for function1
#include "tests/cxx/namespace_alias-d4.h"  // for i4_ns

***** IWYU_SUMMARY */
