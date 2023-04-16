//===-- SimpleRISCInstrInfo.h - SimpleRISC Instruction Information --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the SimpleRISC implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_SimpleRISCINSTRINFO_H
#define LLVM_LIB_TARGET_SimpleRISC_SimpleRISCINSTRINFO_H

//#include "SimpleRISCRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DiagnosticInfo.h"

#define GET_INSTRINFO_HEADER
#define GET_INSTRINFO_OPERAND_ENUM
#include "SimpleRISCGenInstrInfo.inc"

namespace llvm {

class SimpleRISCSubtarget;

class SimpleRISCInstrInfo : public SimpleRISCGenInstrInfo {
protected:
  const SimpleRISCSubtarget &STI;

public:
  explicit SimpleRISCInstrInfo(SimpleRISCSubtarget &STI);
};

}

#endif