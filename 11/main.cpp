#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

unsigned long int recursiveFlash(std::vector <std::string> *grid, unsigned int x, unsigned int y) {

    if(grid->at(y).at(x) != ':') return 0;
    unsigned long int flashes = 0;
    grid->at(y).at(x) = '0';
    flashes++;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {

            if(i == 0 && j == 0) continue;
            if((int)x + j < 0 || (int)x + j >= grid->at(0).size() || 
               (int)y + i < 0 || (int)y + i >= grid->size()) continue;
            
            if(grid->at(y + i).at(x + j) == '0' || grid->at(y + i).at(x + j) == ':') continue;
            grid->at(y + i).at(x + j)++;
            flashes += recursiveFlash(grid, x + j, y + i);
        }
    }
    return flashes;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> grid;

    while(getline(read_file, read_text)) grid.push_back(read_text);

    unsigned long int total_flashes = 0;

    unsigned int step_max = 99;
    for(unsigned int step = 0; step < step_max + 1; step++) {
        
        for(unsigned int y = 0; y < grid.size(); y++) for(unsigned int x = 0; x < grid.at(y).size(); x++) grid.at(y).at(x)++;
        for(unsigned int y = 0; y < grid.size(); y++) for(unsigned int x = 0; x < grid.at(y).size(); x++) total_flashes += recursiveFlash(&grid, y, x);
    }

    read_file.close();

    std::string answer = std::to_string(total_flashes);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> grid;

    while(getline(read_file, read_text)) grid.push_back(read_text);

    unsigned long int total_flashes = 0;

    unsigned int step = 0;
    while(total_flashes != 100) {
        
        total_flashes = 0;
        for(unsigned int y = 0; y < grid.size(); y++) for(unsigned int x = 0; x < grid.at(y).size(); x++) grid.at(y).at(x)++;
        for(unsigned int y = 0; y < grid.size(); y++) for(unsigned int x = 0; x < grid.at(y).size(); x++) total_flashes += recursiveFlash(&grid, y, x);
        step++;
    }

    read_file.close();

    std::string answer = std::to_string(step);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}