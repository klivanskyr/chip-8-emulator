all:
	g++ main.cpp Window2D.cpp Window3D.cpp Player.cpp -o main.exe

clean:
	rm -f main.exe
