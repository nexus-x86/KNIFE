#include <iostream>
#include <string>

int main() {
    // initialize engine, input, board, 
    std::string input;

    while (std::getline(std::cin, input)) {
        if (input == "uci") {
            std::cout << "id name KNIFE\nid author JustListenToTheSong\nuciok\n"; 
        } else if (input == "isready") {
            std::cout << "readyok\n";
        } else if (input == "ucinewgame") {
            // initialize the board
        } else if (input == "quit") {
            return;
        } else if (input == "position") {
            // set the board position

        } else if (input == "go") {
            // go

            
        }
    }
}