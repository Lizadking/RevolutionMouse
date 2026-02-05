CXX = g++
CXXFLAGS = -Wall

bin: src/main.cpp profileNix.o profileManagerNix.o virtualDeviceNix.o src/include/wiiusehelper.h src/include/fileio.h
	$(CXX) $(CXXFLAGS) -g profileNix.o profileManagerNix.o virtualDeviceNix.o src/main.cpp -lwiiuse -lbluetooth -lm  `pkg-config --cflags --libs libevdev` `sdl2-config --cflags --libs` -o bin

virtualDeviceNix.o: src/include/virtualDeviceNix.h src/virtualDeviceNix.cpp profileManagerNix.o
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c src/virtualDeviceNix.cpp

profileManagerNix.o: src/include/profileManagerNix.h src/profileManagerNix.cpp profileNix.o
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c src/profileManagerNix.cpp 

profileNix.o: src/include/profileNix.h src/profileNix.cpp
	$(CXX) $(CXXFLAGS) `pkg-config --cflags --libs libevdev` -c src/profileNix.cpp


clean:
	rm *.o
	rm bin


run:
	./bin

