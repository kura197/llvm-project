#pragma once

#include "llvm/ADT/Triple.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/MC/MCRegisterInfo.h"

namespace llvm {
    class MYRISCVXABIInfo {
        public:
        enum class ABI {Unknown, LP, STACK};

        protected:
        ABI ThisABI;

        public:
        MYRISCVXABIInfo(ABI ThisABI) : ThisABI(ThisABI) {}

        static MYRISCVXABIInfo Unknown() { return MYRISCVXABIInfo(ABI::Unknown); }
        static MYRISCVXABIInfo LP() { return MYRISCVXABIInfo(ABI::LP); }
        static MYRISCVXABIInfo computeTargetABI(StringRef ABIName);

        bool IsKnown() const { return ThisABI != ABI::Unknown; }
        bool IsLP() const { return ThisABI == ABI::LP; }
        bool IsSTACK() const { return ThisABI == ABI::STACK; }
        ABI GetEnumValue() const { return ThisABI; }

        unsigned GetStackPtr() const;
        unsigned GetFramePtr() const;
        unsigned NullPtr() const;

        unsigned GetEhDataReg() const;
        int EhDataRegSize() const;
    };
}