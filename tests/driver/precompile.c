//===--- precompile.c - test input file for iwyu --------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Check that include-what-you-use exits with error and diagnostic for
// --print-supported-exitensions, which generates only a 'precompile' job.

// IWYU_ARGS: -target aarch64-unknown-gnu-linux --print-supported-extensions

// IWYU_DRIVER: expected data or algorithm...*

/**** IWYU_SUMMARY(1)

// No IWYU summary expected.

***** IWYU_SUMMARY */
