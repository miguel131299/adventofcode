#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<int> compactFile(string& file) {
    string original = file;
    uint64_t r = file.size() - 1;
    uint64_t l = 0;

    vector<int> res;
    bool leftNext = true;

    while(l < r) {
        if (leftNext)
        {
            if (file[l] - '0' == 0) {
                leftNext = false;
                continue;
            }
            else {
                file[l] -= 1;
            }
        }

        else {
            if (file[l+1] - '0' == 0) {
                leftNext = true;
                l += 2;
                continue;
            }
            else {
                if (file[r] - '0' == 0) {
                    r -= 2;
                    continue;
                }
                else {
                    file[l+1] -= 1;
                    file[r] -= 1;
                }
            }
        }
        res.push_back(leftNext ? l/2 : r/2);
    }

    while (file[r] - '0' > 0) {
        res.push_back(r/2);
        file[r] -= 1;
    }

    return res;
}

uint64_t computeChecksum(const vector<int>& v) {
    uint64_t res = 0;

    for (size_t i = 0; i < v.size(); i++)
    {
        res += i * v[i];
    }

    return res;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");

    if (!file.is_open())
        std::cerr << "Error opening file." << std::endl;

    std::string line;
    while (std::getline(file, line)) {
    }
    file.close();

    // line = "12345";
    auto v = compactFile(line);

    cout << computeChecksum(v) << endl;

    return 0;
}
