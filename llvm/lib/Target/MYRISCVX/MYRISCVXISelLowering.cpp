
#include "MYRISCVXISelLowering.h"
#include "MYRISCVXTargetMachine.h"
#include "MYRISCVXSubtarget.h"
#include "MCTargetDesc/MYRISCVXABIInfo.h"

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

    MYRISCVXTargetLowering::MYRISCVXTargetLowering(const MYRISCVXTargetMachine &TM, const MYRISCVXSubtarget &STI) : 
        TargetLowering(TM), Subtarget(STI), ABI(TM.getABI()) {
            MVT XLenVT = Subtarget.getXLenVT();

            addRegisterClass(XLenVT, &MYRISCVX::GPRRegClass);
            setMinFunctionAlignment(Align(4));
            computeRegisterProperties(STI.getRegisterInfo());
    } 
}