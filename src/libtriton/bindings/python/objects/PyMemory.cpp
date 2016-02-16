//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifdef TRITON_PYTHON_BINDINGS

#include <memoryOperand.hpp>
#include <pythonObjects.hpp>
#include <pythonUtils.hpp>
#include <pythonXFunctions.hpp>



/*! \page py_Memory_page Memory
    \brief [**python api**] All information about the Memory python object.

\tableofcontents

\section py_Memory_description Description
<hr>

This object is used to represent a memory access operand.

~~~~~~~~~~~~~{.py}
>>> from triton import Memory
>>>
>>> mem = Memory(0x400f4d3, 8, 0x6162636465666768)
>>> hex(mem.getAddress())
'0x400f4d3'
>>> mem.getSize()
8
>>> hex(mem.getConcreteValue())
'0x6162636465666768L'

>>> from struct import pack
>>> pack("<Q", mem.getConcreteValue())
'hgfedcba'

>>> mem = Memory(0x400f4d3, 16)
>>> print mem
*[0x400f4d3]:128 bv[127..0]
>>> mem.getConcreteValue()
0L
~~~~~~~~~~~~~

\section Memory_py_api Python API - Methods of the Memory class
<hr>

- **getAddress(void)**<br>
Returns the target address of the memory access.<br>
e.g: `0x7fffdd745ae0`

- **getBaseRegister(void)**<br>
Returns the base register (if exists) of the  memory access as \ref py_Register_page.<br>

- **getBitSize(void)**<br>
Returns the size (in bits) of the memory access as integer.<br>
e.g: `64`

- **getBitvector(void)**<br>
Returns the bitvector as \ref py_Bitvector_page.

- **getConcreteValue(void)**<br>
Returns the concrete value as integer. It's basically the content which has been LOADED or STORED.

- **getDisplacement(void)**<br>
Returns the displacement (if exists) of the memory access as \ref py_Immediate_page.

- **getIndexRegister(void)**<br>
Returns the index register (if exists) of the memory access as \ref py_Register_page.<br>

- **getScale(void)**<br>
Returns the scale (if exists) of the  memory access as \ref py_Immediate_page.

- **getSize(void)**<br>
Returns the size (in bytes) of the  memory access as integer.<br>
e.g: `8`

- **getType(void)**<br>
Returns type of the memory access as \ref py_OPERAND_page.

- **isTrusted(void)**<br>
True if this concrete memory value is trusted and synchronized with the real MMU value.

- **setBaseRegister(\ref py_Register_page reg)**<br>
Sets the base register of the memory access.

- **setConcreteValue(integer value)**<br>
Sets a concrete value to this memory access.

- **setDisplacement(\ref py_Immediate_page imm)**<br>
Sets the displacement of the memory access.

- **setIndexRegister(\ref py_Register_page reg)**<br>
Sets the index register of the memory' access.

- **setScale(\ref py_Immediate_page imm)**<br>
Sets the scale of the memory access.

- **setTrust(bool flag)**<br>
Sets the trust flag.

*/



namespace triton {
  namespace bindings {
    namespace python {

      //! Memory destructor.
      void MemoryOperand_dealloc(PyObject* self) {
        delete PyMemoryOperand_AsMemoryOperand(self);
        Py_DECREF(self);
      }


      static PyObject* MemoryOperand_getAddress(PyObject* self, PyObject* noarg) {
        return PyLong_FromUint(PyMemoryOperand_AsMemoryOperand(self)->getAddress());
      }


      static PyObject* MemoryOperand_getBaseRegister(PyObject* self, PyObject* noarg) {
        triton::arch::RegisterOperand reg(PyMemoryOperand_AsMemoryOperand(self)->getBaseRegister());
        return PyRegisterOperand(reg);
      }


      static PyObject* MemoryOperand_getBitSize(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", PyMemoryOperand_AsMemoryOperand(self)->getBitSize());
      }


      static PyObject* MemoryOperand_getBitvector(PyObject* self, PyObject* noarg) {
        return PyBitvector(*PyMemoryOperand_AsMemoryOperand(self));
      }


      static PyObject* MemoryOperand_getConcreteValue(PyObject* self, PyObject* noarg) {
        return PyLong_FromUint128(PyMemoryOperand_AsMemoryOperand(self)->getConcreteValue());
      }


      static PyObject* MemoryOperand_getDisplacement(PyObject* self, PyObject* noarg) {
        triton::arch::ImmediateOperand imm(PyMemoryOperand_AsMemoryOperand(self)->getDisplacement());
        return PyImmediateOperand(imm);
      }


      static PyObject* MemoryOperand_getIndexRegister(PyObject* self, PyObject* noarg) {
        triton::arch::RegisterOperand reg(PyMemoryOperand_AsMemoryOperand(self)->getIndexRegister());
        return PyRegisterOperand(reg);
      }


      static PyObject* MemoryOperand_getScale(PyObject* self, PyObject* noarg) {
        triton::arch::ImmediateOperand imm(PyMemoryOperand_AsMemoryOperand(self)->getScale());
        return PyImmediateOperand(imm);
      }


      static PyObject* MemoryOperand_getSize(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", PyMemoryOperand_AsMemoryOperand(self)->getSize());
      }


      static PyObject* MemoryOperand_getType(PyObject* self, PyObject* noarg) {
        return Py_BuildValue("k", PyMemoryOperand_AsMemoryOperand(self)->getType());
      }


      static PyObject* MemoryOperand_isTrusted(PyObject* self, PyObject* noarg) {
        if (PyMemoryOperand_AsMemoryOperand(self)->isTrusted())
          Py_RETURN_TRUE;
        Py_RETURN_FALSE;
      }


      static PyObject* MemoryOperand_setBaseRegister(PyObject* self, PyObject* reg) {
        triton::arch::MemoryOperand *mem;

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "Memory::setBaseRegister(): Expected a Register as argument.");

        mem = PyMemoryOperand_AsMemoryOperand(self);
        mem->setBaseRegister(*PyRegisterOperand_AsRegisterOperand(reg));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* MemoryOperand_setConcreteValue(PyObject* self, PyObject* value) {
        triton::arch::MemoryOperand *mem;

        if (!PyLong_Check(value) && !PyInt_Check(value))
          return PyErr_Format(PyExc_TypeError, "Memory::setConcretevalue(): Expected an integer as argument.");

        mem = PyMemoryOperand_AsMemoryOperand(self);
        mem->setConcreteValue(PyLong_AsUint128(value));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* MemoryOperand_setDisplacement(PyObject* self, PyObject* imm) {
        triton::arch::MemoryOperand *mem;

        if (!PyImmediateOperand_Check(imm))
          return PyErr_Format(PyExc_TypeError, "Memory::setDisplacement(): Expected an Immediate as argument.");

        mem = PyMemoryOperand_AsMemoryOperand(self);
        mem->setDisplacement(*PyImmediateOperand_AsImmediateOperand(imm));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* MemoryOperand_setIndexRegister(PyObject* self, PyObject* reg) {
        triton::arch::MemoryOperand *mem;

        if (!PyRegisterOperand_Check(reg))
          return PyErr_Format(PyExc_TypeError, "Memory::setIndexRegister(): Expected a Register as argument.");

        mem = PyMemoryOperand_AsMemoryOperand(self);
        mem->setIndexRegister(*PyRegisterOperand_AsRegisterOperand(reg));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* MemoryOperand_setScale(PyObject* self, PyObject* imm) {
        triton::arch::MemoryOperand *mem;

        if (!PyImmediateOperand_Check(imm))
          return PyErr_Format(PyExc_TypeError, "Memory::setScale(): Expected an Immediate as argument.");

        mem = PyMemoryOperand_AsMemoryOperand(self);
        mem->setScale(*PyImmediateOperand_AsImmediateOperand(imm));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static PyObject* MemoryOperand_setTrust(PyObject* self, PyObject* flag) {
        if (!PyBool_Check(flag))
          return PyErr_Format(PyExc_TypeError, "Memory::setTrust(): Expected a boolean as argument.");
        PyMemoryOperand_AsMemoryOperand(self)->setTrust(PyLong_AsUint(flag));
        Py_INCREF(Py_None);
        return Py_None;
      }


      static int MemoryOperand_print(PyObject* self) {
        std::cout << PyMemoryOperand_AsMemoryOperand(self);
        return 0;
      }


      static PyObject* MemoryOperand_str(PyObject* self) {
        std::stringstream str;
        str << PyMemoryOperand_AsMemoryOperand(self);
        return PyString_FromFormat("%s", str.str().c_str());
      }


      //! Memory methods.
      PyMethodDef MemoryOperand_callbacks[] = {
        {"getAddress",        MemoryOperand_getAddress,       METH_NOARGS,      ""},
        {"getBaseRegister",   MemoryOperand_getBaseRegister,  METH_NOARGS,      ""},
        {"getBitSize",        MemoryOperand_getBitSize,       METH_NOARGS,      ""},
        {"getBitvector",      MemoryOperand_getBitvector,     METH_NOARGS,      ""},
        {"getConcreteValue",  MemoryOperand_getConcreteValue, METH_NOARGS,      ""},
        {"getDisplacement",   MemoryOperand_getDisplacement,  METH_NOARGS,      ""},
        {"getIndexRegister",  MemoryOperand_getIndexRegister, METH_NOARGS,      ""},
        {"getScale",          MemoryOperand_getScale,         METH_NOARGS,      ""},
        {"getSize",           MemoryOperand_getSize,          METH_NOARGS,      ""},
        {"getType",           MemoryOperand_getType,          METH_NOARGS,      ""},
        {"isTrusted",         MemoryOperand_isTrusted,        METH_NOARGS,      ""},
        {"setBaseRegister",   MemoryOperand_setBaseRegister,  METH_O,           ""},
        {"setConcreteValue",  MemoryOperand_setConcreteValue, METH_O,           ""},
        {"setDisplacement",   MemoryOperand_setDisplacement,  METH_O,           ""},
        {"setIndexRegister",  MemoryOperand_setIndexRegister, METH_O,           ""},
        {"setScale",          MemoryOperand_setScale,         METH_O,           ""},
        {"setTrust",          MemoryOperand_setTrust,         METH_O,           ""},
        {nullptr,             nullptr,                        0,                nullptr}
      };


      PyTypeObject MemoryOperand_Type = {
          PyObject_HEAD_INIT(&PyType_Type)
          0,                                          /* ob_size*/
          "Memory",                                   /* tp_name*/
          sizeof(MemoryOperand_Object),               /* tp_basicsize*/
          0,                                          /* tp_itemsize*/
          (destructor)MemoryOperand_dealloc,          /* tp_dealloc*/
          (printfunc)MemoryOperand_print,             /* tp_print*/
          0,                                          /* tp_getattr*/
          0,                                          /* tp_setattr*/
          0,                                          /* tp_compare*/
          0,                                          /* tp_repr*/
          0,                                          /* tp_as_number*/
          0,                                          /* tp_as_sequence*/
          0,                                          /* tp_as_mapping*/
          0,                                          /* tp_hash */
          0,                                          /* tp_call*/
          (reprfunc)MemoryOperand_str,                /* tp_str*/
          0,                                          /* tp_getattro*/
          0,                                          /* tp_setattro*/
          0,                                          /* tp_as_buffer*/
          Py_TPFLAGS_DEFAULT,                         /* tp_flags*/
          "Memory objects",                           /* tp_doc */
          0,                                          /* tp_traverse */
          0,                                          /* tp_clear */
          0,                                          /* tp_richcompare */
          0,                                          /* tp_weaklistoffset */
          0,                                          /* tp_iter */
          0,                                          /* tp_iternext */
          MemoryOperand_callbacks,                    /* tp_methods */
          0,                                          /* tp_members */
          0,                                          /* tp_getset */
          0,                                          /* tp_base */
          0,                                          /* tp_dict */
          0,                                          /* tp_descr_get */
          0,                                          /* tp_descr_set */
          0,                                          /* tp_dictoffset */
          0,                                          /* tp_init */
          0,                                          /* tp_alloc */
          0,                                          /* tp_new */
      };


      PyObject* PyMemoryOperand(triton::arch::MemoryOperand &mem) {
        MemoryOperand_Object *object;

        PyType_Ready(&MemoryOperand_Type);
        object = PyObject_NEW(MemoryOperand_Object, &MemoryOperand_Type);
        if (object != NULL)
          object->mem = new triton::arch::MemoryOperand(mem);

        return (PyObject* )object;
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */

#endif /* TRITON_PYTHON_BINDINGS */
