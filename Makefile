EXEC=expert

CC = clang++
CCFLAGS = -std=c++11 -ferror-limit=5
#CCFLAGS = -Wall -Wextra -Werror -std=c++11 -ferror-limit=5

SRC_FILE_NAME = main.cpp           \
				ExpertSystem.cpp   \
				ESException.cpp    \
				Fact.cpp           \
				Rule.cpp           \
#				OPN.cpp            \
						

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE_NAME))

OBJ_FILE_NAME = $(SRC_FILE_NAME:.cpp=.o)
OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILE_NAME))

INC = -I./include


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -o $@ -c $< $(INC)

$(OBJ_DIR)/Rule.o: $(SRC_DIR)/Rule.cpp $(SRC_DIR)/OPN.cpp | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -o $@ -c $< $(INC)


$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

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
