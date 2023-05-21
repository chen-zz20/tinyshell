all: main

file:=basic echo main
o:=$(file:%=%.o)
cpp:=$(file:%=%.cpp)

%.o: %.cpp
	g++ -c $^ -o $@ -static

main: $(o)
	g++ $^ -o main.exe -static
	main.exe

debug: $(cpp)
	g++ $^ -static -o debug.exe -g

clean:
	del *.o *.exe

.PHONY:main clean all debug