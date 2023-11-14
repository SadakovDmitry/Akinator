TARGET = Akinator

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
FLAGS = -fsanitize=address -Wall -Wextra

$(TARGET) : $(OBJ)
		g++ $(OBJ) $(FLAGS) -o $(TARGET)

%.o : %.cpp
		g++ $(FLAGS) -c $< -o $@

.PHONY : clean
clean :
		rm *.o $(TARGET)

run : $(TARGET)
		./$(TARGET)
