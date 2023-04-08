//===--- SimpleRISC.cpp - SimpleRISC Helpers for Tools --------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISC.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/DriverDiagnostic.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
#include "llvm/TargetParser/TargetParser.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang::driver;
using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

StringRef simplerisc::getSimpleRISCABI(const ArgList &Args, const llvm::Triple &Triple) {
  if (Arg *A = Args.getLastArg(options::OPT_mabi_EQ))
    return A->getValue();

  return "ilp32";
}