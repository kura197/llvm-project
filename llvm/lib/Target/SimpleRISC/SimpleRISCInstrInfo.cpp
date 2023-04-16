//===-- SimpleRISCInstrInfo.cpp - SimpleRISC Instruction Information ------*- C++ -*-===//
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

#include "SimpleRISCInstrInfo.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#define GET_INSTRINFO_NAMED_OPS
#include "SimpleRISCGenInstrInfo.inc"

SimpleRISCInstrInfo::SimpleRISCInstrInfo(SimpleRISCSubtarget &STI) 
  : SimpleRISCGenInstrInfo(), STI(STI) {}