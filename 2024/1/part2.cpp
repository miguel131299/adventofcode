#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::vector<int> col1(1000);
    std::vector<int> col2(1000);

    std::string line;
    while (std::getline(file, line)) {
        col1.emplace_back(stoi(line.substr(0, 5)));
        col2.emplace_back(stoi(line.substr(8, 5)));
    }
    file.close();

    std::unordered_map<int, int> counter;
    for (size_t i = 0; i < col1.size(); i++)
    {
        counter[col1[i]] = 0;
    }

    for (size_t i = 0; i < col2.size(); i++)
    {
        auto it = counter.find(col2[i]);
        if (it != counter.end())
        {
            it->second++;
        }
    }

    unsigned int sim_score = 0;
    for (auto&& p: counter) {
        sim_score += p.first * p.second;
    }

    std::cout << sim_score << std::endl;
    
    return 0;
}
