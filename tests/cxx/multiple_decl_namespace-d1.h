//===--- multiple_decl_namespace-d1.h - test input file for iwyu ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Forward declaration
namespace test::ns3 {
class Class3;
}

namespace test::ns1 {
typedef unsigned Flags;
const Flags F_None = 0;
const Flags F_All = 1;

void function1(const test::ns3::Class3 &c, Flags f);
}  // namespace test::ns1
