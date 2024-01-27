#include <stdlib.h>
#include "../hdr/redef.h"
#include "../hdr/memory.h"
#include "../hdr/array.h"
#include "../hdr/string.h"

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
 * *-The definitions of memory manager struct.
 *
 * *-The length of the struct on 64-bit system architecture = 16 bytes (no padding required) = (64-bits (for sizt) + 64-bits (for memory *)).
 * 
 * *-The length of the struct on 32-bit system architecture = 8 bytes (no padding required). (32-bits for (sizt) + 32-bits (memory *)).
 *
 * *-The length of the struct on 16-bit system architecture = 4 bytes (no padding required). (16-bits (for sizt) + 16-bits (memory *)).
 * */
typedef struct {
    sizt length;
    memory * segments;
} memoryManager;

//Our memory manager value holder.
memoryManager * blocks = NULL;

/*
 * INPT: Non.
 * OTPT: Returns true on success, otherwise returns false on failure.
 * INFO: This function is used to initialized memoryManager, before using any allocation process.
 * */
static bool initializeBlocks (void) {
    if (blocks) {
        return true;
    }

    ucar limiter = 0;
    bool result = false;

    do {++limiter; blocks = (memoryManager *) malloc (sizeof (memoryManager));} while (limiter < 3 && !blocks);

    if (blocks) {
        blocks -> length = 0;
        blocks -> segments = NULL;
        result = true;
    }

    return result;
}

/*
 * INPT: Non.
 * OTPT: Returns and index of type sizt, where we can place our memory segment inside our memory manager. In case of an error returns -1.
 * INFO: This function is used to find an empty space where we can allocated our memory segment.
 * */
static sizt findEmptySegment (void) {
    if (!initializeBlocks()) {
        return -1;
    }

    sizt index = 0;

    if (blocks -> length == 0) {
        ucar limiter = 0;
        do {++limiter; blocks -> segments = (memory *) malloc (sizeof (memory) * 10);} while (limiter < 3 && !blocks -> segments);

        if (!blocks -> segments) {
            return -1;
        }

        ucar iteration = 0;

        for (; iteration < 10; ++iteration) {
            blocks -> segments [iteration] = NULL;
        }

        blocks -> length = 10;

        return 0;
    }

    bool found = false;

    for (; index < blocks -> length; ++index) {
        if (!blocks -> segments [index]) {
            found = true;
            break;
        }
    }

    //Check there is no empty space found, then extends the array of memory segments in our memory manager.
    if (!found) {
        ucar limiter = 0;
        memory * segments = NULL;

        do {++limiter; segments = (memory *) malloc ((sizeof (memory) * (blocks -> length + 5)));} while (limiter < 3 && !segments);

        if (!segments) {
            return -1;
        }

        index = 0;

        for (; index < blocks -> length; ++index) {
            segments [index] = blocks -> segments [index];
        }

        ucar iteration = 0;

        for (; iteration < 5; ++iteration) {
            segments [index + iteration] = NULL;
        }

        blocks -> length += 5;
        free (blocks -> segments);
        blocks -> segments = segments;

        segments = NULL;
    }

    return index;
}

/*
 * INPT: A memory segment.
 * OTPT: Returns a sizt if found, otherwise returns -1.
 * INFO: This function is used to get an index of a specific memory segment from our memory manager.
 * */
static sizt getMemorySegmentIndex (memory segment) {
    if (!blocks) {
        return -1;
    }

    if (!segment) {
        return -1;
    }

    sizt index = 0;
    boolean found = false;

    for (; index < blocks -> length; ++index) {
        if (blocks -> segments [index] == segment) {
            found = true;
            break;
        }
    }

    if (!found) {
        index = -1;
    }

    return index;
}

/*
 * INPT: A pointer to a memory segment, an uint (which holds which operation to perform), and an array of gptr which holds argument of the operation we will use.
 * OTPT: Returns a numeric version (acts as boolean value or other numeric values) on success, otherwise returns 0 in case of failure.
 * INFO: This function is used to perform different memory segment operation:
 *       1-Allocation (need enum dt).
 *       2-Deallocation (needs nothing).
 *       3-MemoryLength (need nothing).
 *       4-ChangeType (need an enum dt).
 *       5-freeMemoryValue (needs nothing).
 *       6-setMemoryValue (enum dt and gptr).
 *       7-MemoryValueLength (needs nothing).
 * */
static sizt performMemoryOperation (memory * segment, uint operationCode, gptr * args) {
    if (!segment) {
        return 0;
    }
    
    if (!*segment) {
        return 0;
    }

    if (operationCode < 1 || operationCode > 7) {
        return 0;
    }

    enum dt * type = (operationCode == 1 || operationCode == 4 || operationCode == 6) ? ((enum dt *) args [0]) : &((*segment) -> type);

    sizt result = 0;

    gptr temp = NULL;
    memory holder = NULL;
    sizt index = getMemorySegmentIndex (*segment);

    if (index == (sizt) -1) {
        return 0;
    }

    if (operationCode == 1) {
        blocks -> segments [index] -> value = (*type == STRG || *type == STRING) ? NULL : Malloc (*type, 1);

        if (*type != STRG && *type != STRING) {
            if (!blocks -> segments [index] -> value) {
                return 0;
            } 
        }

        result = 1;
    }

    if ((operationCode == 2 || operationCode == 5) && (*type >= BOOLEAN && *type <= STRG)) {
        free (blocks -> segments [index] -> value);
        blocks -> segments [index] -> type = VOID;
        blocks -> segments [index] -> value = NULL;
        blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_MUTABLE | MEM_EXTEND | MEM_SHRINK | MEM_DEFVAL;

        if (operationCode == 2) {
            free (blocks -> segments [index]);
            blocks -> segments [index] = NULL;
            *segment = NULL;
        }

        return 1;
    }

    if (operationCode == 4 && isMemoryMutable (*segment)) {
        result = performMemoryOperation (segment, 5, NULL);
        if (result == 0) {
            return 0;
        }

        result = performMemoryOperation (segment, 1, (gptr []){(gptr) type});
        return 1;
    }

    if (operationCode == 6 && (*type >= BOOLEAN && *type <= LDBL) && (isMemoryWritable (*segment) && !isMemoryConstant (*segment))) {
        if (blocks -> segments [index] -> type != *type) {
            temp = Malloc (GPTR, 1);

            if (!temp) {
                return result;
            }

            if ((*segment) -> value) {
                result = performMemoryOperation (segment, 5, NULL);

                if (result == 0) {
                    free (temp);
                    temp = NULL;
                    return result;
                }
            }

            blocks -> segments [index] -> type = *type;
            blocks -> segments [index] -> value = temp;
            temp = NULL;
        }

        if (blocks -> segments [index] -> attrib & MEM_DEFVAL) {
            blocks -> segments [index] -> attrib &= ~MEM_DEFVAL;
        }

        result = 1;
    }

    switch (*type) {
        case BOOLEAN:
        case BOOL:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((boolean *) blocks -> segments [index] -> value) = false;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (boolean) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((bool *) blocks -> segments [index] -> value) = *((bool *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (boolean);
                    break;
                default:
                    break;
            }

            break;
        case CHAR:
        case CAR:
        case SCAR:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((scar *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (scar) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((scar *) blocks -> segments [index] -> value) = *((scar *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (scar);
                    break;
                default:
                    break;
            }

            break;
        case UCAR:
        case BYTE:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((ucar *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (byte)  + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((ucar *) blocks -> segments [index] -> value) = *((ucar *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (byte);
                    break;
                default:
                    break;
            }

            break;
        case SSHI:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((sshi *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (sshi) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((sshi *) blocks -> segments [index] -> value) = *((sshi *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (sshi);
                    break;
                default:
                    break;
            }

            break;
        case USHI:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((ushi *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (ushi) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((ushi *) blocks -> segments [index] -> value) = *((ushi *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (ushi);
                    break;
                default:
                    break;
            }

            break;
        case SINT:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((sint *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (sint) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((sint *) blocks -> segments [index] -> value) = *((sint *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (sint);
                    break;
                default:
                    break;
            }

            break;
        case UINT:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((uint *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (uint) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((uint *) blocks -> segments [index] -> value) = *((uint *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (uint);
                    break;
                default:
                    break;
            }

            break;
        case SLNG:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((slng *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (slng) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((slng *) blocks -> segments [index] -> value) = *((slng *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (slng);
                    break;
                default:
                    break;
            }

            break;
        case ULNG:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((ulng *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (ulng) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((ulng *) blocks -> segments [index] -> value) = *((ulng *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (ulng);
                    break;
                default:
                    break;
            }

            break;
        case SLLG:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((sllg *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (sllg) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((sllg *) blocks -> segments [index] -> value) = *((sllg *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (sllg);
                    break;
                default:
                    break;
            }

            break;
        case ULLG:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((ullg *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (ullg) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((ullg *) blocks -> segments [index] -> value) = *((ullg *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (ullg);
                    break;
                default:
                    break;
            }

            break;
        case SIZT:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((sizt *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (sizt) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((sizt *) blocks -> segments [index] -> value) = *((sizt *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (sizt);
                    break;
                default:
                    break;
            }

            break;
        case FLOT:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((flot *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (flot) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((flot *) blocks -> segments [index] -> value) = *((flot *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (flot);
                    break;
                default:
                    break;
            }

            break;
        case DBLE:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((dble *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (dble) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((dble *) blocks -> segments [index] -> value) = *((dble *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (dble);
                    break;
                default:
                    break;
            }

            break;
        case LDBL:
            switch (operationCode) {
                //Allocation
                case 1:
                    *((ldbl *) blocks -> segments [index] -> value) = 0;
                    break;
                //Memory Length
                case 3:
                    result = sizeof (ldbl) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        *((ldbl *) blocks -> segments [index] -> value) = *((ldbl *) args [1]);
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = sizeof (ldbl);
                    break;
                default:
                    break;
            }

            break;
        case STRG:
        case STRING:
            switch (operationCode) {
                //MemoryLength
                case 3:
                    result = stringLength (((strg) (*segment) -> value)) + sizeof (struct _mem_);
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        result = stringLength (((strg) args [1]));
                        temp = (!result) ? NULL : Malloc (CHAR, (result + 1));

                        if (result) {
                            ((strg) temp) [result] = '\0';

                            for (sizt counter = 0; counter < result; ++counter) {
                                ((strg) temp) [counter] = ((strg) args [1]) [counter];
                            }
                        }

                        if (blocks -> segments [index] -> value) {
                            result = performMemoryOperation(segment, 5, NULL);
                            if (!result) {
                                free (temp);
                                temp = NULL;
                                break;
                            }
                        }

                        blocks -> segments [index] -> type = *type;
                        blocks -> segments [index] -> value = temp;

                        if (blocks -> segments [index] -> attrib & MEM_DEFVAL) {
                            blocks -> segments [index] -> attrib &= ~MEM_DEFVAL;
                        }

                        result = 1;
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = stringLength (((strg) (*segment) -> value));
                    break;
                default:
                    break;
            }

            break;
        case MEM:
        case MEMORY:
            switch (operationCode) {
                //Allocation
                case 1:
                    ((memory) blocks -> segments [index] -> value) -> type = VOID;
                    ((memory) blocks -> segments [index] -> value) -> value = NULL;
                    ((memory) blocks -> segments [index] -> value) -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_SHRINK | MEM_EXTEND | MEM_MUTABLE;
                    break;
                //Deallocate
                case 2:
                    holder = ((memory) blocks -> segments [index] -> value);

                    if (holder) {
                        result = performMemoryOperation(&holder, 2, NULL);
                        if (!result) {
                            break;
                        }

                        holder = NULL;
                        blocks -> segments [index] -> value = NULL;
                    }

                    free (blocks -> segments [index]);
                    blocks -> segments [index] = NULL;
                    result = 1;
                    break;
                //Memory Length
                case 3:
                    holder = ((memory) blocks -> segments [index] -> value);

                    if (!holder) {
                        break;
                    }

                    result = performMemoryOperation(&holder, 7, NULL);

                    if (result) {
                        result += sizeof (struct _mem_);
                    }

                    break;
                //FreeMemoryValue
                case 5:
                    holder = ((memory) blocks -> segments [index]);

                    if (!holder) {
                        result = 1;
                        break;
                    }

                    result = performMemoryOperation(&holder, 2, NULL);
                    if (result) {
                        blocks -> segments [index] -> type = VOID;
                        blocks -> segments [index] -> value = NULL;
                        blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_EXTEND | MEM_SHRINK | MEM_MUTABLE;
                    }

                    holder = NULL;
                    break;
                //setMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        result = findEmptySegment ();

                        if (result == (sizt) -1) {
                            result = 0;
                            break;
                        }

                        blocks -> segments [result] = (memory) malloc (sizeof (struct _mem_));

                        if (!blocks -> segments [result]) {
                            result = 0;
                            break;
                        }

                        blocks -> segments [result] -> value = NULL;
                        blocks -> segments [result] -> type = ((memory) args [1]) -> type;
                        blocks -> segments [result] -> attrib = MEM_READ | MEM_WRITE | MEM_MUTABLE | MEM_DEFVAL | MEM_SHRINK | MEM_EXTEND;

                        if (!performMemoryOperation (&blocks -> segments [result], 6, (gptr []) {(gptr) &(((memory) ((memory) args [1]) -> value) -> type), ((memory) ((memory) args [1]) -> value) -> value})) {
                            free (blocks -> segments [result]);
                            blocks -> segments [result] = NULL;
                            result = 0;
                            break;
                        }

                        if ((*segment) -> value) {
                            if (!performMemoryOperation (segment, 5, NULL)) {
                                performMemoryOperation(&blocks -> segments [result], 2, NULL);
                                blocks -> segments [result] = NULL;
                                result = 0;
                                break;
                            }
                        }

                       blocks -> segments [index] -> type = *type;
                       blocks -> segments [index] -> value = (gptr) holder;

                        if (blocks -> segments [index] -> attrib & MEM_DEFVAL) {
                            blocks -> segments [index] -> attrib &= ~MEM_DEFVAL;
                        }

                        result = 1;
                    }

                    break;
                //MemoryValueLength
                case 7:
                    holder = ((memory) blocks -> segments [index] -> value);

                    if (!holder) {
                        break;
                    }

                    result = performMemoryOperation (&holder, 7, NULL);
                    break;
                default:
                    break;
            }

            break;
        case ARRY:
        case ARRAY:
            switch (operationCode) {
                //Allocation
                case 1:
                    ((array) blocks -> segments [index] -> value) -> arr = NULL;
                    ((array) blocks -> segments [index] -> value) -> length = 0;
                    ((array) blocks -> segments [index] -> value) -> type = VOID;
                    break;
                //Deallocation
                case 2:
                    temp = blocks -> segments [index] -> value;

                    if (termArray ((array *) &temp)) {
                        temp = NULL;
                        blocks -> segments [index] -> value = NULL;

                        free (blocks -> segments [index]);
                        blocks -> segments [index] = NULL;

                        result = 1;
                        break;
                    }

                    temp = NULL;
                    break;
                //Memory Length
                case 3:
                    result = getArrayLength (((array) blocks -> segments [index] -> value));
                    
                    if (result) {
                        result += sizeof (struct _mem_);
                    }

                    break;
                //FreeMemoryValue
                case 5:
                    temp = blocks -> segments [index] -> value;

                    if (temp) {
                        if (termArray ((array *) &temp)) {
                            temp = NULL;
                            blocks -> segments [index] -> value = NULL;
                            blocks -> segments [index] -> type = VOID;
                            blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_SHRINK | MEM_EXTEND | MEM_MUTABLE;
                        }
                    }

                    result = 1;

                    break;
                //SetMemoryValue
                case 6:
                    if (isMemoryWritable (*segment) && !isMemoryConstant (*segment)) {
                        temp = initArray (((array) args [1]) -> length, ((array) args [1]) -> type);

                        if (!temp) {
                            break;
                        }

                        if (blocks -> segments [index] -> value) {
                            result = performMemoryOperation (segment, 5, NULL);

                            if (!result) {
                                termArray ((array *) &temp);
                            }

                            break;
                        }

                        blocks -> segments [index] -> value = temp;
                        blocks -> segments [index] -> type = ((array) args [1]) -> type;
                        blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_SHRINK | MEM_EXTEND | MEM_MUTABLE;

                        if (blocks -> segments [index] -> attrib & MEM_DEFVAL) {
                            blocks -> segments [index] -> attrib &= ~MEM_DEFVAL;
                        }

                        result = 1;
                    }

                    break;
                //MemoryValueLength
                case 7:
                    result = getArrayLength (((array) blocks -> segments [index] -> value));
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

bool freeAll (void) {
    if (!blocks) {
        return true;
    }

    boolean freed = true;

    for (sizt counter = 0; counter < blocks -> length; ++counter) {
        if (blocks -> segments [counter]) {
            sizt result = performMemoryOperation(&blocks -> segments [counter], 2, NULL);

            if (!result) {
                freed = false;
                continue;
            }

            blocks -> segments [counter] = NULL;
        }
    }

    if (freed) {
        free (blocks -> segments);
        blocks -> segments = NULL;
        free (blocks);
        blocks = NULL;
    }

    return freed;
}

bool Free (gptr address) {
    if (!address) {
        return false;
    }

    memory holder = getMemoryByValue (address);

    if (!holder) {
        return false;
    }

    return performMemoryOperation (&holder, 2, NULL);
}

bool deallocate (memory *segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    sizt result = performMemoryOperation(segment, 2, NULL);

    if (!result) {
        return false;
    }

    return true;
}

bool isMemoryEmpty (memory segment) {
    sizt index = getMemorySegmentIndex(segment);

    if (index == (sizt) -1) {
        return false;
    }

    return (blocks -> segments [index] -> value) ? false : true;
}

bool doesMemoryExist (memory segment) {
    sizt index = getMemorySegmentIndex(segment);

    if (index == (sizt) -1) {
        return false;
    }

    return true;
}

bool isMemoryMutable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_MUTABLE) ? true : false;
}

bool enableReadFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_READ;

    return true;
}

bool isMemoryReadable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_READ) ? true : false;
}

bool isMemoryWritable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_WRITE) ? true : false;
}

bool hasMemoryChanged (memory segment) {
    if (!segment) {
        return false;
    }

    return (!(segment -> attrib & MEM_DEFVAL)) ? true : false;
}

bool isMemoryConstant (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_CONST) ? true : false;
}

bool enableConstFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    //Enable const.
    (*segment) -> attrib |= MEM_CONST;
    return true;
}

bool isMemoryShareable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_SHAREABLE) ? true : false;
}

bool freeMemoryValue (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    sizt result = performMemoryOperation(segment, 5, NULL);

    if (!result) {
        return false;
    }

    return true;
}

bool disableReadFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_READ;
    return true;
}

bool enableWriteFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_WRITE;
    return true;
}

bool isMemoryExtendable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_EXTEND) ? true : false;
}

bool enableExtendFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_EXTEND;
    return true;
}

bool enableShrinkFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_SHRINK;
    return true;
}

bool isMemoryShrinkable (memory segment) {
    if (!segment) {
        return false;
    }

    return (segment -> attrib & MEM_SHRINK) ? true : false;
}

bool disableWriteFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= 0xFFFD;
    return true;
}

bool disableConstFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_CONST;
    return true;
}

bool enableMutableFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_MUTABLE;
    return true;
}

bool disableShrinkFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_SHRINK;
    return true;
}

bool disableExtendFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_EXTEND;
    return true;
}

bool setMem (memory * segment, mem value) {
    return setMemoryValue (segment, MEM, (gptr) value);
}

bool setCar (memory * segment, car value) {
    return setMemoryValue (segment, CAR, (gptr) &value);
}

bool disableMutableFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_MUTABLE;
    return true;
}

bool setScar (memory * segment, scar value) {
    return setMemoryValue (segment, SCAR, (gptr) &value);
}

bool enableReadWriteFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_READ | MEM_WRITE;
    return true;
}

bool enableShareableFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib |= MEM_SHAREABLE;
    return true;
}

bool setUcar (memory * segment, ucar value) {
    return setMemoryValue (segment, UCAR, (gptr) &value);
}

bool setByte (memory * segment, byte value) {
    return setMemoryValue (segment, BYTE, (gptr) &value);
}

bool setChar (memory * segment, char value) {
    return setMemoryValue (segment, CHAR, (gptr) &value);
}

bool setSshi (memory * segment, sshi value) {
    return setMemoryValue (segment, SSHI, (gptr) &value);
}

bool setUshi (memory * segment, ushi value) {
    return setMemoryValue (segment, USHI, (gptr) &value);
}

bool setSint (memory * segment, sint value) {
    return setMemoryValue (segment, SINT, (gptr) &value);
}

bool setUint (memory * segment, uint value) {
    return setMemoryValue (segment, UINT, (gptr) &value);
}

bool setSlng (memory * segment, slng value) {
    return setMemoryValue (segment, SLNG, (gptr) &value);
}

bool setUlng (memory * segment, ulng value) {
    return setMemoryValue (segment, ULNG, (gptr) &value);
}

bool setSllg (memory * segment, sllg value) {
    return setMemoryValue (segment, SLLG, (gptr) &value);
}

bool setUllg (memory * segment, ullg value) {
    return setMemoryValue (segment, ULLG, (gptr) &value);
}

bool setSizt (memory * segment, sizt value) {
    return setMemoryValue (segment, SIZT, (gptr) &value);
}

bool setFlot (memory * segment, flot value) {
    return setMemoryValue (segment, FLOT, (gptr) &value);
}

bool setDble (memory * segment, dble value) {
    return setMemoryValue (segment, DBLE, (gptr) &value);
}

bool setLdbl (memory * segment, ldbl value) {
    return setMemoryValue (segment, LDBL, (gptr) &value);
}

bool setStrg (memory * segment, strg value) {
    return setMemoryValue (segment, STRG, (gptr) value);
}

bool setBool (memory * segment, bool value) {
    return setMemoryValue (segment, BOOL, (gptr) &value);
}

bool memCopy (gptr src, gptr dst, sizt len) {
    if (!dst || !src || !len) {
        return false;
    }

    while (len > 0) {
        --len;
        ((byte *) dst) [len] = ((byte *) src) [len];
    }

    return true;
}

bool disableReadWriteFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~(MEM_READ | MEM_WRITE);
    return true;
}

bool disableShareableFlag (memory * segment) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    (*segment) -> attrib &= ~MEM_SHAREABLE;
    return true;
}

bool setString (memory * segment, string value) {
    return setMemoryValue (segment, STRING, (gptr) value);
}

bool setMemory (memory * segment, memory value) {
    return setMemoryValue (segment, MEMORY, (gptr) value);
}

bool setBoolean (memory * segment, boolean value) {
    return setMemoryValue (segment, BOOLEAN, (gptr) value);
}

bool changeMemoryType (memory *segment, enum dt type) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    if (!isType (type)) {
        return false;
    }
    
    if (type == VOID || type == GPTR) {
        return false;
    }

    if ((*segment) -> type == type) {
        return false;
    }

    if (!isMemoryMutable(*segment)) {
        return false;
    }

    sizt result = performMemoryOperation(segment, 4, (gptr []){(gptr) &type});

    if (!result) {
        return false;
    }

    return true;
}

bool nMemCopy (gptr src, gptr dst, sizt index, sizt len) {
    if (!dst || !src || !len) {
        return false;
    }

    if (index >= len) {
        return false;
    }

    for (sizt iterator = 0; iterator < len; ++iterator) {
        ((byte *) dst) [iterator] = ((byte *) src) [(iterator + index)];
    }

    return true;
}

bool setMemoryValue (memory * segment, enum dt type, gptr value) {
    if (!segment || !value) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    if (!isType (type)) {
        return false;
    }

    if (type == VOID || type == GPTR) {
        return false;
    }

    if (!isMemoryWritable(*segment) && isMemoryConstant(*segment)) {
        return false;
    }

    sizt result = performMemoryOperation(segment, 6, (gptr []) {(gptr) &type, value});

    return (!result) ? false : true;
}

bool changeMemoryAttribute (memory * segment, bool add_rem, enum attrib attrib) {
    if (!segment) {
        return false;
    }

    if (!*segment) {
        return false;
    }

    bool result = true;

    switch (attrib) {
        case READ:
            if (add_rem) {
                (*segment) -> attrib |= MEM_READ;
                break;
            }

            (*segment) -> attrib &= ~MEM_READ;
            break;
        case WRITE:
            if (add_rem) {
                (*segment) -> attrib |= MEM_WRITE;
                break;
            }

            (*segment) -> attrib &= ~MEM_WRITE;
            break;
        case CONST:
            if (add_rem) {
                (*segment) -> attrib |= MEM_CONST;
                break;
            }

            (*segment) -> attrib &= ~MEM_CONST;
            break;
        case SHRINK:
            if (add_rem) {
                (*segment) -> attrib |= MEM_SHRINK;
                break;
            }

            (*segment) -> attrib &= ~MEM_SHRINK;
            break;
        case EXTEND:
            if (add_rem) {
                (*segment) -> attrib |= MEM_EXTEND;
                break;
            }

            (*segment) -> attrib &= ~MEM_EXTEND;
            break;
        case MUTABLE:
            if (add_rem) {
                (*segment) -> attrib |= MEM_MUTABLE;
                break;
            }

            (*segment) -> attrib &= ~MEM_MUTABLE;
            break;
        case SHAREABLE:
            if (add_rem) {
                (*segment) -> attrib |= MEM_SHAREABLE;
                break;
            }

            (*segment) -> attrib &= ~MEM_SHAREABLE;
            break;
        default:
            result = false;
            break;
    }

    return result;
}

ushi getMemoryAttribute (memory segment) {
    if (!segment) {
        return 0;
    }

    return segment -> attrib;
}

sizt getMemoryLength (memory segment) {
    if (!segment) {
        return 0;
    }

    if (!isMemoryReadable(segment)) {
        return 0;
    }

    sizt length = performMemoryOperation(&segment, 3, NULL);
    
    if (!length) {
        return 0;
    }

    return length;
}

sizt getMemoryValueLength (memory segment) {
    if (!segment) {
        return 0;
    }

    if (!isMemoryReadable(segment)) {
        return 0;
    }

    sizt length = performMemoryOperation(&segment, 7, NULL);
    
    if (!length) {
        return 0;
    }

    return length;
}

enum dt getMemoryType (memory segment) {
    if (!segment) {
        return VOID;
    }

    if (!isMemoryReadable(segment)) {
        return VOID;
    }

    return segment -> type;
}

gptr getMemoryValue (memory segment) {
    if (!segment) {
        return NULL;
    }

    if (!isMemoryReadable (segment)) {
        return NULL;
    }

   return segment -> value;
}

gptr Malloc (enum dt type, sizt nBlocks) {
    if (nBlocks == 0 || !isType (type)) {
        return NULL;
    }

    if (type == VOID) {
        return NULL;
    }

    gptr obj = NULL;
    ucar limiter = 0;
    sizt index = findEmptySegment ();

    if (index == (sizt) -1) {
        return NULL;
    }
    
    do {++limiter; obj = malloc ((typeLength (type) * nBlocks));} while (limiter < 3 && !obj);

    if (obj) {
        limiter = 0;
        do {++limiter; blocks -> segments [index] = (memory) malloc (sizeof (struct _mem_));} while (limiter < 3 && !blocks -> segments [index]);

        if (!blocks -> segments [index]) {
            free (obj);
            obj = NULL;
            return NULL;
        }

        blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_MUTABLE | MEM_EXTEND | MEM_SHRINK;
        blocks -> segments [index] -> type = type;
        blocks -> segments [index] -> value = obj;
    }

    return obj;
}

gptr Calloc (enum dt type, sizt nBlocks) {
    if (nBlocks == 0 || !isType (nBlocks)) {
        return NULL;
    }

    if (type == VOID || type == GPTR) {
        return NULL;
    }

    gptr obj = NULL;
    ucar limiter = 0;
    sizt index = findEmptySegment ();

    if (index == (sizt) -1) {
        return NULL;
    }

    do {++limiter; obj = malloc ((typeLength (type) * nBlocks));} while (limiter < 3 && !obj);

    if (obj) {
        limiter = 0;
        do {++limiter; blocks -> segments [index] = (memory) malloc (sizeof (struct _mem_));} while (limiter < 3 && !blocks -> segments [index]);

        if (!blocks -> segments [index]) {
            free (obj);
            obj = NULL;
            return NULL;
        }

        blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_MUTABLE | MEM_SHRINK | MEM_EXTEND;
        blocks -> segments [index] -> type = type;
        blocks -> segments [index] -> value = obj;

        index = (typeLength (type) * nBlocks);
        for (sizt iterator = 0; iterator < index; ++iterator) {
            ((byte *) obj) [iterator] = 0;
        }
    }

    return obj;
}

memory allocate (enum dt type) {
    if (!isType (type)) {
        return NULL;
    }

    if (type == VOID || type == GPTR) {
        return NULL;
    }

    sizt index = findEmptySegment();

    if (index == (sizt) -1) {
        return NULL;
    }

    blocks -> segments [index] = (memory) malloc (sizeof (struct _mem_));

    if (!blocks -> segments [index]) {
        return NULL;
    }

    blocks -> segments [index] -> type = type;
    blocks -> segments [index] -> value = NULL;
    blocks -> segments [index] -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_SHRINK | MEM_EXTEND | MEM_MUTABLE;

    if (type == MEM || type == MEMORY) {
        blocks -> segments [index] -> value = (gptr) allocate (BOOLEAN);

        if (!blocks -> segments [index] -> value) {
            free (blocks -> segments [index]);
            blocks -> segments [index] = NULL;
            return NULL;
        }
    }

    if (!performMemoryOperation (&blocks -> segments [index], 1, (gptr []) {(gptr) &type})) {
        free (blocks -> segments [index]);
        blocks -> segments [index] = NULL;
    }

    return blocks -> segments [index];
}

memory getMemoryByValue (gptr value) {
    if (!value) {
        return NULL;
    }

    if (!blocks) {
        return NULL;
    }

    if (!blocks -> segments) {
        return NULL;
    }

    memory segment = NULL;

    for (sizt counter = 0; counter < blocks -> length; ++counter) {
        if (blocks -> segments [counter]) {
            if (value == blocks -> segments [counter] -> value) {
                segment = blocks -> segments [counter];
                break;
            }
        }
    }

    return segment;
}

memory nestedAllocate (enum dt t1, enum dt t2) {
    if (!isType (t1) || !isType (t2)) {
        return NULL;
    }

    if (t1 != MEM && t1 != MEMORY) {
        return NULL;
    }

    if (t2 == MEM || t2 == MEMORY) {
        return NULL;
    }

    sizt i1 = findEmptySegment ();

    if (i1 == (sizt) -1) {
        return NULL;
    }

    blocks -> segments [i1] = (memory) malloc (sizeof (struct _mem_));

    if (!blocks -> segments [i1]) {
        return NULL;
    }

    blocks -> segments [i1] -> type = t1;
    blocks -> segments [i1] -> value = NULL;
    blocks -> segments [i1] -> attrib = MEM_READ | MEM_WRITE | MEM_DEFVAL | MEM_SHRINK | MEM_WRITE | MEM_MUTABLE;

    blocks -> segments [i1] -> value = (gptr) allocate (t2);

    if (!blocks -> segments [i1] -> value) {
        free (blocks -> segments [i1]);
        blocks -> segments [i1] = NULL;
    }

    return blocks -> segments [i1];
}