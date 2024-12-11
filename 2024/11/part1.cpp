#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


std::vector<uint64_t> splitToInts(std::string& line) {
    std::vector<uint64_t> result;
    std::istringstream stream(line);
    uint64_t number;

    while (stream >> number)
        result.push_back(number);

    return result;
}

vector<uint64_t> blink(const vector<uint64_t>& stones) {
    vector<uint64_t> res;
    res.reserve(stones.size());

    for (auto &&stone : stones)
    {
        string nString = to_string(stone);
        if (stone == 0)
            res.push_back(1);
        
        else if (nString.size() % 2 == 0) {
            uint64_t left = stoull(nString.substr(0, nString.size() / 2));
            uint64_t right = stoull(nString.substr(nString.size() / 2));

            res.push_back(left);
            res.push_back(right);
        }
        else {
            res.push_back(stone * 2024);
        }
        
    }

    return res;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }


    std::string line;
    while (std::getline(file, line)) {
    }
    file.close();


    vector<uint64_t> stones = splitToInts(line);

    for (size_t i = 0; i < 75; i++)
    {
        stones = blink(stones);
        cout << i << endl;
    }
    
    //printVector(stones);

    std::cout << stones.size() << std::endl;
    
    return 0;
}
