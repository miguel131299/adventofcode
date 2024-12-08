#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

std::vector<std::string> splitString(const std::string& input, char c) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string s;
    
    // Split the string by commas
    while (std::getline(ss, s, c)) {
        result.push_back(s); // Convert each substring to an int
    }
    
    return result;
}

std::vector<uint64_t> stringToInts(const std::string& input, char c) {
    std::vector<uint64_t> result;
    std::stringstream ss(input);
    std::string number;
    
    // Split the string by commas
    while (std::getline(ss, number, c)) {
        if (number.empty())
            continue;
        
        result.push_back(std::stoul(number)); // Convert each substring to an int
    }
    
    return result;
}


bool exprValid(const std::vector<uint64_t>& nums, int level, uint64_t cur, uint64_t target) {
    if (cur > target)
        return false;

    if (level == nums.size())
        return cur == target;

    // concatenate 
    uint64_t conc = stoul(to_string(cur) + to_string(nums[level]));

    
    return exprValid(nums, level + 1, cur + nums[level], target) 
            || exprValid(nums, level + 1, cur * nums[level], target)
            || exprValid(nums, level + 1, conc, target);
}


int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line;
    uint64_t res = 0;
    while (std::getline(file, line)) {
        auto s = splitString(line, ':');
        uint64_t target = stoul(s[0]);
        auto nums = stringToInts(s[1], ' ');

        if (exprValid(nums, 1, nums[0], target)) {
            res += target;
        }
        
    }
    file.close();

    std::cout << res << std::endl;
    
    return 0;
}
