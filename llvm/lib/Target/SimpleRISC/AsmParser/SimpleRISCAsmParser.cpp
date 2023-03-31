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

  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  OperandMatchResultTy tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  bool ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;
  bool ParseOperand(OperandVector &Operands, StringRef Mnemonic);
  bool ParseDirective(AsmToken DirectiveID) override;
  bool MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

  SMLoc getLoc() const {return getParser().getTok().getLoc(); }

  OperandMatchResultTy parseRegister(OperandVector &Operands);
  OperandMatchResultTy parseImmediate(OperandVector &Operands);
  OperandMatchResultTy parseOperandWithModifier(OperandVector &Operands);
  OperandMatchResultTy parseMemOperand(OperandVector &Operands);

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

  struct RegOp {
    MCRegister RegNum;
  };

  struct ImmOp {
    const MCExpr *Val;
  };

  union {
    StringRef Tok;
    RegOp Reg;
    ImmOp Imm;
  };

  SMLoc StartLoc, EndLoc;

  SimpleRISCOperand(KindTy K) : Kind(K) {}
  public:
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
    return Reg.RegNum.id();
  };

  const MCExpr* getImm() const {
    assert(isImm() && "Invalid type access!");
    return Imm.Val;
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

  void addExpr(MCInst &Inst, const MCExpr* Expr) const {
    assert(Expr && "Expr shouldn't be null!");
    // TODO: check
    if (!Expr)
      Inst.addOperand(MCOperand::createImm(0));
    else if (const MCConstantExpr *CE = dyn_cast<MCConstantExpr>(Expr))
      Inst.addOperand(MCOperand::createImm(CE->getValue()));
    else
      Inst.addOperand(MCOperand::createExpr(Expr));
  }

  void addImmOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    addExpr(Inst, getImm());
  }

  void print(raw_ostream &OS) const override {
    //TODO:
  }

  static std::unique_ptr<SimpleRISCOperand> CreateToken(StringRef Str, SMLoc S) {
    auto Op = std::make_unique<SimpleRISCOperand>(KindTy::Token);
    Op->Tok = Str;
    Op->StartLoc = S;
    Op->EndLoc = S;
    return Op;
  }

  static std::unique_ptr<SimpleRISCOperand> CreateRegister(unsigned RegNo, SMLoc S, SMLoc E) {
    auto Op = std::make_unique<SimpleRISCOperand>(KindTy::Register);
    Op->Reg.RegNum = MCRegister::from(RegNo);
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  static std::unique_ptr<SimpleRISCOperand> CreateImmediate(const MCExpr *Val, SMLoc S, SMLoc E) {
    auto Op = std::make_unique<SimpleRISCOperand>(KindTy::Immediate);
    Op->Imm.Val = Val;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }
};

#define GET_REGISTER_MATCHER
#define GET_SUBTARGET_FEATURE_NAME
#define GET_MATCHER_IMPLEMENTATION
#define GET_MNEMONIC_SPELL_CHECKER
#include "SimpleRISCGenAsmMatcher.inc"

bool SimpleRISCAsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) {
}

OperandMatchResultTy SimpleRISCAsmParser::tryParseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) {
}

bool SimpleRISCAsmParser::ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                      SMLoc NameLoc, OperandVector &Operands) {
  Operands.push_back(SimpleRISCOperand::CreateToken(Name, NameLoc));
  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    if (ParseOperand(Operands, Name)) {
      SMLoc Loc = getLexer().getLoc();
      getParser().eatToEndOfStatement();
      return Error(Loc, "unexpected token in argument list");
    }

    while (getLexer().is(AsmToken::Comma)) {
      getParser().Lex();
      if (ParseOperand(Operands, Name)) {
        SMLoc Loc = getLexer().getLoc();
        getParser().eatToEndOfStatement();
        return Error(Loc, "unexpected token in argument list");
      }
    }
  }

  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    SMLoc Loc = getLexer().getLoc();
    getParser().eatToEndOfStatement();
    return Error(Loc, "unexpected token in argument list");
  }

  getParser().Lex();
  return false;
}

bool SimpleRISCAsmParser::ParseOperand(OperandVector &Operands, StringRef Mnemonic) {
  // TODO:
  //OperandMatchResultTy Result = MatchOperandParserImpl(Operands, Mnemonic, true);
  //if (Result == MatchOperand_Success) return false;
  //if (Result == MatchOperand_ParseFail) return true;

  LLVM_DEBUG(dbgs() << ".. Parse Operand: " << getLexer().getTok().getIdentifier() << "\n");

  if (parseRegister(Operands) == MatchOperand_Success) {
    return false;
  }

  if (parseImmediate(Operands) == MatchOperand_Success) {
    if (getLexer().is(AsmToken::LParen)) {
      return parseMemOperand(Operands) != MatchOperand_Success;
    }
    return false;
  }

  LLVM_DEBUG(dbgs() << "unknown operands\n");
  return true;
}

bool SimpleRISCAsmParser::ParseDirective(AsmToken DirectiveID) {

}

bool SimpleRISCAsmParser::MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                              OperandVector &Operands, MCStreamer &Out,
                              uint64_t &ErrorInfo,
                              bool MatchingInlineAsm) {
  MCInst Inst;
  FeatureBitset MissingFeatures;
  auto Result = MatchInstructionImpl(Operands, Inst, ErrorInfo, MissingFeatures, MatchingInlineAsm);

  switch(Result) {
    //TODO: add entry
    default:
      break;
    case Match_Success:
      Inst.setLoc(IDLoc);
      Out.emitInstruction(Inst, getSTI());
      return false;
  }

  llvm_unreachable("Unknown match type detected!");
}

OperandMatchResultTy SimpleRISCAsmParser::parseRegister(OperandVector &Operands) {
  switch(getLexer().getKind()) {
    default:
      return MatchOperand_NoMatch;
    case AsmToken::Identifier:
      StringRef Name = getLexer().getTok().getIdentifier();
      unsigned RegNo = MatchRegisterName(Name);
      if (RegNo == 0) {
        RegNo = MatchRegisterAltName(Name);
        if (RegNo == 0) {
          return MatchOperand_NoMatch;
        }
      }

      SMLoc S = getLoc();
      SMLoc E = SMLoc::getFromPointer(S.getPointer() - 1);
      getLexer().Lex();
      Operands.push_back(SimpleRISCOperand::CreateRegister(RegNo, S, E));
  }

  return MatchOperand_Success;
}

OperandMatchResultTy SimpleRISCAsmParser::parseImmediate(OperandVector &Operands) {
  SMLoc S = getLoc();
  SMLoc E;
  const MCExpr *Res;

  switch(getLexer().getKind()) {
    default:
      return MatchOperand_NoMatch;
    // TODO: check
    case AsmToken::LParen:
    case AsmToken::Dot:
    case AsmToken::Minus:
    case AsmToken::Plus:
    case AsmToken::Exclaim: // !
    case AsmToken::Tilde: // ~
    case AsmToken::Integer:
    case AsmToken::String:
    case AsmToken::Identifier:
      if (getParser().parseExpression(Res, E)) {
        return MatchOperand_ParseFail;
      }
      break;
    case AsmToken::Percent:
      return parseOperandWithModifier(Operands);
  }

  Operands.push_back(SimpleRISCOperand::CreateImmediate(Res, S, E));
}

OperandMatchResultTy SimpleRISCAsmParser::parseOperandWithModifier(OperandVector &Operands) {

}

OperandMatchResultTy SimpleRISCAsmParser::parseMemOperand(OperandVector &Operands) {

}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimpleRISCAsmParser() {
  RegisterMCAsmParser<SimpleRISCAsmParser> X(getTheSimpleRISCTarget());
}
