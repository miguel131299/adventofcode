#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<vector<int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

bool inBounds(const std::vector<std::string> grid, int r, int c) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

void runTrail(const vector<string>& grid, int r, int c, char level, int& counter) {
    if (level == '9') {
        ++counter;
        return;
    }

    for (auto&& dir: DIRS) {
        if (inBounds(grid, r + dir[1], c + dir[0]) && grid[r + dir[1]][c + dir[0]] == level + 1)
        {
            runTrail(grid, r + dir[1], c + dir[0], level + 1, counter);
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

    int res = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[0].size(); j++)
        {
            if (lines[i][j] == '0') {
                runTrail(lines, i, j, '0', res);
            }
        }
    }
    
    std::cout << res << std::endl;
    
    return 0;
}
