OS := $(shell uname)

ifeq ($(OS),Darwin)  # macOS
    CFLAGS = -I/opt/homebrew/include
    LFLAGS = -L/opt/homebrew/lib
else  # Assuming Linux
    CFLAGS = `sdl2-config --cflags`
    LFLAGS = `sdl2-config --libs`
endif

all: compiler

clean:
	@printf "\n\e[32m--------| \e[1;32mCLEANING\e[0m\e[32m |--------\e[0m\n\n"
	rm -f out.bin *.gch Quixo
	@printf "\e[32m\tDONE\e[0m\n"

compiler: 
	@printf "\e[32m--------| \e[1;32mCompilation of all your .cpp\e[0m\e[32m |--------\e[0m\n\n"
	clang++ -std=c++17 $(CFLAGS) $(LFLAGS) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o Quixo main.cpp src/GameBoard/GameBoard.cpp src/GameEngine/GameEngine.cpp src/Player/Player.cpp src/Player/PlayerHuman/PlayerHuman.cpp src/Player/AIPlayer/PlayerAI.cpp src/Player/AIPlayer/RandomAI/RandomAI.cpp Config.cpp src/MVC/Controller.cpp src/MVC/View/View.cpp src/MVC/View/MainMenu/MainMenu.cpp src/MVC/View/MageSMelee/MageSMelee.cpp src/MVC/View/PlayVAi/PlayVAi.cpp src/Player/AIPlayer/MinMaxAI/MinMaxAI.cpp src/MVC/View/PlayVPetiGran/PlayVPetiGran.cpp src/MVC/View/Loading/Loading.cpp
	@printf "\e[32m\tDONE\e[0m\n"

test: compiler
	@printf "\e[32m--------| \e[1mTest of the binary file\e[0m\e[32m |--------\e[0m\n\n"
	./Quixo
	@printf "\e[32m\tDONE\e[0m\n"

.PHONY: all clean test
