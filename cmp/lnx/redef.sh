cd ../../src

gcc -Wall -Werror -Wextra -std=c99 -O3 -c -o../bin/redef.o redef.c

if [ $? = 0 ]
then
	cd ../lib
	ar rcv libcp-lnx.a ../bin/redef.o
	cd ../cmp
	echo Redef compilation is successful.
else
	cd ../cmp
fi
