SHELL=/bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o

install: healers

clean:
	-rm main.o healers.exe healers icon.res

icon.res: Assets/icon.rc
	windres Assets/icon.rc -O coff -o Assets/icon.res

main.o: main.cpp
	g++ -c main.cpp 

healers: main.o
	g++ main.o -o healers -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

win: main.o icon.res
	g++ main.o Assets/icon.res -o healers -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system