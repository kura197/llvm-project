//===-- SimpleRISC.td - Describe the SimpleRISC Target Machine -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

def R32 : HwMode<"+32bit">;

include "SimpleRISCRegisterInfo.td"
include "SimpleRISCInstrInfo.td"

def SimpleRISCInstrInfo : InstrInfo {
}

def SimpleRISC: Target {
    let InstructionSet = SimpleRISCInstrInfo;
}

def FeatureR32 : SubtargetFeature<"32bit", "HasR32", "true", "R32 support">;

def : ProcessorModel<"cpu-r32", NoSchedModel, [FeatureR32]>;