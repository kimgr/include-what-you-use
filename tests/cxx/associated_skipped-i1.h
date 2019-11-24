//===--- associated_skipped-i1.h - test input file for iwyu ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_TESTS_CXX_ASSOCIATED_SKIPPED_I1_H_
#define INCLUDE_WHAT_YOU_USE_TESTS_CXX_ASSOCIATED_SKIPPED_I1_H_

// This non-associated header also depends on the associated header.
#include "tests/cxx/associated_skipped.h"

static inline int quad(int v) {
	return twice(v) + twice(v);
}

#endif  // INCLUDE_WHAT_YOU_USE_TESTS_CXX_ASSOCIATED_SKIPPED_I1_H_
