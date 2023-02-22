
#include "MYRISCVX.h"

namespace llvm {
    class MYRISCVXFrameLowering {
        void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const;
        void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;
    };
}