//===-- SimpleRISCRegisterInfo.td - RISC-V Register defs --------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the SimpleRISC register files
//===----------------------------------------------------------------------===//

let Namespace = "SimpleRISC" in {
  class SimpleRISCReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
    let HWEncoding{4-0} = Enc;
    let AltNames = alt;
  }
}

def R0 : SimpleRISCReg<0, "r0", ["ra"]>, DwarfRegNum<[0]>;
def R1 : SimpleRISCReg<1, "r1", ["sp"]>, DwarfRegNum<[1]>;
def R2 : SimpleRISCReg<2, "r2", []>, DwarfRegNum<[2]>;
def R3 : SimpleRISCReg<3, "r3", []>, DwarfRegNum<[3]>;
def R4 : SimpleRISCReg<4, "r4", []>, DwarfRegNum<[4]>;
def R5 : SimpleRISCReg<5, "r5", []>, DwarfRegNum<[5]>;
def R6 : SimpleRISCReg<6, "r6", []>, DwarfRegNum<[6]>;
def R7 : SimpleRISCReg<7, "r7", []>, DwarfRegNum<[7]>;
def R8 : SimpleRISCReg<8, "r8", []>, DwarfRegNum<[8]>;
def R9 : SimpleRISCReg<9, "r9", []>, DwarfRegNum<[9]>;
def R10 : SimpleRISCReg<10, "r10", []>, DwarfRegNum<[10]>;
def R11 : SimpleRISCReg<11, "r11", []>, DwarfRegNum<[11]>;
def R12 : SimpleRISCReg<12, "r12", []>, DwarfRegNum<[12]>;
def R13 : SimpleRISCReg<13, "r13", []>, DwarfRegNum<[13]>;
def R14 : SimpleRISCReg<14, "r14", []>, DwarfRegNum<[14]>;
def R15 : SimpleRISCReg<15, "r15", []>, DwarfRegNum<[15]>;
def R16 : SimpleRISCReg<16, "r16", []>, DwarfRegNum<[16]>;
def R17 : SimpleRISCReg<17, "r17", []>, DwarfRegNum<[17]>;
def R18 : SimpleRISCReg<18, "r18", []>, DwarfRegNum<[18]>;
def R19 : SimpleRISCReg<19, "r19", []>, DwarfRegNum<[19]>;
def R20 : SimpleRISCReg<20, "r20", []>, DwarfRegNum<[20]>;
def R21 : SimpleRISCReg<21, "r21", []>, DwarfRegNum<[21]>;
def R22 : SimpleRISCReg<22, "r22", []>, DwarfRegNum<[22]>;
def R23 : SimpleRISCReg<23, "r23", []>, DwarfRegNum<[23]>;
def R24 : SimpleRISCReg<24, "r24", []>, DwarfRegNum<[24]>;
def R25 : SimpleRISCReg<25, "r25", []>, DwarfRegNum<[25]>;
def R26 : SimpleRISCReg<26, "r26", []>, DwarfRegNum<[26]>;
def R27 : SimpleRISCReg<27, "r27", []>, DwarfRegNum<[27]>;
def R28 : SimpleRISCReg<28, "r28", []>, DwarfRegNum<[28]>;
def R29 : SimpleRISCReg<29, "r29", []>, DwarfRegNum<[29]>;
def R30 : SimpleRISCReg<30, "r30", []>, DwarfRegNum<[30]>;
def R31 : SimpleRISCReg<31, "r31", []>, DwarfRegNum<[31]>;

def XLenVT : ValueTypeByHwMode<[R32, DefaultMode], [i32, i32]>;

def XLenRI : RegInfoByHwMode<[R32, DefaultMode], [RegInfo<32, 32, 32>, RegInfo<32, 32, 32>]>;

def GPR : RegisterClass<"SimpleRISC", [XLenVT], 32, (add (sequence "R%u", 2, 31), R0, R1)> {
  let RegInfos = XLenRI;
}