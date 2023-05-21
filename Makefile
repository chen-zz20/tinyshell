all: main

file:=basic echo pwd main
o:=$(file:%=%.o)
cpp:=$(file:%=%.cpp)

%.o: %.cpp
	g++ -c $^ -o $@ -static

main.exe: $(o)
	g++ $^ -o main.exe -static

main:main.exe
	main.exe

debug.exe: $(cpp)
	g++ $^ -static -o debug.exe -g

debug:debug.exe

clean:
	del *.o *.exe

.PHONY:main clean all debug