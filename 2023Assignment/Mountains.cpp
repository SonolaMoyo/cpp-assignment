#include "Mountains.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

Mountains::Mountains(const std::string& filename) {
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

    void Mountains::print() const {
        for (const auto& mountain : m_mountains) {
            std::cout << mountain.name << " in " << mountain.range << std::endl;
        }
    }

//Refactored code to use std::rand() instead of rand()
std::string Mountains::getRandomMountain() const
{
    int randomIndex = std::rand() % m_mountains.size();
    return m_mountains[randomIndex].name;
}

bool Mountains::checkRange(const std::string& mountain, const std::string& range) const
{
    for (const auto& m : m_mountains) {
        if (m.name == mountain && m.range == range) {
            return true;
        }
    }
    return false;
}


int main()
{
    //std::vector<std::string> filenames = {"Alps.txt", "Carpathians.txt", "Icelandic_Highlands.txt", "Pyrenees.txt"};
    Mountains mountains("mountains.csv");

    int numQuestions = 0;
    int numCorrect = 0;

    std::cout << "Welcome to the Mountain Range Quiz! Type 'exit' or 'quit' to end the quiz. NB: Answers first letters should be capitalized and spaces replaced with underscore" << std::endl;
    while (true) {
        std::string mountainName = mountains.getRandomMountain();

        std::cout << "Which mountain range is " << mountainName << " in?" << std::endl;
        std::string answer;
        
        auto start = std::chrono::steady_clock::now(); // start timer

        std::getline(std::cin, answer);

        auto end = std::chrono::steady_clock::now(); // end timer
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count(); // calculate elapsed time in seconds
        
        if (answer == "exit" || answer == "quit") {
            break;
        }

        if(elapsed > 10){
            std::cout << "Too slow! ";
            std::cout << "Incorrect." << std::endl;
        }
        else if (mountains.checkRange(mountainName, answer)) {
            std::cout << "Correct!" << std::endl;
            numCorrect++;
        }
        else {
            std::cout << "Incorrect." << std::endl;
        }

        numQuestions++;
    }

    std::cout << "You scored " << numCorrect << " out of " << numQuestions << " questions." << std::endl;

    return 0;
}

