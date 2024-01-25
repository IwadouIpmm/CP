#ifndef __C_STRING_HF__
#define __C_STRING_HF__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	void showStringInfo (strg str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	gptr * split (strg str, char splitter);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	gptr * stringMeta (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	gptr * splitString (strg str, strg splitter);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean trim (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean title (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean reverse (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean swapCase (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean setTabWidth (byte width);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean isStringEmpty (strg str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean cut (strg * str, sizt si);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean termSplit (gptr ** splits);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean stringToUpper (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean stringToLower (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean endWith (strg str, strg end);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean termStringMeta (gptr ** meta);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean zfill (strg * str, boolean lp);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean removeExtraSpaces (strg * str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean contain (strg str, strg check);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean concat (strg * str, strg append);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean startWith (strg str, strg start);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean stringCompare (strg str1, strg str2);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean overwrite (strg * str_1, strg str_2);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean replace (strg * str, strg toReplace);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean * cuts (strg * str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean * contains (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean * concats (strg * str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	boolean * stringCompareN (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	car getCharAt (strg str, sizt index);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	car * getCharsAt (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	byte getTabWidth (void);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg getNL (void);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg getTab (void);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg getNewLine (void);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg stringCopy (strg str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg slice (strg str, sizt si, sizt end);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg subString (strg str, sizt si, sizt ei);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg toString (gptr value, enum dt type);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg getStringStartingFrom (strg str, sizt si);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg * getStringsStartingFrom (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg * slices (strg str, sizt n, sizt * si, sizt * ei);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	strg * subStrings (strg str, sizt n, sizt * si, sizt * ei);

	/*
	 * INPT: A string.
	 * OTPT: Returns a sizt value. If string is empty returns 0.
	 * INFO: This function is used to returns the length of a string.
	*/
	sizt stringLength (strg str);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	sizt getIndexOf (strg str, strg check);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	sizt occurrence (strg str, strg toCount);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	sizt repaceAll (strg * str, strg toReplace);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	sizt * occurrences (strg str, sizt n, ...);

	/*
	 * INPT: 
	 * OTPT: 
	 * INFO: 
	*/
	sizt * getIndicesOf (strg str, sizt n, ...);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__C_STRING_HF__