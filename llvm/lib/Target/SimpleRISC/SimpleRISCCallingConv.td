//===-- SimpleRISCCallingConv.td - Calling Conventions SimpleRISC ----*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This describes the calling conventions for the SimpleRISC architecture.
//
//===----------------------------------------------------------------------===//

// The SimpleRISC calling convention is handled with custom code in
// SimpleRISCISelLowering.cpp (CC_SimpleRISC).

// TODO:
def CSR_ILP32
    : CalleeSavedRegs<(add (sequence "R%u", 0, 16))>;