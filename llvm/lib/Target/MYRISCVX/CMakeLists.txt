add_llvm_component_group(MYRISCVX)

set(LLVM_TARGET_DEFINITIONS MYRISCVX.td)

tablegen(LLVM MYRISVXGenRigsterINfo.inc -gen-register-info)

add_public_tablegen_target(MYRISCVXCommonTableGen)

add_llvm_target(MYRISCVXCodeGen 
  MYRISCVXTargetMachine.cpp
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
