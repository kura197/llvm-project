#pragma once

#include "MYRISCVX.h"
#include "MCTargetDesc/MYRISCVXABIInfo.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
    class MYRISCVXSubtarget;
    class MYRISCVXTargetLowering : public TargetLowering {
        SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                                     const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
                                     SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const override;

        SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                            const SmallVectorImpl<ISD::OutputArg> & Outs,
                            const SmallVectorImpl<SDValue> & OutVals,
                            const SDLoc &DL, SelectionDAG &DAG) const override;

        public:
        explicit MYRISCVXTargetLowering(const MYRISCVXTargetMachine &TM, const MYRISCVXSubtarget &STI); 

        protected:
        const MYRISCVXSubtarget &Subtarget;
        const MYRISCVXABIInfo &ABI;
    };
}