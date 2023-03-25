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

def R0 : SimpleRISCReg<0, "R0", ["SP"]>, DwarfRegNum<[0]>;
def R1 : SimpleRISCReg<1, "R1", []>, DwarfRegNum<[1]>;
def R2 : SimpleRISCReg<2, "R2", []>, DwarfRegNum<[2]>;
def R3 : SimpleRISCReg<3, "R3", []>, DwarfRegNum<[3]>;
def R4 : SimpleRISCReg<4, "R4", []>, DwarfRegNum<[4]>;
def R5 : SimpleRISCReg<5, "R5", []>, DwarfRegNum<[5]>;
def R6 : SimpleRISCReg<6, "R6", []>, DwarfRegNum<[6]>;
def R7 : SimpleRISCReg<7, "R7", []>, DwarfRegNum<[7]>;
def R8 : SimpleRISCReg<8, "R8", []>, DwarfRegNum<[8]>;
def R9 : SimpleRISCReg<9, "R9", []>, DwarfRegNum<[9]>;
def R10 : SimpleRISCReg<10, "R10", []>, DwarfRegNum<[10]>;
def R11 : SimpleRISCReg<11, "R11", []>, DwarfRegNum<[11]>;
def R12 : SimpleRISCReg<12, "R12", []>, DwarfRegNum<[12]>;
def R13 : SimpleRISCReg<13, "R13", []>, DwarfRegNum<[13]>;
def R14 : SimpleRISCReg<14, "R14", []>, DwarfRegNum<[14]>;
def R15 : SimpleRISCReg<15, "R15", []>, DwarfRegNum<[15]>;
def R16 : SimpleRISCReg<16, "R16", []>, DwarfRegNum<[16]>;
def R17 : SimpleRISCReg<17, "R17", []>, DwarfRegNum<[17]>;
def R18 : SimpleRISCReg<18, "R18", []>, DwarfRegNum<[18]>;
def R19 : SimpleRISCReg<19, "R19", []>, DwarfRegNum<[19]>;
def R20 : SimpleRISCReg<20, "R20", []>, DwarfRegNum<[20]>;
def R21 : SimpleRISCReg<21, "R21", []>, DwarfRegNum<[21]>;
def R22 : SimpleRISCReg<22, "R22", []>, DwarfRegNum<[22]>;
def R23 : SimpleRISCReg<23, "R23", []>, DwarfRegNum<[23]>;
def R24 : SimpleRISCReg<24, "R24", []>, DwarfRegNum<[24]>;
def R25 : SimpleRISCReg<25, "R25", []>, DwarfRegNum<[25]>;
def R26 : SimpleRISCReg<26, "R26", []>, DwarfRegNum<[26]>;
def R27 : SimpleRISCReg<27, "R27", []>, DwarfRegNum<[27]>;
def R28 : SimpleRISCReg<28, "R28", []>, DwarfRegNum<[28]>;
def R29 : SimpleRISCReg<29, "R29", []>, DwarfRegNum<[29]>;
def R30 : SimpleRISCReg<30, "R30", []>, DwarfRegNum<[30]>;
def R31 : SimpleRISCReg<31, "R31", []>, DwarfRegNum<[31]>;

def XLenVT : ValueTypeByHwMode<[R32], [i32]>;

def XLenRI : RegInfoByHwMode<[R32], [RegInfo<32, 32, 32>]>;

def GPR : RegisterClass<"SimpleRISC", [XLenVT], 32, (add (sequence "R%u", 1, 31), R0 )> {
  let RegInfos = XLenRI;
}