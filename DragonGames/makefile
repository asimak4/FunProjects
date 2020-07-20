CXX = g++
CXXFLAGS = -Wall

proj2: Dragon.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) Dragon.o Game.o proj2.cpp -o proj2

Game.o: Dragon.o Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Dragon.o: Dragon.cpp Dragon.h
	$(CXX) $(CXXFLAGS) -c Dragon.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2
