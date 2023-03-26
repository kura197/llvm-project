//===-- SimpleRISCTargetMachine.cpp - Define TargetMachine for SimpleRISC -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about SimpleRISC target spec.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISC.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

namespace llvm {
  Target &getTheSimpleRISCTarget() {
    static Target TheSimpleRISCTarget;
    return TheSimpleRISCTarget;
  }
}

extern "C" void LLVMInitializeSimpleRISCTargetInfo() {
  RegisterTarget<Triple::simplerisc, true> X(getTheSimpleRISCTarget(), "simplerisc", "SimpleRISC (32-bit)", "SimpleRISC");
}