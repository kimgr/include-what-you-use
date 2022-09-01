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

PolyRegex::PolyRegex(RegexDialect dialect, const std::string& pattern)
    : dialect_(dialect) {
  switch (dialect_) {
    case RegexDialect::LLVM:
      new (&llvm_engine_) llvm::Regex(pattern);
      return;

    case RegexDialect::ECMAScript:
      new (&ecmascript_engine_) std::regex(pattern);
      return;
  }
  CHECK_UNREACHABLE_("Unexpected regex dialect");
}

PolyRegex::PolyRegex(PolyRegex&& rhs) {
  destroy();

  dialect_ = rhs.dialect_;
  switch (dialect_) {
    case RegexDialect::LLVM:
      std::swap(llvm_engine_, rhs.llvm_engine_);
      return;

    case RegexDialect::ECMAScript:
      std::swap(ecmascript_engine_, rhs.ecmascript_engine_);
      return;
  }
  CHECK_UNREACHABLE_("Unexpected regex dialect");
}

PolyRegex::~PolyRegex() {
  destroy();
}

bool PolyRegex::match(const std::string& str) const {
  switch (dialect_) {
    case RegexDialect::LLVM:
      return llvm_engine_.match(str);

    case RegexDialect::ECMAScript:
      return std::regex_match(str, ecmascript_engine_);
  }
  CHECK_UNREACHABLE_("Unexpected regex dialect");
}

void PolyRegex::destroy() {
  switch (dialect_) {
    case RegexDialect::LLVM:
      llvm_engine_.~Regex();
      return;

    case RegexDialect::ECMAScript:
      ecmascript_engine_.~basic_regex();
      return;
  }
  CHECK_UNREACHABLE_("Unexpected regex dialect");
}

bool RegexMatch(RegexDialect dialect, const std::string& str,
                const std::string& pattern) {
  PolyRegex regex(dialect, pattern);
  return regex.match(str);
}

}  // namespace include_what_you_use
