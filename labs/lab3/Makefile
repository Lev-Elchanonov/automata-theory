CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I. -Igenerated
FLEX = flex
BISON = bison

TARGET = robot
GENDIR = generated

# ----------- СБОРКА -----------

all: $(GENDIR)/$(TARGET)

# ----------- BISON -----------

$(GENDIR)/robot.tab.cpp $(GENDIR)/robot.tab.hpp: robot.ypp ast.hpp | $(GENDIR)
	$(BISON) -d robot.ypp \
		-o $(GENDIR)/robot.tab.cpp \
		--report=all \
		--report-file=$(GENDIR)/robot.report \
		-Wcounterexamples -Wconflicts-rr -Wconflicts-sr

# ----------- FLEX -----------

$(GENDIR)/robot.lex.cpp: robot_lexer.l $(GENDIR)/robot.tab.hpp RobotLexer.h ast.hpp | $(GENDIR)
	$(FLEX) -o $(GENDIR)/robot.lex.cpp robot_lexer.l

# ----------- КОМПИЛЯЦИЯ -----------

# Объектные файлы
$(GENDIR)/robot.tab.o: $(GENDIR)/robot.tab.cpp $(GENDIR)/robot.tab.hpp ast.hpp RobotLexer.h
	$(CXX) $(CXXFLAGS) -c $(GENDIR)/robot.tab.cpp -o $@

$(GENDIR)/robot.lex.o: $(GENDIR)/robot.lex.cpp $(GENDIR)/robot.tab.hpp RobotLexer.h ast.hpp
	$(CXX) $(CXXFLAGS) -c $(GENDIR)/robot.lex.cpp -o $@

$(GENDIR)/interpreter.o: interpreter.cpp ast.hpp RobotLexer.h
	$(CXX) $(CXXFLAGS) -c interpreter.cpp -o $@

$(GENDIR)/main.o: main.cpp RobotLexer.h $(GENDIR)/robot.tab.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

# Линковка
$(GENDIR)/$(TARGET): $(GENDIR)/main.o \
                     $(GENDIR)/robot.tab.o \
                     $(GENDIR)/robot.lex.o \
                     $(GENDIR)/interpreter.o
	$(CXX) $(CXXFLAGS) -o $@ \
		$(GENDIR)/main.o \
		$(GENDIR)/robot.tab.o \
		$(GENDIR)/robot.lex.o \
		$(GENDIR)/interpreter.o

# ----------- ДИРЕКТОРИЯ -----------

$(GENDIR):
	mkdir -p $(GENDIR)

# ----------- СИМЛИНК -----------

link: $(GENDIR)/$(TARGET)
	ln -sf $(GENDIR)/$(TARGET) $(TARGET)

# ----------- ОЧИСТКА -----------

clean:
	rm -rf $(GENDIR) $(TARGET)

.PHONY: all clean link