#include <Python.h>
#include <PRP/Surface/plLayerMovie.h>
#include "pyLayerMovie.h"
#include "pyLayerAnimation.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyLayerMovie_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayerMovie* self = (pyLayerMovie*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayerMovie();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayerMovie_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLayerMovie_FromLayerMovie(plLayerMovie::Convert(cre->fThis));
}

static PyObject* pyLayerMovie_getMovieName(pyLayerMovie* self, void*) {
    return PyString_FromString(self->fThis->getMovieName().cstr());
}

static int pyLayerMovie_setMovieName(pyLayerMovie* self, PyObject* value, void*) {
    if (value == NULL || !PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "movieName should be a string");
        return -1;
    }
    self->fThis->setMovieName(PyString_AsString(value));
    return 0;
}

static PyMethodDef pyLayerMovie_Methods[] = {
    { "Convert", (PyCFunction)pyLayerMovie_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLayerMovie" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayerMovie_GetSet[] = {
    { "movieName", (getter)pyLayerMovie_getMovieName, (setter)pyLayerMovie_setMovieName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayerMovie_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plLayerMovie",            /* tp_name */
    sizeof(pyLayerMovie),               /* tp_basicsize */
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
    "plLayerMovie wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayerMovie_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyLayerMovie_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayerMovie_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLayerMovie_Type() {
    pyLayerMovie_Type.tp_base = &pyLayerAnimation_Type;
    if (PyType_Ready(&pyLayerMovie_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayerMovie_Type);
    return (PyObject*)&pyLayerMovie_Type;
}

int pyLayerMovie_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayerMovie_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayerMovie_Type))
        return 1;
    return 0;
}

PyObject* pyLayerMovie_FromLayerMovie(class plLayerMovie* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayerMovie* pyobj = PyObject_New(pyLayerMovie, &pyLayerMovie_Type);
    pyobj->fThis = layer;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
