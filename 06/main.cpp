#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <unsigned long int> all_fish(9, 0);

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_number_string;
            getline(ss, read_number_string, ',');
            int read_number;
            std::stringstream sss(read_number_string);
            sss >> read_number;

            all_fish.at(read_number)++;
        }
    }

    unsigned long int total_day = 80;
    for(unsigned long int day_remaining = 0; day_remaining < total_day; day_remaining++) {

        unsigned long int born_fish = all_fish.at(0);
        for(unsigned long int day = 0; day < 8; day++) all_fish.at(day) = all_fish.at(day + 1);
        all_fish.at(6) += born_fish;
        all_fish.at(8) = born_fish;
    }

    unsigned long int fish_count = 0;
    for(unsigned long int fish : all_fish) fish_count += fish; 

    std::string answer = std::to_string(fish_count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <unsigned long int> all_fish(9, 0);

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_number_string;
            getline(ss, read_number_string, ',');
            int read_number;
            std::stringstream sss(read_number_string);
            sss >> read_number;

            all_fish.at(read_number)++;
        }
    }

    unsigned long int total_day = 256;
    for(unsigned long int day_remaining = 0; day_remaining < total_day; day_remaining++) {

        unsigned long int born_fish = all_fish.at(0);
        for(unsigned long int day = 0; day < 8; day++) all_fish.at(day) = all_fish.at(day + 1);
        all_fish.at(6) += born_fish;
        all_fish.at(8) = born_fish;
    }

    unsigned long int fish_count = 0;
    for(unsigned long int fish : all_fish) fish_count += fish; 

    std::string answer = std::to_string(fish_count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}