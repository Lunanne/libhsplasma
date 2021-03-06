/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pyResponderModifier.h"

#include <PRP/Modifier/plResponderModifier.h>
#include "PRP/Message/pyMessage.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ResponderEnableMsg, plResponderEnableMsg)

PY_PROPERTY(bool, ResponderEnableMsg, enable, getEnable, setEnable)

static PyGetSetDef pyResponderEnableMsg_GetSet[] = {
    pyResponderEnableMsg_enable_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ResponderEnableMsg, plResponderEnableMsg, "plResponderEnableMsg wrapper")

PY_PLASMA_TYPE_INIT(ResponderEnableMsg) {
    pyResponderEnableMsg_Type.tp_new = pyResponderEnableMsg_new;
    pyResponderEnableMsg_Type.tp_getset = pyResponderEnableMsg_GetSet;
    pyResponderEnableMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyResponderEnableMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyResponderEnableMsg_Type);
    return (PyObject*)&pyResponderEnableMsg_Type;
}

PY_PLASMA_IFC_METHODS(ResponderEnableMsg, plResponderEnableMsg)
