//===-- SimpleRISCInstPrinter.cpp - Convert SimpleRISC MCInst to asm syntax ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an SimpleRISC MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISCInstPrinter.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"


std::pair<const char *, uint64_t> SimpleRISCInstPrinter::getMnemonic(const MCInst *MI) {
  // TODO:
  return std::make_pair(nullptr, 0);
}

void SimpleRISCInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                                      const MCSubtargetInfo &STI, raw_ostream &OS) {
  // TODO:
}