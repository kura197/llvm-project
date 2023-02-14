//===-- MYRISCVXMCTargetDesc.h - MYRISCVX Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides MYRISCVX specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MYRISCVX_MCTARGETDESC_MYRISCVXMCTARGETDESC_H
#define LLVM_LIB_TARGET_MYRISCVX_MCTARGETDESC_MYRISCVXMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;
class Triple;

extern Target TheMYRISCVXTarget;
extern Target TheMYRISCVXXelTarget;

}

#endif
