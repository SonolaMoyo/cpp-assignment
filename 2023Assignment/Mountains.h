#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <sstream>

struct Mountain {
    std::string name;
    std::string range;
};

class Mountains
{
public:
	//Time complexity: The time complexity of the function is O(n*m), 
	//where n is the number of files in the input vector and m is the average number of mountains per file.
    Mountains(const std::string& filename) {
        std::srand(std::time(nullptr));
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string range_name;
            if (!(std::getline(iss, range_name, ','))) {
                std::cerr << "Error: invalid input line: " << line << std::endl;
                continue;
            }
            std::string mountain_name;
            while (std::getline(iss, mountain_name, ',')) {
                Mountain mountain;
                mountain.name = mountain_name;
                mountain.range = range_name;
                m_mountains.push_back(mountain);
            }
        }
        infile.close();
    }

    //Time complexity: The time complexity of the print() function is O(n),
    // where n is the number of mountains in the m_mountains vector
    void print() const {
        for (const auto& mountain : m_mountains) {
            std::cout << mountain.name << " in " << mountain.range << std::endl;
        }
    }

	//The time complexity of the function is O(1).
    std::string getRandomMountain() const
    {
    int randomIndex = std::rand() % m_mountains.size();
    return m_mountains[randomIndex].name;
    }

	//The time complexity of the function is O(n),
	//where n is the number of mountains in the m_mountains vector.
    bool checkRange(const std::string& mountain, const std::string& range) const
    {
    for (const auto& m : m_mountains) {
        if (m.name == mountain && m.range == range) {
            return true;
        }
    }
    return false;
    }

private:
    std::vector<Mountain> m_mountains;
};

void writePlayerScoreToCSV(const std::string& playerName, int numCorrect, int numQuestions, double avgCorrectTime) {
    std::ofstream scoreFile;
    scoreFile.open("player_score.csv", std::ios::app);

    if (!scoreFile.is_open()) {
        std::cout << "Failed to open score file" << std::endl;
        return;
    }

    // create a CSV row with player details
    std::stringstream scoreRow;
    scoreRow << playerName << "," << numCorrect << "," << numQuestions << "," << avgCorrectTime << std::endl;

    // write the row to the CSV file
    scoreFile << scoreRow.str();
    scoreFile.close();
}

