#include "../hdr/redef.h"

/*
 * *-The definition of memory struct.
 *
 * *-The length of the struct on 64-bit system architecture = 14 bytes (without padding) [16-bits (for ushi) - 32-bits (for enum dt) - 64-bits (for gptr)].
 *                                                            16 bytes (with padding) [16-bits (for ushi) - 16-bits (for padding) - 32-bits (for enum dt) - 64-bits (for gptr)].
 *
 * *-The length of the struct on 32-bit system architecture = 10 bytes (without padding) [32-bits (for enum dt) - 16-bits (for ushi) - 32-bits (for gptr)].
 *                                                            12 bytes (with padding) [32-bits (for enum dt) - 16-bits (for ushi) - 16-bits (for ushi) - 32-bits (for gptr)].
 *
 * *-The length of the struct on 16-bits system architecture = 6 bytes (no padding required) [16-bits (for enum dt) - 16-bits (for ushi) - 16-bits (for gptr)].
 * */
struct _mem_ {
    ushi attrib;
    enum dt type;
    gptr value;
};

/*
 * *-The definition of array struct.
 * 
 * *-The length of the struct on 64-bit system architecture = 20 bytes (without padding) [4 bytes [enum dt] - 8 bytes [sizt] - 8 bytes [gptr *]].
 *   with padding = 24 bytes [4 bytes [enum dt] - 4 bytes [padding] - 8 bytes [sizt] - 8 bytes [gptr *]].
 *
 * *-The length of the struct on 32-bit system architecture = 12 bytes (with padding) [4 bytes [enum dt] - 4 bytes [sizt] - 4 bytes [gptr *]].
 *
 * *-The length of the struct on 16-bit system architecture = 6 bytes (with padding) [2 bytes [enum dt] - 2 bytes [sizt] - 2 bytes [gptr *]].
*/
struct _array_ {
    enum dt type;
    sizt length;
    gptr * arr;
};

/*
 * INPT: An ucar (tells us which operation to do) and an enum dt (which holds which datatype we are dealing with)
 * OTPT: Returns a sizt value.
 * INFO: This function is used to generalize operations with specific codes:
 *       1-isType.
 *       2-dtLength.
*/
static sizt commonDtOperation (ucar opCode, enum dt type) {
    sizt result = 1;

    switch (type) {
        case VOID:
            if (opCode == 2) {
                result = 0;
            }

            break;
        case BOOLEAN:
        case BOOL:
            if (opCode == 2) {
                result = sizeof (boolean);
            }

            break;
        case CHAR:
        case CAR:
        case SCAR:
            if (opCode == 2) {
                result = sizeof (scar);
            }

            break;
        case UCAR:
        case BYTE:
            if (opCode == 2) {
                result = sizeof (ucar);
            }

            break;
        case SSHI:
            if (opCode == 2) {
                result = sizeof (sshi);
            }

            break;
        case USHI:
            if (opCode == 2) {
                result = sizeof (ushi);
            }

            break;
        case SINT:
            if (opCode == 2) {
                result = sizeof (sint);
            }

            break;
        case UINT:
            if (opCode == 2) {
                result = sizeof (uint);
            }

            break;
        case SLNG:
            if (opCode == 2) {
                result = sizeof (slng);
            }

            break;
        case ULNG:
            if (opCode == 2) {
                result = sizeof (ulng);
            }

            break;
        case SLLG:
            if (opCode == 2) {
                result = sizeof (sllg);
            }

            break;
        case ULLG:
            if (opCode == 2) {
                result = sizeof (ullg);
            }

            break;
        case SIZT:
            if (opCode == 2) {
                result = sizeof (sizt);
            }

            break;
        case FLOT:
            if (opCode == 2) {
                result = sizeof (flot);
            }

            break;
        case DBLE:
            if (opCode == 2) {
                result = sizeof (dble);
            }

            break;
        case LDBL:
            if (opCode == 2) {
                result = sizeof (ldbl);
            }

            break;
        case STRG:
        case STRING:
            if (opCode == 2) {
                result = sizeof (strg);
            }

            break;
        case GPTR:
            if (opCode == 2) {
                result = sizeof (gptr);
            }

            break;
        case MEM:
        case MEMORY:
            if (opCode == 2) {
                result = sizeof (struct _mem_);
            }

            break;
        case ARRY:
        case ARRAY:
            if (opCode == 2) {
                result = sizeof (struct _array_);
            }

            break;
        default:
            result = (opCode == 1) ? 0 : -1;
            break;
    }

    return result;
}

boolean isType(enum dt type) {
    return (boolean) commonDtOperation (1, type);
}

sizt typeLength (enum dt type) {
    return commonDtOperation(2, type);
}