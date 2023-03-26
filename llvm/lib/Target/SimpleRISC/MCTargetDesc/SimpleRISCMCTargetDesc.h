//===-- SimpleRISCMCTargetDesc.h - SimpleRISC Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides SimpleRISC specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCMCTARGETDESC_H
#define LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCMCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {
}

// Defines symbolic names for SimpleRISC registers.
#define GET_REGINFO_ENUM
#include "SimpleRISCGenRegisterInfo.inc"

// Defines symbolic names for SimpleRISC instructions.
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "SimpleRISCGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "SimpleRISCGenSubtargetInfo.inc"

#endif
