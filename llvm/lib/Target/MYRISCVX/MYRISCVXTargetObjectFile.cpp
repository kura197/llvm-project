
#include "MYRISCVXTargetObjectFile.h"

namespace llvm {
    void MYRISCVXTargetObjectFile::Initialize(MCContext &Ctx, const TargetMachine &TM) {
        TargetLoweringObjectFileELF::Initialize(Ctx, TM);
        InitializeELF(TM.Options.UseInitArray);

        this->TM = &static_cast<const MYRISCVXTargetMachine &>(TM);
    }
}