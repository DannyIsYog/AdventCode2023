#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

using namespace std;

// recieves a string with the format example: "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53" and returns a vector of vectors of ints separated by the | symbol
vector<vector<int>> parseLine(string line) {
    vector<vector<int>> cards;
	vector<int> card;
	istringstream iss(line);
	string cardString;
	iss >> cardString;
	iss >> cardString;
    while (getline(iss, cardString, '|')) {
		istringstream cardStream(cardString);
        while (true) {
			int number;
			cardStream >> number;
            if (!cardStream) {
				break;
			}
			card.push_back(number);
		}
		cards.push_back(card);
		card.clear();
	}
	return cards;
}

// recieves a vector of ints with the winning numbers and a vector of ints with the numbers of the card. For each number in the card, if it is in the winning numbers, add 1 point. Return 2 to the power of the points
int getPoints(vector<int> winningNumbers, vector<int> myNumbers) {
	int points = 0;
    for (int i = 0; i < myNumbers.size(); i++) {
        for (int j = 0; j < winningNumbers.size(); j++) {
            if (myNumbers[i] == winningNumbers[j]) {
				points++;
			}
		}
    }
    if (points == 0)
    {
        return 0;
    }
    return pow(2, points-1);
}

// recieves a vector of ints with the winning numbers and a vector of ints with the numbers of the card. For each number in the card, if it is in the winning numbers, add 1 point. Returns the number of matched numbers
int getMatched(vector<int> winningNumbers, vector<int> myNumbers) {
    int matched = 0;
    for (int i = 0; i < myNumbers.size(); i++) {
        for (int j = 0; j < winningNumbers.size(); j++) {
            if (myNumbers[i] == winningNumbers[j]) {
                matched++;
            }
        }
    }
    return matched;
}

int main()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path filePath = currentPath / "AdventCode_Day4_Input.txt";

    std::fstream new_file(filePath, std::ios::in);

    std::vector<std::vector<int>> scratchcards;
    int sum = 0;
    if (new_file.is_open()) {
        std::string line;
        while (std::getline(new_file, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }
            auto cards = parseLine(line);
            for (auto card : cards) {
				scratchcards.push_back(card);
			}   
        }
    }

    // PART TWO
    vector<int> points(scratchcards.size()/2, 0);
    vector<int> copies(scratchcards.size()/2, 1);

    int totalCards = scratchcards.size();

    for (int i = 0; i < scratchcards.size(); i += 2) {
        points[i / 2] = getMatched(scratchcards[i], scratchcards[i + 1]);
    }

    for (int i = 0; i < points.size(); i++) {
        for (int j = 1; j <= points[i]; j++) {
            copies[i+j] += copies[i];
		}
	}

    sum = 0;
    // print the sum of the copies vector
    for (int i = 0; i < copies.size(); i++) {
		sum += copies[i];
	}
    cout << "Total copies: " << sum << endl;

    // END OF PART TWO

    /* PART ONE
    int totalPoints = 0;
    for (int i = 0; i < scratchcards.size(); i += 2) {
		totalPoints += getPoints(scratchcards[i], scratchcards[i+1]);
	}
    cout << "Total points: " << totalPoints << endl;*/

    new_file.close();
}