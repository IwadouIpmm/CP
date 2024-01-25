cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/string.o string.c

if [ $? = 0 ]
then
	cd ../lib
	ar rcv libcp-lnx.a ../bin/string.o
	cd ../cmp
	echo String compilation is successful.
else
	cd ../cmp
fi
