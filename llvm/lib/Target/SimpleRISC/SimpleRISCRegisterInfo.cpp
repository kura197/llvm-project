//===-- SimpleRISCRegisterInfo.cpp - SimpleRISC Register Information ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the SimpleRISC implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCRegisterInfo.h"
#include "SimpleRISC.h"
//#include "SimpleRISCMachineFunctionInfo.h"
#include "SimpleRISCSubtarget.h"
#include "SimpleRISCFrameLowering.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "SimpleRISCGenRegisterInfo.inc"

using namespace llvm;

SimpleRISCRegisterInfo::SimpleRISCRegisterInfo(unsigned HwMode)
    : SimpleRISCGenRegisterInfo(SimpleRISC::R0, /*DwarfFlavour*/0, /*EHFlavor*/0,
                           /*PC*/0, HwMode) {}

const MCPhysReg *
SimpleRISCRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_ILP32_SaveList;
}

const uint32_t *
SimpleRISCRegisterInfo::getCalleeSavedMask(const MachineFunction *MF, CallingConv::ID) const {
  return CSR_ILP32_RegMask;
}

BitVector SimpleRISCRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  static const uint16_t ReservedCPURegs[] = {
    SimpleRISC::R0, SimpleRISC::R1,
  };
  BitVector Reserved(getNumRegs());

  #define array_lengthof(array) (sizeof(array) / sizeof(array[0]))
  for (unsigned I = 0; I < array_lengthof(ReservedCPURegs); I++)
    Reserved.set(ReservedCPURegs[I]);
  
  return Reserved;
}

bool SimpleRISCRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                                 int SPAdj, unsigned FIOperandNum,
                                                 RegScavenger *RS) const {
  return false;
}

Register SimpleRISCRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  // return SP
  return SimpleRISC::R1;
}
