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

int main(int argc, char const *argv[])
{
    std::ifstream file("sample.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }


    std::string line;
    while (std::getline(file, line)) {
    }
    file.close();


    vector<uint64_t> input = splitToInts(line);

    unordered_map<uint64_t, uint64_t> stones;
    vector<uint64_t> evens, odds;

    for (auto &&x : input)
    {
        stones[x] = 1;
        
        if (x == 0)
            continue;

        if (to_string(x).length() % 2 == 0)
            evens.push_back(x);
        else
            odds.push_back(x);
        
    }
    

    for (size_t i = 0; i < 6; i++)
    {
        unordered_map<uint64_t, uint64_t> newStones;
        vector<uint64_t> newEvens, newOdds;

        if (stones.find(0) != stones.end())
        {
            newStones[1] += stones[0];
            newOdds.push_back(1);
        }

        for (auto &&even : evens)
        {
            string s = to_string(even);
            uint64_t mid = s.length() / 2;
            uint64_t first = stoull(s.substr(0, mid));
            uint64_t second = stoull(s.substr(mid));

            newStones[first] += stones[even];
            newStones[second] += stones[even];

            if (to_string(first).length() % 2 == 0) {
                newEvens.push_back(first);
            } else if (first != 0) {
                newOdds.push_back(first);
            }

            if (to_string(second).length() % 2 == 0) {
                newEvens.push_back(second);
            } else if (second != 0) {
                newOdds.push_back(second);
            }
        }

        for (auto &&odd : odds) {
            uint64_t newOdd = odd * 2024;
            newStones[newOdd] += stones[odd];
            if (to_string(newOdd).length() % 2 == 0) {
                newEvens.push_back(newOdd);
            } else {
                newOdds.push_back(newOdd);
            }
        }

        
        evens.assign(newEvens.begin(), newEvens.end());
        odds.assign(newOdds.begin(), newOdds.end());
        stones = newStones;

            // Calculate the total number of stones
    uint64_t stoneCount = 0;
    for (const auto& [stone, count] : stones) {
    cout << stone << " " << count << " stones" << endl;
        stoneCount += count;
    }

    // Output the result
    cout << i+1 << " " << stoneCount << endl;

    }
    
    //printVector(stones);

    // Calculate the total number of stones
    uint64_t stoneCount = 0;
    for (const auto& [stone, count] : stones) {
        stoneCount += count;
    }

    // Output the result
    cout << stoneCount << endl;
    
    return 0;
}
