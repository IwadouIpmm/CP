#include <stdlib.h>
#include "../hdr/redef.h"
#include "../hdr/memory.h"
#include "../hdr/char.h"
#include "../hdr/string.h"
#include "../hdr/array.h"

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
 * INFO: A pointer to an array, a sizt (tells us which operation we perform), and an array of gptr (which holds values to use).
 * OTPT: Returns a sizt value on success, otherwise returns 0 on failure.
 * INFO: This function perform common operation on an array with different datatypes.
 *       1-initArray (needs [enum dt type - sizt length]).
 *       2-termArray (needs nothing).
 *       3-getArrayTypeAt (needs [sizt index]).
 *       4-getArrayLengthAt (needs [sizt index]).
 *       5-getArrayLength (needs nothing).
 *       6-decreaseTheLength (needs [sizt length]).
 *       7-increaseTheLength (needs [sizt length]).
 *       8-assignValueAt (needs [enum dt type - sizt index - gptr value]).
 *       9-freeArrayValue (needs nothing).
*/
static sizt arrayCommonOperations (array * arr, sizt opCode, gptr * args) {
    if (!*arr) {
        return 0;
    }

    if (opCode < 1 && opCode > 9) {
        return 0;
    }

    sizt result = 0;
    boolean success = true;

    enum dt type = (opCode == 1 || opCode == 8) ? *((enum dt *) args [0]) : (*arr) -> type;

    if (opCode == 1) {
        (*arr) -> arr = Malloc (type, *((sizt *) args [1]));

        if (!(*arr) -> arr) {
            return 0;
        }

        result = 1;
    }

    if (opCode == 2 && ((*arr) -> type >= BOOLEAN && (*arr) -> type <= STRG)) {
        for (; result < (*arr) -> length; ++result) {
            free ((*arr) -> arr [result]);
            (*arr) -> arr [result] = NULL;
        }

        free ((*arr) -> arr);
        (*arr) -> arr = NULL;

        free (*arr);
        *arr = NULL;

        return result;
    }

    if (opCode == 5 && ((*arr) -> type >= BOOLEAN && (*arr) -> type <= LDBL)) {
        return (*arr) -> length * typeLength ((*arr) -> type);
    }

    if (opCode == 6 || opCode == 7) {
        array newArr = (array) Malloc (ARRAY, 1);

        if (!newArr) {
            return 0;
        }

        newArr -> arr = NULL;
        newArr -> type = (*arr) -> type;
        newArr -> length = *((sizt *) args [0]);

        newArr -> arr = Malloc (newArr -> type, newArr -> length);

        if (!newArr -> arr) {
            free (newArr);
            newArr = NULL;

            return 0;
        }

        for (; result < (opCode == 6) ? newArr -> length : (*arr) -> length; ++result) {
            newArr -> arr [result] = (*arr) -> arr [result];
        }

        if (opCode == 7) {
            for (; result < newArr -> length; ++result) {
                newArr -> arr [result] = NULL;
            }
        }

        result = arrayCommonOperations (arr, 9, NULL);

        if (!result) {
            result = arrayCommonOperations (&newArr, 2, NULL);
            newArr = NULL;

            return 0;
        }

        (*arr) = newArr;
        newArr = NULL;

        return 1;
    }

    if (opCode == 9) {
        if ((*arr) -> type >= BOOLEAN && (*arr) -> type <= STRG) {
            for (; result < (*arr) -> length; ++result) {
                free ((*arr) -> arr [result]);
                (*arr) -> arr [result] = NULL;
            }

            free ((*arr) -> arr);
            (*arr) -> arr = NULL;

            return 1;
        }

        for (sizt counter = 0; counter < (*arr) -> length; ++counter) {
            if ((*arr) -> arr [counter]) {
                result = ((*arr) -> type == MEM || (*arr) -> type == MEMORY) ? deallocate ((memory *) &(*arr) -> arr [counter]) : termArray ((array *) &(*arr) -> arr [counter]);

                if (!result) {
                    break;
                }
            }
        }

        return result;
    }

    gptr temp = NULL;

    switch (type) {
        case BOOLEAN:
        case BOOL:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((boolean *)(*arr) -> arr [result]) = false;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((boolean *) (*arr) -> arr [*((sizt *) args [1])]) = *((boolean *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case CHAR:
        case SCAR:
        case CAR:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((scar *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((scar *) (*arr) -> arr [*((sizt *) args [1])]) = *((scar *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case UCAR:
        case BYTE:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((ucar *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((byte *) (*arr) -> arr [*((sizt *) args [1])]) = *((byte *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case SSHI:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((sshi *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((sshi *) (*arr) -> arr [*((sizt *) args [1])]) = *((sshi *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case USHI:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((ushi *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((ushi *) (*arr) -> arr [*((sizt *) args [1])]) = *((ushi *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case SINT:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((sint *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((sint *) (*arr) -> arr [*((sizt *) args [1])]) = *((sint *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case UINT:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((uint *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((uint *) (*arr) -> arr [*((sizt *) args [1])]) = *((uint *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case SLNG:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((slng *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((slng *) (*arr) -> arr [*((sizt *) args [1])]) = *((slng *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case ULNG:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((ulng *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((ulng *) (*arr) -> arr [*((sizt *) args [1])]) = *((ulng *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case SLLG:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((sllg *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((sllg *) (*arr) -> arr [*((sizt *) args [1])]) = *((sllg *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case ULLG:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((ullg *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((ullg *) (*arr) -> arr [*((sizt *) args [1])]) = *((ullg *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case SIZT:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((sizt *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((sizt *) (*arr) -> arr [*((sizt *) args [1])]) = *((sizt *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case FLOT:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((flot *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((flot *) (*arr) -> arr [*((sizt *) args [1])]) = *((flot *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case DBLE:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((dble *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((dble *) (*arr) -> arr [*((sizt *) args [1])]) = *((dble *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case LDBL:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        *((ldbl *)(*arr) -> arr [result]) = 0;
                    }

                    break;
                //assignValueAt
                case 8:
                    *((ldbl *) (*arr) -> arr [*((sizt *) args [1])]) = *((ldbl *) args [2]);
                    break;
                default:
                    break;
            }

            break;
        case STRG:
        case STRING:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                       (*arr) -> arr [result] = NULL;
                    }

                    break;
                //getArrayLengthAt
                case 4:
                    result = stringLength ((strg) (*arr) -> arr [*((sizt *) args [0])]);
                    break;
                //getArrayLength
                case 5:
                    for (sizt counter = 0; counter < (*arr) -> length; ++counter) {
                        result += stringLength ((strg) (*arr) -> arr [counter]);
                    }

                    break;
                //assignValueAt
                case 8:
                    result = stringLength (((string) args [2]));
                    temp = (result) ? Malloc (SCAR, (result + 1)) : NULL;

                    if (result && temp) {
                        ((string) temp) [result] = '\0';

                        for (sizt counter = 0; counter < result; ++counter) {
                            ((string) temp) [counter] = ((string) args [2]) [counter];
                        }
                    }

                    (*arr) -> arr [*((sizt *) args [1])] = temp;
                    temp = NULL;

                    break;
                default:
                    break;
            }

            break;
        case MEM:
        case MEMORY:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        (*arr) -> arr [result] = NULL;
                    }

                    break;
                //termArray
                case 2:
                    for (; result < (*arr) -> length; ++result) {
                        if (!deallocate ((memory *) &(*arr) -> arr [result])) {
                            result = 0;
                            success = false;
                            break;
                        }

                        (*arr) -> arr [result] = NULL;
                    }

                    if (success) {
                        free ((*arr) -> arr);
                        (*arr) -> arr = NULL;
                        free (*arr);
                        *arr = NULL;
                    }

                    break;
                //getArrayTypeAt
                case 3:
                    result = getMemoryType ((memory) (*arr) -> arr [*((sizt *) args [0])]);
                    break;
                //getArrayLengthAt
                case 4:
                    result = getMemoryLength ((memory) (*arr) -> arr [*(sizt *) args [0]]);
                    break;
                //getArrayLength
                case 5:
                    for (sizt counter = 0; counter < (*arr) -> length; ++counter) {
                        result += getMemoryLength ((memory) (*arr) -> arr [counter]);
                    }

                    break;
                //assignValueAt
                case 8:
                    break;
                default:
                    break;
            }

            break;
        case ARRAY:
        case ARRY:
            switch (opCode) {
                //InitArray
                case 1:
                    for (; result < *((sizt *) args [1]); ++result) {
                        (*arr) -> arr [result] = NULL;
                    }

                    break;
                //termArray
                case 2:
                    for (; result < (*arr) -> length; ++result) {
                        if (!termArray ((array *) &(*arr) -> arr [result])) {
                            result = 0;
                            success = false;
                            break;
                        }

                        (*arr) -> arr [result] = NULL;
                    }

                    if (success) {
                        free ((*arr) -> arr);
                        (*arr) -> arr = NULL;
                        free (*arr);
                        *arr = NULL;
                    }

                    break;
                //getArrayTypeAt
                case 3:
                    result = getArrayType ((array) (*arr) -> arr [*((sizt *) args [0])]);
                    break;
                //getMemoryLengthAt
                case 4:
                    result = getArrayLength ((array) (*arr) -> arr [*(sizt *) args [0]]);
                    break;
                //getArrayLength
                case 5:
                    for (sizt counter = 0; counter < (*arr) -> length; ++counter) {
                        result += getArrayLength ((array) (*arr) -> arr [counter]);
                    }

                    break;
                //assignValueAt
                case 8:
                    break;
                default:
                    break;
            }

            break;
        default:
            break;
    }

    return result;
}

bool termArray (array * arr) {
    if (!arr) {
        return false;
    }

    if (!*arr) {
        return false;
    }

    if (!arrayCommonOperations (arr, 2, NULL)) {
        return false;
    }

    *arr = NULL;
    return true;
}

bool setArrayLength (array * arr, sizt length) {
    if (!arr) {
        return false;
    }

    if (!*arr) {
        return false;
    }

    if ((*arr) -> length == length) {
        return false;
    }

    return (bool) arrayCommonOperations (arr, (length > (*arr) -> length) ? 7 : 6, (gptr []) {(gptr) &length});
}

bool changeArrayType (array * arr, enum dt type) {
    if (!arr || !isType (type)) {
        return false;
    }

    if (!*arr) {
        return false;
    }

    array temp = NULL;
    temp = initArray (0, type);

    if (!termArray (arr)) {
        termArray (&temp);
        return false;
    }

    *arr = temp;
    temp = NULL;

    return true;
}

bool addCarToArray (array * arr, sizt index, car value) {
    if (!isChar (value)) {
        return false;
    }

    return addValueToArray (arr, index, CAR, (gptr) &value);
}

bool addMemToArray (array * arr, sizt index, mem segment) {
    return addValueToArray (arr, index, MEM, (gptr) segment);
}
	
bool addBoolToArray (array * arr, sizt index, bool value) {
    return addValueToArray (arr, index, BOOL, (gptr) &value);
}

bool addCharToArray (array * arr, sizt index, char value) {
    if (!isChar (value)) {
        return false;
    }

    return addValueToArray (arr, index, CHAR, (gptr) &value);
}

bool addScarToArray (array * arr, sizt index, scar value) {
    return addValueToArray (arr, index, SCAR, (gptr) &value);
}

bool addUcarToArray (array * arr, sizt index, ucar value) {
    return addValueToArray (arr, index, UCAR, (gptr) &value);
}

bool addSshiToArray (array * arr, sizt index, sshi value) {
    return addValueToArray (arr, index, SSHI, (gptr) &value);
}

bool addUshiToArray (array * arr, sizt index, ushi value) {
    return addValueToArray (arr, index, USHI, (gptr) &value);
}

bool addSintToArray (array * arr, sizt index, sint value) {
    return addValueToArray (arr, index, SINT, (gptr) &value);
}

bool addUintToArray (array * arr, sizt index, uint value) {
    return addValueToArray (arr, index, UINT, (gptr) &value);
}

bool addSlngToArray (array * arr, sizt index, slng value) {
    return addValueToArray (arr, index, SLNG, (gptr) &value);
}

bool addUlngToArray (array * arr, sizt index, ulng value) {
    return addValueToArray (arr, index, ULNG, (gptr) &value);
}

bool addSllgToArray (array * arr, sizt index, sllg value) {
    return addValueToArray (arr, index, SLLG, (gptr) &value);
}

bool addUllgToArray (array * arr, sizt index, ullg value) {
    return addValueToArray (arr, index, ULLG, (gptr) &value);
}

bool addSiztToArray (array * arr, sizt index, sizt value) {
    return addValueToArray (arr, index, SIZT, (gptr) &value);
}

bool addFlotToArray (array * arr, sizt index, flot value) {
    return addValueToArray (arr, index, FLOT, (gptr) &value);
}

bool addDbleToArray (array * arr, sizt index, dble value) {
    return addValueToArray (arr, index, DBLE, (gptr) &value);
}

bool addLdblToArray (array * arr, sizt index, ldbl value) {
    return addValueToArray (arr, index, LDBL, (gptr) &value);
}

bool addStrgToArray (array * arr, sizt index, strg value) {
    return addValueToArray (arr, index, STRG, (gptr) value);
}

bool addArryToArray (array * arr, sizt index, arry value) {
    return addValueToArray (arr, index, ARRY, (gptr) value);
}
	
bool addArrayToArray (array * arr, sizt index, array value) {
    return addValueToArray (arr, index, ARRAY, (gptr) value);
}

bool addStringToArray (array * arr, sizt index, string value) {
    return addValueToArray (arr, index, STRING, (gptr) value);
}

bool addBooleanToArray (array * arr, sizt index, boolean value) {
    return addValueToArray (arr, index, BOOLEAN, (gptr) &value);
}

bool addMemoryToArray (array * arr, sizt index, memory segment) {
    return addValueToArray (arr, index, MEMORY, (gptr) segment);
}

bool addValueToArray (array * arr, sizt index, enum dt type, gptr value) {
    if (!arr || !value) {
        return false;
    }

    if (!*arr) {
        return false;
    }

    if (index >= (*arr) -> length) {
        return false;
    }

    if (!isType (type)) {
        return false;
    }

    if (type == VOID || type == GPTR) {
        return false;
    }

    return (bool) arrayCommonOperations (arr, 8, (gptr []) {(gptr) &type, (gptr) &index, value});
}

sizt getArrayLength (array arr) {
    if (!arr) {
        return 0;
    }

    return arr -> length;
}

sizt arrayFullLength (array arr) {
    if (!arr) {
        return 0;
    }

    return arrayCommonOperations (&arr, 5, NULL);;
}

sizt getArrayLengthAt (array arr, sizt index) {
    if (!arr) {
        return 0;
    }

    if (index >= arr -> length) {
        return 0;
    }

    return (arr -> type >= BOOLEAN && arr -> type <= LDBL) ? typeLength (arr -> type) : arrayCommonOperations (&arr, 4, (gptr []) {(gptr) &index});
}

gptr getArrayValueAt (array arr, sizt index) {
    if (!arr) {
        return NULL;
    }

    if (index >= arr -> length) {
        return NULL;
    }

    return arr -> arr [index];
}

enum dt getArrayType (array arr) {
    if (!arr) {
        return VOID;
    }

    return arr -> type;
}

enum dt getArrayTypeAt (array arr, sizt index) {
    if (!arr) {
        return VOID;
    }

    if (index >= arr -> length) {
        return VOID;
    }

    return (arr -> type >= BOOLEAN && arr -> type <= STRG) ? arr -> type : (enum dt) arrayCommonOperations (&arr, 3, (gptr []) {(gptr) &index});
}

array initArray (sizt length, enum dt type) {
    if (!isType (type)) {
        return NULL;
    }

    array arr = (array) Malloc (ARRAY, 1);

    if (!arr) {
        return NULL;
    }

    arr -> arr = NULL;
    arr -> type = type;
    arr -> length = length;

    if (length) {
        if (!arrayCommonOperations (&arr, 1, (gptr []) {(gptr) &type, (gptr) &length})) {
            Free ((gptr) arr);
            arr = NULL;
        }
    }

    return arr;
}