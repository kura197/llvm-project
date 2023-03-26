//===-- SimpleRISCAsmParser.cpp - Parse SimpleRISC assembly to MCInst instructions --===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/SimpleRISCInstPrinter.h"
#include "MCTargetDesc/SimpleRISCMCTargetDesc.h"
#include "TargetInfo/SimpleRISCTargetInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallBitVector.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/MathExtras.h"

using namespace llvm;

#define DEBUG_TYPE "riscv-asm-parser"

struct SimpleRISCOperand;

class SimpleRISCAsmParser : public MCTargetAsmParser {

#define GET_ASSEMBLER_HEADER
#include "SimpleRISCGenAsmMatcher.inc"

  //TODO:
  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override {

  }

  OperandMatchResultTy tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override {
  }

  bool ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override {

  }

  bool ParseDirective(AsmToken DirectiveID) override {

  }

  bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override {

  }

public:
  SimpleRISCAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                      const MCInstrInfo &MII, const MCTargetOptions &Options) 
      : MCTargetAsmParser(Options, STI, MII) {
  }
};


struct SimpleRISCOperand final : public MCParsedAsmOperand {
  enum class KindTy {
    Token,
    Register,
    Immediate
  } Kind;

  union {
    StringRef Tok;
    MCRegister RegNum;
    const MCExpr *Val;
  };

  SMLoc StartLoc, EndLoc;

  public:
  SimpleRISCOperand(KindTy K) : Kind(K) {}
  SimpleRISCOperand(const SimpleRISCOperand &o) : MCParsedAsmOperand() {
      Kind = o.Kind;
      StartLoc = o.StartLoc;
      EndLoc = o.EndLoc;
  }

  bool isToken() const override { return Kind == KindTy::Token; }
  bool isImm() const override { return Kind == KindTy::Immediate; }
  bool isReg() const override { return Kind == KindTy::Register; }
  bool isMem() const override { return false; }

  unsigned getReg() const override {
    assert(isReg() && "Invalid type access!");
    return RegNum.id();
  };

  StringRef getToken() const {
    assert(isToken() && "Invalid type access!");
    return Tok;
  };

  SMLoc getStartLoc() const override { return StartLoc; }
  SMLoc getEndLoc() const override { return EndLoc; }

  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void print(raw_ostream &OS) const override {
    //TODO:
  }
};


#define GET_REGISTER_MATCHER
#define GET_SUBTARGET_FEATURE_NAME
#define GET_MATCHER_IMPLEMENTATION
#define GET_MNEMONIC_SPELL_CHECKER
#include "SimpleRISCGenAsmMatcher.inc"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimpleRISCAsmParser() {
  RegisterMCAsmParser<SimpleRISCAsmParser> X(getTheSimpleRISCTarget());
}
