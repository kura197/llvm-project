//===-- SimpleRISCISelDAGToDAG.cpp - A Dag to Dag Inst Selector for SimpleRISC --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===------------------------------------------------------------------------------===//
//
// This file defines an instruction selector for the SimpleRISC target.
//
//===------------------------------------------------------------------------------===//

#include "SimpleRISCISelDAGToDAG.h"
#include "SimpleRISC.h"

//#include "SimpleRISCMachineFunction.h"
#include "SimpleRISCRegisterInfo.h"
#include "SimpleRISCTargetMachine.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
using namespace llvm;

#define DEBUG_TYPE "SimpleRISC-isel"

FunctionPass *llvm::createSimpleRISCISelDag(SimpleRISCTargetMachine &TM,
                                            CodeGenOpt::Level OptLevel) {
  return new SimpleRISCDAGToDAGISel(TM, OptLevel);
}

void SimpleRISCDAGToDAGISel::Select(SDNode *Node) {
  //TODO:
}

char SimpleRISCDAGToDAGISel::ID = 0;
