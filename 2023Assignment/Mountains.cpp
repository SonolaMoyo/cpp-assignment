#include "Mountains.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>


int main() {
    Mountains mountains("mountains.csv");

    int numQuestions = 0;
    int numCorrect = 0;

    std::vector<std::pair<std::string, int>> correctAnswers; // to store correctly answered questions and their times

    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    std::cout << "Welcome, " << playerName << ", to the Mountain Range Quiz! Type 'exit' or 'quit' to end the quiz. NB: Answers first letters should be capitalized and spaces replaced with underscore" << std::endl;
    while (true) {
        // Quiz logic goes here...
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

        if (elapsed > 10) {
            std::cout << "Too slow! ";
            std::cout << "Incorrect." << std::endl;
        }
        else if (mountains.checkRange(mountainName, answer)) {
            std::cout << "Correct!" << std::endl;
            numCorrect++;

            // add the correctly answered question and its time to the vector
            correctAnswers.push_back(std::make_pair(mountainName, elapsed));
        }
        else {
            std::cout << "Incorrect." << std::endl;
        }

        numQuestions++;
    }

    std::cout << playerName << ", you scored " << numCorrect << " out of " << numQuestions << " questions." << std::endl;

    // Write player score to CSV file...
    // sort the vector of correctly answered questions based on the time taken
    std::sort(correctAnswers.begin(), correctAnswers.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        });

    // print out the correctly answered questions and their times in order of speed
    std::cout << "Correctly answered questions (in order of speed):" << std::endl;
    for (const auto& qa : correctAnswers) {
        std::cout << qa.first << " (" << qa.second << " seconds)" << std::endl;
    }

    double avgCorrectTime = 0.0;
    if (numCorrect > 0) {
        double totalCorrectTime = 0.0;
        for (const auto& qa : correctAnswers) {
            totalCorrectTime += qa.second;
        }
        avgCorrectTime = totalCorrectTime / numCorrect;
    }

    writePlayerScoreToCSV(playerName, numCorrect, numQuestions, avgCorrectTime);
    
    //Read players details from csv file and output in order of performance
    std::vector<PlayerScore> playerScores = readPlayerScoresFromCSV("player_score.csv");
    std::sort(playerScores.begin(), playerScores.end(), comparePlayerScores);

    std::cout << "Players in order of overall performance:" << std::endl;
    for (const auto& playerScore : playerScores) {
        int gpa = 5;
        if (playerScore.avgTime > 5.0 && playerScore.avgTime <= 9.0) {
            gpa = 4;
        }

        double overallGPA = (double)playerScore.correctAnswers / (double)playerScore.totalQuestions * (double)gpa;

        std::cout << playerScore.name << " (" << overallGPA << ")" << std::endl;
    }

    return 0;
}
