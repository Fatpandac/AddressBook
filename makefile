Progeam = AddressBook
objects = main.o file.o func.o cliFunc.o language.o
CC = gcc

$(Progeam) : $(objects)
		$(CC) -o $(Progeam) $(objects)

main.o     : language.h file.h func.h cliFunc.h
func.o     : language.h file.h func.h cliFunc.h
cliFunc.o  : language.h cliFunc.h
file.o     : language.h file.h
language.o :

.PHONY: clean
clean :
ifeq ($(OS),Windows_NT)
	del $(objects) $(Progeam)
else
	rm $(objects) $(Progeam)
endif