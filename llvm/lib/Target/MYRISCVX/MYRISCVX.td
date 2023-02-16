//===----------------------------------------------------------------------===//
// This is the top level entry point for the MYRISCVX target.
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

def RV64 : HwMode<"+64bit">;
def RV32 : HwMode<"-64bit">;

include "MYRISCVXRegisterInfo.td"
include "MYRISCVXSchedule.td"
include "MYRISCVXInstrInfo.td"

def MYRISCVXInstrInfo : InstrInfo;

def MYRISCVX : Target {
  let InstructionSet = MYRISCVXInstrInfo;
}

def FeatureRV64 : SubtargetFeature<"64bit", "HasRV64", "true", "RV64 support">;

def : ProcessorModel<"cpu-rv32", NoSchedModel, []>;
def : ProcessorModel<"cpu-rv64", NoSchedModel, [FeatureRV64]>;