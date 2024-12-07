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

    Position turnRight() const {
        if (x == 1) {
            return Position(1, 0);
        } else if (y == 1) {
            return Position(0, -1);
        } else if (x == -1) {
            return Position(-1, 0);
        } else if (y == -1) {
            return Position(0, 1);
        }
        throw std::runtime_error("Invalid Position for turnRight");
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

bool inBounds(const std::vector<std::string>& grid, const Position& p) {
    return p.y >= 0 && p.y < grid.size() && p.x >= 0 && p.x < grid[p.y].size();
}

Position getNextPos(const std::vector<std::string>& lines, const Position pos, Position& dir) {
    Position nextPos = pos + dir;
    while (lines[nextPos.y][nextPos.x] == '#') {
        dir = dir.turnRight();
        nextPos = pos + dir;
    }
    return nextPos;
}

void movePosition(const std::vector<std::string>& lines, Position& pos, Position& dir) {
    if (!inBounds(lines, pos)) {
        return;
    }
    pos = getNextPos(lines, pos, dir);
}

void printGrid(std::vector<std::string> lines, const Position& p, bool fast) {
    if (!inBounds(lines, p))
    {
        return;
    }

    lines[p.y][p.x] = fast ? 'f' : 's';

    for (auto&& l: lines) {
        std::cout << l << '\n';
    }

    std::cout << std::endl;
}


bool findCycle(const std::vector<std::string>& lines, Position start, Position dir) {
    auto slowPos = start;
    auto slowDir = dir;

    auto fastPos = start;
    auto fastDir = dir;
    movePosition(lines, fastPos, fastDir);

    while (inBounds(lines, fastPos)) {
        if (fastPos == slowPos && fastDir == slowDir)
        {
            return true;
        }

        movePosition(lines, slowPos, slowDir);
        // printGrid(lines, slowPos, false);

        movePosition(lines, fastPos, fastDir);
        movePosition(lines, fastPos, fastDir);
        // printGrid(lines, fastPos, true);
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

    auto s = getCursor(lines);
    auto cursorPos = s.first;
    auto cursorDir = s.second;
    std::unordered_set<Position> visited;

    // get positions we visit
    int res = 0;
    while (inBounds(lines, cursorPos)) {
        visited.insert(cursorPos);
        Position nextPos = getNextPos(lines, cursorPos, cursorDir);

        cursorPos = nextPos;
    }
    
    for (auto && p: visited) {
        if (lines[p.y][p.x] != '.')
            continue;

        lines[p.y][p.x] = '#';
        if (findCycle(lines, s.first, s.second))
            res++;
        lines[p.y][p.x] = '.';
        
    }

    std::cout << res << std::endl;
    
    return 0;
}
