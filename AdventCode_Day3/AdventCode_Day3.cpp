#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

using namespace std;

// Function to get the number at a given position
int getNumber(int i, vector<char> &lines) {
    // Ensure the given position is within the valid range
    if (i < 0 || i >= lines.size() || !isdigit(lines[i])) {
        // Invalid input position, return an error value or handle it accordingly
        return -1;
    }

    // Initialize variables to store the start and end indices of the number
    int start = i, end = i;

    // Find the start index of the number
    while (start >= 0 && isdigit(lines[start])) {
        --start;
    }
    ++start; // Adjust to the actual start index

    // Find the end index of the number
    while (end < lines.size() && isdigit(lines[end])) {
        ++end;
    }
    --end; // Adjust to the actual end index

    // Extract the number from the vector
    std::string number(lines.begin() + start, lines.begin() + end + 1);

    // change the char in the vector to a '.' so it doesn't get counted again
    for (int i = start; i <= end; i++)
    {
        lines[i] = '.';
    }

    // Convert the extracted string to an integer
    return std::stoi(number);
}

// Function to get the adjacent numbers of a given position
vector<int> getAdjacentNumbers(int i, int j, vector<vector<char>> &lines) {
    std::vector<int> adjacentNumbers;

    // Initialize the directions to check
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

    // Check all the directions
    for (int d = 0; d < 8; ++d) {
        int ni = i + directions[d][0];
        int nj = j + directions[d][1];

        // Check if the new position is within the valid range and is a digit
        if (ni >= 0 && ni < lines.size() && nj >= 0 && nj < lines[0].size() && isdigit(lines[ni][nj])) {

            int adjacentNumber = getNumber(nj, lines[ni]);

            adjacentNumbers.push_back(adjacentNumber);
        }
    }
    // print the adjacent numbers
    for (int i = 0; i < adjacentNumbers.size(); i++)
    {
		cout << adjacentNumbers[i] << " ";
	}
    cout << "End of Get Adjacent Call" << endl;

    return adjacentNumbers;
}

int main()
{
    cout << "Advent of Code - Day 3" << endl;
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path filePath = currentPath / "AdventCode_Day3_Input.txt";

    std::fstream new_file(filePath, std::ios::in);

    std::vector<std::vector<char>> engineSchema;
    int sum = 0;

    // stores the engine schema in a 2D vector of chars
    if (new_file.is_open()) {
        std::string line;

        int i = 0;
        while (std::getline(new_file, line)) {
            engineSchema.push_back(std::vector<char>());
            for (char c : line)
            {
                engineSchema[i].push_back(c);
            }
            i++;
        }

        new_file.close();
    }

    vector<int> adjacentNumbers;
    int multiplicationResult = 1;

    // iterate through the engineSchema
    for (int i = 0; i < engineSchema.size(); i++)
    {
        for (int j = 0; j < engineSchema[i].size(); j++)
        {
		    // check if engineSchema[i][j] is a digit or a '.'
            if (engineSchema[i][j] == '.' || isdigit(engineSchema[i][j]))
            {
                continue;
			}
            // check if engineSchema[i][j] is a '*'
            if (engineSchema[i][j] == '*') {
                adjacentNumbers = getAdjacentNumbers(i, j, engineSchema);

                // check if there are exactly 2 adjacent numbers
                if (adjacentNumbers.size() != 2) {
					continue;
				}

                // multiply the adjacent numbers
                for (int k : adjacentNumbers)
                {
                    multiplicationResult *= k;
                }

                // add the result to the sum
                sum += multiplicationResult;
                multiplicationResult = 1;
            }
		}
	}

	cout << "Sum of all adjacent numbers: " << sum << endl;

	return 0;
}