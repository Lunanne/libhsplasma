#include <Python.h>
#include <PRP/Surface/plLayerAnimation.h>
#include "pyLayerAnimation.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyLayerSDLAnimation_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayerSDLAnimation* self = (pyLayerSDLAnimation*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayerSDLAnimation();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayerSDLAnimation_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLayerSDLAnimation_FromLayerSDLAnimation(plLayerSDLAnimation::Convert(cre->fThis));
}

static PyObject* pyLayerSDLAnimation_getVarName(pyLayerSDLAnimation* self, void*) {
    return PyString_FromString(self->fThis->getVarName().cstr());
}

static int pyLayerSDLAnimation_setVarName(pyLayerSDLAnimation* self, PyObject* value, void*) {
    if (value == NULL || !PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "varName should be a string");
        return -1;
    }
    self->fThis->setVarName(PyString_AsString(value));
    return 0;
}

static PyMethodDef pyLayerSDLAnimation_Methods[] = {
    { "Convert", (PyCFunction)pyLayerSDLAnimation_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLayerSDLAnimation" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerSDLAnimation_GetSet[] = {
    { "varName", (getter)pyLayerSDLAnimation_getVarName, (setter)pyLayerSDLAnimation_setVarName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerSDLAnimation_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plLayerSDLAnimation",     /* tp_name */
    sizeof(pyLayerSDLAnimation),        /* tp_basicsize */
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
    "plLayerSDLAnimation wrapper",      /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerSDLAnimation_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerSDLAnimation_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerSDLAnimation_new,            /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLayerSDLAnimation_Type() {
    pyLayerSDLAnimation_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_Ready(&pyLayerSDLAnimation_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerSDLAnimation_Type);
    return (PyObject*)&pyLayerSDLAnimation_Type;
}

int pyLayerSDLAnimation_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerSDLAnimation_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerSDLAnimation_Type))
        return 1;
    return 0;
}

PyObject* pyLayerSDLAnimation_FromLayerSDLAnimation(class plLayerSDLAnimation* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerSDLAnimation* pyobj = PyObject_New(pyLayerSDLAnimation, &pyLayerSDLAnimation_Type);
    pyobj->fThis = layer;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
