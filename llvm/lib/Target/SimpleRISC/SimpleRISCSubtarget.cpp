//===-- SimpleRISCSubtarget.cpp - SimpleRISC Subtarget Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the SimpleRISC specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCSubtarget.h"
//#include "GISel/SimpleRISCCallLowering.h"
//#include "GISel/SimpleRISCLegalizerInfo.h"
//#include "GISel/SimpleRISCRegisterBankInfo.h"
#include "SimpleRISC.h"
//#include "SimpleRISCFrameLowering.h"
//#include "SimpleRISCMacroFusion.h"
#include "SimpleRISCTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "riscv-subtarget"

//#define GET_SUBTARGETINFO_TARGET_DESC
//#define GET_SUBTARGETINFO_CTOR
//#include "SimpleRISCGenSubtargetInfo.inc"

void SimpleRISCSubtarget::anchor() {}

//SimpleRISCSubtarget &
//SimpleRISCSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
//                                                StringRef TuneCPU, StringRef FS,
//                                                StringRef ABIName) {
//  // Determine default and user-specified characteristics
//  bool Is64Bit = TT.isArch64Bit();
//  if (CPU.empty() || CPU == "generic")
//    CPU = Is64Bit ? "generic-rv64" : "generic-rv32";
//
//  if (TuneCPU.empty())
//    TuneCPU = CPU;
//
//  ParseSubtargetFeatures(CPU, TuneCPU, FS);
//  if (Is64Bit) {
//    XLenVT = MVT::i64;
//    XLen = 64;
//  }
//
//  TargetABI = SimpleRISCABI::computeTargetABI(TT, getFeatureBits(), ABIName);
//  SimpleRISCFeatures::validate(TT, getFeatureBits());
//  return *this;
//}
//
//SimpleRISCSubtarget::SimpleRISCSubtarget(const Triple &TT, StringRef CPU,
//                               StringRef TuneCPU, StringRef FS,
//                               StringRef ABIName, unsigned RVVVectorBitsMin,
//                               unsigned RVVVectorBitsMax,
//                               const TargetMachine &TM)
//    : SimpleRISCGenSubtargetInfo(TT, CPU, TuneCPU, FS),
//      RVVVectorBitsMin(RVVVectorBitsMin), RVVVectorBitsMax(RVVVectorBitsMax),
//      FrameLowering(
//          initializeSubtargetDependencies(TT, CPU, TuneCPU, FS, ABIName)),
//      InstrInfo(*this), RegInfo(getHwMode()), TLInfo(TM, *this) {
//  if (SimpleRISC::isX18ReservedByDefault(TT))
//    UserReservedRegister.set(SimpleRISC::X18);
//
//  CallLoweringInfo.reset(new SimpleRISCCallLowering(*getTargetLowering()));
//  Legalizer.reset(new SimpleRISCLegalizerInfo(*this));
//
//  auto *RBI = new SimpleRISCRegisterBankInfo(*getRegisterInfo());
//  RegBankInfo.reset(RBI);
//  InstSelector.reset(createSimpleRISCInstructionSelector(
//      *static_cast<const SimpleRISCTargetMachine *>(&TM), *this, *RBI));
//}
