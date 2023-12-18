all:    test

clean:
	@printf "\n\e[32m--------| \e[1;32mCLEANING\e[0m\e[32m |--------\e[0m\n\n"
	rm out.bin *.gch
	@printf "\e[32m\tDONE\e[0m\n"
cmake: 
	cmake -S ./ -B ./build
compiler:
	@printf "\e[32m--------| \e[1;32mCompilation of all your .cpp\e[0m\e[32m |--------\e[0m\n\n"
	clang++  -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -o Quixo main.cpp src/GameBoard/GameBoard.cpp src/GameEngine/GameEngine.cpp src/Player/Player.cpp src/Player/PlayerHuman/PlayerHuman.cpp src/Player/AIPlayer/PlayerAI.cpp src/Player/AIPlayer/RandomAI/RandomAI.cpp Config.cpp src/MVC/Model.cpp src/MVC/Controller.cpp src/MVC/View/View.cpp src/MVC/View/MainMenu/MainMenu.cpp
	@printf "\e[32m\tDONE\e[0m\n"

test:   compiler
	@printf "\e[32m--------| \e[1mTest of the binary file\e[0m\e[32m |--------\e[0m\n\n"
	./Quixo
	@printf "\e[32m\tDONE\e[0m\n"

.PHONY = all clean
