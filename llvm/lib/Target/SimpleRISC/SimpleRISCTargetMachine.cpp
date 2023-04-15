//===-- SimpleRISCTargetMachine.cpp - Define TargetMachine for SimpleRISC -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about SimpleRISC target spec.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISC.h"
#include "SimpleRISCTargetMachine.h"
#include "SimpleRISCTargetObjectFile.h"
#include "TargetInfo/SimpleRISCTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/CodeGen/TargetPassConfig.h"

using namespace llvm;

extern "C" void LLVMInitializeSimpleRISCTarget() {
    RegisterTargetMachine<SimpleRISCTargetMachine> X(getTheSimpleRISCTarget());
}

static StringRef computeDataLayout(const Triple &TT) {
    return "e-m:e-p:32:32-i64:64-n32-S32";
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
    return RM.value_or(Reloc::Static);
}

SimpleRISCTargetMachine::SimpleRISCTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM,
                    std::optional<CodeModel::Model> CM, CodeGenOpt::Level OL, bool JIT) : 
        LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                          getEffectiveRelocModel(RM), getEffectiveCodeModel(CM, CodeModel::Small), OL),
        TLOF(std::make_unique<SimpleRISCELFTargetObjectFile>()) {
        //ABI(SimpleRISCABIInfo::computeTargetABI(Options.MCOptions.getABIName())),
        //DefaultSubtarget(TT, CPU, CPU, FS, *this) {
    initAsmInfo();
}


namespace {
    class SimpleRISCPassConfig : public TargetPassConfig {
        public:
        SimpleRISCPassConfig(SimpleRISCTargetMachine &TM, PassManagerBase &PM)
            : TargetPassConfig(TM, PM) {}

        SimpleRISCTargetMachine &getSimpleRISCTargetMachine() const {
            return getTM<SimpleRISCTargetMachine>();
        }

        bool addInstSelector() override;
    };
}

TargetPassConfig *SimpleRISCTargetMachine::createPassConfig(PassManagerBase &PM) {
    return new SimpleRISCPassConfig(*this, PM);
}

bool SimpleRISCPassConfig::addInstSelector() {
    addPass(createSimpleRISCISelDag(getSimpleRISCTargetMachine(), getOptLevel()));
    return false;
}