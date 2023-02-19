add_llvm_component_group(MYRISCVX)

set(LLVM_TARGET_DEFINITIONS MYRISCVX.td)

tablegen(LLVM MYRISVXGenRegsterInfo.inc -gen-register-info)
tablegen(LLVM MYRISVXGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM MYRISVXGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM MYRISVXGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM MYRISVXGenCallingConv.inc -gen-callingconv)

add_public_tablegen_target(MYRISCVXCommonTableGen)

add_llvm_target(MYRISCVXCodeGen 
  MYRISCVXTargetMachine.cpp
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
