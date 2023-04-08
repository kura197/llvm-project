//===--- SimpleRISCV.cpp - Implement SimpleRISCV target feature support ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements SimpleRISCV TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "SimpleRISC.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;


ArrayRef<const char *> SimpleRISCTargetInfo::getGCCRegNames() const {
  static const char *const GCCRegNames[] = {
      "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
      "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
      "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
      "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"};
  return llvm::ArrayRef(GCCRegNames);
}

ArrayRef<TargetInfo::GCCRegAlias> SimpleRISCTargetInfo::getGCCRegAliases() const {
    //TODO: check
    static const TargetInfo::GCCRegAlias GCCRegAliases[] = {
        {{"ra"}, "r0"}, {{"sp"}, "r1"}
    };
    return llvm::ArrayRef(GCCRegAliases);
}

ArrayRef<Builtin::Info> SimpleRISCTargetInfo::getTargetBuiltins() const {
    //TODO:
    ArrayRef<Builtin::Info> ret;
    return ret;
}

void SimpleRISCTargetInfo::getTargetDefines(const LangOptions &Opts, MacroBuilder &Builder) const {
    Builder.defineMacro("__ELF__");
    Builder.defineMacro("__simplerisc__");
    //bool is64Bit = false;
    Builder.defineMacro("__simplerisc_xlen32");
}