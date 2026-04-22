CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
FLEX = flex
BISON = bison

TARGET = robot

all: $(TARGET)

# Bison
robot.tab.cpp robot.tab.hpp: robot.ypp ast.hpp
	$(BISON) -d robot.ypp -o robot.tab.cpp

# Flex
robot.lex.cpp: robot_lexer.l robot.tab.hpp ast.hpp RobotLexer.h
	$(FLEX) -o robot.lex.cpp robot_lexer.l

# Компиляция
$(TARGET): main.cpp robot.tab.cpp robot.lex.cpp RobotLexer.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp robot.tab.cpp robot.lex.cpp

clean:
	rm -f $(TARGET) *.o robot.tab.cpp robot.tab.hpp robot.lex.cpp

.PHONY: all clean