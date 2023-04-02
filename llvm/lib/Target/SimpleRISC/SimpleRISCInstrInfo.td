//===-- SimpleRISCInstrInfo.td - Target Description for SimpleRISC ---*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the SimpleRISC instructions in TableGen format.
//
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
// Instruction Formats
//===----------------------------------------------------------------------===//

include "SimpleRISCInstrFormats.td"


class ArithLogicR<bits<4> opcode, string instr_asm, SDNode OpNode, RegisterClass RC> :
    SimpleRISC_A<opcode, (outs RC:$rd), (ins RC:$rs1, RC:$rs2),
                 !strconcat(instr_asm, "\t$rd, $rs1, $rs2"),
                 [(set RC:$rd, (OpNode RC:$rs1, RC:$rs2))], NoItinerary> {
    let isReMaterializable = 1;
    let mayLoad = 0;
    let mayStore = 0;
}

def ADD : ArithLogicR<0b0000, "add", add, GPR>;
def SUB : ArithLogicR<0b0001, "sub", sub, GPR>;
def AND : ArithLogicR<0b0010, "and", and, GPR>;
def OR  : ArithLogicR<0b0011, "or",  or,  GPR>;
def XOR : ArithLogicR<0b0100, "xor", xor, GPR>;
def SHL : ArithLogicR<0b0101, "shl", shl, GPR>;
def SHR : ArithLogicR<0b0110, "shr", srl, GPR>;

def simm26 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<26>(Imm);}]> {
    // add DecoderMethod for dis-assembler
}

class LoadImm<string instr_asm, RegisterClass RC> :
    SimpleRISC_I<(outs RC:$rd), (ins simm26:$imm),
                 !strconcat(instr_asm, "\t$rd, $imm"), [], NoItinerary> {
    let isReMaterializable = 1;
    let mayLoad = 0;
    let mayStore = 0;
}

def LI : LoadImm<"li", GPR>;


class SetCC_R<bits<4> opcode, bits<1> funct1, string instr_asm, PatFrag cond_op, RegisterClass RC> :
    SimpleRISC_C<opcode, funct1, (outs RC:$rd), (ins RC:$rs1, RC:$rs2),
                 !strconcat(instr_asm, "\t$rd, $rs1, $rs2"),
                 [(set RC:$rd, (cond_op RC:$rs1, RC:$rs2))], NoItinerary> {
    let isReMaterializable = 1;
    let mayLoad = 0;
    let mayStore = 0;
}

def SLT  : SetCC_R<0b0111, 0b0, "slt",  setlt, GPR>;
def SLTU : SetCC_R<0b0111, 0b1, "sltu", setult, GPR>;

def : Pat<(seteq GPR:$rs1, GPR:$rs2), (SLTU (XOR GPR:$rs1, GPR:$rs2), (LI 1))>;
def : Pat<(setne GPR:$rs1, GPR:$rs2), (SLTU (LI 0), (XOR GPR:$rs1, GPR:$rs2))>;
def : Pat<(setugt GPR:$rs1, GPR:$rs2), (SLTU GPR:$rs2, GPR:$rs1)>;
def : Pat<(setuge GPR:$rs1, GPR:$rs2), (XOR (SLTU GPR:$rs1, GPR:$rs2), (LI 1))>;
def : Pat<(setule GPR:$rs1, GPR:$rs2), (XOR (SLTU GPR:$rs2, GPR:$rs1), (LI 1))>;
def : Pat<(setgt GPR:$rs1, GPR:$rs2), (SLT GPR:$rs2, GPR:$rs1)>;
def : Pat<(setge GPR:$rs1, GPR:$rs2), (XOR (SLT GPR:$rs1, GPR:$rs2), (LI 1))>;
def : Pat<(setle GPR:$rs1, GPR:$rs2), (XOR (SLT GPR:$rs2, GPR:$rs1), (LI 1))>;


def simm17 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<17>(Imm);}]> {
    // add DecoderMethod for dis-assembler
}

def brtarget22 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<22>(Imm);}]> {
    let OperandType = "OPERAND_PCREL";
}

let canFoldAsLoad = 1 in
class LoadMemory<bits<4> opcode, string instr_asm, RegisterClass RC> :
    SimpleRISC_L<opcode, (outs RC:$rd), (ins RC:$rs1, simm17:$simm17),
                 !strconcat(instr_asm, "\t$rd, ${simm17}(${rs1})"), [], NoItinerary>;

class StoreMemory<bits<4> opcode, string instr_asm, RegisterClass RC> :
    SimpleRISC_S<opcode, (outs RC:$rd), (ins RC:$rs1, simm17:$simm17),
                 !strconcat(instr_asm, "\t$rd, ${simm17}(${rs1})"), [], NoItinerary>;

def LW : LoadMemory<0b1010, "lw", GPR>;
def LH : LoadMemory<0b1011, "lh", GPR>;
def LB : LoadMemory<0b1100, "lb", GPR>;
def SW : StoreMemory<0b1101, "sw", GPR>;
def SH : StoreMemory<0b1110, "sh", GPR>;
def SB : StoreMemory<0b1111, "sb", GPR>;


let isCall = 1 in
class JumpAndLink<string instr_asm, RegisterClass RC> :
    SimpleRISC_J<(outs RC:$rd), (ins RC:$rs1), !strconcat(instr_asm, "\t$rd, $rs1"), [], NoItinerary>;

def JA : JumpAndLink<"ja", GPR>;


class CBranch<string instr_asm, RegisterClass RC> :
    SimpleRISC_B<(outs), (ins RC:$rs1, brtarget22:$imm), 
    !strconcat(instr_asm, "\t$rs1, ${imm}"), [], NoItinerary> {
    let isBranch = 1;
    let isTerminator = 1;
}

def B : CBranch<"br", GPR>;