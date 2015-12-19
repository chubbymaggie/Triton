/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef BASEIRBUILDER_H
#define BASEIRBUILDER_H

#include <ostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "ContextHandler.h"
#include "IRBuilder.h"
#include "TritonOperand.h"

#ifndef LIGHT_VERSION
  #include "ControlFlow.h"
#endif



/*
 * Abstract class which its main purpose is too implement common methods
 * shared by its children classes.
 */
class BaseIRBuilder: public IRBuilder {
  public:
    // Constructor take the two main informations of an instruction.
    BaseIRBuilder(__uint address, const std::string &disassembly);

    virtual bool                             isBranch(void);
    virtual bool                             isBranchTaken(void);
    virtual const std::string                &getDisassembly(void) const;
    virtual const std::string                &getImageName(void) const;
    virtual const std::string                &getRoutineName(void) const;
    virtual const std::string                &getSectionName(void) const;
    virtual const std::vector<TritonOperand> &getOperands(void) const;
    virtual sint32                           getOpcodeCategory(void) const;
    virtual uint32                           getOpcode(void) const;
    virtual __uint                           getAddress(void) const;
    virtual __uint                           getBaseAddress(void) const;
    virtual __uint                           getBranchTargetAddress(void) const;
    virtual __uint                           getNextAddress(void) const;
    virtual __uint                           getOffset(void) const;
    virtual __uint                           getThreadID(void) const;
    virtual void                             setBranchTaken(bool flag);
    virtual void                             setBranchTargetAddress(__uint addr);
    virtual void                             setNextAddress(__uint nextAddr);
    virtual void                             setOpcode(uint32 op);
    virtual void                             setOpcodeCategory(sint32 category);
    virtual void                             setThreadID(__uint threadId);

    /*
     * Add an operand to IRBuilder.
     *
     * If it's type is:
     *  - IMM (Immediate), the value is the immediate value.
     *  - REG (Register), the value is the register ID.
     *  - MEM_*, the value doesn't mean anything and it's unused.
     *    The object will need a setup before any processing.
     */
    virtual void addOperand(const TritonOperand &operand);
    virtual void setup(__uint mem_value);
    virtual void checkSetup(void) const;

  protected:
    bool                        branchTaken;
    bool                        needSetup;
    sint32                      opcodeCategory;
    std::string                 disas;
    std::string                 imageName;
    std::string                 routineName;
    std::string                 sectionName;
    std::vector<TritonOperand>  operands;
    uint32                      opcode;
    __uint                      address;
    __uint                      baseAddress;
    __uint                      branchTargetAddress;
    __uint                      nextAddress;
    __uint                      offset;
    __uint                      threadId;
};

#endif // BASEIRBUILDER_H

