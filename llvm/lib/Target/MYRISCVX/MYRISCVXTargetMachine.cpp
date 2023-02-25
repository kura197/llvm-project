//===-- MYRISCVXTargetMachine.cpp - Define TargetMachine for MYRISCVX -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about MYRISCVX target spec.
//
//===----------------------------------------------------------------------===//

#include "MYRISCVXTargetMachine.h"
#include "MYRISCVXTargetObjectFile.h"
#include "TargetInfo/MYRISCVXTargetInfo.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"

#define DEBUG_TYPE "riscv-disassembler"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeMYRISCVXTarget() {
    RegisterTargetMachine<MYRISCVX32TargetMachine> X(getTheMYRISCVX32Target()); 
    RegisterTargetMachine<MYRISCVX64TargetMachine> Y(getTheMYRISCVX64Target()); 
}

static StringRef computeDataLayout(const Triple &TT, StringRef CPU, const TargetOptions &Options) {
    std::string Ret = "";
    Ret += "e";
    //Ret += "-m:e";
    Ret += "-m:m";

    if (TT.isAArch64()) Ret += "-p:64:64";
    else Ret += "-p:32:32";

    Ret += "-i8:8:32-i16:16:32-i64:64";
    if (TT.isAArch64()) Ret += "-n64-S128";
    else Ret += "-n32-S64";

    LLVM_DEBUG(dbgs() << "DataLayout: " << Ret << "\n");

    return Ret;
}

static Reloc::Model getEffectiveRelocModel(bool JIT, Optional<Reloc::Model> RM) {
    if (!RM.hasValue() || JIT) return Reloc::Static;
    return *RM;
}

MYRISCVX32TargetMachine::MYRISCVX32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                        StringRef FS, const TargetOptions &Options,
                        Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                        CodeGenOpt::Level OL, bool JIT) 
    : MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT) {}

// TODO:
void MYRISCVX32TargetMachine::anchor() {}

MYRISCVX64TargetMachine::MYRISCVX64TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                        StringRef FS, const TargetOptions &Options,
                        Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                        CodeGenOpt::Level OL, bool JIT) 
    : MYRISCVXTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT) {}

// TODO:
void MYRISCVX64TargetMachine::anchor() {}


MYRISCVXTargetMachine::MYRISCVXTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                        StringRef FS, const TargetOptions &Options,
                        Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                        CodeGenOpt::Level OL, bool JIT) :
    LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT,
                      CPU, FS, Options, getEffectiveRelocModel(JIT, RM),
                      getEffectiveCodeModel(CM, CodeModel::Small), OL),
                      TLOF(std::make_unique<MYRISCVXTargetObjectFile>()),
                      ABI(MYRISCVXABIInfo::computeTargetABI(Options.MCOptions.getABIName())),
                      DefaultSubtarget(TT, CPU, CPU, FS, *this) 
{
    initAsmInfo();
}