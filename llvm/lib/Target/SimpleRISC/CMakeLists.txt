add_llvm_component_group(SimpleRISC)

set(LLVM_TARGET_DEFINITIONS SimpleRISC.td)

tablegen(LLVM SimpleRISCGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimpleRISCGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(SimpleRISCCommonTableGen)

add_llvm_target(SimpleRISCCodeGen
  SimpleRISCTargetMachine.cpp
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)