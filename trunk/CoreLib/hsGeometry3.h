#ifndef _HSGEOMETRY3_H
#define _HSGEOMETRY3_H

#include "hsStream.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

DllStruct hsScalarTriple {
public:
    float fX, fY, fZ;

public:
    hsScalarTriple();
    hsScalarTriple(float x, float y, float z);
    virtual ~hsScalarTriple();

    virtual const char* ClassName();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllStruct hsPoint3 : public hsScalarTriple {
public:
    hsPoint3();
    hsPoint3(float x, float y, float z);
    hsPoint3(const hsScalarTriple& src);
    virtual ~hsPoint3();
    
    virtual const char* ClassName();

    void Zero();

    hsPoint3& operator=(const hsPoint3& other);
    bool operator==(const hsPoint3 & other);
    hsPoint3 operator+(const hsPoint3& other);
    hsPoint3 operator*(const hsPoint3& other);
    hsPoint3 operator*(const float mult);
};

DllStruct hsVector3 : hsScalarTriple {
public:
    hsVector3(const hsScalarTriple& src);
    hsVector3(float x, float y, float z);
    hsVector3();
    virtual ~hsVector3();
    
    virtual const char* ClassName();
};

DllStruct hsPlane3 {
public:
    hsVector3 fN;
    float fD;

public:
    hsPlane3();
    ~hsPlane3();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllStruct hsFloatPoint2 {
public:
    float fX, fY;
};

#endif

