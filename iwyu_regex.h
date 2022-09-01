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
#include <variant>

#include "llvm/Support/Regex.h"

namespace include_what_you_use {

enum class RegexDialect { LLVM = 0, ECMAScript = 1 };
typedef std::variant<llvm::Regex, std::regex> RegexImpl;

class PolyRegex {
 public:
  PolyRegex(RegexDialect dialect, const std::string& pattern);

  bool Match(const std::string& str) const;

 private:
  PolyRegex(const PolyRegex&) = delete;
  PolyRegex& operator=(const PolyRegex&) = delete;

  RegexImpl impl_;
};

bool RegexMatch(RegexDialect dialect, const std::string& str,
                const std::string& pattern);

}  // namespace include_what_you_use

#endif  // INCLUDE_WHAT_YOU_USE_IWYU_REGEX_H_
