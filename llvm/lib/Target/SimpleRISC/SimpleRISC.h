//===-- SimpleRISC.h - Top-level interface for SimpleRISC -----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// RISC-V back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_SimpleRISC_H
#define LLVM_LIB_TARGET_SimpleRISC_SimpleRISC_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
    class SimpleRISCTargetMachine;
    class MCInst;
    class MachineInstr;
    class FunctionPass;

    void LowerSimpleRISCMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI);

    FunctionPass *createSimpleRISCISelDag(SimpleRISCTargetMachine &TM, CodeGenOpt::Level OptLevel);
} // namespace llvm

#endif
