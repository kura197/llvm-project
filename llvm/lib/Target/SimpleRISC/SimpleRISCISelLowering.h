//===-- SimpleRISCISelLowering.h - SimpleRISC DAG Lowering Interface ------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_SimpleRISC_SimpleRISCISELLOWERING_H
#define LLVM_LIB_TARGET_SimpleRISC_SimpleRISCISELLOWERING_H

#include "SimpleRISC.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"
//#include "llvm/TargetParser/SimpleRISCTargetParser.h"
#include <optional>

namespace llvm {
class SimpleRISCSubtarget;
struct SimpleRISCRegisterInfo;

class SimpleRISCTargetLowering : public TargetLowering {
  const SimpleRISCSubtarget &Subtarget;

public:
  explicit SimpleRISCTargetLowering(const TargetMachine &TM,
                                    const SimpleRISCSubtarget &STI);

  const SimpleRISCSubtarget &getSubtarget() const { return Subtarget; }

  // Lower incoming arguments, copy physregs into vregs
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;
  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, const SDLoc &DL,
                      SelectionDAG &DAG) const override;
  //SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
  //                  SmallVectorImpl<SDValue> &InVals) const override;

};

} // end namespace llvm

#endif
