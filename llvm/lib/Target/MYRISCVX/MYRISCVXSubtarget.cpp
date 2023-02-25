#include "MYRISCVXSubtarget.h"
#include "MYRISCVXTargetMachine.h"

#define DEBUG_TYPE "MYRISCVX-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MYRISCVXGenSubtargetInfo.inc"

namespace llvm {
    void MYRISCVXSubtarget::anchor() {}

    MYRISCVXSubtarget &MYRISCVXSubtarget::initializeSubtargetDependencies(
        StringRef CPU, StringRef TuneCPU, StringRef FS, const TargetMachine &TM) {
        if (TargetTriple.getArch() == Triple::myriscvx32) {
            if (CPU.empty() || CPU == "generic") CPU = "cpu-rv32";
        } else if (TargetTriple.getArch() == Triple::myriscvx64)  {
            if (CPU.empty() || CPU == "generic") CPU = "cpu-rv64";
        } else {
            errs() << "!!!Error, TargetTriple.getArch() = " << TargetTriple.getArch() << " CPU = " << CPU << "\n";
            exit(0);
        }

        ParseSubtargetFeatures(CPU, TuneCPU, FS);
        InstrItins = getInstrItineraryForCPU(CPU);

        if (HasRV64) {
            XLenVT = MVT::i64;
        } else {
            XLenVT = MVT::i32;
        }

        return *this;
    }

    bool MYRISCVXSubtarget::isPositionIndependent() const {
        return TM.isPositionIndependent();
    }

    MYRISCVXSubtarget::MYRISCVXSubtarget(const Triple &TT, StringRef &CPU, StringRef &TuneCPU, StringRef &FS, const MYRISCVXTargetMachine &_TM) :
        MYRISCVXGenSubtargetInfo(TT, CPU, TuneCPU, FS),
        TM(_TM), TargetTriple(TT), TSInfo(), InstrInfo(),
        FrameLowering(initializeSubtargetDependencies(CPU, TuneCPU, FS, _TM)),
        TLInfo(TM, *this), RegInfo(*this, getHwMode())
    {

    }

    bool MYRISCVXSubtarget::abiUsesSoftFloat() const {
        //  return TM->Options.UseSoftFloat;
        return true;
    }

    const MYRISCVXABIInfo &MYRISCVXSubtarget::getABI() const { return TM.getABI(); }
}