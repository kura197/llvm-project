//===-- SimpleRISCBaseInfo.cpp - Top level definitions for SimpleRISC MC ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains small standalone enum definitions for the SimpleRISC target
// useful for the compiler back-end and the MC libraries.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCBaseInfo.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/TargetParser.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "simplerisc-baseinfo"

namespace llvm {

namespace SimpleRISCABI {
ABI computeTargetABI(const Triple &TT, FeatureBitset FeatureBits,
                     StringRef ABIName) {
  auto TargetABI = getTargetABI(ABIName);

  if (!ABIName.empty() && TargetABI == ABI_Unknown) {
    errs()
        << "'" << ABIName
        << "' is not a recognized ABI for this target (ignoring target-abi)\n";
  }
  LLVM_DEBUG(dbgs() << "ABI:" << ABIName << "\n");

  if (TargetABI != ABI_Unknown)
    return TargetABI;

  // TODO:
  //llvm_unreachable("invalid ABI");
}

ABI getTargetABI(StringRef ABIName) {
  auto TargetABI = StringSwitch<ABI>(ABIName)
                       .Case("ilp32", ABI_ILP32)
                       .Default(ABI_Unknown);
  return TargetABI;
}

// TODO:
// To avoid the BP value clobbered by a function call, we need to choose a
// callee saved register to save the value. RV32E only has X8 and X9 as callee
// saved registers and X8 will be used as fp. So we choose X9 as bp.
MCRegister getBPReg() { return SimpleRISC::R30; }

// Returns the register holding shadow call stack pointer.
MCRegister getSCSPReg() { return SimpleRISC::R31; }

} // namespace SimpleRISCABI
} // namespace llvm
