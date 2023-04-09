//===-- SimpleRISCISelLowering.cpp - SimpleRISC DAG Lowering Implementation  --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that SimpleRISC uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCISelLowering.h"
//#include "MCTargetDesc/SimpleRISCMatInt.h"
#include "SimpleRISC.h"
//#include "SimpleRISCMachineFunctionInfo.h"
#include "SimpleRISCRegisterInfo.h"
#include "SimpleRISCSubtarget.h"
#include "SimpleRISCTargetMachine.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/IR/IRBuilder.h"
//#include "llvm/IR/IntrinsicsSimpleRISC.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/KnownBits.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include <optional>

using namespace llvm;

#define DEBUG_TYPE "simplerisc-lower"

SimpleRISCTargetLowering::SimpleRISCTargetLowering(const TargetMachine &TM,
                                                   const SimpleRISCSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {

}

SDValue SimpleRISCTargetLowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                                                       bool IsVarArg,
                                                       const SmallVectorImpl<ISD::InputArg> &Ins,
                                                       const SDLoc &DL, SelectionDAG &DAG,
                                                       SmallVectorImpl<SDValue> &InVals) const {
  return Chain;
}

SDValue SimpleRISCTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                                              const SmallVectorImpl<ISD::OutputArg> &Outs,
                                              const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                                              SelectionDAG &DAG) const {
  return Chain;
}