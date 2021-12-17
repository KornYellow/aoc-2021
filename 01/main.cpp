#include <iostream>
#include <sstream>
#include <fstream>

void part1() {

    std::ifstream read_file("input.txt"); 
    std::string read_text;

    unsigned int count = 0;

    unsigned int last_int = 0;
    while(getline(read_file, read_text)) {

        unsigned int read_int;
        std::stringstream ss(read_text);
        ss >> read_int;
        
        if(last_int != 0 && read_int > last_int) count++;
        last_int = read_int;
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt"); 
    std::string read_text;

    unsigned int count = 0;

    unsigned int read_int_1 = 0;
    unsigned int read_int_2 = 0;
    unsigned int read_int_3 = 0;

    unsigned int last_sum = 0;
    unsigned int read_sum = 0;

    while(getline(read_file, read_text)) {

        unsigned int read_int;
        std::stringstream ss(read_text);
        ss >> read_int;

        if(read_int_1 != 0 && read_int_2 != 0 && read_int_3 != 0) {

            read_sum = read_int_1 + read_int_2 + read_int_3;
            
            if(last_sum != 0 && read_sum > last_sum) count++;
            last_sum = read_sum;
        }

        read_int_3 = read_int_2;
        read_int_2 = read_int_1;
        read_int_1 = read_int;
    }

    read_sum = read_int_1 + read_int_2 + read_int_3;
    if(last_sum != 0 && read_sum > last_sum) count++;

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}