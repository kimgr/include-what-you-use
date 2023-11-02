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
}

namespace include_what_you_use {

typedef std::function<std::unique_ptr<clang::ASTFrontendAction>()>
    IwyuActionFactory;

// Use Clang's Driver to parse the command-line arguments and create a frontend
// action through which we can execute IWYU.
// IWYU action is injected via a factory callback.
int ExecuteAction(int argc, const char** argv, IwyuActionFactory make_action);

}  // namespace include_what_you_use

#endif  // INCLUDE_WHAT_YOU_USE_IWYU_DRIVER_H_
