//===--- filtered_offload.c - test input file for iwyu --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// IWYU_ARGS: -Xiwyu -v2 -target arm64-apple-macosx11.0.0 -nogpulib -nogpuinc -xhip -c

// IWYU_DRIVER: ignoring offload job

/**** IWYU_SUMMARY(0)

(tests/driver/filtered_offload.c has correct #includes/fwd-decls)

***** IWYU_SUMMARY */
