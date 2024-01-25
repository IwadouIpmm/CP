#ifndef __C_ARRAY_HF__
#define __C_ARRAY_HF__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	typedef struct _array_ * arry;
	typedef struct _array_ * array;

	/*
	 * INPT: A pointer to an array.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to remove/deallocate an array.
	*/
	bool termArray (array * arr);

	/*
	 * INPT: A pointer to an array, a sizt (which holds the length of the new array).
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to change the length of the array.
	 * 		 If the new length is lower than the current length then remove the additional values.
	 * 		 If the new length is greater than the current length then add a default value to the new indices.
	*/
	bool setArrayLength (array * arr, sizt length);

	/*
	 * INPT: A pointer to an array and an enum dt (which tells us which datatype we are dealing with).
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is to change the type of an array, and by doing that we remove all values reside in an array.
	*/
	bool changeArrayType (array * arr, enum dt type);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addCarToArray (array * arr, sizt index, car value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addMemToArray (array * arr, sizt index, mem segment);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addBoolToArray (array * arr, sizt index, bool value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addCharToArray (array * arr, sizt index, char value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addScarToArray (array * arr, sizt index, scar value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addUcarToArray (array * arr, sizt index, ucar value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addSshiToArray (array * arr, sizt index, sshi value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addUshiToArray (array * arr, sizt index, ushi value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addSintToArray (array * arr, sizt index, sint value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addUintToArray (array * arr, sizt index, uint value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addSlngToArray (array * arr, sizt index, slng value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addUlngToArray (array * arr, sizt index, ulng value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addSllgToArray (array * arr, sizt index, sllg value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addUllgToArray (array * arr, sizt index, ullg value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addSiztToArray (array * arr, sizt index, sizt value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addFlotToArray (array * arr, sizt index, flot value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addDbleToArray (array * arr, sizt index, dble value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addLdblToArray (array * arr, sizt index, ldbl value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addStrgToArray (array * arr, sizt index, strg value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addArryToArray (array * arr, sizt index, arry value);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	bool addArrayToArray (array * arr, sizt index, array value);

	/*
	 * INPT: A pointer to an array, a sizt (which tells us which index to set the value), a string (which holds the value to assign to a specific index).
	 * OTPT: Return true on success, otherwise returns false on failure.
	 * INFO: This function is used to set a string, by creating a copy of it to a specific index in an array.
	*/
	bool addStringToArray (array * arr, sizt index, string value);

	/*
	 * INPT: A pointer to an array, a sizt (which tells us which index to set the value), a boolean (which holds the value to assign to a specific index).
	 * OTPT: Return true on success, otherwise returns false on failure.
	 * INFO: This function is used to set a boolean value, by creating a copy of it to a specific index in an array.
	*/
	bool addBooleanToArray (array * arr, sizt index, boolean value);

	/*
	 * INPT: A pointer to an array, a sizt (which tells us which index to set the value), a memory (which holds the value to assign to a specific index).
	 * OTPT: Return true on success, otherwise returns false on failure.
	 * INFO: This function is used to set a memory segment, by creating a copy of it to a specific index in an array.
	*/
	bool addMemoryToArray (array * arr, sizt index, memory segment);

	/*
	 * INPT: A pointer to an array, a sizt (which tells us which index to access),
	         an enum dt (tells us which datatype we are dealing with), and a gptr (holds the value we need to assign).
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to change a value of a specific index while the passed value type equal to the type of an array.
	 * 		 Make sure you pass the correct type or undefined behaviors may occur.
	*/
	bool addValueToArray (array * arr, sizt index, enum dt type, gptr value);

	/*
	 * INPT: An array.
	 * OTPT: Returns a sizt on success.
	 * INFO: This function is used to how many cells in an array.
	*/
	sizt getArrayLength (array arr);

	/*
	 * INPT: An array.
	 * OTPT: Returns sizt on success, otherwise returns 0.
	 * INFO: This function is used to get the length of an array and the sizeof each object in it.
	*/
	sizt arrayFullLength (array arr);

	/*
	 * INPT: An array and a sizt (which tells us which array cell to get its length).
	 * OTPT: Returns sizt on success, otherwise returns 0.
	 * INFO: This function is used to get the length of an object in an array.
	*/
	sizt getArrayLengthAt (array arr, sizt index);

	/*
	 * INPT: An array and sizt value (tells us which index to use).
	 * OTPT: Returns a gptr on success, otherwise returns NULL on failure.
	 * INFO: This function is used to get an array value at a specific index of that array.
	*/
	gptr getArrayValueAt (array arr, sizt index);

	/*
	 * INPT: An array.
	 * OTPT: Returns an enum dt value on success, otherwise returns VOID on failure.
	 * INFO: This function is used to return the type of an array.
	*/
	enum dt getArrayType (array arr);

	/*
	 * INPT: An array and a sizt (which tells us which index we need to get its type).
	 * OTPT: Returns an enum dt value on success, otherwise returns VOID on failure.
	 * INFO: This function is used to get the type of a specific index in an array.
	*/
	enum dt getArrayTypeAt (array arr, sizt index);

	/*
	 * INPT: A sizt (tells how many array cells will be allocated) and an enum dt (which tells us which datatype we are dealing with).
	 * OTPT: Returns an array on success, otherwise returns NULL on failure.
	 * INFO: This function is used to initialized an array (with size and type).
	 * 		 VERY IMPORTANT: when we use this function a memory segment is created which hold our allocated array and we return this memory segment value.
	*/
	array initArray (sizt length, enum dt type);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__C_ARRAY_HF__