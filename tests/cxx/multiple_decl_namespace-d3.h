//===--- multiple_decl_namespace-d3.h - test input file for iwyu ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

namespace test::ns3 {

class Class3 {
  int i1;
  int i2;
};

Class3* function3a();
void function3b();
}  // namespace test::ns3
