Progeam = AddressBook
objects = main.o file.o func.o cliFunc.o language.o
CC = gcc

$(Progeam) : $(objects)
		$(CC) -o $(Progeam) $(objects)
		@echo "    _       _     _                   ____              _     "
		@echo "   / \   __| | __| |_ __ ___  ___ ___| __ )  ___   ___ | | __ "
		@echo "  / _ \ / _` |/ _` | '__/ _ \/ __/ __|  _ \ / _ \ / _ \| |/ / "
		@echo " / ___ \ (_| | (_| | | |  __/\__ \__ \ |_) | (_) | (_) |   <  "
		@echo "/_/   \_\__,_|\__,_|_|  \___||___/___/____/ \___/ \___/|_|\_\ "

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