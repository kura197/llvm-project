//===-- SimpleRISCInstrFormats.td - SimpleRISC Instruction Formats ---*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

class InstFormat<bits<3> val> {
    bits<3> Value = val;
}

def InstFormatA : InstFormat<0>;
def InstFormatI : InstFormat<1>;
def InstFormatB : InstFormat<2>;
def InstFormatJ : InstFormat<3>;
def InstFormatL : InstFormat<4>;
def InstFormatS : InstFormat<5>;

class SimpleRISCInst<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin, InstFormat f> : Instruction {
    let Size = 4;

    // TODO: check
    field bits<32> Inst;
    //bits<4> Opcode = 0;
    //let Inst{30-27} = Opcode;

    let Namespace = "SimpleRISC";

    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmstr;
    let Pattern = pattern;
    let Itinerary = itin;

    let TSFlags{2-0} = f.Value;

    let DecoderNamespace = "SimpleRISC";

    //field bits<32> SoftFail = 0;
}


class SimpleRISC_A<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatA> {

    bits<5> rd;
    bits<5> rs1;
    bits<5> rs2;

    let Inst{31}    = 0;
    let Inst{30-27} = opcode;
    let Inst{26-22} = rd;
    let Inst{21-17} = rs1;
    let Inst{16-12} = rs2;
    let Inst{11-0}  = 0;
}

class SimpleRISC_C<bits<4> opcode, bits<1> funct1, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatA> {

    bits<5> rd;
    bits<5> rs1;
    bits<5> rs2;

    let Inst{31}    = 0;
    let Inst{30-27} = opcode;
    let Inst{26-22} = rd;
    let Inst{21-17} = rs1;
    let Inst{16-12} = rs2;
    let Inst{11}    = funct1;
    let Inst{10-0}  = 0;
}

class SimpleRISC_I<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatA> {

    bits<5> rd;
    bits<26> simm26;

    let Inst{31}    = 1;
    let Inst{30-27} = simm26{25-22};
    let Inst{26-22} = rd;
    let Inst{21-0}  = simm26{21-0};
}

class SimpleRISC_B<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatA> {

    bits<5> rs1;
    bits<22> simm22;

    let Inst{31}    = 0;
    let Inst{30-27} = 0b1000;
    let Inst{26-22} = simm22{21-17};
    let Inst{21-17} = rs1;
    let Inst{16-0} = simm22{16-0};
}

class SimpleRISC_J<dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatA> {

    bits<5> rd;
    bits<5> rs1;

    let Inst{31}    = 0;
    let Inst{30-27} = 0b1001;
    let Inst{26-22} = rd;
    let Inst{21-17} = rs1;
    let Inst{16-0}  = 0;
}

class SimpleRISC_L<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatL> {

    bits<5> rd;
    bits<5> rs1;
    bits<17> simm17;

    let Inst{31}    = 0;
    let Inst{30-27} = opcode;
    let Inst{26-22} = rd;
    let Inst{21-17} = rs1;
    let Inst{16-0}  = simm17;
}

class SimpleRISC_S<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern, InstrItinClass itin> : 
    SimpleRISCInst<outs, ins, asmstr, pattern, itin, InstFormatS> {

    bits<5> rs1;
    bits<5> rs2;
    bits<17> simm17;

    let Inst{31}    = 0;
    let Inst{30-27} = opcode;
    let Inst{26-22} = simm17{16-12};
    let Inst{21-17} = rs1;
    let Inst{16-12} = rs2;
    let Inst{11-0}  = simm17{11-0};
}