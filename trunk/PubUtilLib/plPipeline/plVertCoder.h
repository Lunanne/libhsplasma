#ifndef _PLVERTCODER_H
#define _PLVERTCODER_H

#include "../../CoreLib/hsStream.h"

class plVertCoder {
public:
    enum { kPosition, kWeight, kUVW, kNumFloatFields = 10 };

    enum Formats {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40,
        kEncoded = 0x80
    };

    static float FieldScales[kNumFloatFields];

private:
    struct FloatCode {
        float fOffset;
        bool fAllSame;
        unsigned short fCount;
    } fFloats[3][kNumFloatFields];

    struct ByteCode {
        unsigned short fCount;
        unsigned char fVal;
        bool fSame;
    } fColors[4];

    void IDecode(hsStream* S, unsigned char*& dest,unsigned char format);
    void IDecodeByte(hsStream* S, int chan, unsigned char*& dest);
    void IDecodeFloat(hsStream* S, int field, int chan, unsigned char*& dest);
    void IDecodeNormal(hsStream* S, unsigned char*& dest);
    void IDecodeColor(hsStream* S, unsigned char*& dest);

    void IEncode(hsStream* S, unsigned int vertsLeft, const unsigned char*& src,
                 unsigned char format);
    void IEncodeByte(hsStream* S, unsigned int vertsLeft, int chan,
                     const unsigned char*& src);
    void IEncodeFloat(hsStream* S, unsigned int vertsLeft, int field, int chan,
                      const unsigned char*& src);
    void IEncodeNormal(hsStream* S, const unsigned char*& src);
    void IEncodeColor(hsStream* S, unsigned int vertsLeft, const unsigned char*& src);

    void ICountBytes(unsigned int vertsLeft, const unsigned char* src,
                     unsigned short& len, bool& same);
    void ICountFloats(unsigned int vertsLeft, const unsigned char* src,
                      float fieldScale, float& offset, bool& same,
                      unsigned short& count);

public:
    plVertCoder();
    ~plVertCoder();

    void clear();
    void read(hsStream* S, unsigned char* dest, unsigned char format,
              unsigned short numVerts);
    void write(hsStream* S, const unsigned char* src, unsigned char format,
               unsigned short numVerts);
};

#endif

