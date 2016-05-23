//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifdef TRITON_PYTHON_BINDINGS

#include <api.hpp>
#include <bitsVector.hpp>
#include <cpuSize.hpp>
#include <immediateOperand.hpp>
#include <memoryOperand.hpp>
#include <pythonBindings.hpp>
#include <pythonObjects.hpp>
#include <pythonUtils.hpp>
#include <pythonXFunctions.hpp>
#include <registerOperand.hpp>



/*! \page py_triton_page Python bindings
    \brief [**python api**] All information about the libTriton's Python API.
    \anchor triton

\tableofcontents

\section triton_py_description Description
<hr>

The Triton Triton offers Python bindings on its C++ API which allow you to build analysis in Python as well as in C++.

\section triton_py_api Python API - Classes, methods, modules and namespaces of libTriton
<hr>

By default, the libTriton contains Python bindings and can be loaded with a classical Python `import`.

~~~~~~~~~~~~~{.py}
>>> from triton import *
~~~~~~~~~~~~~

If you want to use the libTriton without Python bindings, recompile the project with the `cmake` flag `-DTRITON_PYTHON_BINDINGS=no`.

\subsection triton_py_api_classes Classes

- \ref py_AstNode_page
- \ref py_Bitvector_page
- \ref py_Immediate_page
- \ref py_Instruction_page
- \ref py_Memory_page
- \ref py_PathConstraint_page
- \ref py_Register_page
- \ref py_SolverModel_page
- \ref py_SymbolicExpression_page
- \ref py_SymbolicVariable_page


\subsection triton_py_api_modules Modules

- \ref ast


\subsection triton_py_api_methods Methods

- <b>assignSymbolicExpressionToMemory(\ref py_SymbolicExpression_page symExpr, \ref py_Memory_page mem)</b><br>
Assigns a \ref py_SymbolicExpression_page to a \ref py_Memory_page area. **Be careful**, use this function only if you know what you are doing.
The symbolic expression (`symExpr`) must be aligned to the memory access.

- <b>assignSymbolicExpressionToRegister(\ref py_SymbolicExpression_page symExpr, \ref py_REG_page reg)</b><br>
Assigns a \ref py_SymbolicExpression_page to a \ref py_REG_page. **Be careful**, use this function only if you know what you are doing.
The symbolic expression (`symExpr`) must be aligned to the targeted size register. E.g: for SSE registers, the expression must be aligned
to 128-bits. Otherwise, you will probably get a sort mismatch error when you will solve the expression. If you want to assign an
expression to a sub-register like `AX`, `AH` or `AL`, please, craft your expression with the `concat()` and `extract()` ast functions.

- **buildSemantics(\ref py_Instruction_page inst)**<br>
Builds the instruction semantics. You must define an architecture before.

- **buildSymbolicImmediate(\ref py_Immediate_page imm)**<br>
Builds a symbolic \ref py_Immediate_page and returns a \ref py_AstNode_page.

- **buildSymbolicMemory(\ref py_Memory_page mem)**<br>
Builds a symbolic \ref py_Memory_page and returns a \ref py_AstNode_page.

- **buildSymbolicRegister(\ref py_REG_page reg)**<br>
Builds a symbolic \ref py_REG_page and returns a \ref py_AstNode_page.

- **clearPathConstraints(void)**<br>
Clears the logical conjunction vector of path constraints.

- **concretizeAllMemory(void)**<br>
Concretizes all symbolic memory references.

- **concretizeAllRegister(void)**<br>
Concretizes all symbolic register references.

- **concretizeMemory(integer addr)**<br>
Concretizes a specific symbolic memory reference.

- **concretizeMemory(\ref py_Memory_page mem)**<br>
Concretizes a specific symbolic memory reference.

- **concretizeRegister(\ref py_REG_page reg)**<br>
Concretizes a specific symbolic register reference.

- **convertExpressionToSymbolicVariable(integer symExprId, integer symVarSize, string comment="")**<br>
Converts a symbolic expression to a symbolic variable. `symVarSize` must be in bits. This function returns the \ref py_SymbolicVariable_page created.

- **convertMemoryToSymbolicVariable(\ref py_Memory_page mem, string comment="")**<br>
Converts a symbolic memory expression to a symbolic variable. This function returns the \ref py_SymbolicVariable_page created.

- **convertRegisterToSymbolicVariable(\ref py_REG_page reg, string comment="")**<br>
Converts a symbolic register expression to a symbolic variable. This function returns the \ref py_SymbolicVariable_page created.

- **cpuInvalidRegister(void)**<br>
 Returns the invalid CPU register id.

- **cpuRegisterBitSize(void)**<br>
Returns the max size (in bit) of the CPU register (GPR).

- **cpuRegisterSize(void)**<br>
Returns the max size (in byte) of the CPU register (GPR).

- <b>createSymbolicFlagExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_REG_page flag, string comment="")</b><br>
Returns the new symbolic register expression as \ref py_SymbolicExpression_page and links this expression to the \ref py_Instruction_page.

- <b>createSymbolicMemoryExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_Memory_page mem, string comment="")</b><br>
Returns the new symbolic memory expression as \ref py_SymbolicExpression_page and links this expression to the \ref py_Instruction_page.

- <b>createSymbolicRegisterExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_REG_page reg, string comment="")</b><br>
Returns the new symbolic register expression as \ref py_SymbolicExpression_page and links this expression to the \ref py_Instruction_page.

- <b>createSymbolicVolatileExpression (\ref py_Instruction_page inst, \ref py_AstNode_page node, string comment="")</b><br>
Returns the new symbolic volatile expression as \ref py_SymbolicExpression_page and links this expression to the \ref py_Instruction_page.

- **disassembly(\ref py_Instruction_page inst)**<br>
Disassembles the instruction and setup operands. You must define an architecture before.

- **enableSymbolicEmulation(bool flag)**<br>
Enables or disables the symbolic emulation. Set `true` for a full symbolic execution (emulation) or `false` for a concolic execution.

- **enableSymbolicEngine(bool flag)**<br>
Enables or disables the symbolic execution engine.

- **enableSymbolicOptimization(\ref py_OPTIMIZATION_page opti, bool flag)**<br>
Enables or disablrs a symbolic optimization.

- **enableSymbolicZ3Simplification(bool flag)**<br>
Enabled, Triton will use the simplification passes of z3 before to call its recorded simplification passes.

- **enableTaintEngine(bool flag)**<br>
Enables or disables the taint engine.

- **evaluateAstViaZ3(\ref py_AstNode_page node)**<br>
Evaluates an AST via Z3 and returns the symbolic value as integer.

- **getAllRegisters(void)**<br>
Returns the list of all registers. Each item of this list is a \ref py_Register_page.

- **getArchitecture(void)**<br>
Returns the architecture which has been initialized as \ref py_ARCH_page.

- **getAstRepresentationMode(void)**<br>
Returns the AST representation mode as \ref py_AST_REPRESENTATION_page.

- **getAstFromId(integer symExprId)**<br>
Returns the partial AST as \ref py_AstNode_page from a symbolic expression id.

- **getAstDictionariesStats(void)**<br>
Returns a dictionary which contains all information about number of nodes allocated via AST dictionaries.

- **getFullAst(\ref py_AstNode_page node)**<br>
Returns the full AST of a root node as \ref py_AstNode_page.

- **getFullAstFromId(integer symExprId)**<br>
Returns the full AST as \ref py_AstNode_page from a symbolic expression id.

- **getMemoryAreaValue(integer baseAddr, integer size)**<br>
If the emulation is enabled, returns the emulated value otherwise returns the last concrete values of a memory area as a list of integer.

- **getMemoryValue(intger addr)**<br>
If the emulation is enabled, returns the emulated value otherwise returns the last concrete value recorded of the memory access.

- **getMemoryValue(\ref py_Memory_page mem)**<br>
If the emulation is enabled, returns the emulated value otherwise returns the last concrete value recorded of the memory access.

- **getModel(\ref py_AstNode_page node)**<br>
Computes and returns a model as a dictionary of {integer symVarId : \ref py_SolverModel_page model} from a symbolic constraint.

- **getModels(\ref py_AstNode_page node)**<br>
Computes and returns several models from a symbolic constraint. The `limit` is the number of models returned.

- **getParentRegisters(void)**<br>
Returns the list of parent registers. Each item of this list is a \ref py_Register_page.

- **getPathConstraints(void)**<br>
Returns the logical conjunction vector of path constraints as list of \ref py_PathConstraint_page.

- **getPathConstraintsAst(void)**<br>
Returns the logical conjunction AST of path constraints as \ref py_AstNode_page.

- **getRegisterValue(\ref py_REG_page reg)**<br>
If the emulation is enabled, returns the emulated value otherwise returns the last concrete value recorded of the register.

- **getSymbolicExpressionFromId(intger symExprId)**<br>
Returns the symbolic expression as \ref py_SymbolicExpression_page corresponding to the id.

- **getSymbolicExpressions(void)**<br>
Returns all symbolic expressions as a dictionary of {integer SymExprId : \ref py_SymbolicExpression_page expr}.

- **getSymbolicMemory(void)**<br>
Returns the map of symbolic memory as {integer address : \ref py_SymbolicExpression_page expr}.

- **getSymbolicMemoryId(intger addr)**<br>
Returns the symbolic expression id as integer corresponding to the memory address.

- **getSymbolicMemoryValue(intger addr)**<br>
Returns the symbolic memory value as integer.

- **getSymbolicMemoryValue(\ref py_Memory_page mem)**<br>
Returns the symbolic memory value as integer.

- **getSymbolicRegisters(void)**<br>
Returns the map of symbolic register as {\ref py_REG_page reg : \ref py_SymbolicExpression_page expr}.

- **getSymbolicRegisterId(\ref py_REG_page reg)**<br>
Returns the symbolic expression id as integer corresponding to the register.

- **getSymbolicRegisterValue(\ref py_REG_page reg)**<br>
Returns the symbolic register value as integer.

- **getSymbolicVariableFromId(integer symVarId)**<br>
Returns the symbolic variable as \ref py_SymbolicVariable_page corresponding to the symbolic variable id.

- **getSymbolicVariableFromName(string symVarName)**<br>
Returns the symbolic variable as \ref py_SymbolicVariable_page corresponding to the symbolic variable name.

- **getSymbolicVariables(void)**<br>
Returns all symbolic variable as a dictionary of {integer SymVarId : \ref py_SymbolicVariable_page var}.

- **getTaintedSymbolicExpressions(void)**<br>
Returns the list of all tainted \ref py_SymbolicExpression_page.

- **isArchitectureValid(void)**<br>
Returns true if the architecture is valid.

- **isMemoryTainted(integer addr)**<br>
Returns true if the address is tainted.

- **isMemoryTainted(\ref py_Memory_page mem)**<br>
Returns true if the memory is tainted.

- **isRegisterTainted(\ref py_REG_page reg)**<br>
Returns true if the register is tainted.

- **isSymbolicEmulationEnabled(void)**<br>
Returns true if Triton performs a full symbolic execution (emulation).

- **isSymbolicEngineEnabled(void)**<br>
Returns true if the symbolic execution engine is enabled.

- **isSymbolicExpressionIdExists(integer symExprId)**<br>
Returns true if the symbolic expression id exists.

- **isSymbolicOptimizationEnabled(\ref py_OPTIMIZATION_page opti)**<br>
Returns true if the symbolic optimization is enabled.

- **isSymbolicZ3SimplificationEnabled(void)**<br>
Returns true if Triton can use the simplification passes of z3.

- **isTaintEngineEnabled(void)**<br>
Returns true if the taint engine is enabled.

- **newSymbolicExpression(\ref py_AstNode_page node, string comment="")**<br>
Returns a new symbolic expression. Note that if there are simplification passes recorded, simplification will be applied.

- **newSymbolicVariable(intger varSize, string comment="")**<br>
Returns a new symbolic variable.

- **processing(\ref py_Instruction_page inst)**<br>
The main function. This function processes everything (engine, IR, optimization, state, ...) from a given instruction.

- **recordSimplificationCallback(function cb)**<br>
Records a simplification callback. The callback will be called before every symbolic assignments.

- **removeSimplificationCallback(function cb)**<br>
Removes a simplification callback.

- **resetEngines(void)**<br>
Resets everything.

- **setArchitecture(\ref py_ARCH_page arch)**<br>
Initializes an architecture. This function must be called before any call to the rest of the API.

- **setAstRepresentationMode(\ref py_AST_REPRESENTATION_page mode)**<br>
Sets the AST representation mode.

- **setLastMemoryAreaValue(integer baseAddr, [integer,])**<br>
Sets the last concrete values of a memory area.

- **setLastMemoryValue(integer addr, integer value)**<br>
Sets the last concrete value of a memory access.

- **setLastMemoryValue(\ref py_Memory_page mem)**<br>
Sets the last concrete value of a memory access.

- **setLastRegisterValue(\ref py_REG_page reg)**<br>
Sets the last concrete value of a register state. You cannot set an isolated flag, if so, use the flags registers like EFLAGS.

- **setTaintMemory(\ref py_Memory_page mem, bool flag)**<br>
Sets the targeted memory as tainted or not.

- **setTaintRegister(\ref py_REG_page reg, bool flag)**<br>
Sets the targeted register as tainted or not.

- **simplify(\ref py_AstNode_page node, bool z3=False)**<br>
Calls all simplification callbacks recorded and returns the simplified node as \ref py_AstNode_page. If the `z3` flag is set to True, Triton will use z3 to simplify the given `node` before to call recorded callbacks.

- <b>taintAssignmentMemoryImmediate(\ref py_Memory_page memDst)</b><br>
Taints `memDst` with an assignment - `memDst` is untained.

- <b>taintAssignmentMemoryMemory(\ref py_Memory_page memDst, \ref py_Memory_page memSrc)</b><br>
Taints `memDst` from `memSrc` with an assignment - `memDst` is tainted if `memSrc` is tainted, otherwise `memDst` is untained.

- <b>taintAssignmentMemoryRegister(\ref py_Memory_page memDst, \ref py_REG_page regSrc)</b><br>
Taints `memDst` from `regSrc` with an assignment - `memDst` is tainted if `regSrc` is tainted, otherwise `memDst` is untained.

- <b>taintAssignmentRegisterImmediate(\ref py_REG_page regDst)</b><br>
Taints `regDst` with an assignment - `regSrc` is untained.

- <b>taintAssignmentRegisterMemory(\ref py_REG_page regDst, \ref py_Memory_page memSrc)</b><br>
Taints `regDst` from `MemSrc` with an assignment - `regDst` is tainted if `memSrc` is tainted, otherwise `regDst` is untained.

- <b>taintAssignmentRegisterRegister(\ref py_REG_page regDst, \ref py_REG_page regSrc)</b><br>
Taints `regDst` from `regSrc` with an assignment - `regDst` is tainted if `regSrc` is tainted, otherwise `regDst` is untained.

- **taintMemory(intger addr)**<br>
Taints an address.

- **taintMemory(\ref py_Memory_page mem)**<br>
Taints a memory.

- **taintRegister(\ref py_REG_page reg)**<br>
Taints a register.

- <b>taintUnionMemoryImmediate(\ref py_Memory_page memDst)</b><br>
Taints `memDst` with an union - `memDst` does not changes.

- <b>taintUnionMemoryMemory(\ref py_Memory_page memDst, \ref py_Memory_page memSrc)</b><br>
Taints `memDst` from `memSrc` with an union - `memDst` is tainted if `memDst` or `memSrc` are tainted.

- <b>taintUnionMemoryRegister(\ref py_Memory_page memDst, \ref py_REG_page regSrc)</b><br>
Taints `memDst` from `RegSrc` with an union - `memDst` is tainted if `memDst` or `regSrc` are tainted.

- <b>taintUnionRegisterImmediate(\ref py_REG_page regDst)</b><br>
Taints `regDst` with an union - `regDst` does not changes.

- <b>taintUnionRegisterMemory(\ref py_REG_page regDst, \ref py_Memory_page memSrc)</b><br>
Taints `regDst` from `memSrc` with an union - `regDst` is tainted if `regDst` or `memSrc` are tainted.

- <b>taintUnionRegisterRegister(\ref py_REG_page regDst, \ref py_REG_page regSrc)</b><br>
Taints `regDst` from `regSrc` with an union - `regDst` is tainted if `regDst` or `regSrc` are tainted.

- **untaintMemory(intger addr)**<br>
Untaints an address.

- **untaintMemory(\ref py_Memory_page mem)**<br>
Untaints a memory.

- **untaintRegister(\ref py_REG_page reg)**<br>
Untaints a register.


\subsection triton_py_api_namespaces Namespaces

- \ref py_ARCH_page
- \ref py_AST_NODE_page
- \ref py_AST_REPRESENTATION_page
- \ref py_CPUSIZE_page
- \ref py_OPCODE_page
- \ref py_OPERAND_page
- \ref py_OPTIMIZATION_page
- \ref py_REG_page
- \ref py_SYMEXPR_page
- \ref py_SYSCALL_page
- \ref py_VERSION_page

\section pintool_py_api Python API - Methods and namespaces of the pintool
<hr>

This project is shipped with a Pin \ref Tracer_page which can be compile with the `cmake` flag `-DPINTOOL=on`. Then, the pintool must be used like this:


~~~~~~~~~~~~~{.sh}
$ ./triton <your_script.py> <your_targeted_binary>
~~~~~~~~~~~~~

Your script must contains the pintool and triton imports.

~~~~~~~~~~~~~{.py}
>>> from triton import *
>>> from pintool import *
~~~~~~~~~~~~~


\subsection pintool_py_api_methods Methods

- <b>addCallback(function, \ref py_CALLBACK_page type)</b><br>
Adds a callback before and after several cases. All code executed into a callback function are executed during the instrumentation.

- **checkReadAccess(integer addr)**<br>
Checks whether the memory page which contains this address has a read access protection. Returns true or false.

- **checkWriteAccess(integer addr)**<br>
Checks whether the memory page which contains this address has a write access protection. Returns true or false.

- **detachProcess(void)**<br>
Detachs the pintool from the targeted process. The control flow is returned to the original uninstrumented code and the application is natively executed.

- **disableSnapshot(void)**<br>
Disables the snapshot engine. When you have done with the `tracer::pintool::Snapshot::restoreSnapshot()` function, you may use this function to improve performance. Then, the
snapshot engine will be enable at the next `tracer::pintool::Snapshot::takeSnapshot()` call.

- **getCurrentMemoryValue(\ref py_Memory_page mem)**<br>
Returns the memory value from a \ref py_Memory_page.

- **getCurrentMemoryValue(integer addr)**<br>
Returns the memory value from the address.

- **getCurrentMemoryValue(integer addr, integer readSize)**<br>
Returns the memory value according to the `readSize` from the address.

- **getCurrentRegisterValue(\ref py_REG_page reg)**<br>
Returns the register value from a \ref py_REG_page.

- **getImageName(integer addr)**<br>
Returns the image name from a given address. Returns an empty string if not found.

- **getRoutineName(integer addr)**<br>
Returns the routine name from a given address. Returns an empty string if not found.

- **getSyscallArgument(\ref py_STANDARD_page std, integer argNum)**<br>
Returns the argument value of the system call which is executed in the current context. It is a user's responsibility to make sure that the
current instruction is a syscall. This function is mainly used in a `SYSCALL_ENTRY` \ref py_CALLBACK_page.

- **getSyscallNumber(\ref py_STANDARD_page std)**<br>
Returns the syscall number of the system call which is executed in the current context. It is a user's responsibility to make sure that the
current instruction is a syscall. This function is mainly used in a `SYSCALL_ENTRY` \ref py_CALLBACK_page.

- **getSyscallReturn(\ref py_STANDARD_page std)**<br>
Returns the result of the syscall. It is a user's responsibility to make sure that the current context represents the state of a system call after its execution.
This function is mainly used in a `SYSCALL_EXIT` \ref py_CALLBACK_page.

- **isSnapshotEnabled(void)**<br>
Returns true if the snapshot engine is enabled.

- **restoreSnapshot(void)**<br>
Restores the last snpahost taken. Check the `tracer::pintool::Snapshot::takeSnapshot()` function. Note that this function have to execute a new context registers, so `RIP` will be modified and your callback stopped (checkout the [Pin API](https://software.intel.com/sites/landingpage/pintool/docs/71313/Pin/html/group__CONTEXT__API.html#g4e6408c641479c22918a888d95ca1930)).

- **runProgram(void)**<br>
Starts the binary instrumentation over Pin.

- **setCurrentMemoryValue(\ref py_Memory_page mem)**<br>
Sets the current memory value from a \ref py_Memory_page. `triton::arch::MemoryOperand::getConcreteValue()` is used to define the value.

- **setCurrentMemoryValue(\ref py_Memory_page mem, integer value)**<br>
Sets the current memory value from a \ref py_Memory_page.

- **setCurrentMemoryValue(integer addr, integer value)**<br>
Sets the current memory value from an address.

- **setCurrentRegisterValue(\ref py_Register_page reg)**<br>
Sets the current register value from a \ref py_Register_page. `triton::arch::RegisterOperand::getConcreteValue()` is used to define the value. This method can only be called into a `BEFORE_SYMPROC` and `AFTER` callback. This method also synchronizes the Triton's register.

- **setCurrentRegisterValue(\ref py_Register_page reg, integer value)**<br>
Sets the current register value from a \ref py_Register_page. This method can only be called into a `BEFORE_SYMPROC` and `AFTER` callback. This method also synchronizes the Triton's register.

- **setupImageBlacklist([""])**<br>
Setups a blacklist of image names, it means that these images will not be instrumented and executed natively.

- **setupImageWhitelist([""])**<br>
Setups a whitelist of image names, it means that these images will be instrumented and all other images will be executed natively.

- **startAnalysisFromAddress(integer addr)**<br>
Starts the instrumentation at a specific address.

- **startAnalysisFromEntry(void)**<br>
Starts the instrumentation at the entry point.

- **startAnalysisFromOffset(integer offset)**<br>
Starts the instrumentation at a specific offset in the binary

- **startAnalysisFromSymbol(string symbol)**<br>
Starts the instrumentation at a specific symbol.

- **stopAnalysisFromAddress(integer addr)**<br>
Stops the instrumentation at a specific address.

- **stopAnalysisFromOffset(integer offset)**<br>
Stops the instrumentation at a specific offset.

- **takeSnapshot(void)**<br>
Creates a snaphost at this program point.

\subsection pintool_py_api_namespaces Namespaces

- \ref py_CALLBACK_page
- \ref py_STANDARD_page

*/



namespace triton {
  namespace bindings {
    namespace python {

      static PyObject* triton_Bitvector(PyObject* self, PyObject* args) {
        PyObject* high = nullptr;
        PyObject* low  = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &high, &low);

        /* Check if the first arg is a integer */
        if (high == nullptr || (!PyLong_Check(high) && !PyInt_Check(high)))
          return PyErr_Format(PyExc_TypeError, "Bitvector(): Expects an integer as first argument.");

        /* Check if the second arg is a integer */
        if (low == nullptr || (!PyLong_Check(low) && !PyInt_Check(low)))
          return PyErr_Format(PyExc_TypeError, "Bitvector(): Expects an integer as second argument.");

        try {
          return PyBitvector(PyLong_AsUint(high), PyLong_AsUint(low));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_Immediate(PyObject* self, PyObject* args) {
        PyObject* value = nullptr;
        PyObject* size  = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &value, &size);

        /* Check if the first arg is a integer */
        if (value == nullptr || (!PyLong_Check(value) && !PyInt_Check(value)))
          return PyErr_Format(PyExc_TypeError, "Immediate(): Expects an integer as first argument.");

        /* Check if the second arg is a integer */
        if (size == nullptr || (!PyLong_Check(size) && !PyInt_Check(size)))
          return PyErr_Format(PyExc_TypeError, "Immediate(): Expects an integer as second argument.");

        try {
          triton::arch::ImmediateOperand imm(PyLong_AsUint(value), PyLong_AsUint(size));
          return PyImmediateOperand(imm);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_Instruction(PyObject* self, PyObject* noarg) {
        return PyInstruction();
      }


      static PyObject* triton_Memory(PyObject* self, PyObject* args) {
        PyObject* address       = nullptr;
        PyObject* size          = nullptr;
        PyObject* concreteValue = nullptr;
        triton::uint512 cv      = 0;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOO", &address, &size, &concreteValue);

        /* Check if the first arg is a integer */
        if (address == nullptr || (!PyLong_Check(address) && !PyInt_Check(address)))
          return PyErr_Format(PyExc_TypeError, "Memory(): Expects an integer as first argument.");

        /* Check if the second arg is a integer */
        if (size == nullptr || (!PyLong_Check(size) && !PyInt_Check(size)))
          return PyErr_Format(PyExc_TypeError, "Memory(): Expects an integer as second argument.");

        /* Check if the third arg is a integer */
        if (concreteValue != nullptr && (!PyLong_Check(concreteValue) && !PyInt_Check(concreteValue)))
          return PyErr_Format(PyExc_TypeError, "Memory(): Expects an integer as third argument.");

        if (concreteValue != nullptr)
          cv = PyLong_AsUint512(concreteValue);

        try {
          triton::arch::MemoryOperand mem(PyLong_AsUint(address), PyLong_AsUint(size), cv);
          return PyMemoryOperand(mem);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_Register(PyObject* self, PyObject* args) {
        PyObject* concreteValue         = nullptr;
        PyObject* regIn                 = nullptr;
        triton::uint512 cv              = 0;
        triton::arch::RegisterOperand*  r;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &regIn, &concreteValue);

        /* Check if the first arg is a Register */
        if (regIn == nullptr || !PyRegisterOperand_Check(regIn))
          return PyErr_Format(PyExc_TypeError, "Register(): Expects a Register as first argument.");

        /* Check if the second arg is a integer */
        if (concreteValue != nullptr && (!PyLong_Check(concreteValue) && !PyInt_Check(concreteValue)))
          return PyErr_Format(PyExc_TypeError, "Register(): Expects an integer as second argument.");

        if (concreteValue != nullptr)
          cv = PyLong_AsUint512(concreteValue);

        try {
          r = PyRegisterOperand_AsRegisterOperand(regIn);
          triton::arch::RegisterOperand regOut(r->getId(), cv);
          return PyRegisterOperand(regOut);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_assignSymbolicExpressionToMemory(PyObject* self, PyObject* args) {
        PyObject* se  = nullptr;
        PyObject* mem = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &se, &mem);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToMemory(): Architecture is not defined.");

        if (se == nullptr || (!PySymbolicExpression_Check(se)))
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToMemory(): Expects a SymbolicExpression as first argument.");

        if (mem == nullptr || (!PyMemoryOperand_Check(mem)))
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToMemory(): Expects a Memory as second argument.");

        triton::engines::symbolic::SymbolicExpression* arg1 = PySymbolicExpression_AsSymbolicExpression(se);
        triton::arch::MemoryOperand arg2 = *PyMemoryOperand_AsMemoryOperand(mem);

        try {
          triton::api.assignSymbolicExpressionToMemory(arg1, arg2);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_assignSymbolicExpressionToRegister(PyObject* self, PyObject* args) {
        PyObject* se  = nullptr;
        PyObject* reg = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &se, &reg);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToRegister(): Architecture is not defined.");

        if (se == nullptr || (!PySymbolicExpression_Check(se)))
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToRegister(): Expects a SymbolicExpression as first argument.");

        if (reg == nullptr || (!PyRegisterOperand_Check(reg)))
          return PyErr_Format(PyExc_TypeError, "assignSymbolicExpressionToRegister(): Expects a REG as second argument.");

        triton::engines::symbolic::SymbolicExpression* arg1 = PySymbolicExpression_AsSymbolicExpression(se);
        triton::arch::RegisterOperand arg2 = *PyRegisterOperand_AsRegisterOperand(reg);

        try {
          triton::api.assignSymbolicExpressionToRegister(arg1, arg2);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_buildSemantics(PyObject* self, PyObject* inst) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "buildSemantics(): Architecture is not defined.");

        if (!PyInstruction_Check(inst))
          return PyErr_Format(PyExc_TypeError, "buildSemantics(): Expects an Instruction as argument.");

        try {
          triton::api.buildSemantics(*PyInstruction_AsInstruction(inst));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_buildSymbolicImmediate(PyObject* self, PyObject* imm) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "buildSymbolicImmediate(): Architecture is not defined.");

        if (!PyImmediateOperand_Check(imm))
          return PyErr_Format(PyExc_TypeError, "buildSymbolicImmediate(): Expects an Immediate as argument.");

        try {
          return PyAstNode(triton::api.buildSymbolicImmediateOperand(*PyImmediateOperand_AsImmediateOperand(imm)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_buildSymbolicMemory(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "buildSymbolicMemory(): Architecture is not defined.");

        if (!PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "buildSymbolicMemory(): Expects an Memory as argument.");

        try {
          return PyAstNode(triton::api.buildSymbolicMemoryOperand(*PyMemoryOperand_AsMemoryOperand(mem)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_buildSymbolicRegister(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "buildSymbolicRegister(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "buildSymbolicRegister(): Expects an Register as argument.");

        try {
          return PyAstNode(triton::api.buildSymbolicRegisterOperand(*PyRegisterOperand_AsRegisterOperand(reg)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_clearPathConstraints(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "clearPathConstraints(): Architecture is not defined.");
        triton::api.clearPathConstraints();
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_concretizeAllMemory(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "concretizeAllMemory(): Architecture is not defined.");
        triton::api.concretizeAllMemory();
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_concretizeAllRegister(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "concretizeAllRegister(): Architecture is not defined.");
        triton::api.concretizeAllRegister();
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_concretizeMemory(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "concretizeMemory(): Architecture is not defined.");

        /* If mem is an address */
        if (PyLong_Check(mem) || PyInt_Check(mem)) {
          try {
            triton::api.concretizeMemory(PyLong_AsUint(mem));
          }
          catch (const std::exception& e) {
            return PyErr_Format(PyExc_TypeError, "%s", e.what());
          }
        }

        /* If mem is a Memory */
        else if (PyMemoryOperand_Check(mem)) {
          try {
            triton::api.concretizeMemory(*PyMemoryOperand_AsMemoryOperand(mem));
          }
          catch (const std::exception& e) {
            return PyErr_Format(PyExc_TypeError, "%s", e.what());
          }
        }

        /* Invalid parameter */
        else
          return PyErr_Format(PyExc_TypeError, "concretizeMemory(): Expects an integer or Memory as argument.");

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_concretizeRegister(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "concretizeRegister(): Architecture is not defined.");

        /* If mem is a Memory */
        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "concretizeRegister(): Expects a REG as argument.");

        try {
          triton::api.concretizeRegister(*PyRegisterOperand_AsRegisterOperand(reg));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_convertExpressionToSymbolicVariable(PyObject* self, PyObject* args) {
        PyObject* exprId        = nullptr;
        PyObject* symVarSize    = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOO", &exprId, &symVarSize, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "convertExpressionToSymbolicVariable(): Architecture is not defined.");

        if (exprId == nullptr || (!PyLong_Check(exprId) && !PyInt_Check(exprId)))
          return PyErr_Format(PyExc_TypeError, "convertExpressionToSymbolicVariable(): Expects an integer as first argument.");

        if (symVarSize == nullptr || (!PyLong_Check(symVarSize) && !PyInt_Check(symVarSize)))
          return PyErr_Format(PyExc_TypeError, "convertExpressionToSymbolicVariable(): Expects an integer as second argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "convertExpressionToSymbolicVariable(): Expects a sting as third argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        try {
          return PySymbolicVariable(triton::api.convertExpressionToSymbolicVariable(PyLong_AsUint(exprId), PyLong_AsUint(symVarSize), ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_convertMemoryToSymbolicVariable(PyObject* self, PyObject* args) {
        PyObject* mem           = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "convertMemoryToSymbolicVariable(): Architecture is not defined.");

        if (mem == nullptr || (!PyMemoryOperand_Check(mem)))
          return PyErr_Format(PyExc_TypeError, "convertMemoryToSymbolicVariable(): Expects a Memory as first argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "convertMemoryToSymbolicVariable(): Expects a sting as second argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        try {
          return PySymbolicVariable(triton::api.convertMemoryToSymbolicVariable(*PyMemoryOperand_AsMemoryOperand(mem), ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_convertRegisterToSymbolicVariable(PyObject* self, PyObject* args) {
        PyObject* reg           = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "convertRegisterToSymbolicVariable(): Architecture is not defined.");

        if (reg == nullptr || (!PyRegisterOperand_Check(reg)))
          return PyErr_Format(PyExc_TypeError, "convertRegisterToSymbolicVariable(): Expects a REG as first argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "convertRegisterToSymbolicVariable(): Expects a sting as second argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        try {
          return PySymbolicVariable(triton::api.convertRegisterToSymbolicVariable(*PyRegisterOperand_AsRegisterOperand(reg), ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_cpuInvalidRegister(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", triton::api.cpuInvalidRegister());
      }


      static PyObject* triton_cpuRegisterBitSize(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", triton::api.cpuRegisterBitSize());
      }


      static PyObject* triton_cpuRegisterSize(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", triton::api.cpuRegisterSize());
      }


      static PyObject* triton_createSymbolicFlagExpression(PyObject* self, PyObject* args) {
        PyObject* inst          = nullptr;
        PyObject* node          = nullptr;
        PyObject* flag          = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOOO", &inst, &node, &flag, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "createSymbolicFlagExpression(): Architecture is not defined.");

        if (inst == nullptr || (!PyInstance_Check(inst)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicFlagExpression(): Expects an Instruction as first argument.");

        if (node == nullptr || (!PyAstNode_Check(node)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicFlagExpression(): Expects a AstNode as second argument.");

        if (flag == nullptr || (!PyRegisterOperand_Check(flag)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicFlagExpression(): Expects a REG as third argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "createSymbolicFlagExpression(): Expects a sting as fourth argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        triton::arch::Instruction arg1 = *PyInstruction_AsInstruction(inst);
        triton::ast::AbstractNode *arg2 = PyAstNode_AsAstNode(node);
        triton::arch::RegisterOperand arg3 = *PyRegisterOperand_AsRegisterOperand(flag);

        try {
          return PySymbolicExpression(triton::api.createSymbolicFlagExpression(arg1, arg2, arg3, ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_createSymbolicMemoryExpression(PyObject* self, PyObject* args) {
        PyObject* inst          = nullptr;
        PyObject* node          = nullptr;
        PyObject* mem           = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOOO", &inst, &node, &mem, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "createSymbolicMemoryExpression(): Architecture is not defined.");

        if (inst == nullptr || (!PyInstance_Check(inst)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicMemoryExpression(): Expects an Instruction as first argument.");

        if (node == nullptr || (!PyAstNode_Check(node)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicMemoryExpression(): Expects a AstNode as second argument.");

        if (mem == nullptr || (!PyMemoryOperand_Check(mem)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicMemoryExpression(): Expects a Memory as third argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "createSymbolicMemoryExpression(): Expects a sting as fourth argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        triton::arch::Instruction arg1 = *PyInstruction_AsInstruction(inst);
        triton::ast::AbstractNode *arg2 = PyAstNode_AsAstNode(node);
        triton::arch::MemoryOperand arg3 = *PyMemoryOperand_AsMemoryOperand(mem);

        try {
          return PySymbolicExpression(triton::api.createSymbolicMemoryExpression(arg1, arg2, arg3, ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_createSymbolicRegisterExpression(PyObject* self, PyObject* args) {
        PyObject* inst          = nullptr;
        PyObject* node          = nullptr;
        PyObject* reg           = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOOO", &inst, &node, &reg, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "createSymbolicRegisterExpression(): Architecture is not defined.");

        if (inst == nullptr || (!PyInstance_Check(inst)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicRegisterExpression(): Expects an Instruction as first argument.");

        if (node == nullptr || (!PyAstNode_Check(node)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicRegisterExpression(): Expects a AstNode as second argument.");

        if (reg == nullptr || (!PyRegisterOperand_Check(reg)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicRegisterExpression(): Expects a REG as third argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "createSymbolicRegisterExpression(): Expects a sting as fourth argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        triton::arch::Instruction arg1 = *PyInstruction_AsInstruction(inst);
        triton::ast::AbstractNode *arg2 = PyAstNode_AsAstNode(node);
        triton::arch::RegisterOperand arg3 = *PyRegisterOperand_AsRegisterOperand(reg);

        try {
          return PySymbolicExpression(triton::api.createSymbolicRegisterExpression(arg1, arg2, arg3, ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_createSymbolicVolatileExpression(PyObject* self, PyObject* args) {
        PyObject* inst          = nullptr;
        PyObject* node          = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OOO", &inst, &node, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "createSymbolicVolatileExpression(): Architecture is not defined.");

        if (inst == nullptr || (!PyInstance_Check(inst)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicVolatileExpression(): Expects an Instruction as first argument.");

        if (node == nullptr || (!PyAstNode_Check(node)))
          return PyErr_Format(PyExc_TypeError, "createSymbolicVolatileExpression(): Expects a AstNode as second argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "createSymbolicVolatileExpression(): Expects a sting as third argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        triton::arch::Instruction arg1 = *PyInstruction_AsInstruction(inst);
        triton::ast::AbstractNode *arg2 = PyAstNode_AsAstNode(node);

        try {
          return PySymbolicExpression(triton::api.createSymbolicVolatileExpression(arg1, arg2, ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_disassembly(PyObject* self, PyObject* inst) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "disassembly(): Architecture is not defined.");

        if (!PyInstruction_Check(inst))
          return PyErr_Format(PyExc_TypeError, "disassembly(): Expects an Instruction as argument.");

        try {
          triton::api.disassembly(*PyInstruction_AsInstruction(inst));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_enableSymbolicEmulation(PyObject* self, PyObject* flag) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "enableSymbolicEmulation(): Architecture is not defined.");

        if (!PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "enableSymbolicEmulation(): Expects an boolean as argument.");

        try {
          triton::api.enableSymbolicEmulation(PyLong_AsUint(flag));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_enableSymbolicEngine(PyObject* self, PyObject* flag) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "enableSymbolicEngine(): Architecture is not defined.");

        if (!PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "enableSymbolicEngine(): Expects an boolean as argument.");

        try {
          triton::api.enableSymbolicEngine(PyLong_AsUint(flag));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_enableSymbolicOptimization(PyObject* self, PyObject* args) {
        PyObject* opti = nullptr;
        PyObject* flag = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &opti, &flag);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "enableSymbolicOptimization(): Architecture is not defined.");

        if (opti == nullptr || (!PyLong_Check(opti) && !PyInt_Check(opti)))
          return PyErr_Format(PyExc_TypeError, "enableSymbolicOptimization(): Expects an OPTIMIZATION as argument.");

        if (flag == nullptr || !PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "enableSymbolicOptimization(): Expects an boolean flag as second argument.");

        try {
          triton::api.enableSymbolicOptimization(static_cast<enum triton::engines::symbolic::optimization_e>(PyLong_AsUint(opti)), PyLong_AsUint(flag));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_enableSymbolicZ3Simplification(PyObject* self, PyObject* flag) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "enableSymbolicZ3Simplification(): Architecture is not defined.");

        if (!PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "enableSymbolicZ3Simplification(): Expects a boolean as argument.");

        try {
          triton::api.enableSymbolicZ3Simplification(PyLong_AsUint(flag));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_enableTaintEngine(PyObject* self, PyObject* flag) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "enableTaintEngine(): Architecture is not defined.");

        if (!PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "enableTaintEngine(): Expects an boolean as argument.");

        try {
          triton::api.enableTaintEngine(PyLong_AsUint(flag));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_evaluateAstViaZ3(PyObject* self, PyObject* node) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "evaluateAstViaZ3(): Architecture is not defined.");

        if (!PyAstNode_Check(node))
          return PyErr_Format(PyExc_TypeError, "evaluateAstViaZ3(): Expects a AstNode as argument.");

        try {
          return PyLong_FromUint512(triton::api.evaluateAstViaZ3(PyAstNode_AsAstNode(node)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
        catch (const z3::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.msg());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_getAllRegisters(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        std::set<triton::arch::RegisterOperand*> reg;
        std::set<triton::arch::RegisterOperand*>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getAllRegisters(): Architecture is not defined.");

        try {
          reg = triton::api.getAllRegisters();
          ret = xPyList_New(reg.size());
          triton::uint32 index = 0;
          for (it = reg.begin(); it != reg.end(); it++)
            PyList_SetItem(ret, index++, PyRegisterOperand(**it));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getArchitecture(PyObject* self, PyObject* noarg) {
        return PyLong_FromUint(triton::api.getArchitecture());
      }


      static PyObject* triton_getAstFromId(PyObject* self, PyObject* symExprId) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getAstFromId(): Architecture is not defined.");

        if (!PyLong_Check(symExprId) && !PyInt_Check(symExprId))
          return PyErr_Format(PyExc_TypeError, "getAstFromId(): Expects an integer as argument.");

        try {
          return PyAstNode(triton::api.getAstFromId(PyLong_AsUint(symExprId)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getAstRepresentationMode(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getAstRepresentationMode(): Architecture is not defined.");
        return PyLong_FromUint(triton::api.getAstRepresentationMode());
      }


      static PyObject* triton_getAstDictionariesStats(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        std::map<std::string, triton::uint32> stats;
        std::map<std::string, triton::uint32>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getAstDictionariesStats(): Architecture is not defined.");

        try {
          stats = triton::api.getAstDictionariesStats();
          ret   = xPyDict_New();
          for (it = stats.begin(); it != stats.end(); it++)
            PyDict_SetItem(ret, PyString_FromString(it->first.c_str()), PyLong_FromUint(it->second));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getFullAst(PyObject* self, PyObject* node) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getFullAst(): Architecture is not defined.");

        if (!PyAstNode_Check(node))
          return PyErr_Format(PyExc_TypeError, "getFullAst(): Expects a AstNode as argument.");

        try {
          return PyAstNode(triton::api.getFullAst(PyAstNode_AsAstNode(node)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getFullAstFromId(PyObject* self, PyObject* symExprId) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getFullAstFromId(): Architecture is not defined.");

        if (!PyLong_Check(symExprId) && !PyInt_Check(symExprId))
          return PyErr_Format(PyExc_TypeError, "getFullAstFromId(): Expects an integer as argument.");

        try {
          return PyAstNode(triton::api.getFullAstFromId(PyLong_AsUint(symExprId)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getMemoryAreaValue(PyObject* self, PyObject* args) {
        std::vector<triton::uint8> vv;
        PyObject* ret  = nullptr;
        PyObject* addr = nullptr;
        PyObject* size = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &addr, &size);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getMemoryAreaValue(): Architecture is not defined.");

        try {
          vv  = triton::api.getMemoryAreaValue(PyLong_AsUint(addr), PyLong_AsUint(size));
          ret = xPyList_New(vv.size());
          for (triton::uint32 index = 0; index < vv.size(); index++)
            PyList_SetItem(ret, index, PyLong_FromUint(vv[index]));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getMemoryValue(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getMemoryValue(): Architecture is not defined.");

        try {
          if (PyLong_Check(mem) || PyInt_Check(mem))
              return PyLong_FromUint512(triton::api.getMemoryValue(PyLong_AsUint(mem)));
          else if (PyMemoryOperand_Check(mem))
              return PyLong_FromUint512(triton::api.getMemoryValue(*PyMemoryOperand_AsMemoryOperand(mem)));
          else
            return PyErr_Format(PyExc_TypeError, "getMemoryValue(): Expects a Memory or an integer as argument.");
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getModel(PyObject* self, PyObject* node) {
        PyObject* ret = nullptr;
        std::map<triton::uint32, triton::engines::solver::SolverModel> model;
        std::map<triton::uint32, triton::engines::solver::SolverModel>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getModel(): Architecture is not defined.");

        if (!PyAstNode_Check(node))
          return PyErr_Format(PyExc_TypeError, "getModel(): Expects a AstNode as argument.");

        try {
          ret = xPyDict_New();
          model = triton::api.getModel(PyAstNode_AsAstNode(node));
          for (it = model.begin(); it != model.end(); it++) {
            PyDict_SetItem(ret, PyLong_FromUint(it->first), PySolverModel(it->second));
          }
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getModels(PyObject* self, PyObject* args) {
        PyObject* ret   = nullptr;
        PyObject* node  = nullptr;
        PyObject* limit = nullptr;
        triton::uint32 index = 0;
        std::list<std::map<triton::uint32, triton::engines::solver::SolverModel>> models;
        std::list<std::map<triton::uint32, triton::engines::solver::SolverModel>>::iterator it;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &node, &limit);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getModels(): Architecture is not defined.");

        if (node == nullptr || !PyAstNode_Check(node))
          return PyErr_Format(PyExc_TypeError, "getModels(): Expects a AstNode as first argument.");

        if (limit == nullptr || (!PyLong_Check(limit) && !PyInt_Check(limit)))
          return PyErr_Format(PyExc_TypeError, "getModels(): Expects an integer as second argument.");

        try {
          models = triton::api.getModels(PyAstNode_AsAstNode(node), PyLong_AsUint(limit));
          ret = xPyList_New(models.size());
          for (it = models.begin(); it != models.end(); it++) {
            PyObject* mdict = xPyDict_New();
            std::map<triton::uint32, triton::engines::solver::SolverModel> model = *it;
            for (auto it2 = model.begin(); it2 != model.end(); it2++) {
              PyDict_SetItem(mdict, PyLong_FromUint(it2->first), PySolverModel(it2->second));
            }
            if (model.size() > 0)
              PyList_SetItem(ret, index++, mdict);
          }
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getParentRegisters(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        std::set<triton::arch::RegisterOperand*> reg;
        std::set<triton::arch::RegisterOperand*>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getParentRegisters(): Architecture is not defined.");

        try {
          reg = triton::api.getParentRegisters();
          ret = xPyList_New(reg.size());
          triton::uint32 index = 0;
          for (it = reg.begin(); it != reg.end(); it++)
            PyList_SetItem(ret, index++, PyRegisterOperand(**it));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getPathConstraints(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getPathConstraintsAst(): Architecture is not defined.");

        try {
          const std::vector<triton::engines::symbolic::PathConstraint>& pc = triton::api.getPathConstraints();
          ret = xPyList_New(pc.size());

          triton::uint32 index = 0;
          for (auto it = pc.begin(); it != pc.end(); it++)
            PyList_SetItem(ret, index++, PyPathConstraint(*it));

          return ret;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getPathConstraintsAst(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getPathConstraintsAst(): Architecture is not defined.");

        try {
          return PyAstNode(triton::api.getPathConstraintsAst());
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getRegisterValue(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getRegisterValue(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "getRegisterValue(): Expects a REG as argument.");

        try {
          return PyLong_FromUint512(triton::api.getRegisterValue(*PyRegisterOperand_AsRegisterOperand(reg)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicExpressionFromId(PyObject* self, PyObject* symExprId) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicExpressionFromId(): Architecture is not defined.");

        if (!PyLong_Check(symExprId) && !PyInt_Check(symExprId))
          return PyErr_Format(PyExc_TypeError, "getSymbolicExpressionFromId(): Expects an integer as argument.");

        try {
          return PySymbolicExpression(triton::api.getSymbolicExpressionFromId(PyLong_AsUint(symExprId)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicExpressions(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        const std::map<triton::__uint, triton::engines::symbolic::SymbolicExpression*>& expressions = triton::api.getSymbolicExpressions();
        std::map<triton::__uint, triton::engines::symbolic::SymbolicExpression*>::const_iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getTaintedSymbolicExpressions(): Architecture is not defined.");

        try {
          ret = xPyDict_New();
          for (it = expressions.begin(); it != expressions.end(); it++)
            PyDict_SetItem(ret, PyLong_FromUint(it->first), PySymbolicExpression(it->second));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getSymbolicMemory(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        std::map<triton::__uint, triton::engines::symbolic::SymbolicExpression*> regs = triton::api.getSymbolicMemory();
        std::map<triton::__uint, triton::engines::symbolic::SymbolicExpression*>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicMemory(): Architecture is not defined.");

        try {
          ret = xPyDict_New();
          for (it = regs.begin(); it != regs.end(); it++) {
            PyDict_SetItem(ret, PyLong_FromUint(it->first), PySymbolicExpression(it->second));
          }
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getSymbolicMemoryId(PyObject* self, PyObject* addr) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicMemoryId(): Architecture is not defined.");

        if (!PyLong_Check(addr) && !PyInt_Check(addr))
          return PyErr_Format(PyExc_TypeError, "getSymbolicMemoryId(): Expects an integer as argument.");

        try {
          return PyLong_FromUint(triton::api.getSymbolicMemoryId(PyLong_AsUint(addr)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicMemoryValue(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicMemoryValue(): Architecture is not defined.");

        if (!PyLong_Check(mem) && !PyInt_Check(mem) && !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "getSymbolicMemoryValue(): Expects an integer or a Memory as argument.");

        try {
          if (PyLong_Check(mem) || PyInt_Check(mem))
            return PyLong_FromUint512(triton::api.getSymbolicMemoryValue(PyLong_AsUint(mem)));
          return PyLong_FromUint512(triton::api.getSymbolicMemoryValue(*PyMemoryOperand_AsMemoryOperand(mem)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicRegisters(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        std::map<triton::arch::RegisterOperand, triton::engines::symbolic::SymbolicExpression*> regs = triton::api.getSymbolicRegisters();
        std::map<triton::arch::RegisterOperand, triton::engines::symbolic::SymbolicExpression*>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicRegisters(): Architecture is not defined.");

        try {
          ret = xPyDict_New();
          for (it = regs.begin(); it != regs.end(); it++) {
            triton::arch::RegisterOperand reg(it->first);
            PyDict_SetItem(ret, PyRegisterOperand(reg), PySymbolicExpression(it->second));
          }
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getSymbolicRegisterId(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicRegisterId(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "getSymbolicRegisterId(): Expects a REG as argument.");

        try {
          return PyLong_FromUint(triton::api.getSymbolicRegisterId(*PyRegisterOperand_AsRegisterOperand(reg)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicRegisterValue(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicRegisterValue(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "getSymbolicRegisterValue(): Expects a REG as argument.");

        try {
          return PyLong_FromUint512(triton::api.getSymbolicRegisterValue(*PyRegisterOperand_AsRegisterOperand(reg)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicVariableFromId(PyObject* self, PyObject* symVarId) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicVariableFromId(): Architecture is not defined.");

        if (!PyLong_Check(symVarId) && !PyInt_Check(symVarId))
          return PyErr_Format(PyExc_TypeError, "getSymbolicVariableFromId(): Expects an integer as argument.");

        try {
          return PySymbolicVariable(triton::api.getSymbolicVariableFromId(PyLong_AsUint(symVarId)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicVariableFromName(PyObject* self, PyObject* symVarName) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getSymbolicVariableFromName(): Architecture is not defined.");

        if (!PyString_Check(symVarName))
          return PyErr_Format(PyExc_TypeError, "getSymbolicVariableFromName(): Expects a string as argument.");

        try {
          std::string arg = PyString_AsString(symVarName);
          return PySymbolicVariable(triton::api.getSymbolicVariableFromName(arg));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_getSymbolicVariables(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        const std::map<triton::__uint, triton::engines::symbolic::SymbolicVariable*>& variables = triton::api.getSymbolicVariables();
        std::map<triton::__uint, triton::engines::symbolic::SymbolicVariable*>::const_iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getTaintedSymbolicVariables(): Architecture is not defined.");

        try {
          ret = xPyDict_New();
          for (it = variables.begin(); it != variables.end(); it++)
            PyDict_SetItem(ret, PyLong_FromUint(it->first), PySymbolicVariable(it->second));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_getTaintedSymbolicExpressions(PyObject* self, PyObject* noarg) {
        PyObject* ret = nullptr;
        triton::uint32 size = 0, index = 0;
        std::list<triton::engines::symbolic::SymbolicExpression*> expressions;
        std::list<triton::engines::symbolic::SymbolicExpression*>::iterator it;

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "getTaintedSymbolicExpressions(): Architecture is not defined.");

        try {
          expressions = triton::api.getTaintedSymbolicExpressions();
          size = expressions.size();
          ret = xPyList_New(size);
          for (it = expressions.begin(); it != expressions.end(); it++) {
            PyList_SetItem(ret, index, PySymbolicExpression(*it));
            index++;
          }
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        return ret;
      }


      static PyObject* triton_isArchitectureValid(PyObject* self, PyObject* noarg) {
        if (triton::api.isArchitectureValid() == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isMemoryTainted(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isMemoryTainted(): Architecture is not defined.");

        if (PyMemoryOperand_Check(mem)) {
          if (triton::api.isMemoryTainted(*PyMemoryOperand_AsMemoryOperand(mem)) == true)
            Py_RETURN_TRUE;
        }

        else if (PyLong_Check(mem) || PyInt_Check(mem)) {
          if (triton::api.isMemoryTainted(PyLong_AsUint(mem)) == true)
            Py_RETURN_TRUE;
        }

        else
          return PyErr_Format(PyExc_TypeError, "isMemoryTainted(): Expects a Memory or an integer as argument.");

        Py_RETURN_FALSE;
      }


      static PyObject* triton_isRegisterTainted(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isRegisterTainted(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "isRegisterTainted(): Expects a REG as argument.");

        if (triton::api.isRegisterTainted(*PyRegisterOperand_AsRegisterOperand(reg)) == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isSymbolicEmulationEnabled(PyObject* self, PyObject* noarg) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isSymbolicEmulationEnabled(): Architecture is not defined.");

        if (triton::api.isSymbolicEmulationEnabled() == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isSymbolicEngineEnabled(PyObject* self, PyObject* noarg) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isSymbolicEngineEnabled(): Architecture is not defined.");

        if (triton::api.isSymbolicEngineEnabled() == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isSymbolicExpressionIdExists(PyObject* self, PyObject* symExprId) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isSymbolicExpressionIdExists(): Architecture is not defined.");

        if (!PyInt_Check(symExprId) && !PyLong_Check(symExprId))
          return PyErr_Format(PyExc_TypeError, "isSymbolicExpressionIdExists(): Expects an integer as argument.");

        if (triton::api.isSymbolicExpressionIdExists(PyLong_AsUint(symExprId)) == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isSymbolicOptimizationEnabled(PyObject* self, PyObject* opti) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isSymbolicOptimizationEnabled(): Architecture is not defined.");

        if (!PyInt_Check(opti) && !PyLong_Check(opti))
          return PyErr_Format(PyExc_TypeError, "isSymbolicOptimizationEnabled(): Expects an OPTIMIZATION as argument.");

        if (triton::api.isSymbolicOptimizationEnabled(static_cast<enum triton::engines::symbolic::optimization_e>(PyLong_AsUint(opti))) == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isSymbolicZ3SimplificationEnabled(PyObject* self, PyObject* noarg) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isSymbolicZ3SimplificationEnabled(): Architecture is not defined.");

        if (triton::api.isSymbolicZ3SimplificationEnabled() == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_isTaintEngineEnabled(PyObject* self, PyObject* noarg) {
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "isTaintEngineEnabled(): Architecture is not defined.");

        if (triton::api.isTaintEngineEnabled() == true)
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* triton_newSymbolicExpression(PyObject* self, PyObject* args) {
        PyObject* node          = nullptr;
        PyObject* comment       = nullptr;
        std::string ccomment    = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &node, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "newSymbolicExpression(): Architecture is not defined.");

        if (node == nullptr || (!PyAstNode_Check(node)))
          return PyErr_Format(PyExc_TypeError, "newSymbolicExpression(): Expects a AstNode as first argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "newSymbolicExpression(): Expects a sting as second argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        try {
          return PySymbolicExpression(triton::api.newSymbolicExpression(PyAstNode_AsAstNode(node), ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_newSymbolicVariable(PyObject* self, PyObject* args) {
        PyObject* size        = nullptr;
        PyObject* comment     = nullptr;
        std::string ccomment  = "";

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &size, &comment);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "newSymbolicVariable(): Architecture is not defined.");

        if (size == nullptr || (!PyLong_Check(size) && !PyInt_Check(size)))
          return PyErr_Format(PyExc_TypeError, "newSymbolicVariable(): Expects an integer as first argument.");

        if (comment != nullptr && !PyString_Check(comment))
          return PyErr_Format(PyExc_TypeError, "newSymbolicVariable(): Expects a sting as second  argument.");

        if (comment != nullptr)
          ccomment = PyString_AsString(comment);

        try {
          return PySymbolicVariable(triton::api.newSymbolicVariable(PyLong_AsUint(size), ccomment));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_processing(PyObject* self, PyObject* inst) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "processing(): Architecture is not defined.");

        if (!PyInstruction_Check(inst))
          return PyErr_Format(PyExc_TypeError, "processing(): Expects an Instruction as argument.");

        try {
          triton::api.processing(*PyInstruction_AsInstruction(inst));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_recordSimplificationCallback(PyObject* self, PyObject* cb) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "recordSimplificationCallback(): Architecture is not defined.");

        if (!PyCallable_Check(cb))
          return PyErr_Format(PyExc_TypeError, "recordSimplificationCallback(): Expects a callback function as argument.");

        try {
          triton::api.recordSimplificationCallback(cb);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_removeSimplificationCallback(PyObject* self, PyObject* cb) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "removeSimplificationCallback(): Architecture is not defined.");

        if (!PyCallable_Check(cb))
          return PyErr_Format(PyExc_TypeError, "removeSimplificationCallback(): Expects a callback function as argument.");

        try {
          triton::api.removeSimplificationCallback(cb);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_resetEngines(PyObject* self, PyObject* noarg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "resetEngines(): Architecture is not defined.");

        try {
          triton::api.resetEngines();
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setArchitecture(PyObject* self, PyObject* arg) {
        if (!PyLong_Check(arg) && !PyInt_Check(arg))
          return PyErr_Format(PyExc_TypeError, "setArchitecture(): Expects an ARCH as argument.");

        try {
          triton::api.setArchitecture(PyLong_AsUint(arg));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setAstRepresentationMode(PyObject* self, PyObject* arg) {
        if (!PyLong_Check(arg) && !PyInt_Check(arg))
          return PyErr_Format(PyExc_TypeError, "setArcsetAstRepresentationMode(): Expects an AST_REPRESENTATION as argument.");

        try {
          triton::api.setAstRepresentationMode(PyLong_AsUint(arg));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setLastMemoryAreaValue(PyObject* self, PyObject* args) {
        std::vector<triton::uint8> vv;
        PyObject* baseAddr  = nullptr;
        PyObject* values    = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &baseAddr, &values);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "setLastMemoryAreaValue(): Architecture is not defined.");

        if (baseAddr == nullptr || (!PyLong_Check(baseAddr) && !PyInt_Check(baseAddr)))
          return PyErr_Format(PyExc_TypeError, "setLastMemoryAreaValue(): Expects an integer as first argument.");

        if (values == nullptr || !PyList_Check(values))
          return PyErr_Format(PyExc_TypeError, "setLastMemoryAreaValue(): Expects a list as second argument.");

        for (Py_ssize_t i = 0; i < PyList_Size(values); i++) {
          PyObject* item = PyList_GetItem(values, i);

          if ((!PyLong_Check(item) && !PyInt_Check(item)) || PyLong_AsUint(item) > 0xff)
            return PyErr_Format(PyExc_TypeError, "setLastMemoryAreaValue(): Each item of the list must be a 8-bits integer.");

          vv.push_back(PyLong_AsUint(item));
        }

        try {
          triton::api.setLastMemoryAreaValue(PyLong_AsUint(baseAddr), vv);
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setLastMemoryValue(PyObject* self, PyObject* args) {
        PyObject* mem    = nullptr;
        PyObject* value  = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem, &value);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "setLastMemoryValue(): Architecture is not defined.");

        /* setLastMemoryValue(integer, integer) */
        if (mem != nullptr && (PyLong_Check(mem) || PyInt_Check(mem))) {
          if (value == nullptr || (!PyLong_Check(value) && !PyInt_Check(value)))
            return PyErr_Format(PyExc_TypeError, "setLastMemoryValue(): Expects a value as second argument.");

          triton::__uint addr = PyLong_AsUint(mem);
          triton::__uint cvalue = PyLong_AsUint(value);

          if (cvalue > 0xff)
            return PyErr_Format(PyExc_TypeError, "setLastMemoryValue(): Value must be on 8 bits.");

          try {
            triton::api.setLastMemoryValue(addr, cvalue);
          }
          catch (const std::exception& e) {
            return PyErr_Format(PyExc_TypeError, "%s", e.what());
          }

        }

        /* setLastMemoryValue(MemoryOperand) */
        else if (mem != nullptr && PyMemoryOperand_Check(mem)) {
          if (value != nullptr)
            return PyErr_Format(PyExc_TypeError, "setLastMemoryValue(): Expects no second argument.");
          try {
            triton::api.setLastMemoryValue(*PyMemoryOperand_AsMemoryOperand(mem));
          }
          catch (const std::exception& e) {
            return PyErr_Format(PyExc_TypeError, "%s", e.what());
          }
        }

        /* Invalid */
        else
          return PyErr_Format(PyExc_TypeError, "setLastMemoryValue(): Expects a Memory or an integer as first argument.");

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setLastRegisterValue(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "setLastRegisterValue(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "setLastRegisterValue(): Expects a REG as first argument.");

        try {
          triton::api.setLastRegisterValue(*PyRegisterOperand_AsRegisterOperand(reg));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }

        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* triton_setTaintMemory(PyObject* self, PyObject* args) {
        PyObject* mem    = nullptr;
        PyObject* flag   = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem, &flag);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "setTaintMemory(): Architecture is not defined.");

        if (mem == nullptr || !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "setTaintMemory(): Expects a Memory as first argument.");

        if (flag == nullptr || !PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "setTaintMemory(): Expects a boolean as second argument.");

        try {
          if (triton::api.setTaintMemory(*PyMemoryOperand_AsMemoryOperand(mem), PyLong_AsUint(flag)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_setTaintRegister(PyObject* self, PyObject* args) {
        PyObject* reg    = nullptr;
        PyObject* flag   = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg, &flag);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "setTaintRegister(): Architecture is not defined.");

        if (reg == nullptr || !PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "setTaintRegister(): Expects a REG as first argument.");

        if (flag == nullptr || !PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "setTaintRegister(): Expects a boolean as second argument.");

        try {
          if (triton::api.setTaintRegister(*PyRegisterOperand_AsRegisterOperand(reg), PyLong_AsUint(flag)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_simplify(PyObject* self, PyObject* args) {
        PyObject* node        = nullptr;
        PyObject* z3Flag      = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &node, &z3Flag);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "simplify(): Architecture is not defined.");

        if (node == nullptr || !PyAstNode_Check(node))
          return PyErr_Format(PyExc_TypeError, "simplify(): Expects a AstNode as first argument.");

        if (z3Flag != nullptr && !PyBool_Check(z3Flag))
          return PyErr_Format(PyExc_TypeError, "simplify(): Expects a boolean as second argument.");

        if (z3Flag == nullptr)
          z3Flag = PyLong_FromUint(false);

        try {
          return PyAstNode(triton::api.processSimplification(PyAstNode_AsAstNode(node), PyLong_AsUint(z3Flag)));
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentMemoryImmediate(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryImmediate(): Architecture is not defined.");

        if (!PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryImmediate(): Expects a Memory as argument.");

        try {
          if (triton::api.taintAssignmentMemoryImmediate(*PyMemoryOperand_AsMemoryOperand(mem)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentMemoryMemory(PyObject* self, PyObject* args) {
        PyObject* mem1 = nullptr;
        PyObject* mem2 = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem1, &mem2);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryMemory(): Architecture is not defined.");

        if (mem1 == nullptr || !PyMemoryOperand_Check(mem1))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryMemory(): Expects a Memory as first argument.");

        if (mem2 == nullptr || !PyMemoryOperand_Check(mem2))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryMemory(): Expects a Memory as second argument.");

        try {
          if (triton::api.taintAssignmentMemoryMemory(*PyMemoryOperand_AsMemoryOperand(mem1), *PyMemoryOperand_AsMemoryOperand(mem2)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentMemoryRegister(PyObject* self, PyObject* args) {
        PyObject* mem = nullptr;
        PyObject* reg = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem, &reg);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryRegister(): Architecture is not defined.");

        if (mem == nullptr || !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryRegister(): Expects a Memory as first argument.");

        if (reg == nullptr || !PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentMemoryRegister(): Expects a REG as second argument.");

        try {
          if (triton::api.taintAssignmentMemoryRegister(*PyMemoryOperand_AsMemoryOperand(mem), *PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentRegisterImmediate(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterImmediate(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterImmediate(): Expects a REG as argument.");

        try {
          if (triton::api.taintAssignmentRegisterImmediate(*PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentRegisterMemory(PyObject* self, PyObject* args) {
        PyObject* reg = nullptr;
        PyObject* mem = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg, &mem);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterMemory(): Architecture is not defined.");

        if (reg == nullptr || !PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterMemory(): Expects a REG as first argument.");

        if (mem == nullptr || !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterMemory(): Expects a Memory as second argument.");

        try {
          if (triton::api.taintAssignmentRegisterMemory(*PyRegisterOperand_AsRegisterOperand(reg), *PyMemoryOperand_AsMemoryOperand(mem)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintAssignmentRegisterRegister(PyObject* self, PyObject* args) {
        PyObject* reg1 = nullptr;
        PyObject* reg2 = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg1, &reg2);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterRegister(): Architecture is not defined.");

        if (reg1 == nullptr || !PyRegisterOperand_Check(reg1))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterRegister(): Expects a REG as first argument.");

        if (reg2 == nullptr || !PyRegisterOperand_Check(reg2))
          return PyErr_Format(PyExc_TypeError, "taintAssignmentRegisterRegister(): Expects a REG as second argument.");

        try {
          if (triton::api.taintAssignmentRegisterRegister(*PyRegisterOperand_AsRegisterOperand(reg1), *PyRegisterOperand_AsRegisterOperand(reg2)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintMemory(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintMemory(): Architecture is not defined.");

        try {
          if (PyMemoryOperand_Check(mem)) {
            if (triton::api.taintMemory(*PyMemoryOperand_AsMemoryOperand(mem)) == true)
              Py_RETURN_TRUE;
          }

          else if (PyLong_Check(mem) || PyInt_Check(mem)) {
            if (triton::api.taintMemory(PyLong_AsUint(mem)) == true)
              Py_RETURN_TRUE;
          }

          else
            return PyErr_Format(PyExc_TypeError, "taintMemory(): Expects a Memory or an integer as argument.");
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
        Py_RETURN_FALSE;
      }


      static PyObject* triton_taintRegister(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintRegister(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintRegister(): Expects a Memory as argument.");

        try {
          if (triton::api.taintRegister(*PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionMemoryImmediate(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryImmediate(): Architecture is not defined.");

        if (!PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryImmediate(): Expects a Memory as argument.");

        try {
          if (triton::api.taintUnionMemoryImmediate(*PyMemoryOperand_AsMemoryOperand(mem)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionMemoryMemory(PyObject* self, PyObject* args) {
        PyObject* mem1 = nullptr;
        PyObject* mem2 = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem1, &mem2);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryMemory(): Architecture is not defined.");

        if (mem1 == nullptr || !PyMemoryOperand_Check(mem1))
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryMemory(): Expects a Memory as first argument.");

        if (mem2 == nullptr || !PyMemoryOperand_Check(mem2))
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryMemory(): Expects a Memory as second argument.");

        try {
          if (triton::api.taintUnionMemoryMemory(*PyMemoryOperand_AsMemoryOperand(mem1), *PyMemoryOperand_AsMemoryOperand(mem2)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionMemoryRegister(PyObject* self, PyObject* args) {
        PyObject* mem = nullptr;
        PyObject* reg = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &mem, &reg);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryRegister(): Architecture is not defined.");

        if (mem == nullptr || !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryRegister(): Expects a Memory as first argument.");

        if (reg == nullptr || !PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintUnionMemoryRegister(): Expects a REG as second argument.");

        try {
          if (triton::api.taintUnionMemoryRegister(*PyMemoryOperand_AsMemoryOperand(mem), *PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionRegisterImmediate(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterImmediate(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterImmediate(): Expects a REG as argument.");

        try {
          if (triton::api.taintUnionRegisterImmediate(*PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionRegisterMemory(PyObject* self, PyObject* args) {
        PyObject* reg = nullptr;
        PyObject* mem = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg, &mem);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterMemory(): Architecture is not defined.");

        if (reg == nullptr || !PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterMemory(): Expects a REG as first argument.");

        if (mem == nullptr || !PyMemoryOperand_Check(mem))
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterMemory(): Expects a Memory as second argument.");

        try {
          if (triton::api.taintUnionRegisterMemory(*PyRegisterOperand_AsRegisterOperand(reg), *PyMemoryOperand_AsMemoryOperand(mem)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_taintUnionRegisterRegister(PyObject* self, PyObject* args) {
        PyObject* reg1 = nullptr;
        PyObject* reg2 = nullptr;

        /* Extract arguments */
        PyArg_ParseTuple(args, "|OO", &reg1, &reg2);

        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterRegister(): Architecture is not defined.");

        if (reg1 == nullptr || !PyRegisterOperand_Check(reg1))
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterRegister(): Expects a REG as first argument.");

        if (reg2 == nullptr || !PyRegisterOperand_Check(reg2))
          return PyErr_Format(PyExc_TypeError, "taintUnionRegisterRegister(): Expects a REG as second argument.");

        try {
          if (triton::api.taintUnionRegisterRegister(*PyRegisterOperand_AsRegisterOperand(reg1), *PyRegisterOperand_AsRegisterOperand(reg2)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      static PyObject* triton_untaintMemory(PyObject* self, PyObject* mem) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "untaintMemory(): Architecture is not defined.");

        try {
          if (PyMemoryOperand_Check(mem)) {
            if (triton::api.untaintMemory(*PyMemoryOperand_AsMemoryOperand(mem)) == true)
              Py_RETURN_TRUE;
          }

          else if (PyLong_Check(mem) || PyInt_Check(mem)) {
            if (triton::api.untaintMemory(PyLong_AsUint(mem)) == true)
              Py_RETURN_TRUE;
          }

          else
            return PyErr_Format(PyExc_TypeError, "untaintMemory(): Expects a Memory or an integer as argument.");
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
        Py_RETURN_FALSE;
      }


      static PyObject* triton_untaintRegister(PyObject* self, PyObject* reg) {
        /* Check if the architecture is definied */
        if (triton::api.getArchitecture() == triton::arch::ARCH_INVALID)
          return PyErr_Format(PyExc_TypeError, "untaintRegister(): Architecture is not defined.");

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "untaintRegister(): Expects a Memory as argument.");

        try {
          if (triton::api.untaintRegister(*PyRegisterOperand_AsRegisterOperand(reg)) == true)
            Py_RETURN_TRUE;
          Py_RETURN_FALSE;
        }
        catch (const std::exception& e) {
          return PyErr_Format(PyExc_TypeError, "%s", e.what());
        }
      }


      PyMethodDef tritonCallbacks[] = {
        {"Bitvector",                           (PyCFunction)triton_Bitvector,                              METH_VARARGS,       ""},
        {"Immediate",                           (PyCFunction)triton_Immediate,                              METH_VARARGS,       ""},
        {"Instruction",                         (PyCFunction)triton_Instruction,                            METH_NOARGS,        ""},
        {"Memory",                              (PyCFunction)triton_Memory,                                 METH_VARARGS,       ""},
        {"Register",                            (PyCFunction)triton_Register,                               METH_VARARGS,       ""},
        {"assignSymbolicExpressionToMemory",    (PyCFunction)triton_assignSymbolicExpressionToMemory,       METH_VARARGS,       ""},
        {"assignSymbolicExpressionToRegister",  (PyCFunction)triton_assignSymbolicExpressionToRegister,     METH_VARARGS,       ""},
        {"buildSemantics",                      (PyCFunction)triton_buildSemantics,                         METH_O,             ""},
        {"buildSymbolicImmediate",              (PyCFunction)triton_buildSymbolicImmediate,                 METH_O,             ""},
        {"buildSymbolicMemory",                 (PyCFunction)triton_buildSymbolicMemory,                    METH_O,             ""},
        {"buildSymbolicRegister",               (PyCFunction)triton_buildSymbolicRegister,                  METH_O,             ""},
        {"clearPathConstraints",                (PyCFunction)triton_clearPathConstraints,                   METH_NOARGS,        ""},
        {"concretizeAllMemory",                 (PyCFunction)triton_concretizeAllMemory,                    METH_NOARGS,        ""},
        {"concretizeAllRegister",               (PyCFunction)triton_concretizeAllRegister,                  METH_NOARGS,        ""},
        {"concretizeMemory",                    (PyCFunction)triton_concretizeMemory,                       METH_O,             ""},
        {"concretizeRegister",                  (PyCFunction)triton_concretizeRegister,                     METH_O,             ""},
        {"convertExpressionToSymbolicVariable", (PyCFunction)triton_convertExpressionToSymbolicVariable,    METH_VARARGS,       ""},
        {"convertMemoryToSymbolicVariable",     (PyCFunction)triton_convertMemoryToSymbolicVariable,        METH_VARARGS,       ""},
        {"convertRegisterToSymbolicVariable",   (PyCFunction)triton_convertRegisterToSymbolicVariable,      METH_VARARGS,       ""},
        {"cpuInvalidRegister",                  (PyCFunction)triton_cpuInvalidRegister,                     METH_NOARGS,        ""},
        {"cpuRegisterBitSize",                  (PyCFunction)triton_cpuRegisterBitSize,                     METH_NOARGS,        ""},
        {"cpuRegisterSize",                     (PyCFunction)triton_cpuRegisterSize,                        METH_NOARGS,        ""},
        {"createSymbolicFlagExpression",        (PyCFunction)triton_createSymbolicFlagExpression,           METH_VARARGS,       ""},
        {"createSymbolicMemoryExpression",      (PyCFunction)triton_createSymbolicMemoryExpression,         METH_VARARGS,       ""},
        {"createSymbolicRegisterExpression",    (PyCFunction)triton_createSymbolicRegisterExpression,       METH_VARARGS,       ""},
        {"createSymbolicVolatileExpression",    (PyCFunction)triton_createSymbolicVolatileExpression,       METH_VARARGS,       ""},
        {"disassembly",                         (PyCFunction)triton_disassembly,                            METH_O,             ""},
        {"enableSymbolicEmulation",             (PyCFunction)triton_enableSymbolicEmulation,                METH_O,             ""},
        {"enableSymbolicEngine",                (PyCFunction)triton_enableSymbolicEngine,                   METH_O,             ""},
        {"enableSymbolicOptimization",          (PyCFunction)triton_enableSymbolicOptimization,             METH_VARARGS,       ""},
        {"enableSymbolicZ3Simplification",      (PyCFunction)triton_enableSymbolicZ3Simplification,         METH_O,             ""},
        {"enableTaintEngine",                   (PyCFunction)triton_enableTaintEngine,                      METH_O,             ""},
        {"evaluateAstViaZ3",                    (PyCFunction)triton_evaluateAstViaZ3,                       METH_O,             ""},
        {"getAllRegisters",                     (PyCFunction)triton_getAllRegisters,                        METH_NOARGS,        ""},
        {"getArchitecture",                     (PyCFunction)triton_getArchitecture,                        METH_NOARGS,        ""},
        {"getAstFromId",                        (PyCFunction)triton_getAstFromId,                           METH_O,             ""},
        {"getAstRepresentationMode",            (PyCFunction)triton_getAstRepresentationMode,               METH_NOARGS,        ""},
        {"getAstDictionariesStats",             (PyCFunction)triton_getAstDictionariesStats,                METH_NOARGS,        ""},
        {"getFullAst",                          (PyCFunction)triton_getFullAst,                             METH_O,             ""},
        {"getFullAstFromId",                    (PyCFunction)triton_getFullAstFromId,                       METH_O,             ""},
        {"getMemoryAreaValue",                  (PyCFunction)triton_getMemoryAreaValue,                     METH_VARARGS,       ""},
        {"getMemoryValue",                      (PyCFunction)triton_getMemoryValue,                         METH_O,             ""},
        {"getModel",                            (PyCFunction)triton_getModel,                               METH_O,             ""},
        {"getModels",                           (PyCFunction)triton_getModels,                              METH_VARARGS,       ""},
        {"getParentRegisters",                  (PyCFunction)triton_getParentRegisters,                     METH_NOARGS,        ""},
        {"getPathConstraints",                  (PyCFunction)triton_getPathConstraints,                     METH_NOARGS,        ""},
        {"getPathConstraintsAst",               (PyCFunction)triton_getPathConstraintsAst,                  METH_NOARGS,        ""},
        {"getRegisterValue",                    (PyCFunction)triton_getRegisterValue,                       METH_O,             ""},
        {"getSymbolicExpressionFromId",         (PyCFunction)triton_getSymbolicExpressionFromId,            METH_O,             ""},
        {"getSymbolicExpressions",              (PyCFunction)triton_getSymbolicExpressions,                 METH_NOARGS,        ""},
        {"getSymbolicMemory",                   (PyCFunction)triton_getSymbolicMemory,                      METH_NOARGS,        ""},
        {"getSymbolicMemoryId",                 (PyCFunction)triton_getSymbolicMemoryId,                    METH_O,             ""},
        {"getSymbolicMemoryValue",              (PyCFunction)triton_getSymbolicMemoryValue,                 METH_O,             ""},
        {"getSymbolicRegisterId",               (PyCFunction)triton_getSymbolicRegisterId,                  METH_O,             ""},
        {"getSymbolicRegisterValue",            (PyCFunction)triton_getSymbolicRegisterValue,               METH_O,             ""},
        {"getSymbolicRegisters",                (PyCFunction)triton_getSymbolicRegisters,                   METH_NOARGS,        ""},
        {"getSymbolicVariableFromId",           (PyCFunction)triton_getSymbolicVariableFromId,              METH_O,             ""},
        {"getSymbolicVariableFromName",         (PyCFunction)triton_getSymbolicVariableFromName,            METH_O,             ""},
        {"getSymbolicVariables",                (PyCFunction)triton_getSymbolicVariables,                   METH_NOARGS,        ""},
        {"getTaintedSymbolicExpressions",       (PyCFunction)triton_getTaintedSymbolicExpressions,          METH_NOARGS,        ""},
        {"isArchitectureValid",                 (PyCFunction)triton_isArchitectureValid,                    METH_NOARGS,        ""},
        {"isMemoryTainted",                     (PyCFunction)triton_isMemoryTainted,                        METH_O,             ""},
        {"isRegisterTainted",                   (PyCFunction)triton_isRegisterTainted,                      METH_O,             ""},
        {"isSymbolicEmulationEnabled",          (PyCFunction)triton_isSymbolicEmulationEnabled,             METH_NOARGS,        ""},
        {"isSymbolicEngineEnabled",             (PyCFunction)triton_isSymbolicEngineEnabled,                METH_NOARGS,        ""},
        {"isSymbolicExpressionIdExists",        (PyCFunction)triton_isSymbolicExpressionIdExists,           METH_O,             ""},
        {"isSymbolicOptimizationEnabled",       (PyCFunction)triton_isSymbolicOptimizationEnabled,          METH_O,             ""},
        {"isSymbolicZ3SimplificationEnabled",   (PyCFunction)triton_isSymbolicZ3SimplificationEnabled,      METH_NOARGS,        ""},
        {"isTaintEngineEnabled",                (PyCFunction)triton_isTaintEngineEnabled,                   METH_NOARGS,        ""},
        {"newSymbolicExpression",               (PyCFunction)triton_newSymbolicExpression,                  METH_VARARGS,       ""},
        {"newSymbolicVariable",                 (PyCFunction)triton_newSymbolicVariable,                    METH_VARARGS,       ""},
        {"processing",                          (PyCFunction)triton_processing,                             METH_O,             ""},
        {"recordSimplificationCallback",        (PyCFunction)triton_recordSimplificationCallback,           METH_O,             ""},
        {"removeSimplificationCallback",        (PyCFunction)triton_removeSimplificationCallback,           METH_O,             ""},
        {"resetEngines",                        (PyCFunction)triton_resetEngines,                           METH_NOARGS,        ""},
        {"setArchitecture",                     (PyCFunction)triton_setArchitecture,                        METH_O,             ""},
        {"setAstRepresentationMode",            (PyCFunction)triton_setAstRepresentationMode,               METH_O,             ""},
        {"setLastMemoryAreaValue",              (PyCFunction)triton_setLastMemoryAreaValue,                 METH_VARARGS,       ""},
        {"setLastMemoryValue",                  (PyCFunction)triton_setLastMemoryValue,                     METH_VARARGS,       ""},
        {"setLastRegisterValue",                (PyCFunction)triton_setLastRegisterValue,                   METH_O,             ""},
        {"setTaintMemory",                      (PyCFunction)triton_setTaintMemory,                         METH_VARARGS,       ""},
        {"setTaintRegister",                    (PyCFunction)triton_setTaintRegister,                       METH_VARARGS,       ""},
        {"simplify",                            (PyCFunction)triton_simplify,                               METH_VARARGS,       ""},
        {"taintAssignmentMemoryImmediate",      (PyCFunction)triton_taintAssignmentMemoryImmediate,         METH_O,             ""},
        {"taintAssignmentMemoryMemory",         (PyCFunction)triton_taintAssignmentMemoryMemory,            METH_VARARGS,       ""},
        {"taintAssignmentMemoryRegister",       (PyCFunction)triton_taintAssignmentMemoryRegister,          METH_VARARGS,       ""},
        {"taintAssignmentRegisterImmediate",    (PyCFunction)triton_taintAssignmentRegisterImmediate,       METH_O,             ""},
        {"taintAssignmentRegisterMemory",       (PyCFunction)triton_taintAssignmentRegisterMemory,          METH_VARARGS,       ""},
        {"taintAssignmentRegisterRegister",     (PyCFunction)triton_taintAssignmentRegisterRegister,        METH_VARARGS,       ""},
        {"taintMemory",                         (PyCFunction)triton_taintMemory,                            METH_O,             ""},
        {"taintRegister",                       (PyCFunction)triton_taintRegister,                          METH_O,             ""},
        {"taintUnionMemoryImmediate",           (PyCFunction)triton_taintUnionMemoryImmediate,              METH_O,             ""},
        {"taintUnionMemoryMemory",              (PyCFunction)triton_taintUnionMemoryMemory,                 METH_VARARGS,       ""},
        {"taintUnionMemoryRegister",            (PyCFunction)triton_taintUnionMemoryRegister,               METH_VARARGS,       ""},
        {"taintUnionRegisterImmediate",         (PyCFunction)triton_taintUnionRegisterImmediate,            METH_O,             ""},
        {"taintUnionRegisterMemory",            (PyCFunction)triton_taintUnionRegisterMemory,               METH_VARARGS,       ""},
        {"taintUnionRegisterRegister",          (PyCFunction)triton_taintUnionRegisterRegister,             METH_VARARGS,       ""},
        {"untaintMemory",                       (PyCFunction)triton_untaintMemory,                          METH_O,             ""},
        {"untaintRegister",                     (PyCFunction)triton_untaintRegister,                        METH_O,             ""},
        {nullptr,                               nullptr,                                                    0,                  nullptr}

      };

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */

#endif /* TRITON_PYTHON_BINDINGS */

