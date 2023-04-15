//===---- SimpleRISCISelDAGToDAG.h - A Dag to Dag Inst Selector for SimpleRISC --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===------------------------------------------------------------------------------===//
//
// This file defines an instruction selector for the SimpleRISC target.
//
//===------------------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SimpleRISC_SimpleRISCISELDAGTODAG_H
#define LLVM_LIB_TARGET_SimpleRISC_SimpleRISCISELDAGTODAG_H

#include "SimpleRISC.h"
#include "SimpleRISCSubtarget.h"
#include "SimpleRISCTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"

namespace llvm {
    class SimpleRISCDAGToDAGISel : public SelectionDAGISel {
        public:
        static char ID;
        explicit SimpleRISCDAGToDAGISel(SimpleRISCTargetMachine &TM, CodeGenOpt::Level OL)
            : SelectionDAGISel(ID, TM, OL), Subtarget(nullptr) {};

        void Select(SDNode *Node) override;

        protected:
        const SimpleRISCSubtarget *Subtarget;
    };
}

#endif