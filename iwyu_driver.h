//===--- iwyu_driver.h - iwyu driver implementation -----------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_IWYU_DRIVER_H_
#define INCLUDE_WHAT_YOU_USE_IWYU_DRIVER_H_

#include <functional>
#include <memory>

namespace clang {
class ASTFrontendAction;
class CompilerInstance;
}

namespace include_what_you_use {

typedef std::function<std::unique_ptr<clang::ASTFrontendAction>()>
    IwyuActionFactory;

// Creates a CompilerInstance object based on the commandline
// arguments, or NULL if there's an error of some sort.
clang::CompilerInstance* CreateCompilerInstance(int argc, const char **argv);

int ExecuteAction(int argc, const char** argv, IwyuActionFactory create_action);

}  // namespace include_what_you_use

#endif  // INCLUDE_WHAT_YOU_USE_IWYU_DRIVER_H_
