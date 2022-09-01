//===--- iwyu_regex.cc - map to canonical #includes for iwyu --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "iwyu_regex.h"

#include "iwyu_port.h"

namespace include_what_you_use {

namespace impl {
static RegexImpl Make(RegexDialect dialect, const std::string& pattern) {
  switch (dialect) {
    case RegexDialect::LLVM:
      return RegexImpl(llvm::Regex(pattern));

    case RegexDialect::ECMAScript:
      return RegexImpl(std::regex(pattern));
  }
  CHECK_UNREACHABLE_("Unexpected regex dialect");
}

static bool Match(const llvm::Regex& r, const std::string& str) {
  return r.match(str);
}

static bool Match(const std::regex& r, const std::string& str) {
  return std::regex_match(str, r);
}

} // impl

PolyRegex::PolyRegex(RegexDialect dialect, const std::string& pattern)
    : impl_(impl::Make(dialect, pattern)) {
}

bool PolyRegex::Match(const std::string& str) const {
  return std::visit([&](auto&& r) { return impl::Match(r, str); }, impl_);
}

bool RegexMatch(RegexDialect dialect, const std::string& str,
                const std::string& pattern) {
  PolyRegex regex(dialect, pattern);
  return regex.Match(str);
}

}  // namespace include_what_you_use
