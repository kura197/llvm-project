
#include "MYRISCVXABIInfo.h"

namespace llvm {
    MYRISCVXABIInfo MYRISCVXABIInfo::computeTargetABI(StringRef ABIName) {
        MYRISCVXABIInfo abi(ABI::UnKnown);

        if (ABIName.empty()) return ABI::LP;
        else if (ABIName == "lp") return ABI::LP;

        errs() << "UnKnown ABI : " << ABIName << '\n';

        return abi;
    }
}