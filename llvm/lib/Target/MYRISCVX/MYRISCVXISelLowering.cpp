
#include "MYRISCVXISelLowering.h"

namespace llvm {
    SDValue MYRISCVXTargetLowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                                     const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
                                     SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
        // TODO:
        return Chain;
    }

    SDValue MYRISCVXTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                                                const SmallVectorImpl<ISD::OutputArg> & Outs,
                                                const SmallVectorImpl<SDValue> & OutVals,
                                                const SDLoc &DL, SelectionDAG &DAG) const {
        // TODO:
        return Chain;
    }
}