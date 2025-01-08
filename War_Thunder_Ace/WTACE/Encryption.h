#pragma once
#include "stdafx.h"


#define KEY1 0xFF
#define KEY2 0x6
#define KEY3 0xA1

#define INTEL_KEY1 0x67
#define INTEL_KEY2 0x4C
#define INTEL_KEY3 0xFF


// Decryption function with three keys and additional byte rotations
__forceinline void decryptByteArray(unsigned char* data, size_t size, int intel) 
{
    if (!intel)
    {
        for (size_t i = 0; i < size; ++i) {
            // Convert to unsigned char before bitwise operations
            unsigned char udata = (data[i]);

            // Round 6: Rotate left by 1 bit
            udata = ((udata << 1) | (udata >> (8 - 1)));

            // Round 5: Rotate right by 2 bits
            udata = ((udata >> 2) | (udata << (8 - 2)));

            // Round 4: Rotate left by 3 bits
            udata = ((udata << 3) | (udata >> (8 - 3)));

            // Round 3: XOR with key3, and rotate right by 4 bits
            udata ^= KEY3;
            udata = ((udata >> 4) | (udata << (8 - 4)));

            // Round 2: XOR with key2, and rotate left by 5 bits
            udata ^= KEY2;
            udata = ((udata << 5) | (udata >> (8 - 5)));

            // Round 1: XOR with key1, and rotate right by 6 bits
            udata ^= KEY1;
            udata = ((udata >> 6) | (udata << (8 - 6)));

            // Store the result back in data array
            data[i] = udata;
        }
        
    }
    else
    {
        for (size_t i = 0; i < size; ++i) {
            // Convert to unsigned char before bitwise operations
            unsigned char udata = (data[i]);

            // Round 6: Rotate left by 1 bit
            udata = ((udata << 1) | (udata >> (8 - 1)));

            // Round 5: Rotate right by 2 bits
            udata = ((udata >> 2) | (udata << (8 - 2)));

            // Round 4: Rotate left by 3 bits
            udata = ((udata << 3) | (udata >> (8 - 3)));

            // Round 3: XOR with key3, and rotate right by 4 bits
            udata ^= INTEL_KEY3;
            udata = ((udata >> 4) | (udata << (8 - 4)));

            // Round 2: XOR with key2, and rotate left by 5 bits
            udata ^= INTEL_KEY2;
            udata = ((udata << 5) | (udata >> (8 - 5)));

            // Round 1: XOR with key1, and rotate right by 6 bits
            udata ^= INTEL_KEY1;
            udata = ((udata >> 6) | (udata << (8 - 6)));

            // Store the result back in data array
            data[i] = udata;
        }
        
    }
}
