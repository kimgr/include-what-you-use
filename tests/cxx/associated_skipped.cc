//===--- associated_skipped.cc - test input file for iwyu ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Regression test for issue #738.
//
// The symptom was an assertion failure because an associated header had not had
// its desired includes calculated before the main file. This happened when the
// associated header was first indirectly included through another header and
// then directly included (and skipped due to include guards).
// That path added it as an associated header, but not as needing IWYU analysis,
// so desired includes were never calculated.

#include "tests/cxx/associated_skipped-d1.h"
#include "tests/cxx/associated_skipped.h"

int main() {
  // twice is in the associated header, which is already present, so
  // no diagnostic expected.
  int x = twice(4);

  // IWYU: quad is...*associated_skipped-i1.h
  return quad(2);
}

/**** IWYU_SUMMARY

tests/cxx/associated_skipped.cc should add these lines:
#include "tests/cxx/associated_skipped-i1.h"

tests/cxx/associated_skipped.cc should remove these lines:
- #include "tests/cxx/associated_skipped-d1.h"  // lines XX-XX

The full include-list for tests/cxx/associated_skipped.cc:
#include "tests/cxx/associated_skipped.h"
#include "tests/cxx/associated_skipped-i1.h"  // for quad

***** IWYU_SUMMARY */
