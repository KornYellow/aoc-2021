#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

unsigned long int abs(long number) {

    if(number < 0) return -number;
    return number;
}

unsigned long int sum_of_number(unsigned long number) {

    if(number == 0) return 0;
    return sum_of_number(number - 1) + number;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <unsigned long int> numbers;

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_number_string;
            getline(ss, read_number_string, ',');
            int read_number;
            std::stringstream sss(read_number_string);
            sss >> read_number;

            numbers.push_back(read_number);
        }
    }

    unsigned long int lowest = 999999999;
    unsigned long int pointer = 0;
    while(pointer != numbers.size()) {
        
        unsigned long int fuel = 0;
        for(unsigned long int i = 0; i < numbers.size(); i++) {

            unsigned long int fuel_cost = abs((long)numbers.at(pointer) - (long)numbers.at(i));
            fuel += fuel_cost;
        }
        if(fuel < lowest) lowest = fuel;

        pointer++;
    }

    read_file.close();

    std::string answer = std::to_string(lowest);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <unsigned long int> numbers;

    unsigned long int max_number = 0;
    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_number_string;
            getline(ss, read_number_string, ',');
            int read_number;
            std::stringstream sss(read_number_string);
            sss >> read_number;

            numbers.push_back(read_number);
            if(read_number > max_number) max_number = read_number;
        }
    }

    unsigned long int lowest = 999999999;
    unsigned long int pointer = 0;
    while(pointer != max_number) {
        
        unsigned long int fuel = 0;
        for(unsigned long int i = 0; i < numbers.size(); i++) {

            unsigned long int fuel_cost = sum_of_number(abs((long)pointer - (long)numbers.at(i)));
            fuel += fuel_cost;
        }
        if(fuel < lowest) lowest = fuel;

        pointer++;
    }
    
    read_file.close();

    std::string answer = std::to_string(lowest);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}