#ifndef __C_CHAR_HF__
#define __C_CHAR_HF__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if passed character is either one of the follwing:
	 *		 1-isAlpha, isNumber, isSpecial, isWhiteSpace, isLineFeed, isCarriageReturn.
	*/
	bool isChar (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false.
	 * INFO: This function is used to check if a character is a horizental tab.
	*/
	bool isHtab (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false.
	 * INFO: This function is used to check if passed character is vertical tab.
	*/
	bool isVtab (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if passed character is either lowerCase or UpperCase.
	*/
	bool isAlpha (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is a lower case or not.
	*/
	bool isLower (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is an upper case or not.
	*/
	bool isUpper (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is a space from the space bar.
	*/
	bool isSpace (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is a numeric value or not.
	*/
	bool isNumber (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if passed character is a special case character.
	*/
	bool isSpecial (char _car);	

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if passed character is a line feed (new line).
	*/
	bool isLineFeed (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if passed character is a form feed (\f (new page)).
	*/
	bool isFormFeed (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is a backspace character (\b).
	*/
	bool isBackSpace (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is any for of space.
	*/
	bool isWhiteSpace (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is either an alphabetical or a numeric value.
	*/
	bool isAlphaNumeric (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is either alphabetical or a special value.
	*/
	bool isAlphaSpecial (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is numeric or special character.
	*/
	bool isNumericSpecial (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is check if passed character is carriage return (\r (return to the beginning to the line)).
	*/
	bool isCarriageReturn (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is Null terminator (\0).
	*/
	bool isNullTerminator (char _car);

	/*
	 * INFO: A char.
	 * OTPT: Returns true on success, otherwise returns false on failure.
	 * INFO: This function is used to check if a passed character is either on of the following (alphabetical, numeric, or special).
	*/
	bool isAlphaNumericSpecial (char _car);

	/*
	 * INFO: A char.
	 * OTPT: A char.
	 * INFO: This function is used to convert an uppercase character to lowercase character.
	*/
	char charToLower (char _car);

	/*
	 * INFO: A char.
	 * OTPT: A char.
	 * INFO: This function is used to convert a lowercase character to an uppercase character.
	*/
	char charToUpper (char _car);

	/*
	 * INFO: A char.
	 * OTPT: A byte.
	 * INFO: This function is used to return the numeric value of a character.
	*/
	byte getCharCode (char _car);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__C_CHAR_HF__