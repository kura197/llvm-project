#pragma once

#include "MYRISCVX.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
    class MYRISCVXFrameLowering : public TargetFrameLowering {
        void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const;
        void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;
    };
}