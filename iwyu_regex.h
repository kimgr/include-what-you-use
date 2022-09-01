//===--- iwyu_regex.h - iwyu driver implementation ------------*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef INCLUDE_WHAT_YOU_USE_IWYU_REGEX_H_
#define INCLUDE_WHAT_YOU_USE_IWYU_REGEX_H_

#include <regex>
#include <string>

#include "llvm/Support/Regex.h"
#include "iwyu_port.h"

namespace include_what_you_use {

enum class RegexDialect { LLVM = 0, ECMAScript = 1 };

class PolyRegex {
 public:
  PolyRegex(const PolyRegex&) = delete;
  PolyRegex& operator=(const PolyRegex&) = delete;

  PolyRegex(RegexDialect dialect, const std::string& pattern);
  PolyRegex(PolyRegex&& rhs);

  ~PolyRegex();

  bool match(const std::string& str) const;

 private:
  void destroy();

  RegexDialect dialect_;
  union {
    std::regex ecmascript_engine_;
    llvm::Regex llvm_engine_;
  };
};

bool RegexMatch(RegexDialect dialect, const std::string& str,
                const std::string& pattern);

}  // namespace include_what_you_use

#endif  // INCLUDE_WHAT_YOU_USE_IWYU_REGEX_H_
