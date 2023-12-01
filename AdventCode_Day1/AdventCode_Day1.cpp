using namespace std;

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

int isWrittenDigit(string s) {
    vector<string> sa = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int index = 0;
    string original = s;
    string temp = "";
    for (int i = 0; i < s.length(); i++) {
        temp = original.substr(s.length() - i - 1);
        for (string comp : sa) {
            if (temp == comp) {
                return index;
            }
            index++;
        }
        index = 0;
	}
    return -1;
}

int main() {
    std::filesystem::path currentPath = std::filesystem::current_path();

    std::filesystem::path filePath = currentPath / "AdventCode_Day1_Input.txt";

    std::fstream new_file(filePath, std::ios::in);

    int total = 0;

    if (new_file.is_open()) {
        std::string sa;
        std::string firstDigit;
        std::string lastDigit;
        std::string temp;
        while (std::getline(new_file, sa)) {
            firstDigit = "";
            lastDigit = "";
            temp = "";
            for (char ch : sa) {
                temp += ch;
                if (std::isdigit(ch)) {
                    if (firstDigit == "") {
                        firstDigit = ch;
                    }
                    else {
                        lastDigit = ch;
                    }
                }
                else {
                    int index = isWrittenDigit(temp);
                    if (index != -1) {
                        if (firstDigit == "") {
							firstDigit = std::to_string(index);
						}
                        else {
							lastDigit = std::to_string(index);
						}
					}
                }
            }
            if (lastDigit == "") {
				lastDigit = firstDigit;
			}
            cout << "New Line:" << endl;
            cout << sa << endl;
            cout << firstDigit + lastDigit << endl;
            total += std::stoi(firstDigit + lastDigit);
        }

        new_file.close();
    }
    else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    std::cout << "Total: " << total << std::endl;

    return 0;
}
