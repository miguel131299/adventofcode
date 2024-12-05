#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>

bool findXMAS(std::vector<std::string>& lines, int r, int c, int dr, int dc, int depth) {

    if (r < 0 || c < 0 || r >= lines.size() || c >= lines[0].size())
        return false;
    
    char cDesired;
    switch (depth)
    {
    case 1:
        cDesired = 'M';
        break;
    case 2:
        cDesired = 'A';
        break;
    case 3:
        cDesired = 'S';
        break;
    default:
        throw std::runtime_error("Depth not supported");
        break;
    }

    if (lines[r][c] != cDesired)
        return false;

    if (depth == 3)
        return true;

    return findXMAS(lines, r + dr, c + dc, dr, dc, depth + 1);
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
    for (size_t r = 0; r < lines.size(); r++)
    {
        for (size_t c = 0; c < lines[r].size(); c++)
        {
            if (lines[r][c] == 'X')
            {
                for (int dr = -1; dr <= 1; dr++)
                {
                    for (int dc = -1; dc <= 1; dc++)
                    {
                        if (findXMAS(lines, r + dr, c + dc, dr, dc, 1))
                        {
                            ++xmasCounter;
                        }
                        
                    }
                }
                
            }
            
        }
        
    }

    std::cout << xmasCounter << std::endl;
    
    return 0;
}
