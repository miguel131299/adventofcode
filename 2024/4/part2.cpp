#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>

bool findCrossMAS(std::vector<std::string>& lines, int r, int c) {
    // // out of bounds
    // if (r < 1 || r >= lines.size() - 1 || c < 1 || c >= lines[0].size() - 1)
    // {
    //     return false;
    // }
    

    std::unordered_set<char> s;

    std::string mas = "MAS";

    // left to right
    for (int i = -1; i <= 1; i++)
        s.insert(lines[r+i][c+i]);

    for (char c: mas) {
        if (!s.count(c))
            return false;
    }

    s.clear();

    // right to left
    for (int i = -1; i <= 1; i++)
        s.insert(lines[r+i][c-i]);

    for (char c: mas) {
        if (!s.count(c))
            return false;
    }

    return true;

}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::vector<std::string> lines;
    lines.reserve(1000);

    std::string line;
    while (std::getline(file, line)) {

        lines.emplace_back(line);
    }
    file.close();


    unsigned int xmasCounter = 0;
    for (size_t r = 1; r < lines.size() - 1; r++)
    {
        for (size_t c = 1; c < lines[r].size() - 1; c++)
        {
            if (lines[r][c] == 'A')
            {
                if (findCrossMAS(lines, r, c))
                {
                    ++xmasCounter;
                }
            }
        }
    }

    std::cout << xmasCounter << std::endl;
    
    return 0;
}
