all:    test

clean:
	@printf "\n\e[32m--------| \e[1;32mCLEANING\e[0m\e[32m |--------\e[0m\n\n"
	rm out.bin *.gch
	@printf "\e[32m\tDONE\e[0m\n"

compiler:
	@printf "\e[32m--------| \e[1;32mCompilation of all your .cpp\e[0m\e[32m |--------\e[0m\n\n"
	cmake -S ./ -B ./build
	@printf "\n \e[32m\cmake done\e[0m\n"
	clang++ -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o Quixo main.cpp src/GameBoard/GameBoard.cpp

	@printf "\e[32m\tDONE\e[0m\n"

test:   compiler
	@printf "\e[32m--------| \e[1mTest of the binary file\e[0m\e[32m |--------\e[0m\n\n"
	./Quixo
	@printf "\e[32m\tDONE\e[0m\n"

.PHONY = all clean
