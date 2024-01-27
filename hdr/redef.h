#ifndef __C_REDEF_HF__
#define __C_REDEF_HF__

#ifdef __cplusplus
extern "C" {
#endif //For __cplusplus

#   ifndef True
#   define True 1
#   endif //True

#   ifndef true
#   define true 1
#   endif //true

#   ifndef False
#   define False 0
#   endif //False

#   ifndef false
#   define false 0
#   endif //false

#   ifndef NULL
#   define NULL ((void *) 0)
#   endif //NULL

#   ifdef __STDC__
    typedef void * gptr;
#   else
    typedef char * gptr;
#   endif // __STDC__

    /* To know these macros please visit the following site: https://sourceforge.net/p/predef/wiki/Home/
     * */
#   if __STDC_VERSION__ >= 199901L
    typedef _Bool bool;
    typedef _Bool boolean;
#   else
    typedef unsigned char bool;
    typedef unsigned char boolean;
#   endif //__STDC_VERSION__

    typedef char car;
    typedef char scar;
    typedef unsigned char ucar;
    typedef unsigned char byte;
    typedef short sshi;
    typedef unsigned short ushi;
    typedef int sint;
    typedef unsigned int uint;
    typedef long slng;
    typedef unsigned long ulng;
    typedef long long sllg;
    typedef unsigned long long ullg;
    typedef float flot;
    typedef double dble;
    typedef long double ldbl;
    typedef char * string;
    typedef char * strg;

#   if __x86_64__ || __x86_64 || __amd64__ || __amd64 || __aarch64__ || __ia64__ || _IA64 || __IA64__
#       if defined(_INC_STDIO) || defined(_STDIO_H_) || defined(__STDIO_H) || defined(_INC_STDLIB) || defined(_STDLIB_H_) || defined(__STDLIB_H)
        typedef size_t sizt;
#       else
        typedef unsigned long long sizt;
#       endif //if defined ...
#   else
        typedef unsigned int sizt;
#   endif //if __x86_64__ ...

#   if _WIN16 || _WIN32 || _WIN64 || __MSDOS__ || _MSDOS || __DOS__ || MSDOS
#       ifndef nl
#           define nl "\r\n"
#       endif //nl
#       ifndef newLine
#           define newLine "\r\n"
#       endif //newLine
#   else
#       ifndef nl
#           define nl "\n"
#       endif //nl
#       ifndef newLine
#           define newLine "\n"
#       endif //newLine
#   endif //_WIN16 ...

    /*
     * VOID = 00, Void type.
     * BOOLEAN = 01, Booleab type.
     * BOOL = 02, Bool type.
     * CHAR = 03, For character type.
     * CAR = 04, For character type.
     * SCAR = 05, Signed character type.
     * UCAR = 06, unsigned character type.
     * BYTE = 07, Byte type type.
     * SSHI = 08, Signed short int type.
     * USHI = 09, Unsigned Short int type.
     * SINT = 10, Signed int type.
     * UINT = 11, Unsigned int type.
     * slng = 12, signed long int type.
     * ulng = 13, unsigned long int type.
     * sllg = 14, signed long long int type.
     * ullg = 15, unsigned long long int type.
     * sizt = 16, Size_t type.
     * FLOT = 17, Float type.
     * DBLE = 18, Double type.
     * LDBL = 19, Long double type.
     * GPTR = 20, Generic Pointer (void *) type.
     * STRING = 21, For string type.
     * STRG = 22, For string type.
     * MEM = 23, For Memory type.
     * Memory = 24, For Memory Type.
     * ARRY = 25, for an array type.
     * ARRAY = 26, for an array type.
     * */
    enum dt {VOID, BOOLEAN, BOOL, CHAR, CAR, SCAR, UCAR, BYTE, SSHI, USHI, SINT, UINT, SLNG, ULNG, SLLG, ULLG, SIZT, FLOT, \
             DBLE, LDBL, STRING, STRG, GPTR, MEM, MEMORY, ARRY, ARRAY};

    /*
     * INPT: Enum dt, which tells us which value we might use.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if passed enum dt value is correct or not.
     * */
    boolean isType (enum dt type);

    /*
     * INPT: An enum dt.
     * OTPT: Returns sizt value on success, otherwise returns -1 on failure.
     * INFO: This function is used to return the datatype length.
    */
    sizt typeLength (enum dt type);

#ifdef __cplusplus
}
#endif //For __cplusplus
#endif //For __C_REDEF_HF__