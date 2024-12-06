#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

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

    void turnRight() {
        // turn right to bottom
        if (x == 1)
        {
            x = 0;
            y = 1;
        }

        // turn bottom to left
        else if (y == 1)
        {
            x = -1;
            y = 0;
        }

        // turn left to top
        else if (x == -1)
        {
            x = 0;
            y = -1;
        }

        // turn top to right
        else if (y == -1)
        {
            x = 1;
            y = 0;
        }
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

// Return <cursor position, cursor direction>
std::pair<Position, Position> getCursor(const std::vector<std::string>& lines) {
    for (size_t i = 0; i < lines.size(); i++)
    {
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            switch (lines[i][j])
            {
            case '>':
                return {Position(i, j), Position(0, 1)};            
            case 'v':
                return {Position(i, j), Position(1, 0)};            
            case '<':
                return {Position(i, j), Position(0, -1)};            
            case '^':
                return {Position(i, j), Position(-1, 0)};            
            default:
                continue;
            }
        }
    }

    throw std::runtime_error("No cursor found!");
}

bool inBounds(const std::vector<std::string> grid, const Position& p) {
    return p.y >= 0 && p.y < grid.size() && p.x >= 0 && p.x < grid[0].size();
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

    auto p = getCursor(lines);
    auto cursorPos = p.first;
    auto cursorDir = p.second;
    std::unordered_set<Position> visited;
    visited.insert(cursorPos);

    while (inBounds(lines, cursorPos)) {
        visited.insert(cursorPos);
        
        Position nextPos = cursorPos + cursorDir;

        while (lines[nextPos.y][nextPos.x] == '#')
        {
            cursorDir.turnRight();
            nextPos = cursorPos + cursorDir;
        }

        cursorPos = nextPos;
    }

    std::cout << visited.size() << std::endl;
    
    return 0;
}
