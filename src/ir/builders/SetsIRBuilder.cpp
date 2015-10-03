/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef LIGHT_VERSION

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <SetsIRBuilder.h>
#include <Registers.h>
#include <SMT2Lib.h>
#include <SymbolicExpression.h>


SetsIRBuilder::SetsIRBuilder(uint64 address, const std::string &disassembly):
  BaseIRBuilder(address, disassembly) {
}


void SetsIRBuilder::imm(AnalysisProcessor &ap, Inst &inst) const {
  OneOperandTemplate::stop(this->disas);
}


void SetsIRBuilder::reg(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *sf;
  auto reg = this->operands[0].getReg();
  auto regSize = this->operands[0].getReg().getSize();

  /* Create the SMT semantic */
  sf = ap.buildSymbolicFlagOperand(ID_TMP_SF);

  /* Finale expr */
  expr = smt2lib::ite(
            smt2lib::equal(
              sf,
              smt2lib::bvtrue()),
            smt2lib::bv(1, BYTE_SIZE_BIT),
            smt2lib::bv(0, BYTE_SIZE_BIT));

  /* Create the symbolic expression */
  se = ap.createRegSE(inst, expr, reg, regSize);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_TMP_SF) == 1)
    ap.assignmentSpreadTaintRegReg(se, reg, ID_TMP_SF);

}


void SetsIRBuilder::mem(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *sf;
  auto mem = this->operands[0].getMem();
  auto memSize = this->operands[0].getMem().getSize();

  /* Create the SMT semantic */
  sf = ap.buildSymbolicFlagOperand(ID_TMP_SF);

  /* Finale expr */
  expr = smt2lib::ite(
            smt2lib::equal(
              sf,
              smt2lib::bvtrue()),
            smt2lib::bv(1, BYTE_SIZE_BIT),
            smt2lib::bv(0, BYTE_SIZE_BIT));

  /* Create the symbolic expression */
  se = ap.createMemSE(inst, expr, mem, memSize);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_TMP_SF) == 1)
    ap.assignmentSpreadTaintMemReg(se, mem, ID_TMP_SF, memSize);

}


void SetsIRBuilder::none(AnalysisProcessor &ap, Inst &inst) const {
  OneOperandTemplate::stop(this->disas);
}


Inst *SetsIRBuilder::process(AnalysisProcessor &ap) const {
  this->checkSetup();

  Inst *inst = new Inst(ap.getThreadID(), this->address, this->disas);

  try {
    this->templateMethod(ap, *inst, this->operands, "SETS");
    ap.incNumberOfExpressions(inst->numberOfExpressions()); /* Used for statistics */
    ControlFlow::rip(*inst, ap, this->nextAddress);
  }
  catch (std::exception &e) {
    delete inst;
    throw;
  }

  return inst;
}

#endif /* LIGHT_VERSION */

