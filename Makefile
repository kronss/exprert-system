
EXEC=expert

CC = clang
CCFLAGS = -Wall -Wextra -Werror -std=c++11 -ferror-limit=5

SRC_FILE_NAME = main.c \

SRC = $(addprefix src/, $(SRC_FILE_NAME))

OBJ_FILE_NAME = $(SRC:.cpp=.o)
OBJ = $(addprefix .obj/, $(SRC_FILE_NAME))

INC = -I./include




all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(EXEC)




%.o: %.cpp
	$(CC) $(CCFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(EXEC)

re: fclean all

r: all
	./$(EXEC) 

rf: all
	./$(EXEC) test/tes

.phony: all clean fclean re r rf
