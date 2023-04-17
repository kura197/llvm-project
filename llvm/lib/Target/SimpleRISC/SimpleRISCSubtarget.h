//===-- SimpleRISCSubtarget.h - Define Subtarget for the SimpleRISC -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the SimpleRISC specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_SimpleRISCSUBTARGET_H
#define LLVM_LIB_TARGET_SimpleRISC_SimpleRISCSUBTARGET_H

#include "MCTargetDesc/SimpleRISCBaseInfo.h"
#include "SimpleRISCFrameLowering.h"
#include "SimpleRISCISelLowering.h"
#include "SimpleRISCInstrInfo.h"
#include "SimpleRISCRegisterInfo.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "SimpleRISCGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class SimpleRISCSubtarget : public SimpleRISCGenSubtargetInfo {
public:

private:
  virtual void anchor();

#define GET_SUBTARGETINFO_MACRO(ATTRIBUTE, DEFAULT, GETTER) \
  bool ATTRIBUTE = DEFAULT;
#include "SimpleRISCGenSubtargetInfo.inc"

  unsigned XLen = 32;
  SimpleRISCABI::ABI TargetABI = SimpleRISCABI::ABI_Unknown;
  SimpleRISCFrameLowering FrameLowering;
  SimpleRISCInstrInfo InstrInfo;
  SimpleRISCRegisterInfo RegInfo;
  SimpleRISCTargetLowering TLInfo;

  /// Initializes using the passed in CPU and feature strings so that we can
  /// use initializer lists for subtarget initialization.
  SimpleRISCSubtarget &initializeSubtargetDependencies(const Triple &TT,
                                                       StringRef CPU,
                                                       StringRef TuneCPU,
                                                       StringRef FS,
                                                       StringRef ABIName);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

public:
  // Initializes the data members to match that of the specified triple.
  SimpleRISCSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU, 
                      StringRef FS, StringRef ABIName, const TargetMachine &TM);

  const SimpleRISCFrameLowering *getFrameLowering() const override { return &FrameLowering; };
  const SimpleRISCInstrInfo *getInstrInfo() const override { return &InstrInfo; };
  const SimpleRISCRegisterInfo *getRegisterInfo() const override { return &RegInfo; };
  const SimpleRISCTargetLowering *getTargetLowering() const override { return &TLInfo; };
};
} // End llvm namespace

#endif
