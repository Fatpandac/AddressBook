Progeam = AddressBook
objects = main.o file.o func.o cliFunc.o language.o global.o
CC = gcc

$(Progeam) : $(objects)
		@$(CC) -o $(Progeam) $(objects)
		@echo + Successfully built +

main.o     : language.h file.h func.h cliFunc.h global.h
func.o     : language.h file.h func.h cliFunc.h	global.h
cliFunc.o  : language.h cliFunc.h
file.o     : language.h file.h
global.o   : global.h
language.o : language.h


.PHONY: clean
clean :
ifeq ($(OS),Windows_NT)
	del $(objects) $(Progeam)
else
	rm $(objects) $(Progeam)
endif
