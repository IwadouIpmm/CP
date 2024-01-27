#ifndef __C_MEMORY_HF__
#define __C_MEMORY_HF__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

    typedef struct _mem_ * mem;
    typedef struct _mem_ * memory;

#   define MEM_READ      0x0001 //Read only flag.
#   define MEM_WRITE     0x0002 //Write only flag.
#   define MEM_CONST     0x0004 //Constant value flag.
#   define MEM_DEFVAL    0x0008 //Default Value flag.
#   define MEM_SHRINK    0x0010 //Allow Shrink flag.
#   define MEM_EXTEND    0x0020 //Allow Extend flag.
#   define MEM_MUTABLE   0x0040 //Allow value type flag.
#   define MEM_SHAREABLE 0x0080 //Allow value to be shared on a network.

    enum attrib {READ = 1, WRITE, CONST = 4, SHRINK = 16, EXTEND = 32, MUTABLE = 64, SHAREABLE = 128};

    /*
     * INPT: Non.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to remove all allocated memory segments during the run-time of an application.
     * */
    bool freeAll (void);

    /*
     * INPT: A gptr.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to deallocate an allocated object from Malloc or Calloc function.
    */
    bool Free (gptr address);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to deallocate a specific memory segment.
     * */
    bool deallocate (memory * segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true if empty, otherwise returns false if not empty.
     * INFO: This function is used to check if either memory segment is empty or memory segment value is empty.
     * */
    bool isMemoryEmpty (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Return true on if exist, otherwise returns false if not.
     * INFO: This function is used to check if a memory segment exists or not.
     * */
    bool doesMemoryExist (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if a memory segment attribute is mutable or not.
    */
    bool isMemoryMutable (memory segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable read flag option to our memory segment.
    */
    bool enableReadFlag (memory * segment);

    /*
     * INFO: A memory segment.
     * OTPT: Returns true on success, otherwise return false on failure.
     * INFO: This function is used to check if we can read from a memory segment value.
    */
    bool isMemoryReadable (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if we can write a value to a memory segment.
    */
    bool isMemoryWritable (memory segment);
    
    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function check if the change memory segment value from the default value.
    */
    bool hasMemoryChanged (memory segment);
    
    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if the memory segment is a constant value.
    */
    bool isMemoryConstant (memory segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to only deallocate memory segment value not the memory segment itself.
     * */
    bool freeMemoryValue (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to disable read flag for a memory segment.
    */
    bool disableReadFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable write flag/option on a memory segment.
    */
    bool enableWriteFlag (memory * segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if a memory segment can be shared over a network.
    */
    bool isMemoryShareable (memory segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise return false on failure.
     * INFO: This function enable const flag to a memory segment.
    */
    bool enableConstFlag (memory * segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if a memory value can be extended.
    */
    bool isMemoryExtendable (memory segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable extend flag to a memory segment.
    */
    bool enableExtendFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable shrink flag to a memory segment.
    */
    bool enableShrinkFlag (memory * segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to check if a memory value can be shrinked.
    */
    bool isMemoryShrinkable (memory segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on a failure.
     * INFO: This function is used to disable write flag of a memory segment.
    */
    bool disableWriteFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on a failure.
     * INFO: This function is used to disable const flag of a memory segment.
    */
    bool disableConstFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable a mutable option for memory segment.
    */
    bool enableMutableFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to disable a mutable option for memory segment.
    */
    bool disableShrinkFlag (memory * segment);
    
    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to disable a extend option for memory segment.
    */
    bool disableExtendFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment (where we will set value) and a memory segment (a value to set to our main segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type memory segment.
    */
    bool setMem (memory * segment, mem value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a car (which only accept ascii/unicode characters).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type car.
    */
    bool setCar (memory * segment, car value);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to disable a mutable flag for memory segment.
    */
    bool disableMutableFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a scar (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to add/set a scar value to a memory segment.
    */
    bool setScar (memory * segment, scar value);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to enable read and write flag to a memory segment.
    */
    bool enableReadWriteFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This funtion is used to enable shareable flag to a memory segment.
    */
    bool enableShareableFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and an ucar (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to add/set an ucar value to a memory segment.
    */
    bool setUcar (memory * segment, ucar value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a byte (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to add/set a byte value to our memory segment value.
    */
    bool setByte (memory * segment, byte value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a char (which only accept ascii/unicode characters).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type char.
    */
    bool setChar (memory * segment, char value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a sshi (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type sshi.
    */
    bool setSshi (memory * segment, sshi value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and an ushi (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type ushi.
    */
    bool setUshi (memory * segment, ushi value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a sint (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type sint.
    */
    bool setSint (memory * segment, sint value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and an uint (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type uint.
    */
    bool setUint (memory * segment, uint value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a slng (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type slng.
    */
    bool setSlng (memory * segment, slng value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and an ulng (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type ulng.
    */
    bool setUlng (memory * segment, ulng value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a sllg (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type sllg.
    */
    bool setSllg (memory * segment, sllg value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and an ullg (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type ullg.
    */
    bool setUllg (memory * segment, ullg value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a sizt (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type sizt.
    */
    bool setSizt (memory * segment, sizt value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a flot (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type flot.
    */
    bool setFlot (memory * segment, flot value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a dble (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type dble.
    */
    bool setDble (memory * segment, dble value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a ldbl (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type ldbl.
    */
    bool setLdbl (memory * segment, ldbl value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a strg (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type strg.
    */
    bool setStrg (memory * segment, strg value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a bool (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type bool.
    */
    bool setBool (memory * segment, bool value);

    /*
     * INPT: A gptr (which points to source), a gptr (which points to the destination), and a sizt (which holds the number of bytes to copy).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to copy number of bytes from the source to destination. The source and destination must be already allocated.
    */
    bool memCopy (gptr src, gptr dst, sizt len);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to disable both read and write flage for a memory segment.
    */
    bool disableReadWriteFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment.
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to remove the shareable flag from memory segment.
    */
    bool disableShareableFlag (memory * segment);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a string (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type string.
    */
    bool setString (memory * segment, string value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a memory (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type memory.
    */
    bool setMemory (memory * segment, memory value);

    /*
     * INPT: A pointer to a memory segment (where we will set a value) and a boolean (which a value to add in our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set memory segment value of type boolean.
    */
    bool setBoolean (memory * segment, boolean value);

    /*
     * INPT: A pointer to a memory segment and an enum dt type (which tells us which datatype we want to change to).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used change the datatype of memory segment value. In case of a user provides the same type
     *       nothing will happen and this will be seems as operation has been successfull.
     * */
    bool changeMemoryType (memory * segment, enum dt type);

    /*
     * INPT: A gptr (which points to source), a gptr (which points to destination), a sizt (which points to the index where to start copying from source), and sizt (which holds the number of bytes to copy).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to copy number of bytes from source to a destination starting from a specific location from the source.
    */
    bool nMemCopy (gptr dst, gptr src, sizt index, sizt len);

    /*
     * INPT: A pointer to a memory segment (where we assign a value), an enum dt (to tells us which datatype we are dealing with), and a gptr (which holds the data we want to assign to our memory segment).
     * OTPT: Returns true on success, otherwise returns false on failure.
     * INFO: This function is used to set a value to our memory segment and THIS IS VERY IMPORTANT (PASS THE CORRECT enum dt and gptr OTHERWISE UNDEFINED BEHAVIOR MAY OCCURS).
     *       If you have any issues using this funtion, then use our explict function where you can set a specific type.
    */
    bool setMemoryValue (memory * segment, enum dt type, gptr value);

    /*
     * INPT: A pointer to a memory segment, a boolean value (which tells us either to enable or disable a flag), and an enum attrib (which holds which flag to change).
     * OTPT: Return true on success, otherwise returns false on failure.
     * INFO: This function is used to either enable or disable a specific memory segment attribute. To add pass (true) to remove pass (false).
    */
    bool changeMemoryAttribute (memory * segment, bool add_rem, enum attrib attrib);

    /*
     * INPT: A memory segment.
     * OTPT: Return an ushi.
     * INFO: This function returns memory segment attribute.
    */
    ushi getMemoryAttribute (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns a sizt value on success, otherwise returns 0 on failure.
     * INFO: This function is used to returns the length/size of memory segment and memory segment value.
     *       To get the actual length of the memory segment value subtract the return value from dtLength (MEM or MEMORY).
     *       Or use getMemoryValueLength (memory segment) function.
     * */
    sizt getMemoryLength (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns a sizt value on success, otherwise returns 0 on failure.
     * INFO: This function is used to returns the length/size of memory segment value.
     * */
    sizt getMemoryValueLength (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns enum dt value on success, otherwise returns VOID value on failure.
     * INFO: This function is used to return the datatype of memory segment value.
     * */
    enum dt getMemoryType (memory segment);

    /*
     * INPT: A memory segment.
     * OTPT: Returns a memory segment value of type gptr.
     * INFO: This function is used to get memory segment value. A user must cast the output of this function to dereference the actual value.
     * */
    gptr getMemoryValue (memory segment);

    /*
     * INPT: An enum dt (which holds the type), a sizt (which holds the number of blocks to allocate of the same type).
     * OTPT: Return gptr on success, otherwise returns NULL on failure.
     * INFO: This function acts as a wrapper of malloc function, where when we allocate and failure occurs we try to allocate two times before returning an error
     *       value of gptr value.
     * */
    gptr Malloc (enum dt type, sizt nBlocks);

    /*
     * INPT: An enum dt (which holds the type), a sizt (which holds the number of blocks to allocate of the same type).
     * OTPT: Returns a gptr on success, otherwise returns NULL on failure.
     * INFO: This function is used to create a memory block of size length and initialize it with 0 value.
    */
    gptr Calloc (enum dt type, sizt nBlocks);

    /*
     * INPT: An enum dt .
     * OTPT: Returns a memory segment on success, otherwise returns NULL on failure.
     * INFO: This function is used create a memory segment. Acts as a wrapper around to malloc and allow the user to keep track
     *       of all allocated object during the run-time of an application and have the ability to deallocated all allocated objects
     *       at any time during the run-time of an application or deallocate all object at the end of an application run-time through
     *       inkoving/calling boolean/bool freeAll (void) function.
     *
     *       Each memory segment allocated will have these attribute:
     *              1-READ, 2-WRITE, 3-DEFVAL, 4-MUTABLE, 5-SHIRNK, 6-EXTEND.
     *
     *       If the passed element was of value MEM or MEMORY, then another memory segment will be created of type BOOLEAN.
     *
     *       If the type passed is ARRY or ARRAY, then we create an empty array with type VOID with length of 0. (To change the type use changeArrayType function).
     * */
    memory allocate (enum dt type);

    /*
     * INPT: A gptr (which hold a value address which should points us to a memory segment).
     * OTPT: Returns a memory segment on success, otherwise returns NULL on failure.
     * INFO: This function is used to return a memory segment associated with an address value. If the passed value is
     *       either MEM or MEMORY the nested memory segment value will be of type BOOLEAN.
    */
    memory getMemoryByValue (gptr value);

    /*
     * INPT: An enum dt (which will only accept MEM or/and MEMORY) and an enum dt (which will hold any type accept for MEM or/and MEMORY).
     * OTPT: Returns memory on success, otherwise returns NULL on failure.
     * INFO: This function is used to allow a user to allocated a memory segment as a value of another memory segment.
     *       1-The first argument (parameter): will (MEM or MEMORY) and (ARRAY or ARRY).
     *       2-The second argument (parameter): will accept anythin except for both (MEM or MEMORY) and (ARRAY or ARRY).
    */
    memory nestedAllocate (enum dt t1, enum dt t2);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__C_MEMORY_HF__