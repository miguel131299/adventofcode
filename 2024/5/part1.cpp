#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

std::vector<int> stringToIntVector(const std::string& input, char c) {
    std::vector<int> result;
    std::stringstream ss(input);
    std::string number;
    
    // Split the string by commas
    while (std::getline(ss, number, c)) {
        result.push_back(std::stoi(number)); // Convert each substring to an int
    }
    
    return result;
}

bool checkOrdering(const std::vector<int>& v, std::unordered_map<int, std::unordered_set<int>>& deps) {
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = i; j < v.size(); j++)
        {
            if (deps[v[i]].count(v[j]))
            {
                return false;
            }
            
        }
        
    }

    return true;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }


    // maps from job to jobs that have to come before.
    int res = 0;
    std::unordered_map<int, std::unordered_set<int>> dependencies;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        else if (line[2] == '|')
        {
            auto v = stringToIntVector(line, '|');
            dependencies[v[1]].insert(v[0]);
        }
        else {
            auto v = stringToIntVector(line, ',');
            if (checkOrdering(v, dependencies))
            {
                res += v[v.size()/2];
            }
            
        }        
    }
    file.close();

    std::cout << res << std::endl;
    
    return 0;
}
