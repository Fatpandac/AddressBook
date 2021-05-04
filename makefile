Progeam = AddressBook
objects = main.o file.o func.o cliFunc.o language.o global.o TUI.o control.o tuiFunc.o theme.o
CC = gcc

$(Progeam) : $(objects)
		@$(CC) -o $(Progeam) $(objects)
		@echo + Successfully built +

main.o     : language.h file.h global.h cliFunc.h func.h 

cliFunc.o  : language.h file.h global.h cliFunc.h
func.o     : language.h file.h global.h func.h 

tuiFunc.o  : tuiFunc.h  file.h control.h theme.h global.h
TUI.o 	   : tuiFunc.h  file.h control.h theme.h
control.o  : tuiFunc.h  file.h control.h theme.h

global.o   : language.h file.h global.h
file.o     : language.h file.h
language.o : language.h
theme.o    : theme.h


.PHONY: clean
clean :
ifeq ($(OS),Windows_NT)
	del $(objects) $(Progeam)
else
	rm $(objects)
endif
