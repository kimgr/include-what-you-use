//===--- minimal.cc - test input file for iwyu ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -I . -xc++

int i;

/**** IWYU_SUMMARY

(<stdin> has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
