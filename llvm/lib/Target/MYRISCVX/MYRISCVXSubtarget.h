#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H

#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/GlobalISel/RegisterBankInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "MYRISCVXGenSubtargetInfo.inc"

namespace llvm {
    class StringRef;
    class MYRISCVXTargetMachine;
    class MYRISCVXSubtarget : public MYRISCVXGenSubtargetInfo {
        virtual void anchor();
        MYRISCVXSubtarget& initializeSubtargetDependencies(StringRef CPU, StringRef TuneCPU, StringRef FS, const TargetMachine &TM);

        public:
        protected:
        bool HasRV64 = false;
        MVT XLenVT = MVT::i32;
        InstrItineraryData InstrItins;
        Triple TargetTriple;

        void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
    };
}

#endif