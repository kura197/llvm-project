//===-- MYRISCVXMCTargetDesc.cpp - MYRISCVX Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// This file provides MYRISCVX-specific target descriptions.
///
//===----------------------------------------------------------------------===//

#include "MYRISCVXMCTargetDesc.h"
#include "MYRISCVXMCAsmInfo.h"
#include "MYRISCVXInstPrinter.h"

#include "TargetInfo/MYRISCVXTargetInfo.h"
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
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"


#define GET_REGINFO_MC_DESC
#include "MYRISCVXGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "MYRISCVXGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MYRISCVXGenSubtargetInfo.inc"

using namespace llvm;

static MCInstrInfo *createMYRISCVXMCInstrInfo() {
    MCInstrInfo *X = new MCInstrInfo();
    InitMYRISCVXMCInstrInfo(X);
    return X;
}

static MCRegisterInfo *createMYRISCVXMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitMYRISCVXMCRegisterInfo(X, MYRISCVX::RA);
    return X;
}

static MCSubtargetInfo *createMYRISCVXMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    std::string CPUName = std::string(CPU);
    if (CPU.empty())
        CPU = TT.isArch64Bit() ? "cpu-rv64" : "cpu-rv32";
    return createMYRISCVXMCSubtargetInfoImpl(TT, CPU, CPUName, FS);
}

namespace {
    class MYRISCVXMCInstrAnalysis : public MCInstrAnalysis {
        public:
        MYRISCVXMCInstrAnalysis(const MCInstrInfo *Info) : MCInstrAnalysis(Info) {}
    };
}

static MCInstrAnalysis *createMYRISCVXMCInstrAnalysis(const MCInstrInfo *Info) {
    return new MYRISCVXMCInstrAnalysis(Info);
}

static MCAsmInfo *createMYRISCVXMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT, const MCTargetOptions &Options) {
    MCAsmInfo *MAI = new MYRISCVXMCAsmInfo(TT);

    unsigned SP = MRI.getDwarfRegNum(MYRISCVX::SP, true);
    MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
    MAI->addInitialFrameState(Inst);

    return MAI;
}

static MCInstPrinter *createMYRISCVXMCInstPrinter(const Triple &T, unsigned SyntaxVariant,
                                                  const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI) {
    return new MYRISCVXInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMYRISCVXTargetMC() {
    for (Target *T : {&getTheMYRISCVX32Target(), &getTheMYRISCVX64Target()}) {
        RegisterMCAsmInfoFn X(*T, createMYRISCVXMCAsmInfo);
        
        TargetRegistry::RegisterMCInstrInfo(*T, createMYRISCVXMCInstrInfo);
        TargetRegistry::RegisterMCRegInfo(*T, createMYRISCVXMCRegisterInfo);
        TargetRegistry::RegisterMCSubtargetInfo(*T, createMYRISCVXMCSubtargetInfo);
        TargetRegistry::RegisterMCInstrAnalysis(*T, createMYRISCVXMCInstrAnalysis);
        TargetRegistry::RegisterMCInstPrinter(*T, createMYRISCVXMCInstPrinter);
    }
}
