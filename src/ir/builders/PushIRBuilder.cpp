/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef LIGHT_VERSION

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <PushIRBuilder.h>
#include <Registers.h>
#include <SMT2Lib.h>
#include <SymbolicExpression.h>


PushIRBuilder::PushIRBuilder(__uint address, const std::string &disassembly):
  BaseIRBuilder(address, disassembly) {
}



static SymbolicExpression *alignStack(Inst &inst, uint32 memSize)
{
  SymbolicExpression    *se;
  smt2lib::smtAstAbstractNode   *expr, *op1, *op2;

  /* Create the SMT semantic */
  op1 = ap.buildSymbolicRegOperand(ID_TMP_RSP, memSize);
  op2 = smt2lib::bv(memSize, memSize * BYTE_SIZE_BIT);

  expr = smt2lib::bvsub(op1, op2);

  /* Create the symbolic expression */
  se = ap.createRegSE(inst, expr, ID_TMP_RSP, REG_SIZE, "Aligns stack");

  /* Apply the taint */
  se->isTainted = ap.isRegTainted(ID_TMP_RSP);

  return se;
}


void PushIRBuilder::reg(Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *op1;
  auto reg = this->operands[0].getReg(); // Reg pushed
  auto mem = this->operands[1].getMem(); // The dst memory writing
  auto regSize = this->operands[0].getReg().getSize();
  auto memSize = this->operands[1].getMem().getSize();

  /* Create the SMT semantic side effect */
  alignStack(inst, memSize);

  /* Create the SMT semantic */
  op1 = ap.buildSymbolicRegOperand(reg, regSize);

  /* Finale expr */
  expr = op1;

  /* Create the symbolic expression */
  se = ap.createMemSE(inst, expr, mem, memSize);

  /* Apply the taint */
  ap.assignmentSpreadTaintMemReg(se, mem, reg, memSize);

}


void PushIRBuilder::imm(Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *op1;
  auto imm = this->operands[0].getImm().getValue(); // Imm pushed
  auto mem = this->operands[1].getMem(); // The dst memory writing
  auto memSize = this->operands[1].getMem().getSize();

  /* Create the SMT semantic side effect */
  alignStack(inst, memSize);

  /* Create the SMT semantic */
  /* OP_1 */
  op1 = smt2lib::bv(imm, memSize * BYTE_SIZE_BIT);

  /* Finale expr */
  expr = op1;

  /* Create the symbolic expression */
  se = ap.createMemSE(inst, expr, mem, memSize);

  /* Apply the taint */
  ap.assignmentSpreadTaintMemImm(se, mem, memSize);

}


void PushIRBuilder::mem(Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *op1;
  auto mem1 = this->operands[0].getMem(); // Mem pushed
  auto memSize1 = this->operands[0].getMem().getSize();
  auto mem2 = this->operands[1].getMem(); // The dst memory writing
  auto memSize2 = this->operands[1].getMem().getSize();

  /* Create the SMT semantic side effect */
  alignStack(inst, memSize2);

  /* Create the SMT semantic */
  op1 = ap.buildSymbolicMemOperand(mem1, memSize1);

  /* Finale expr */
  expr = op1;

  /* Create the symbolic expression */
  se = ap.createMemSE(inst, expr, mem2, memSize2);

  /* Apply the taint */
  ap.assignmentSpreadTaintMemMem(se, mem2, mem1, memSize1);

}


void PushIRBuilder::none(Inst &inst) const {
  /* There is no <push none> available in x86 */
  OneOperandTemplate::stop(this->disas);
}


Inst *PushIRBuilder::process(void) const {
  this->checkSetup();

  Inst *inst = new Inst(ap.getThreadID(), this->address, this->disas);

  try {
    this->templateMethod(*inst, this->operands, "PUSH");
    ControlFlow::rip(*inst, this->nextAddress);
    ap.incNumberOfExpressions(inst->numberOfExpressions()); /* Used for statistics */
  }
  catch (std::exception &e) {
    delete inst;
    throw;
  }

  return inst;
}

#endif /* LIGHT_VERSION */

