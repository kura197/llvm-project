
#include "MYRISCVXRegisterInfo.h"
#include "MYRISCVXFrameLowering.h"
#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"

#define GET_REGINFO_TARGET_DESC
#include "MYRISCVXGenRegisterInfo.inc"
// TODO:
//#include "MYRISCVXMachineFunction.h"

namespace llvm {
    const MCPhysReg* MYRISCVXRegisterInfo::getCalleeSaveRegs(const MachineFunction* MF) const {
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
}