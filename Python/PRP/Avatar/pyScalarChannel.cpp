#include <Python.h>
#include <PRP/Avatar/plScalarChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyScalarChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarChannel* self = (pyScalarChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarChannel_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScalarChannel_FromScalarChannel(plScalarChannel::Convert(cre->fThis));
}

static PyObject* pyScalarChannel_getResult(pyScalarChannel* self, void*) {
    return PyFloat_FromDouble(self->fThis->getResult());
}

static int pyScalarChannel_setResult(pyScalarChannel* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "result should be a float");
        return -1;
    }
    self->fThis->setResult(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyScalarChannel_Methods[] = {
    { "Convert", (PyCFunction)pyScalarChannel_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScalarChannel" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyScalarChannel_GetSet[] = {
    { "result", (getter)pyScalarChannel_getResult, (setter)pyScalarChannel_setResult, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScalarChannel_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plScalarChannel",         /* tp_name */
    sizeof(pyScalarChannel),            /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plScalarChannel wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarChannel_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyScalarChannel_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarChannel_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScalarChannel_Type() {
    pyScalarChannel_Type.tp_base = &pyAGChannel_Type;
    if (PyType_Ready(&pyScalarChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarChannel_Type);
    return (PyObject*)&pyScalarChannel_Type;
}

int pyScalarChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarChannel_Type))
        return 1;
    return 0;
}

PyObject* pyScalarChannel_FromScalarChannel(class plScalarChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarChannel* pyobj = PyObject_New(pyScalarChannel, &pyScalarChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}