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

bool inBounds(const std::vector<std::string> grid, const Position& p) {
    return p.y >= 0 && p.y < grid.size() && p.x >= 0 && p.x < grid[0].size();
}

void movePosition(const std::vector<std::string>& lines, Position& pos, Position& dir) {
    if (!inBounds(lines, pos))
    {
        return;
    }
    
    Position nextPos = pos + dir;

    while (lines[nextPos.y][nextPos.x] == '#')
    {
        dir.turnRight();
        nextPos = pos + dir;
    }

    pos = nextPos;
}


bool findCycle(const std::vector<std::string>& lines, const Position& start, const Position& dir) {
    auto slowPos = start;
    auto slowDir = dir;

    auto fastPos = start;
    auto fastDir = dir;
    movePosition(lines, fastPos, fastDir);

    while (inBounds(lines, fastPos)) {
        if (fastPos == slowPos)
        {
            return true;
        }

        movePosition(lines, slowPos, slowDir);

        movePosition(lines, fastPos, fastDir);
        movePosition(lines, fastPos, fastDir);
    }

    return false;
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

int main(int argc, char const *argv[])
{
    std::ifstream file("smallinput.txt");

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

    // get positions we visit
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

    // remove starting position
    visited.erase(p.first);

    int res = 0;
    for (auto &&pos : visited)
    {
        lines[pos.y][pos.x] = '#';
        if (findCycle(lines, pos, p.second))
        {
            ++res;
        }    
    }
    
    std::cout << res << std::endl;
    
    return 0;
}
