//===--- builtins_new_included_cxx14.cc - test input file for iwyu --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Test that iwyu suggests the include for <new> be removed if only
// built-in functions are used, C++14 edition (i.e. with -fsized-deallocation).

#include <new>

void foo() {
  char* ch = new char;
  delete ch;
  int* int_array = new int[10];
  delete[] int_array;
}

/**** IWYU_SUMMARY

tests/cxx/builtins_new_included_cxx14.cc should add these lines:

tests/cxx/builtins_new_included_cxx14.cc should remove these lines:
- #include <new>  // lines XX-XX

The full include-list for tests/cxx/builtins_new_included_cxx14.cc:

***** IWYU_SUMMARY */
