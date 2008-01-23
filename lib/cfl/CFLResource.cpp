    ////// ////// //     /////
   //     //     //         //
  //     ////   //       ///
 //     //     //         //
////// //     ////// /////

///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// Compressed File Library 3
// Copyright (c) 2001 Jari Komppa
//
//
///////////////////////////////////////////////
// License
///////////////////////////////////////////////
// 
//     This software is provided 'as-is', without any express or implied
//     warranty.    In no event will the authors be held liable for any damages
//     arising from the use of this software.
// 
//     Permission is granted to anyone to use this software for any purpose,
//     including commercial applications, and to alter it and redistribute it
//     freely, subject to the following restrictions:
// 
//     1. The origin of this software must not be misrepresented; you must not
//        claim that you wrote the original software. If you use this software
//        in a product, an acknowledgment in the product documentation would be
//        appreciated but is not required.
//     2. Altered source versions must be plainly marked as such, and must not be
//        misrepresented as being the original software.
//     3. This notice may not be removed or altered from any source distribution.
// 
// (eg. same as ZLIB license)
// 
//
///////////////////////////////////////////////
//
// See cfl.h for documentation
//
///////////////////////////////////////////////

#include "CFL.h"
#include "CFLResource.h"

CFLResource * CFLResource::load(FILE *aFilePtr) 
{
    CFLResource *d = new CFLResource();
    if (d == NULL) return NULL;
    fread(&d->mCompressedSize, 1, 4, aFilePtr);
    d->mData = new char[d->mCompressedSize];
    if (d->mData==NULL)
    {
        delete d;
        return NULL;
    }
    fread(d->mData, 1, d->mCompressedSize, aFilePtr);
    return d;
}


void CFLResource::save(FILE *aFilePtr) 
{
    fwrite(&mCompressedSize, 1, 4, aFilePtr);
    fwrite(mData, 1, mCompressedSize, aFilePtr);
}


CFLResource::CFLResource()
{
    mData = NULL;
    mCompressedSize = 0;
}


CFLResource::~CFLResource()
{
    if (mData != NULL)
        delete[] mData;
}

