#pragma once

#include <vector>
#include <string>

struct Mountain {
    std::string name;
    std::string range;
};

class Mountains
{
public:
	//Time complexity: The time complexity of the function is O(n*m), 
	//where n is the number of files in the input vector and m is the average number of mountains per file.
    Mountains(const std::string& filename);

    //Time complexity: The time complexity of the print() function is O(n),
    // where n is the number of mountains in the m_mountains vector
    void print() const;

	//The time complexity of the function is O(1).
    std::string getRandomMountain() const;

	//The time complexity of the function is O(n),
	//where n is the number of mountains in the m_mountains vector.
    bool checkRange(const std::string& mountain, const std::string& range) const;

private:
    std::vector<Mountain> m_mountains;
};
