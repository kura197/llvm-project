
#include "MYRISCVXFrameLowering.h"
#include "MYRISCVXSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"


namespace llvm {
    void MYRISCVXFrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const {
        //TODO:
    }

    void MYRISCVXFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {
        //TODO:
    }

    bool MYRISCVXFrameLowering::hasFP(const MachineFunction &MF) const {
        const MachineFrameInfo &MFI = MF.getFrameInfo();
        const TargetRegisterInfo *TRI = STI.getRegisterInfo(); 

        return MF.getTarget().Options.DisableFramePointerElim(MF) ||
               MFI.hasVarSizedObjects() || MFI.isFrameAddressTaken() ||
               TRI->hasStackRealignment(MF);
    }
}