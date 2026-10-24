//===--- use_class.cc - test input file for iwyu --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I . -xc++

#include "tests/stdin/direct.h"

// IWYU: Class is...*indirect.h
Class c;

/**** IWYU_SUMMARY

<stdin> should add these lines:
#include "tests/stdin/indirect.h"

<stdin> should remove these lines:
- #include "tests/stdin/direct.h"  // lines XX-XX

The full include-list for <stdin>:
#include "tests/stdin/indirect.h"  // for Class

***** IWYU_SUMMARY */
