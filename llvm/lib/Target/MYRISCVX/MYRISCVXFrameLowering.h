#pragma once

#include "MYRISCVX.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
    class MYRISCVXSubtarget;

    class MYRISCVXFrameLowering : public TargetFrameLowering {
        protected:
        const MYRISCVXSubtarget &STI;

        public:
        explicit MYRISCVXFrameLowering(const MYRISCVXSubtarget &sti) : 
            TargetFrameLowering(StackGrowsDown, /*StackAlignment=*/Align(16), /*LocalAreaOffset=*/0), STI(sti) {
        }

        void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
        void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
        bool hasFP(const MachineFunction &MF) const override;
    };
}