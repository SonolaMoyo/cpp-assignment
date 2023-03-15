#include "Mountains.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>

Mountains::Mountains(const std::vector<std::string>& filenames)
{
    std::srand(std::time(nullptr));

    for (const auto& filename : filenames) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            Mountain mountain;
            mountain.name = line;
            mountain.range = filename.substr(0, filename.size() - 4);
            m_mountains.push_back(mountain);
        }
        infile.close();
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
    std::vector<std::string> filenames = {"Alps.txt", "Carpathians.txt", "Icelandic_Highlands.txt", "Pyrenees.txt"};
    Mountains mountains(filenames);

    int numQuestions = 0;
    int numCorrect = 0;
    std::atomic<bool> timedOut(false);

    std::cout << "Welcome to the Mountain Range Quiz! Type 'exit' or 'quit' to end the quiz. NB: Answers first letters should be capitalized and spaces replaced with underscore" << std::endl;
    while (true) {
        std::string mountainName = mountains.getRandomMountain();

        std::cout << "Which mountain range is " << mountainName << " in?" << std::endl;
        std::string answer;

        auto start = std::chrono::steady_clock::now(); // start timer

        std::thread timeoutThread([&](){
            std::this_thread::sleep_for(std::chrono::seconds(10));
            timedOut.store(true);
        });

        std::getline(std::cin, answer);

        auto end = std::chrono::steady_clock::now(); // end timer
        timeoutThread.join();
        if (timedOut.load()) {
            std::cout << "Timeout! ";
            std::cout << "The correct answer is " << mountains.checkRange(mountainName, "") << "." << std::endl;
        }
        else if (answer == "exit" || answer == "quit") {
            break;
        }
        else if (mountains.checkRange(mountainName, answer)) {
            std::cout << "Correct!" << std::endl;
            numCorrect++;
        }
        else {
            std::cout << "Incorrect." << std::endl;
        }

        numQuestions++;
        timedOut.store(false);
    }

    std::cout << "You scored " << numCorrect << " out of " << numQuestions << " questions." << std::endl;

    return 0;
}

