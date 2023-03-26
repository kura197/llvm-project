//===-- SimpleRISCInstPrinter.h - Convert SimpleRISC MCInst to asm syntax ---*- C++ -*--//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints a SimpleRISC MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCINSTPRINTER_H
#define LLVM_LIB_TARGET_SimpleRISC_MCTARGETDESC_SimpleRISCINSTPRINTER_H

#include "MCTargetDesc/SimpleRISCMCTargetDesc.h"
#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class SimpleRISCInstPrinter : public MCInstPrinter {
public:
  SimpleRISCInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                        const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  std::pair<const char *, uint64_t> getMnemonic(const MCInst *MI) override;

  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &OS) override;
};
} // namespace llvm

#endif
