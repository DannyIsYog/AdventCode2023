#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

using namespace std;

int main() {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path filePath = currentPath / "AdventCode_Day2_Input.txt";

    std::fstream new_file(filePath, std::ios::in);

    std::vector<std::vector<std::map<std::string, int>>> rounds;
    int sum = 0;
    if (new_file.is_open()) {
        std::string line;
        while (std::getline(new_file, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            std::istringstream iss(line);
            std::string game;
            std::vector<std::map<std::string, int>> gameData;

            iss >> game;
            iss >> game;

            while (std::getline(iss, game, ';')) {
                std::istringstream gameStream(game);
                std::map<std::string, int> colorCount;

                while (true) {
                    int count;
                    std::string color;

                    gameStream >> count >> color;

                    if (!gameStream) {
                        break;
                    }

                    color.erase(std::remove(color.begin(), color.end(), ','), color.end());

                    colorCount[color] += count;
                }

                gameData.push_back(colorCount);
            }

            rounds.push_back(gameData);
        }

        new_file.close();

        // part one
        /*
        bool possible = true;
        for (size_t i = 0; i < rounds.size(); ++i) {
            for (size_t j = 0; j < rounds[i].size(); ++j) {
                if (rounds[i][j]["red"] > 12 || rounds[i][j]["green"] > 13 || rounds[i][j]["blue"] > 14) {
                    // print round X possible
                    std::cout << "Round " << j + 1 << "not possible\n";
                    possible = false;
                }
                else {
					// print round X not possible
					std::cout << "Round " << j + 1 << "possible\n";
				}
            }
            if (possible) {
				sum += i + 1;
                cout << "Sum: " << sum << endl;
            }
            possible = true;
        }*/

        // part two
        int maxRedCount = 0;
        int maxGreenCount = 0;
        int maxBlueCount = 0;

        int powerSum = 0;

        for (size_t i = 0; i < rounds.size(); ++i) {
            for (size_t j = 0; j < rounds[i].size(); ++j) {
                if (rounds[i][j]["red"] > maxRedCount) {
					maxRedCount = rounds[i][j]["red"];
				}
                if (rounds[i][j]["green"] > maxGreenCount) {
                    maxGreenCount = rounds[i][j]["green"];
                }
                if (rounds[i][j]["blue"] > maxBlueCount) {
					maxBlueCount = rounds[i][j]["blue"];
				}
            }
            powerSum += (maxRedCount * maxGreenCount * maxBlueCount);
            maxRedCount = 0;
            maxGreenCount = 0;
            maxBlueCount = 0;
        }
        cout << "Power Sum: " << powerSum << endl;

        // end part two
    }
    else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    
    // std::cout << "Sum: " << sum << std::endl; # part one
    return 0;
}
