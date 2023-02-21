#include "MYRISCVXSubtarget.h"


namespace llvm {
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
}