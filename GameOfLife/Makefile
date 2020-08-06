CXX = g++
CFLAGS = -std=c++14 -g -Wall

%.o : %.cpp
	$(CXX) -c $(CFLAGS) $< 

test-game.exe: game.o cell.o test-game.o   
	$(CXX) -o $@ $^

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o)
