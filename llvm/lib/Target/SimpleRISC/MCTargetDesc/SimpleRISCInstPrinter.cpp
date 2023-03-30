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
#include "llvm/Support/Debug.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define PRINT_ALIAS_INSTR
#include "SimpleRISCGenAsmWriter.inc"

void SimpleRISCInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                                      const MCSubtargetInfo &STI, raw_ostream &OS) {
  LLVM_DEBUG(dbgs() << "SimpleRISCInstPrinter::printInst\n");

  //if (!PrintAliases) {
  //}

  printInstruction(MI, Address, STI, OS);
  printAnnotation(OS, Annot);
}

void SimpleRISCInstPrinter::printOperand(const MCInst *MI, unsigned OpNo, const MCSubtargetInfo &STI, raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    O << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand kind in printOperand");
  Op.getExpr()->print(O, &MAI, true);
}

void SimpleRISCInstPrinter::printRegName(raw_ostream &O, MCRegister Reg) const {
  O << getRegisterName(Reg);
}

// TODO:
//void SimpleRISCInstPrinter::printMemOperand(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
//  printOperand(MI, OpNum+1, O);
//  O << "(";
//  printOperand(MI, OpNum, O);
//  O << ")";
//}