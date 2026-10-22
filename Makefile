NAME        = scop

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++17 -Iinclude
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude

LDFLAGS     = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRC_DIR     = src
OBJ_DIR     = obj

SRCS_CPP    =   $(SRC_DIR)/main.cpp \
                $(SRC_DIR)/Mesh.cpp \
				$(SRC_DIR)/App.cpp \
				$(SRC_DIR)/Mat4.cpp \
				$(SRC_DIR)/Shader.cpp \
				$(SRC_DIR)/Texture.cpp \

SRCS_C      =   $(SRC_DIR)/glad.c

OBJS        =   $(SRCS_CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
                $(SRCS_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re