//===--- SimpleRISC.h - SimpleRISC-specific Tool Helpers ------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SimpleRISC_H
#define LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SimpleRISC_H

#include "clang/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace clang {
namespace driver {
namespace tools {
namespace simplerisc {
StringRef getSimpleRISCABI(const llvm::opt::ArgList &Args,
                      const llvm::Triple &Triple);
} // end namespace simplerisc
} // namespace tools
} // end namespace driver
} // end namespace clang

#endif // LLVM_CLANG_LIB_DRIVER_TOOLCHAINS_ARCH_SimpleRISC_H