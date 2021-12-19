#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    const int size = 12;
    unsigned int on_bit[size] = {0};
    unsigned int off_bit[size] = {0};

    while(getline(read_file, read_text)) {

        for(unsigned int i = 0; i < size; i++) {

            if(read_text.at(i) == '1') on_bit[i]++;
            else off_bit[i]++;
        }
    }

    std::string gamma_rate_bin = "000000000000";
    std::string epsilon_rate_bin = "111111111111";

    for(unsigned int i = 0; i < size; i++) {
        if(on_bit[i] > off_bit[i]) {
            
            gamma_rate_bin.at(i) = '1';
            epsilon_rate_bin.at(i) = '0';
        }
    }

    read_file.close();
    
    unsigned int gamma_rate = std::stoi(gamma_rate_bin, 0, 2);
    unsigned int epsilon_rate = std::stoi(epsilon_rate_bin, 0, 2);

    std::string answer = std::to_string(gamma_rate * epsilon_rate);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> oxygen_bit_grid;
    std::vector <std::string> carbon_bit_grid;

    while(getline(read_file, read_text)) {
        oxygen_bit_grid.push_back(read_text);
        carbon_bit_grid.push_back(read_text);
    }

    const unsigned int bit_size = 12;

    for(unsigned int bit_column = 0; bit_column < bit_size; bit_column++) {
        
        unsigned int on_bit_count = 0;
        unsigned int off_bit_count = 0;

        if(oxygen_bit_grid.size() == 1) break;
        for(unsigned int bit_row = 0; bit_row < oxygen_bit_grid.size(); bit_row++) {

            if(oxygen_bit_grid.at(bit_row).at(bit_column) == '1') on_bit_count++;
            else off_bit_count++;
        }
        
        char keep_bit = '1';
        if(on_bit_count < off_bit_count) keep_bit = '0';

        bool is_found = true;
        while(is_found) {

            is_found = false;
            for(unsigned int sample_index = 0; sample_index < oxygen_bit_grid.size(); sample_index++) {

                if(oxygen_bit_grid.at(sample_index).at(bit_column) != keep_bit) {
                    
                    is_found = true;
                    oxygen_bit_grid.erase(oxygen_bit_grid.begin() + sample_index);
                    break;
                }
            }
        }
    }

    for(unsigned int bit_column = 0; bit_column < bit_size; bit_column++) {
        
        unsigned int on_bit_count = 0;
        unsigned int off_bit_count = 0;

        if(carbon_bit_grid.size() == 1) break;
        for(unsigned int bit_row = 0; bit_row < carbon_bit_grid.size(); bit_row++) {

            if(carbon_bit_grid.at(bit_row).at(bit_column) == '1') on_bit_count++;
            else off_bit_count++;
        }
        
        char keep_bit = '0';
        if(on_bit_count < off_bit_count) keep_bit = '1';

        bool is_found = true;
        while(is_found) {

            is_found = false;
            for(unsigned int sample_index = 0; sample_index < carbon_bit_grid.size(); sample_index++) {

                if(carbon_bit_grid.at(sample_index).at(bit_column) != keep_bit) {
                    
                    is_found = true;
                    carbon_bit_grid.erase(carbon_bit_grid.begin() + sample_index);
                    break;
                }
            }
        }
    }

    read_file.close();
    
    unsigned int oxygen_rate = std::stoi(oxygen_bit_grid.at(0), 0, 2);
    unsigned int carbon_rate = std::stoi(carbon_bit_grid.at(0), 0, 2);

    std::string answer = std::to_string(oxygen_rate * carbon_rate);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}