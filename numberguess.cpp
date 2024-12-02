#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// ANSI color codes
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

void setupConsole() {
#ifdef _WIN32
    // Enable ANSI escape code support in Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}
int main() {
    setupConsole();

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));
    int numberToGuess = std::rand() % 100 + 1;
    int playerGuess = 0;
    int attempts = 0;

    std::cout << YELLOW << "Welcome to the Number Guessing Game!" << RESET << std::endl;
    std::cout << CYAN << "I have selected a number between 1 and 100." << RESET << std::endl;
    std::cout << "Can you guess what it is?" << std::endl;

    // Main game loop
    while (true) {
        std::cout << GREEN << "Enter your guess: " << RESET;
        std::cin >> playerGuess;
        attempts++;

        if (playerGuess == numberToGuess) {
            std::cout << GREEN << "Congratulations! You guessed the correct number " << numberToGuess << " in " << attempts << " attempts." << RESET << std::endl;
            break;
        } else if (playerGuess < numberToGuess) {
            std::cout << RED << "Too low! Try again." << RESET << std::endl;
        } else {
            std::cout << RED << "Too high! Try again." << RESET << std::endl;
        }
    }

    return 0;
}
