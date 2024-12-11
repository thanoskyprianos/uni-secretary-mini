CC = g++
OBJS = Person/person.o Secretary/secretary.o Util/util.o
FLAGS = -Werror -Wall -Wextra -pedantic -O3
MAKE = make -s --no-print-directory

CYAN = \033[1;96m
RED = \033[1;91m
GREEN = \033[0;92m
RESET = \033[0m

main: main.o $(OBJS)
	@$(CC) $(FLAGS) -o main main.o $(OBJS)

	@printf "$(CYAN)Created: $(RESET)main \n\n"
	@printf "$(GREEN)To run the program execute: $(RESET)./main \n"

help:
	@printf "$(GREEN) make $(RESET)|| $(GREEN)make main $(RESET): $(CYAN)Compile secretary program. \n"
	@printf "$(GREEN) make showcase $(RESET): $(CYAN)Compile showcase program, used to showcase extra functions not used in main. \n"
	@printf "$(GREEN) make clean $(RESET): $(CYAN)Clean object files and execuatables.$(RESET) \n"

showcase: showcase.o $(OBJS)
	@$(CC) $(FLAGS) -o showcase showcase.o $(OBJS)

	@printf "$(CYAN)Created: $(RESET)showcase \n\n"
	@printf "$(GREEN)To run the program execute: $(RESET)./showcase\n"

main.o: main.cpp
	@$(CC) $(FLAGS) -c main.cpp

	@printf "$(CYAN)Created: $(RESET)main.o \n"
	
showcase.o: showcase.cpp
	@$(CC) $(FLAGS) -c showcase.cpp

	@printf "$(CYAN)Created: $(RESET)showcase.o \n"

Person/person.o: Person/person.cpp
	@$(MAKE) -C Person person.o

Secretary/secretary.o: Secretary/secretary.cpp
	@$(MAKE) -C Secretary secretary.o

Util/util.o: Util/util.cpp Util/util.h
	@$(MAKE) -C Util util.o

.PHONY: clean
clean:
	@rm -f main showcase *.o
	@printf "$(RED)Deleted: $(RESET)main, main.o, showcase, showcase.o \n"

	@$(MAKE) -C Person clean
	@$(MAKE) -C Secretary clean
	@$(MAKE) -C Util clean