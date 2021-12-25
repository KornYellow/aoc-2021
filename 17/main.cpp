#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

int calcHighestPosition(int y_1) {

    int current_y = 0;
    for(int current_y_spd = (-y_1) - 1; current_y_spd != 0; current_y_spd--) {
        current_y += current_y_spd;
    }
    return current_y;
}

unsigned int findAllPath(int min_x, int max_x, int min_y, int max_y) {

    unsigned int counter = 0;
    int max_t = std::max(-2 * min_y + 1, max_x);
    
    for (int velo_y = min_y; velo_y <= -min_y; velo_y++) {
        for (int velo_x = 1; velo_x <= max_x; velo_x++) {
            for (int t = 1; t <= max_t; t++) {

                int y = velo_y * t - t * (t - 1) / 2;

                int x;
                if (t < velo_x) x = velo_x * t - t * (t - 1) / 2;
                else x = velo_x * (velo_x + 1) / 2;

                if (min_y <= y && y <= max_y && 
                    min_x <= x && x <= max_x) {

                    counter++;
                    break;
                }
            }
        }
    }
    return counter;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;
    getline(read_file, read_text);

    std::vector <std::string> read_text_vector;
    std::stringstream ss(read_text);
    while(ss.good()) {
        std::string read_text_sep;
        getline(ss, read_text_sep, ' ');
        read_text_vector.push_back(read_text_sep);
    }

    std::pair <int, int> target_1;
    std::pair <int, int> target_2;
    target_1.first = std::stoi(read_text_vector.at(0), 0, 10);
    target_1.second = std::stoi(read_text_vector.at(2), 0, 10);
    target_2.first = std::stoi(read_text_vector.at(1), 0, 10);
    target_2.second = std::stoi(read_text_vector.at(3), 0, 10);

    read_file.close();

    std::string answer = std::to_string(calcHighestPosition(target_1.second));
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;
    getline(read_file, read_text);

    std::vector <std::string> read_text_vector;
    std::stringstream ss(read_text);
    while(ss.good()) {
        std::string read_text_sep;
        getline(ss, read_text_sep, ' ');
        read_text_vector.push_back(read_text_sep);
    }

    std::pair <int, int> target_1;
    std::pair <int, int> target_2;
    target_1.first = std::stoi(read_text_vector.at(0), 0, 10);
    target_1.second = std::stoi(read_text_vector.at(2), 0, 10);
    target_2.first = std::stoi(read_text_vector.at(1), 0, 10);
    target_2.second = std::stoi(read_text_vector.at(3), 0, 10);

    read_file.close();

    std::string answer = std::to_string(findAllPath(target_1.first, target_2.first, target_1.second, target_2.second));
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}