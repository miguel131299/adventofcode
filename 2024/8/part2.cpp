#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Position {
    int x;
    int y;

    Position(int y_, int x_): y{y_}, x{x_} 
    {}

    Position operator+(const Position& other) const {
        return Position(this->y + other.y, this->x + other.x);
    }

    bool operator==(const Position& other) const {
        return this->x == other.x && this->y == other.y;
    }

};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
}

bool inBounds(const std::vector<std::string> grid, const Position& p) {
    return p.y >= 0 && p.y < grid.size() && p.x >= 0 && p.x < grid[0].size();
}

void checkAntiNodes(vector<string> lines, int startRow, int startCol, char charDes, unordered_set<Position>& visited) {
    for (int r = startRow; r < lines.size(); r++)
    {
        // if in startRow, keep looking where we stopped, else start from beginning
        for (int c = r == startRow ? startCol + 1 : 0; c < lines[r].size(); c++)
        {
            if (lines[r][c] == charDes)
            {
                int dr = r - startRow;
                int dc = c - startCol;

                for (int i = 0; ; i++)
                {
                    Position a(startRow - dr * i, startCol - dc * i);
                    if (inBounds(lines, a))
                        visited.insert(a);
                    else
                        break;
                }
                
                for (int i = 0; ; i++)
                {
                    Position a(startRow + dr * i, startCol + dc * i);
                    if (inBounds(lines, a))
                        visited.insert(a);
                    else
                        break;
                }
            }
        }
    }   
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::vector<std::string> lines;

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::unordered_set<Position> visited;

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[0].size(); j++)
        {
            if (lines[i][j] != '.') {
                checkAntiNodes(lines, i, j, lines[i][j], visited);
            }
        }
    }
    
    std::cout << visited.size() << std::endl;
    
    return 0;
}
