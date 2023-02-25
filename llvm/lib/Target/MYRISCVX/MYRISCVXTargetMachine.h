//===-- MYRISCVXTargetMachine.h - Define TargetMachine for MYRISCVX ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the MYRISCVX specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVXTARGETMACHINE_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVXTARGETMACHINE_H

#include "MCTargetDesc/MYRISCVXABIInfo.h"
#include "MYRISCVXSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
    class formatted_raw_ostream;
    class MYRISCVXRegisterInfo;

    class MYRISCVXTargetMachine : public LLVMTargetMachine {
        std::unique_ptr<TargetLoweringObjectFile> TLOF;
        MYRISCVXABIInfo ABI;
        MYRISCVXSubtarget DefaultSubtarget;

        public: 
        MYRISCVXTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                              StringRef FS, const TargetOptions &Options,
                              Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                              CodeGenOpt::Level OL, bool JIT);

        public:
        const MYRISCVXABIInfo &getABI() const { return ABI; }
    };

    class MYRISCVX32TargetMachine : public MYRISCVXTargetMachine {
        virtual void anchor();
        public:
        MYRISCVX32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                                StringRef FS, const TargetOptions &Options,
                                Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                                CodeGenOpt::Level OL, bool JIT);
    };

    class MYRISCVX64TargetMachine : public MYRISCVXTargetMachine {
        virtual void anchor();
        public:
        MYRISCVX64TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                                StringRef FS, const TargetOptions &Options,
                                Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                                CodeGenOpt::Level OL, bool JIT);
    };
}

#endif
