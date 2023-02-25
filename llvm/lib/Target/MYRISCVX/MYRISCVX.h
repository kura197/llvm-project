//===-- MYRISCVX.h - Top-level interface for MYRISCVX -----------------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVX_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVX_H

#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
    class MYRISCVXTargetMachine;
    class FunctionPass;
}

#endif