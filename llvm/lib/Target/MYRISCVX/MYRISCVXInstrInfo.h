#pragma once

#include "MYRISCVXRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "MYRISCVXGenInstrInfo.inc"


namespace llvm {
    class MYRISCVXInstrInfo : public MYRISCVXGenInstrInfo {
        virtual void anchor();

        public:
        explicit MYRISCVXInstrInfo();

        unsigned GetInstSizeInBytes(const MachineInstr &MI) const;
    };
}