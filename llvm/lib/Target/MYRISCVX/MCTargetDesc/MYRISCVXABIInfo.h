#pragma once

#include "llvm/ADT/Triple.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/MC/MCRegisterInfo.h"

namespace llvm {
    class MYRISCVXABIInfo {
        public:
        enum class ABI {UnKnown, LP, /*STACK*/};

        protected:
        ABI ThisABI;

        public:
        MYRISCVXABIInfo(ABI ThisABI) : ThisABI(ThisABI) {}

        static MYRISCVXABIInfo UnKnown() { return MYRISCVXABIInfo(ABI::UnKnown); }
        static MYRISCVXABIInfo LP() { return MYRISCVXABIInfo(ABI::LP); }
        static MYRISCVXABIInfo computeTargetABI(StringRef ABIName);

        unsigned GetStackPtr() const;
        unsigned GetFramePtr() const;
        unsigned NullPtr() const;

        unsigned GetEhDataReg() const;
        int EhDataRegSize() const;
    };
}