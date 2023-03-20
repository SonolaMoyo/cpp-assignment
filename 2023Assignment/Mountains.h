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

// writes players information to a CSV 'player_score.csv
// time complexity of the function is O(1)'
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

//data structure and functions for outputing all players performance
struct PlayerScore {
    std::string name;
    int correctAnswers;
    int totalQuestions;
    double avgTime;
};

//returns the playerScores vector containing all the player scores read from the CSV file.
// the time complexity of the function is linear time O(n), where n is the number of lines in the CSV file.
std::vector<PlayerScore> readPlayerScoresFromCSV(const std::string& filename) {
    std::vector<PlayerScore> playerScores;

    std::ifstream file(filename);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            int correctAnswers, totalQuestions;
            double avgTime;
            if (std::getline(iss, name, ',') &&
                iss >> correctAnswers &&
                iss.ignore() &&
                iss >> totalQuestions &&
                iss.ignore() &&
                iss >> avgTime) {
                playerScores.push_back({ name, correctAnswers, totalQuestions, avgTime });
            }
        }
    }

    return playerScores;
}

//Compares player score according to GPA and returns boolean
//the time complexity is O(1)
bool comparePlayerScores(const PlayerScore& a, const PlayerScore& b) {
    int aGPA = 5;
    if (a.avgTime > 5.0 && a.avgTime <= 9.0) {
        aGPA = 4;
    }

    int bGPA = 5;
    if (b.avgTime > 5.0 && b.avgTime <= 9.0) {
        bGPA = 4;
    }

    double aOverallGPA = (double)a.correctAnswers / (double)a.totalQuestions * (double)aGPA;
    double bOverallGPA = (double)b.correctAnswers / (double)b.totalQuestions * (double)bGPA;

    return aOverallGPA > bOverallGPA;
}