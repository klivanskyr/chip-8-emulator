all:
	g++ main.cpp Window.cpp Player.cpp -o main.exe

clean:
	rm -f main.exe
