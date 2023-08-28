all:
	g++ -I src/include -L src/lib source/*.cpp -o main main.cpp -lmingw32 -lSDL2main -lSDL2