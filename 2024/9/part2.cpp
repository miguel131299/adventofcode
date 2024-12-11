#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

long long solve(const string& D, bool part2) {
    deque<tuple<int, int, int>> A; // Stores file segments (pos, size, file_id)
    deque<pair<int, int>> SPACE;  // Stores space segments (pos, size)
    vector<int> FINAL;            // Represents the final arrangement
    int file_id = 0, pos = 0;

    // Process input string D
    for (size_t i = 0; i < D.size(); ++i) {
        int c = D[i] - '0';
        if (i % 2 == 0) { // File segment
            if (part2) {
                A.push_back({pos, c, file_id});
            }
            for (int j = 0; j < c; ++j) {
                FINAL.push_back(file_id);
                if (!part2) {
                    A.push_back({pos, 1, file_id});
                }
                ++pos;
            }
            ++file_id;
        } else { // Space segment
            SPACE.push_back({pos, c});
            for (int j = 0; j < c; ++j) {
                FINAL.push_back(-1); // -1 indicates empty space
                ++pos;
            }
        }
    }

    // Rearrange file segments into spaces
    for (auto it = A.rbegin(); it != A.rend(); ++it) {
        int pos = get<0>(*it), sz = get<1>(*it), file_id = get<2>(*it);
        for (size_t space_i = 0; space_i < SPACE.size(); ++space_i) {
            int space_pos = SPACE[space_i].first, space_sz = SPACE[space_i].second;
            if (space_pos < pos && sz <= space_sz) {
                for (int j = 0; j < sz; ++j) {
                    assert(FINAL[pos + j] == file_id);
                    FINAL[pos + j] = -1; // Clear the original position
                    FINAL[space_pos + j] = file_id; // Move to space
                }
                SPACE[space_i] = {space_pos + sz, space_sz - sz}; // Update space
                break;
            }
        }
    }

    // Calculate the result
    long long ans = 0;
    for (size_t i = 0; i < FINAL.size(); ++i) {
        if (FINAL[i] != -1) {
            ans += i * FINAL[i];
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    string infile = (argc >= 2) ? argv[1] : "9.in";
    ifstream file(infile);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << infile << endl;
        return 1;
    }

    string D;
    file >> D;
    file.close();

    long long p1 = solve(D, false);
    long long p2 = solve(D, true);

    cout << p1 << endl;
    cout << p2 << endl;

    return 0;
}
