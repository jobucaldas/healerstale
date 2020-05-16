SHELL=/bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o
ENGINE  = bin/Engine/Window.o bin/Engine/GUIElement.o bin/Engine/Scene.o
SCENES  = bin/Scenes/Credits.o bin/Scenes/Menu.o bin/Scenes/Gameplay.o bin/Scenes/Sponsor.o
MODULES = 

OBJS = bin/Main.o $(ENGINE) $(SCENES) $(MODULES)
CC = g++
LINKER_FLAGS = -lSDL2 -lSDL2_image -Isrc

## Install
install: bin/Healer

# Windows Specific - Not finished
icon.res: Assets/icon.rc
	windres assets/icon.rc -O coff -o assets/icon.res

win: main.o icon.res
	$(CC) bin/main-old.o assets/icon.res -o bin/healers $(LINKER_FLAGS)

# Folders
bin:
	mkdir bin

bin/Engine: bin
	mkdir bin/Engine

bin/Scenes: bin
	mkdir bin/Scenes

# Binaries
bin/Healer: bin $(OBJS)
	$(CC) $(OBJS) -o bin/Healer $(LINKER_FLAGS)

bin/Main.o: src/Main.cpp
	$(CC) -c src/Main.cpp -o bin/Main.o $(LINKER_FLAGS)

#bin/Game.o: $(ENGINE) $(SCENES) src/Game.cpp 
#	$(CC) -c src/Game.cpp -o bin/Game.o $(LINKER_FLAGS)

# Engine
bin/Engine/GUIElement.o: bin/Engine src/Engine/GUIElement.cpp
	$(CC) -c src/Engine/GUIElement.cpp -o bin/Engine/GUIElement.o $(LINKER_FLAGS)

bin/Engine/Window.o: bin/Engine src/Engine/Window.cpp
	$(CC) -c src/Engine/Window.cpp -o bin/Engine/Window.o $(LINKER_FLAGS)

bin/Engine/Scene.o: bin/Engine src/Engine/Scene.cpp
	$(CC) -c src/Engine/Scene.cpp -o bin/Engine/Scene.o $(LINKER_FLAGS)

# Scenes
bin/Scenes/Credits.o: bin/Scenes bin/Engine/Scene.o src/Scenes/Credits.cpp
	$(CC) -c src/Scenes/Credits.cpp -o bin/Scenes/Credits.o $(LINKER_FLAGS)

bin/Scenes/Sponsor.o: bin/Scenes bin/Engine/Scene.o src/Scenes/Sponsor.cpp
	$(CC) -c src/Scenes/Sponsor.cpp -o bin/Scenes/Sponsor.o $(LINKER_FLAGS)

bin/Scenes/Menu.o: bin/Scenes bin/Engine/Scene.o src/Scenes/Menu.cpp 
	$(CC) -c src/Scenes/Menu.cpp -o bin/Scenes/Menu.o $(LINKER_FLAGS)

bin/Scenes/Gameplay.o: bin/Scenes bin/Engine/Scene.o src/Scenes/Gameplay.cpp 
	$(CC) -c src/Scenes/Gameplay.cpp -o bin/Scenes/Gameplay.o $(LINKER_FLAGS)

# Clean Up
clean:
	rm -r bin