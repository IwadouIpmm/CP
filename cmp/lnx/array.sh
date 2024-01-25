cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/array.o array.c

if [ $? = 0 ]
then
	cd ../lib
	ar rcv libcp-lnx.a ../bin/array.o
	cd ../cmp
	echo Array compilation is successful.
else
	cd ../cmp
fi
