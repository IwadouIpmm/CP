cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/char.o char.c

if [ $? = 0 ]
then
	cd ../lib
	ar rcv libcp-lnx.a ../bin/char.o
	cd ../cmp
	echo Char compilation is successful.
else
	cd ../cmp
fi
