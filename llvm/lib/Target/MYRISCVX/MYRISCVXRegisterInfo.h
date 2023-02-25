#pragma once

#include "MYRISCVX.h"
#include "MYRISCVXFrameLowering.h"
#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/MC/MCInst.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

#define GET_REGINFO_HEADER
#include "MYRISCVXGenRegisterInfo.inc"

namespace llvm {
    class MYRISCVXRegisterInfo;
    class MYRISCVXRegisterInfo : public MYRISCVXGenRegisterInfo {

        const MCPhysReg* getCalleeSavedRegs(const MachineFunction* MF) const override;
        const uint32_t* getCallPreservedMask(const MachineFunction &MF, CallingConv::ID) const override;
        BitVector getReservedRegs(const MachineFunction &MF) const override;
        void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum, RegScavenger *RS) const override;
        Register getFrameRegister(const MachineFunction &MF) const override;

        public:
        MYRISCVXRegisterInfo(const MYRISCVXSubtarget &Subtarget, unsigned HwMode);
    };
}