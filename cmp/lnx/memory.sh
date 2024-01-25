cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/memory.o memory.c

if [ $? = 0 ]
then
	cd ../lib
	ar rcv libcp-lnx.a ../bin/memory.o
	cd ../cmp
	echo Memory compilation is successful.
else
	cd ../cmp
fi
