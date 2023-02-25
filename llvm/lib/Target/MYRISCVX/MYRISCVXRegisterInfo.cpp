
#include "MYRISCVXRegisterInfo.h"
#include "MYRISCVXFrameLowering.h"
#include "MYRISCVXSubtarget.h"
#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"

#define GET_REGINFO_TARGET_DESC
#include "MYRISCVXGenRegisterInfo.inc"
// TODO:
//#include "MYRISCVXMachineFunction.h"

namespace llvm {
    MYRISCVXRegisterInfo::MYRISCVXRegisterInfo(const MYRISCVXSubtarget &Subtarget, unsigned HwMode) : 
        MYRISCVXGenRegisterInfo(MYRISCVX::RA, 0, 0, 0, HwMode) {}

    const MCPhysReg* MYRISCVXRegisterInfo::getCalleeSavedRegs(const MachineFunction* MF) const {
        //TODO:
        return CSR_LP32_SaveList;
    }

    const uint32_t* MYRISCVXRegisterInfo::getCallPreservedMask(const MachineFunction &MF, CallingConv::ID) const {
        return CSR_LP32_RegMask;
    }

    BitVector MYRISCVXRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
        static const uint16_t ReservedCPURegs[] = {
            MYRISCVX::ZERO, MYRISCVX::RA, MYRISCVX::FP, MYRISCVX::SP, MYRISCVX::GP, MYRISCVX::TP
        };
        BitVector Reserved(getNumRegs());

        for (unsigned I = 0; I < array_lengthof(ReservedCPURegs); I++) {
            Reserved.set(ReservedCPURegs[I]);
        }

        return Reserved;
    }

    void MYRISCVXRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, 
                                                   unsigned FIOperandNum, RegScavenger *RS) const {
        //TODO:
    }

    Register MYRISCVXRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
        const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
        return TFI->hasFP(MF) ? MYRISCVX::FP : MYRISCVX::SP;
    }
}