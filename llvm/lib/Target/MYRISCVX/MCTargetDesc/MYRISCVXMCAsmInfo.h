#ifndef LLVM_LIB_TARGET_MYRISCVX_MCTARGETDESC_MYRISCVXMCASMINFO_H
#define LLVM_LIB_TARGET_MYRISCVX_MCTARGETDESC_MYRISCVXMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
    class Triple;

    class MYRISCVXMCAsmInfo : public MCAsmInfoELF {
        void anchor() override;

        public:
        explicit MYRISCVXMCAsmInfo(const Triple &TargetTriple);

        //const MCExpr *getExprForFDESymbol(const MCSymbol *Sym, unsigned Encoding, MCStreamer &Streamer) const override;
    };
}

#endif