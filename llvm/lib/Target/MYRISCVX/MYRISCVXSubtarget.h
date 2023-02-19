#ifndef LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H
#define LLVM_LIB_TARGET_RISCV_RISCVSUBTARGET_H

#define GET_SUBTARGETINFO_HEADER
#include "MYRISCVXGenSubtargetInfo.inc"

namespace llvm {
    class StringRef;
    class MYRISCVXTargetMachine;
    class MYRISCVXSubtarget : public MYRISCVXGenSubtargetInfo {
        virtual void anchor();

        public:
        protected:
        bool HasRV64 = false;
    }
}

#endif