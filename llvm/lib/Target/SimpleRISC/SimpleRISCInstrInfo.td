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