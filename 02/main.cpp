#include <iostream>
#include <sstream>
#include <fstream>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string command;
    unsigned int unit;

    unsigned int final_pos_h = 0;
    unsigned int final_pos_v = 0;

    while(getline(read_file, read_text)) {

        command = read_text.substr(0, read_text.find(' '));
        std::string unit_string = read_text.substr(read_text.find(' ') + 1, read_text.find('\n'));
        std::stringstream ss(unit_string);
        ss >> unit;

        if(command == "forward") final_pos_h += unit;
        else if(command == "down") final_pos_v += unit;
        else final_pos_v -= unit;
    }

    read_file.close();

    std::string answer = std::to_string(final_pos_h * final_pos_v);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string command;
    unsigned int unit;

    unsigned int final_pos_h = 0;
    unsigned int final_pos_v = 0;
    unsigned int final_aim = 0;

    while(getline(read_file, read_text)) {

        command = read_text.substr(0, read_text.find(' '));
        std::string unit_string = read_text.substr(read_text.find(' ') + 1, read_text.find('\n'));
        std::stringstream ss(unit_string);
        ss >> unit;

        if(command == "forward") {
            
            final_pos_h += unit;
            final_pos_v += final_aim * unit;
        }
        else if(command == "down") final_aim += unit;
        else final_aim -= unit;
    }

    read_file.close();

    std::string answer = std::to_string(final_pos_h * final_pos_v);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}