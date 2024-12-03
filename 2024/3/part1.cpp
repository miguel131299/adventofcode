#include <iostream>
#include <fstream>
#include <vector>
#include <fcntl.h>      // file control options (open, and its arguments)
#include <unistd.h>     // lseek
#include <sys/mman.h>   // mmap


inline uint32_t fromChars(const char* begin, size_t n) {
    uint sum = 0;

    for (size_t i = 0; i < n; ++i) {
        sum *= 10;
        sum += *begin - '0';

        begin++;
    }

    return sum;
}

class FileView
{
private:
    int handle;
    char* data;
    size_t size;

public:
    explicit FileView(const std::string& filename) {
        handle = open(filename.c_str(), O_RDONLY);
        if (handle < 0)
            exit(1);

        lseek(handle, 0, SEEK_END);
        size = lseek(handle, 0, SEEK_CUR);

        void *ptr = mmap(nullptr, size, PROT_READ, MAP_SHARED, handle, 0);
        data = static_cast<char*>(ptr);
    }

    ~FileView() {
        munmap(data, size);
        close(handle);
    }

    const char* begin() const { return data; }
    const char* end() const { return data + size; }
};

bool checkOps(const char* begin, bool& enabled) {
    if (*begin == 'm' && *(begin+1) == 'u' && *(begin+2)=='l' && *(begin+3) == '(')
        return true;

    // uncomment for part2 answer
    // if ((*begin == 'd' && *(begin+1) == 'o' && *(begin+2)=='(' && *(begin+3) == ')'))
    //     enabled = true;
    
    // if (*begin == 'd' && *(begin+1) == 'o' && *(begin+2)=='n' 
    //     && *(begin+3) == '\'' && *(begin+4) == 't'
    //     && *(begin+5) == '(' && *(begin+6) == ')')
    //     enabled = false;

    return false;
}

int doMults(const char* viewBegin, const char* viewEnd) {
    uint64_t res = 0;
    bool enabled = true;
    //shortest mul operation has at least 8 chars (e.g. mul(x,y))
    int SHORTEST_MUL = 8;

    for (auto begin = viewBegin; begin < viewEnd - SHORTEST_MUL;) {

        // go to start of mul operation
        while(begin < viewEnd - SHORTEST_MUL && !checkOps(begin, enabled)) {
            ++begin;
        }

        if (!enabled)
        {
            ++begin;
            continue;
        }
        


        // begin to start of first operand
        begin += 4;


        bool abort = false;

        // number can be max 3 digits long
        const char* iter;
        for (iter = begin; iter < begin + 3; ++iter) {
            if ((*iter) == ',')
            {
                // comma came too early. First number doesnt exist
                if (iter == begin)
                {
                    abort = true;
                    break;
                }
                else
                    break;
            }
            
            else if ((*iter) < '0' || (*iter) > '9') {
                abort = true;
                break;
            }

            // normal numbers
        }

        if (abort || ((*iter) != ','))
        {
            //continue with outer loop;
            begin = iter + 1;
            continue;
        }

        int firstOp = fromChars(begin, iter - begin);

        // skip comma
        begin = iter+1;

        for (iter = begin; iter < begin + 3; ++iter) {     
            if ((*iter) == ')')
            {
                // comma came too early. First number doesnt exist
                if (iter == begin)
                {
                    abort = true;
                    break;
                }
                else
                    break;
            }
            
            else if ((*iter) < '0' || (*iter) > '9') {
                abort = true;
                break;
            }

            // normal numbers
        }

        if (abort || (*iter) != ')') {
            //continue with outer loop;
            begin = iter + 1;
            continue;
        }

        int secondOp = fromChars(begin, iter - begin);

        res += firstOp * secondOp;
    }

    return res;
}


int main() {
    // Open the file in binary mode
    FileView fv("input.txt");

    std::cout << doMults(fv.begin(), fv.end()) << std::endl;
    return 0;
}
