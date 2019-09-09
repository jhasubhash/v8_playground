CC=g++
INC = -I. -I./inc -I./../v8/include
CFLAGS= -std=c++17 -pthread
LFLAGS= -lv8_monolith -L./../v8/out.gn/x64.release.sample/obj/
src = $(wildcard src/*.cpp) 

main :
	$(CC) $(INC) $(CFLAGS) $(src) -o dist/main.out $(LFLAGS)

$(shell   mkdir -p dist)