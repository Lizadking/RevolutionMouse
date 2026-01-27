CXX = g++
CXXFLAGS = -Wall

bin: main.o monitor.o
	gcc -Wall main.o monitor.o -lwiiuse -lbluetooth -lm  -o bin

test: toml.hpp logger.h
	$(CXX) $(CXXFLAGS) test.cpp -lwiiuse -lbluetooth -lm -o test


profiledriver: profileDriver.cpp profileNix.o profileManagerNix.o virtualDeviceNix.o wiiusehelper.h fileio.h
	$(CXX) $(CXXFLAGS) profileNix.o profileManagerNix.o virtualDeviceNix.o profileDriver.cpp -lwiiuse -lbluetooth -lm  `pkg-config --cflags --libs libevdev` -o profiledriver

profileNix.o: profileNix.h profileNix.cpp
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c profileNix.cpp

profileManagerNix.o: profileManagerNix.h profileManagerNix.cpp 
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c profileManagerNix.cpp 

virtualDeviceNix.o: virtualDeviceNix.h virtualDeviceNix.cpp
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c virtualDeviceNix.cpp

main.o: main.c monitor.o
	gcc -Wall -c main.c

monitor.o: monitor.c monitor.h
	gcc -Wall -c monitor.c

clean:
	rm *.o
	rm bin


run:
	./bin

