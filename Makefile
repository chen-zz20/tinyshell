all: main

echo.o: echo.cpp
	g++ -c $^ -o $@ -static

main.o:main.cpp
	g++ -c $^ -o $@ -static

main: main.o echo.o
	g++ $^ -o main.exe -static

clean:
	del *.o *.exe