//===-- SimpleRISCFrameLowering.cpp - SimpleRISC Frame Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the SimpleRISC implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCFrameLowering.h"
//#include "SimpleRISCMachineFunctionInfo.h"
#include "SimpleRISCSubtarget.h"
#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/Support/LEB128.h"

#include <algorithm>

using namespace llvm;


void SimpleRISCFrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const {

}

void SimpleRISCFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {

}
