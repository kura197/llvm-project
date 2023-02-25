
#include "MYRISCVXInstrInfo.h"

#include "MYRISCVXInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "MYRISCVXGenInstrInfo.inc"

namespace llvm {
    void MYRISCVXInstrInfo::anchor() {}
    MYRISCVXInstrInfo::MYRISCVXInstrInfo() {}

    unsigned MYRISCVXInstrInfo::GetInstSizeInBytes(const MachineInstr &MI) const {
        switch (MI.getOpcode()) {
            default: return MI.getDesc().getSize();
        }
    }
}