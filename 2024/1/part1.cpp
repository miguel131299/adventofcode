#include <fstream>
#include <iostream>
#include <string>

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

    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());

    unsigned int diff = 0;
    for (size_t i = 0; i < col1.size(); i++)
    {
        diff += abs(col1[i] - col2[i]);
    }

    std::cout << diff << std::endl;
    
    return 0;
}
