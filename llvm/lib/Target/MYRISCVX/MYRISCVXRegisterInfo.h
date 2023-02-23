#pragma once

#include "MYRISCVX.h"
#include "MYRISCVXSubtarget.h"
#include "MYRISCVXFrameLowering.h"
#include "MCTargetDesc/MYRISCVXMCTargetDesc.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/MC/MCInst.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

#define GET_REGINFO_HEADER
#include "MYRISCVXGenRegisterInfo.inc"

namespace llvm {
    class MYRISCVXRegisterInfo : public MYRISCVXGenRegisterInfo {
        const MCPhysReg* getCalleeSaveRegs(const MachineFunction* MF) const;
        const uint32_t* getCallPreservedMask(const MachineFunction &MF, CallingConv::ID) const;
        BitVector getReservedRegs(const MachineFunction &MF) const;
        void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum, RegScavenger *RS) const;
    };
}