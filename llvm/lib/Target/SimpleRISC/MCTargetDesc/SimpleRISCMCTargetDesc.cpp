//===-- SimpleRISCMCTargetDesc.cpp - SimpleRISC Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file provides SimpleRISC-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "SimpleRISCMCTargetDesc.h"
#include "TargetInfo/SimpleRISCTargetInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "SimpleRISCGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "SimpleRISCGenRegisterInfo.inc"

//#define GET_SUBTARGETINFO_MC_DESC
//#include "SimpleRISCGenSubtargetInfo.inc"

using namespace llvm;

//static MCInstrInfo *createSimpleRISCMCInstrInfo() {
//  MCInstrInfo *X = new MCInstrInfo();
//  InitSimpleRISCMCInstrInfo(X);
//  return X;
//}
//
//static MCRegisterInfo *createSimpleRISCMCRegisterInfo(const Triple &TT) {
//  MCRegisterInfo *X = new MCRegisterInfo();
//  InitSimpleRISCMCRegisterInfo(X, SimpleRISC::X1);
//  return X;
//}
//
//static MCAsmInfo *createSimpleRISCMCAsmInfo(const MCRegisterInfo &MRI,
//                                       const Triple &TT,
//                                       const MCTargetOptions &Options) {
//  MCAsmInfo *MAI = new SimpleRISCMCAsmInfo(TT);
//
//  MCRegister SP = MRI.getDwarfRegNum(SimpleRISC::X2, true);
//  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
//  MAI->addInitialFrameState(Inst);
//
//  return MAI;
//}
//
//static MCObjectFileInfo *
//createSimpleRISCMCObjectFileInfo(MCContext &Ctx, bool PIC,
//                            bool LargeCodeModel = false) {
//  MCObjectFileInfo *MOFI = new SimpleRISCMCObjectFileInfo();
//  MOFI->initMCObjectFileInfo(Ctx, PIC, LargeCodeModel);
//  return MOFI;
//}
//
//static MCSubtargetInfo *createSimpleRISCMCSubtargetInfo(const Triple &TT,
//                                                   StringRef CPU, StringRef FS) {
//  if (CPU.empty() || CPU == "generic")
//    CPU = TT.isArch64Bit() ? "generic-rv64" : "generic-rv32";
//
//  return createSimpleRISCMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
//}
//
//static MCInstPrinter *createSimpleRISCMCInstPrinter(const Triple &T,
//                                               unsigned SyntaxVariant,
//                                               const MCAsmInfo &MAI,
//                                               const MCInstrInfo &MII,
//                                               const MCRegisterInfo &MRI) {
//  return new SimpleRISCInstPrinter(MAI, MII, MRI);
//}
//
//static MCTargetStreamer *
//createSimpleRISCObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
//  const Triple &TT = STI.getTargetTriple();
//  if (TT.isOSBinFormatELF())
//    return new SimpleRISCTargetELFStreamer(S, STI);
//  return nullptr;
//}
//
//static MCTargetStreamer *createSimpleRISCAsmTargetStreamer(MCStreamer &S,
//                                                      formatted_raw_ostream &OS,
//                                                      MCInstPrinter *InstPrint,
//                                                      bool isVerboseAsm) {
//  return new SimpleRISCTargetAsmStreamer(S, OS);
//}
//
//static MCTargetStreamer *createSimpleRISCNullTargetStreamer(MCStreamer &S) {
//  return new SimpleRISCTargetStreamer(S);
//}
//
//namespace {
//
//class SimpleRISCMCInstrAnalysis : public MCInstrAnalysis {
//public:
//  explicit SimpleRISCMCInstrAnalysis(const MCInstrInfo *Info)
//      : MCInstrAnalysis(Info) {}
//
//  bool evaluateBranch(const MCInst &Inst, uint64_t Addr, uint64_t Size,
//                      uint64_t &Target) const override {
//    if (isConditionalBranch(Inst)) {
//      int64_t Imm;
//      if (Size == 2)
//        Imm = Inst.getOperand(1).getImm();
//      else
//        Imm = Inst.getOperand(2).getImm();
//      Target = Addr + Imm;
//      return true;
//    }
//
//    if (Inst.getOpcode() == SimpleRISC::C_JAL || Inst.getOpcode() == SimpleRISC::C_J) {
//      Target = Addr + Inst.getOperand(0).getImm();
//      return true;
//    }
//
//    if (Inst.getOpcode() == SimpleRISC::JAL) {
//      Target = Addr + Inst.getOperand(1).getImm();
//      return true;
//    }
//
//    return false;
//  }
//};
//
//} // end anonymous namespace
//
//static MCInstrAnalysis *createSimpleRISCInstrAnalysis(const MCInstrInfo *Info) {
//  return new SimpleRISCMCInstrAnalysis(Info);
//}
//
//namespace {
//MCStreamer *createSimpleRISCELFStreamer(const Triple &T, MCContext &Context,
//                                   std::unique_ptr<MCAsmBackend> &&MAB,
//                                   std::unique_ptr<MCObjectWriter> &&MOW,
//                                   std::unique_ptr<MCCodeEmitter> &&MCE,
//                                   bool RelaxAll) {
//  return createSimpleRISCELFStreamer(Context, std::move(MAB), std::move(MOW),
//                                std::move(MCE), RelaxAll);
//}
//} // end anonymous namespace

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimpleRISCTargetMC() {
  for (Target *T : {&getTheSimpleRISCTarget()}) {
    //TargetRegistry::RegisterMCAsmInfo(*T, createSimpleRISCMCAsmInfo);
    //TargetRegistry::RegisterMCObjectFileInfo(*T, createSimpleRISCMCObjectFileInfo);
    //TargetRegistry::RegisterMCInstrInfo(*T, createSimpleRISCMCInstrInfo);
    //TargetRegistry::RegisterMCRegInfo(*T, createSimpleRISCMCRegisterInfo);
    //TargetRegistry::RegisterMCAsmBackend(*T, createSimpleRISCAsmBackend);
    //TargetRegistry::RegisterMCCodeEmitter(*T, createSimpleRISCMCCodeEmitter);
    //TargetRegistry::RegisterMCInstPrinter(*T, createSimpleRISCMCInstPrinter);
    //TargetRegistry::RegisterMCSubtargetInfo(*T, createSimpleRISCMCSubtargetInfo);
    //TargetRegistry::RegisterELFStreamer(*T, createSimpleRISCELFStreamer);
    //TargetRegistry::RegisterObjectTargetStreamer(
    //    *T, createSimpleRISCObjectTargetStreamer);
    //TargetRegistry::RegisterMCInstrAnalysis(*T, createSimpleRISCInstrAnalysis);

    //// Register the asm target streamer.
    //TargetRegistry::RegisterAsmTargetStreamer(*T, createSimpleRISCAsmTargetStreamer);
    //// Register the null target streamer.
    //TargetRegistry::RegisterNullTargetStreamer(*T,
    //                                           createSimpleRISCNullTargetStreamer);
  }
}
