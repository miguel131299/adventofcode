#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Function to print a vector
template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


bool checkReportSafe(const std::vector<int>& v, bool incresing) {

    for (size_t i = 1; i < v.size(); i++)
    {
        bool condition = incresing ? v[i-1] < v[i] : v[i-1] > v[i];
        int dist = abs(v[i] - v[i-1]);

        if (!condition || dist > 3)
            return false;
    }

    return true;
}

std::vector<int> splitToInts(std::string& line) {
    std::vector<int> result;
    std::istringstream stream(line);
    int number;

    while (stream >> number)
        result.push_back(number);

    return result;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
    }

    std::vector<std::vector<int>> reports;
    reports.reserve(1000);

    std::string line;
    while (std::getline(file, line)) {

        reports.emplace_back(splitToInts(line));
    }
    file.close();


    // reports = {
    //     {1, 2, 4, 7, 9, 8},                 // not safe
    //     {43, 44, 47, 49, 49},               // not safe
    //     {6, 7, 9, 11, 13, 14, 18},          // not safe
    //     {34, 35, 38, 39, 42, 48},           // not safe
    //     {73, 76, 79, 80, 82, 85, 83, 86},   // not safe
    //     {64, 67, 69, 66, 69, 68},           // not safe
    //     {43, 45, 48, 50, 49, 49},           // not safe
    //     {77, 78, 81, 78, 81, 83, 87},       // not safe
    //     {7, 6, 4, 2, 1},                    // safe
    //     {1, 3, 6, 7, 9}                     // safe
    // };

//     reports = {
//     {7, 6, 4, 2, 1},
//     {1, 2, 7, 8, 9},
//     {9, 7, 6, 2, 1},
//     {1, 3, 2, 4, 5},
//     {8, 6, 4, 4, 1},
//     {1, 3, 6, 7, 9}
// };



    unsigned int safeReports = 0;
    for (size_t i = 0; i < reports.size(); i++)
    {
        if (checkReportSafe(reports[i], false) || checkReportSafe(reports[i], true))
        {
            ++safeReports;
        }
        
    }

    std::cout << safeReports << std::endl;
    
    return 0;
}
