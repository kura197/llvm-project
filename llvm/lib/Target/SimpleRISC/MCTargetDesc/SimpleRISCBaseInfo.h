//===-- SimpleRISCBaseInfo.h - Top level definitions for SimpleRISC MC ----*- C++ -*-===//
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
#ifndef LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCBASEINFO_H
#define LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCBASEINFO_H

#include "MCTargetDesc/SimpleRISCMCTargetDesc.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/SubtargetFeature.h"

namespace llvm {

namespace SimpleRISCABI {

enum ABI {
  ABI_ILP32,
  ABI_Unknown
};

// Returns the target ABI, or else a StringError if the requested ABIName is
// not supported for the given TT and FeatureBits combination.
ABI computeTargetABI(const Triple &TT, FeatureBitset FeatureBits,
                     StringRef ABIName);

ABI getTargetABI(StringRef ABIName);

// Returns the register used to hold the stack pointer after realignment.
MCRegister getBPReg();

// Returns the register holding shadow call stack pointer.
MCRegister getSCSPReg();

} // namespace SimpleRISCABI

} // namespace llvm

#endif
