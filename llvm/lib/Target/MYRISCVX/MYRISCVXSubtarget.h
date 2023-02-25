#ifndef LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H
#define LLVM_LIB_TARGET_MYRISCVX_MYRISCVXSUBTARGET_H

#include "MYRISCVXFrameLowering.h"
#include "MYRISCVXISelLowering.h"
#include "MYRISCVXInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/MC/MCInstrItineraries.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "MYRISCVXGenSubtargetInfo.inc"

namespace llvm {
    class StringRef;
    class MYRISCVXTargetMachine;
    class MYRISCVXSubtarget : public MYRISCVXGenSubtargetInfo {
        virtual void anchor();

        protected:
        bool HasRV64 = false;
        MVT XLenVT = MVT::i32;
        InstrItineraryData InstrItins;

        const MYRISCVXTargetMachine &TM;

        Triple TargetTriple;

        const SelectionDAGTargetInfo TSInfo;

        MYRISCVXInstrInfo InstrInfo;
        MYRISCVXFrameLowering FrameLowering;
        MYRISCVXTargetLowering TLInfo;
        MYRISCVXRegisterInfo RegInfo;

        public:
        bool isPositionIndependent() const;
        const MYRISCVXABIInfo &getABI() const;

        MYRISCVXSubtarget(const Triple &TT, StringRef &CPU, StringRef &TuneCPU, StringRef &FS, const MYRISCVXTargetMachine &TM);
        MVT getXLenVT() const { return XLenVT; }

        void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
        bool abiUsesSoftFloat() const;

        unsigned stackAlignment() const { return 8; }

        MYRISCVXSubtarget& initializeSubtargetDependencies(StringRef CPU, StringRef TuneCPU, StringRef FS, const TargetMachine &TM);

        const SelectionDAGTargetInfo *getSelectionDAGInfo() const override { return &TSInfo; }
        const MYRISCVXInstrInfo *getInstrInfo() const override { return &InstrInfo; }
        const TargetFrameLowering *getFrameLowering() const override { return &FrameLowering; }
        const MYRISCVXRegisterInfo *getRegisterInfo() const override { return &RegInfo; }
        const MYRISCVXTargetLowering *getTargetLowering() const override { return &TLInfo; }
        const InstrItineraryData *getInstrItineraryData() const override { return &InstrItins; }
    };
}

#endif