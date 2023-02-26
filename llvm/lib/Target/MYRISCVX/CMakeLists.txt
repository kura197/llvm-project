add_llvm_component_group(MYRISCVX)

set(LLVM_TARGET_DEFINITIONS MYRISCVX.td)

tablegen(LLVM MYRISCVXGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM MYRISCVXGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MYRISCVXGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MYRISCVXGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM MYRISCVXGenCallingConv.inc -gen-callingconv)
tablegen(LLVM MYRISCVXGenCodeEmitter.inc -gen-emitter)
tablegen(LLVM MYRISCVXGenMCCodeEmitter.inc -gen-emitter)

tablegen(LLVM MYRISCVXGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(MYRISCVXCommonTableGen)

add_llvm_target(MYRISCVXCodeGen 
  MYRISCVXTargetMachine.cpp
  MYRISCVXSubtarget.cpp
  MYRISCVXRegisterInfo.cpp
  MYRISCVXISelLowering.cpp
  MYRISCVXMachineFunction.cpp
  MYRISCVXFrameLowering.cpp
  MYRISCVXInstrInfo.cpp
  MYRISCVXTargetObjectFile.cpp
  MYRISCVXAsmPrinter.cpp
  MYRISCVXMCInstLower.cpp
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
