all: main

file:=basic import echo pwd cd ls cat tee cp main
o:=$(file:%=%.o)
cpp:=$(file:%=%.cpp)

%.o: %.cpp
	g++ -c $^ -o $@ -static --std=c++17

main.exe: $(o)
	g++ $^ -o main.exe -static

main:main.exe
	main.exe

debug.exe: $(cpp)
	g++ $^ -o debug.exe -g --std=c++17

debug:debug.exe

clean:
	del *.o *.exe

.PHONY:main clean all debug