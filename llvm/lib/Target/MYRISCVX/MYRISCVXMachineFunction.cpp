
#include "MYRISCVXMachineFunction.h"

#include "MYRISCVXInstrInfo.h"
#include "MYRISCVXSubtarget.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool FixGlobalBaseReg;

MYRISCVXFunctionInfo::~MYRISCVXFunctionInfo() {}

void MYRISCVXFunctionInfo::anchor() { }