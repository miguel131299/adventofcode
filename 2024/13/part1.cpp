#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

// Function to print a vector
template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

std::vector<string> splitS(std::string& input, char del = ' ') {
    std::istringstream stream(input);
    std::vector<string> result;
    string word;

    while (getline(stream, word, del))
        result.push_back(word);

    return result;
}

int64_t solveLinearEquation(int64_t a1, int64_t a2, int64_t b1, int64_t b2, int64_t c1, int64_t c2) {
    int64_t det = a1 * b2 - a2 * b1;
    int64_t Dx = c1 * b2 - c2 * b1; // Determinant for x
    int64_t Dy = a1 * c2 - a2 * c1; // Determinant for y


    if (det != 0)
    {
        int64_t x = Dx / det;
        int64_t y = Dy / det;

        // if (x < 0 || y < 0 || x > 100 || y > 100)
        //     return 0;

        if (a1 * x + b1 * y == c1 && a2 * x + b2 * y == c2)
            return 3 * x + y;
        else 
            return 0;
    }
    else if (Dx == 0 || Dy == 0)
        throw runtime_error("infinte solutions");
    else 
        throw runtime_error("No solutions");
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    int idx = 0;
    vector<array<int64_t, 2>> equations;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        auto words = splitS(line);
        switch (idx % 3)
        {
        case 0:
        case 1:{
            auto f = splitS(words[2], '+');
            auto s = splitS(words[3], '+');
            if (f.size() <= 1 || s.size() <= 1)
                throw runtime_error("Invalid input format in line: " + line);
            array<int64_t, 2> fs;
            fs[0] = stoull(f[1].substr(0, f[1].size() - 1));
            fs[1] = stoull(s[1].substr(0, s[1].size()));
            equations.push_back(fs);
            break;
        }
        case 2:
        {
            auto f = splitS(words[1], '=');
            auto s = splitS(words[2], '=');
            if (f.size() <= 1 || s.size() <= 1)
                throw runtime_error("Invalid input format in line: " + line);
            array<int64_t, 2> fs;
            fs[0] = stoi(f[1].substr(0, f[1].size() - 1)) + 10000000000000;
            fs[1] = stoi(s[1].substr(0, s[1].size())) + 10000000000000;
            equations.push_back(fs);
        }
        default:
            break;
        }

        ++idx;
    }
    file.close();

    if (equations.size() % 3 != 0) {
    throw runtime_error("Invalid number of equations. Must be multiple of 3.");
    }


    uint64_t res = 0;
    for (size_t i = 0; i < equations.size(); i += 3)
    {
        res += solveLinearEquation(equations[i][0], equations[i][1], 
                            equations[i+1][0], equations[i+1][1], 
                            equations[i+2][0], equations[i+2][1]);
    }

    cout << res << endl;
    
    return 0;
}
