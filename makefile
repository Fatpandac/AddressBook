Progeam = AddressBook
objects = main.o file.o func.o cliFunc.o language.o global.o
CC = gcc

$(Progeam) : $(objects)
		@$(CC) -o $(Progeam) $(objects)
		@echo + Successfully built +

main.o     : language.h file.h global.h cliFunc.h func.h 
cliFunc.o  : language.h file.h global.h cliFunc.h
func.o     : language.h file.h global.h func.h 
global.o   : language.h file.h global.h
file.o     : language.h file.h
language.o : language.h


.PHONY: clean
clean :
ifeq ($(OS),Windows_NT)
	del $(objects) $(Progeam)
else
	rm $(objects) $(Progeam)
endif
