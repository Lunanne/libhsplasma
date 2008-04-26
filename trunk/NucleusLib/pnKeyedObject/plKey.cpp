#include <stdlib.h>
#include <string.h>
#include "plKey.h"
#include "hsKeyedObject.h"
#include "CoreLib/plDebug.h"

plKeyData::plKeyData() : fUoid(), fObjPtr(NULL), fFileOff(0), fObjSize(0),
                         fRefCnt(0) { }

plKeyData::~plKeyData() {
    if (fObjPtr != NULL) {
		Ref();
        delete fObjPtr;
		--fRefCnt;  // Under absolutely NO circumstance replace this with UnRef()
	}
}

bool plKeyData::operator==(plKeyData& other) const {
    return (fUoid == other.fUoid);
}

plString plKeyData::toString() const {
    return fUoid.toString();
}

void plKeyData::read(hsStream* S) {
    fUoid.read(S);
    fFileOff = S->readInt();
    fObjSize = S->readInt();
}

void plKeyData::write(hsStream* S) {
    fUoid.write(S);
    S->writeInt(fFileOff);
    S->writeInt(fObjSize);
}

void plKeyData::readUoid(hsStream* S) {
    fUoid.read(S);
}

void plKeyData::writeUoid(hsStream* S) {
    fUoid.write(S);
}

void plKeyData::prcWrite(pfPrcHelper* prc) {
    if (this == NULL || !getUoid().getLocation().isValid()) {
        prc->startTag("plKey");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        fUoid.prcWrite(prc);
    }
}

plUoid& plKeyData::getUoid() { return fUoid; }
class hsKeyedObject* plKeyData::getObj() { return fObjPtr; }
void plKeyData::setObj(class hsKeyedObject* obj) { fObjPtr = obj; }
short plKeyData::getType() const { return fUoid.getType(); }
const PageID& plKeyData::getPageID() const { return fUoid.getPageID(); }
const plString& plKeyData::getName() const { return fUoid.getName(); }
hsUint32 plKeyData::getID() const { return fUoid.getID(); }
void plKeyData::setID(hsUint32 id) { fUoid.setID(id); }
hsUint32 plKeyData::getFileOff() const { return fFileOff; }
void plKeyData::setFileOff(hsUint32 off) { fFileOff = off; }
hsUint32 plKeyData::getObjSize() const { return fObjSize; }
void plKeyData::setObjSize(hsUint32 size) { fObjSize = size; }

hsUint32 plKeyData::RefCnt() const { return fRefCnt; }
hsUint32 plKeyData::Ref() { return ++fRefCnt; }
hsUint32 plKeyData::UnRefNoDelete() { return --fRefCnt; }
void plKeyData::UnRef() {
    if (--fRefCnt == 0) {
        plDebug::Debug("Key %s no longer in use, deleting...", toString().cstr());
        delete this;
    }
}

// plKey //
plKey::plKey() { }

plKey::plKey(const plWeakKey& init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::plKey(const plKey& init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::plKey(plKeyData* init) : plWeakKey(init) {
    if (fKeyData) fKeyData->Ref();
}

plKey::~plKey() {
    if (fKeyData) fKeyData->UnRef();
}

plKeyData& plWeakKey::operator*() const { return *fKeyData; }
plKeyData* plWeakKey::operator->() const { return fKeyData; }
plWeakKey::operator plKeyData*() const { return fKeyData; }

plKey& plKey::operator=(const plWeakKey& other) {
    if (*this != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        *this = other;
    }
    return *this;
}

plKey& plKey::operator=(const plKey& other) {
    if (*this != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}

plKey& plKey::operator=(plKeyData* other) {
    if (fKeyData != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}

bool plWeakKey::operator==(const plWeakKey& other) const {
    return fKeyData == other.fKeyData;
}

bool plWeakKey::operator==(const plKeyData* other) const {
    return fKeyData == other;
}

bool plWeakKey::operator!=(const plWeakKey& other) const {
    return fKeyData != other.fKeyData;
}

bool plWeakKey::operator!=(const plKeyData* other) const {
    return fKeyData != other;
}

bool plWeakKey::operator<(const plWeakKey& other) const {
    return fKeyData->getUoid() < other->getUoid();
}

bool plWeakKey::Exists() const {
    return (fKeyData != NULL) && (fKeyData->getUoid().getLocation().isValid());
}

bool plWeakKey::isLoaded() const {
    if (!Exists())
        return true;
    return fKeyData->getObj() != NULL;
}
