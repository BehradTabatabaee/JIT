FLAGS = -Wall -Werror -Wextra -ggdb
all:
	g++ $(FLAGS) ./jit.cpp -o jit 