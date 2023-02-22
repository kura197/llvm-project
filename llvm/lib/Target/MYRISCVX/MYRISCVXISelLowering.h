
#include "MYRISCVX.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
    class MYRISCVXTargetLowering : public TargetLowering {
        SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                                     const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
                                     SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const;

        SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                            const SmallVectorImpl<ISD::OutputArg> & Outs,
                            const SmallVectorImpl<SDValue> & OutVals,
                            const SDLoc &DL, SelectionDAG &DAG) const;
    };
}