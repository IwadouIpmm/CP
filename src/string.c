#include "../hdr/redef.h"
#include "../hdr/memory.h"
#include "../hdr/string.h"

sizt stringLength(strg str) {
	if (!str) {
		return (sizt) 0;
	}

	sizt length = 0;

	while (str [length] != '\0') {
		++length;
	}

	return length;
}