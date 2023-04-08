//===--- SimpleRISC.h - Declare SimpleRISC target feature support ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares SimpleRISC TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_SimpleRISC_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_SimpleRISC_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

// SimpleRISC Target
class SimpleRISCTargetInfo : public TargetInfo {
protected:
  std::string ABI;

public:
  SimpleRISCTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    TLSSupported = false;
    LongDoubleWidth = 128;
    LongDoubleAlign = 128;
    LongDoubleFormat = &llvm::APFloat::IEEEquad();
    SuitableAlign = 128;
    WCharType = SignedInt;
    WIntType = UnsignedInt;

    IntPtrType = SignedInt;
    PtrDiffType = SignedInt;
    SizeType = UnsignedInt;
    resetDataLayout("e-m:e-p:32:32-i64:64-n32-S32");
  }

  StringRef getABI() const override { return ABI; }
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  const char *getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }

  bool setABI(const std::string &Name) override {
    if (Name == "ilp32") {
      ABI = Name;
      return true;
    }
    return false;
  }
};

} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_SimpleRISC_H