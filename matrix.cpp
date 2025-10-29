#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const int DROP_CHANCE = 15;
const int FRAME_DELAY_MS = 70;

char getRandomChar(std::mt19937& gen) {
    std::uniform_int_distribution<> dist(33, 126);
    return static_cast<char>(dist(gen));
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> chance(0, 100);

    std::vector<std::string> screen(SCREEN_HEIGHT, std::string(SCREEN_WIDTH, ' '));

    while (true) {
        for (int i = SCREEN_HEIGHT - 1; i > 0; --i) {
            screen[i] = screen[i - 1];
        }

        std::string& topLine = screen[0];
        for (int i = 0; i < SCREEN_WIDTH; ++i) {
            if (screen[1][i] != ' ') {
                topLine[i] = (chance(gen) < 90) ? getRandomChar(gen) : ' ';
            } else {
                topLine[i] = (chance(gen) < DROP_CHANCE) ? getRandomChar(gen) : ' ';
            }
        }

        std::system("cls || clear");

        std::cout << "\033[32m";

        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            std::cout << screen[i] << '\n';
        }
        
        std::cout.flush();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
    }

    std::cout << "\033[0m";
    return 0;
}