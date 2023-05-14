all: main

echo.o: echo.cpp
	g++ -c $^ -o $@

main.o:main.cpp
	g++ -c $^ -o $@

main: main.o echo.o
	g++ $^ -o main.exe

clean:
	del *.o *.exe