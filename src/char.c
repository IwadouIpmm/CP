#include "../hdr/redef.h"
#include "../hdr/char.h"

bool isChar (char _car) {
	return ((_car >= 32 && _car <= 126) || isWhiteSpace (_car) || _car == 10 || _car == 13 || _car == 0 || _car == 8) ? true : false;
}

bool isHtab (char _car) {
	return (_car == 9) ? true : false;
}
	
bool isVtab (char _car) {
	return (_car == 11) ? true : false;
}

bool isAlpha (char _car) {
	return ((_car >= 65 && _car <= 90) || (_car >= 97 && _car <= 122)) ? true : false;
}

bool isLower (char _car) {
	return (_car >= 97 && _car <= 122) ? true : false;
}

bool isUpper (char _car) {
	return (_car >= 65 && _car <= 90) ? true : false;
}

bool isSpace (char _car) {
	return (_car == 32) ? true : false;
}

bool isNumber (char _car) {
	return (_car >= 48 && _car <= 57) ? true : false;
}

bool isSpecial (char _car) {
	return ((_car >= 33 && _car <= 47) || (_car >= 58 && _car <= 64) || (_car >= 91 && _car <= 96) || (_car >= 123 && _car <= 126)) ? true : false;
}

bool isLineFeed (char _car) {
	return (_car == 10) ? true : false;
}

bool isFormFeed (char _car) {
	return (_car == 12) ? true : false;
}

bool isBackSpace (char _car) {
	return (_car == 8) ? true : false;
}

bool isWhiteSpace (char _car) {
	return (_car == 32 || _car == 9 || _car == 11 || _car == 12) ? true : false;
}

bool isAlphaNumeric (char _car) {
	return (isAlpha (_car) || isNumber (_car)) ? true : false;
}

bool isAlphaSpecial (char _car) {
	return (isAlpha (_car) || isSpecial (_car)) ? true : false;
}

bool isNumericSpecial (char _car) {
	return (isNumber (_car) || isSpecial (_car)) ? true : false;
}

bool isCarriageReturn (char _car) {
	return (_car == 13) ? true : false;
}

bool isNullTerminator (char _car) {
	return (_car == 0) ? true : false;
}

bool isAlphaNumericSpecial (char _car) {
	return (isAlpha (_car) || isNumber (_car) || isSpecial (_car)) ? true : false;
}

char charToLower (char _car) {
	return (isUpper (_car)) ? (_car + 32) : 0;
}

char charToUpper (char _car) {
	return (isLower (_car)) ? (_car - 32) : 0;
}

byte getCharCode (char _car) {
	return (byte) _car;
}