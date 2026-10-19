NAME        = scop

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++17 -Iinclude
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude

LDFLAGS     = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRCS_CPP    = src/main.cpp \
				src/scop.cpp
SRCS_C      = src/glad.c

OBJS        = $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re