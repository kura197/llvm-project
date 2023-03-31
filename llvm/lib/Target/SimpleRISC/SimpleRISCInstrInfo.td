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

// TODO: B, JA

class ArithLogicR<bits<4> opcode, string instr_asm, SDNode OpNode, RegisterClass RC> :
    SimpleRISC_A<opcode, (outs RC:$rd), (ins RC:$rs1, RC:$rs2),
                 !strconcat(instr_asm, "\t$rd, $rs1, $rs2"),
                 [(set RC:$rd, (OpNode RC:$rs1, RC:$rs2))], NoItinerary> {
    let isReMaterializable = 1;
}

def ADD : ArithLogicR<0b0000, "add", add, GPR>;
def SUB : ArithLogicR<0b0001, "sub", sub, GPR>;
def AND : ArithLogicR<0b0010, "and", and, GPR>;
def OR  : ArithLogicR<0b0011, "or",  or,  GPR>;
def XOR : ArithLogicR<0b0100, "xor", xor, GPR>;
def SHL : ArithLogicR<0b0101, "shl", shl, GPR>;
def SHR : ArithLogicR<0b0110, "shr", srl, GPR>;
//TODO:
//def SLT : ArithLogicR<0b0111, "slt", setlt, GPR>;

def simm17 : Operand<XLenVT>, ImmLeaf<XLenVT, [{return isInt<17>(Imm);}]> {
    // add DecoderMethod for dis-assembler
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