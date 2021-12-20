#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> grid_map;

    while(getline(read_file, read_text)) grid_map.push_back(read_text);

    unsigned long int count = 0;

    for(unsigned long int row_index = 0; row_index < grid_map.size(); row_index++) {
        for(unsigned long int column_index = 0; column_index < grid_map.at(row_index).size(); column_index++) {

            unsigned short self = grid_map.at(row_index).at(column_index);
            unsigned short north = 255;
            unsigned short south = 255;
            unsigned short east = 255;
            unsigned short west = 255;
            if((long)row_index - 1 >= 0) north = grid_map.at(row_index - 1).at(column_index);
            if(row_index + 1 < grid_map.size()) south = grid_map.at(row_index + 1).at(column_index);
            if((long)column_index - 1 >= 0) west = grid_map.at(row_index).at(column_index - 1);
            if(column_index + 1 < grid_map.at(row_index).size()) east = grid_map.at(row_index).at(column_index + 1);

            if(self >= north) continue;
            if(self >= south) continue;
            if(self >= east) continue;
            if(self >= west) continue;

            count += self + 1 - '0';
        }
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

unsigned long int recursiveFind(std::vector <std::string> *grid_map, long x_pos, long y_pos) {

    if(y_pos < 0 || y_pos >= grid_map->size() || x_pos < 0 || x_pos >= grid_map->at(y_pos).size()) return 0;
    if(grid_map->at(y_pos).at(x_pos) == '.' || grid_map->at(y_pos).at(x_pos) - '0' == 9) return 0;
    
    grid_map->at(y_pos).at(x_pos) = '.';
    return 1 + 
        recursiveFind(grid_map, x_pos, y_pos - 1) + 
        recursiveFind(grid_map, x_pos, y_pos + 1) + 
        recursiveFind(grid_map, x_pos - 1, y_pos) + 
        recursiveFind(grid_map, x_pos + 1, y_pos);
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> grid_map;
    std::vector <std::string> number_map;

    while(getline(read_file, read_text)) grid_map.push_back(read_text);
    number_map = grid_map;

    std::vector <unsigned long int> answer_set;

    for(unsigned long int row_index = 0; row_index < number_map.size(); row_index++) {
        for(unsigned long int column_index = 0; column_index < number_map.at(row_index).size(); column_index++) {

            unsigned short self = number_map.at(row_index).at(column_index);
            unsigned short north = 255;
            unsigned short south = 255;
            unsigned short east = 255;
            unsigned short west = 255;
            if((long)row_index - 1 >= 0) north = number_map.at(row_index - 1).at(column_index);
            if(row_index + 1 < number_map.size()) south = number_map.at(row_index + 1).at(column_index);
            if((long)column_index - 1 >= 0) west = number_map.at(row_index).at(column_index - 1);
            if(column_index + 1 < number_map.at(row_index).size()) east = number_map.at(row_index).at(column_index + 1);

            if(self >= north) continue;
            if(self >= south) continue;
            if(self >= east) continue;
            if(self >= west) continue;

            unsigned long int count = recursiveFind(&grid_map, (long)column_index, (long)row_index);
            answer_set.push_back(count);
        }
    }

    sort(answer_set.begin(), answer_set.end());
    
    unsigned long int sum = 1;
    for(unsigned long int i = answer_set.size() - 3; i < answer_set.size(); i++) sum *= answer_set.at(i);
    
    read_file.close();

    std::string answer = std::to_string(sum);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}