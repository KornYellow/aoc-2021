#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

std::vector <std::string> seaCucumber(std::vector <std::string> grid) {

    std::vector <std::string> next_grid = grid;
    for(unsigned int row_index = 0; row_index < grid.size(); row_index++) {
        for(unsigned int cell_index = 0; cell_index < grid.at(row_index).size(); cell_index++) {   

            if(grid.at(row_index).at(cell_index) == '>') {

                unsigned int next_cell_index = cell_index;
                if(next_cell_index + 1 > grid.at(row_index).size() - 1) next_cell_index = 0;
                else next_cell_index++;
                if(grid.at(row_index).at(next_cell_index) != '.') next_cell_index = cell_index;

                next_grid.at(row_index).at(cell_index) = '.';
                next_grid.at(row_index).at(next_cell_index) = '>';
            }
        }   
    }
    grid = next_grid;

    for(unsigned int row_index = 0; row_index < grid.size(); row_index++) {
        for(unsigned int cell_index = 0; cell_index < grid.at(row_index).size(); cell_index++) {   

            if(grid.at(row_index).at(cell_index) == 'v') {
                
                unsigned int next_row_index = row_index;
                if(next_row_index + 1 > grid.size() - 1) next_row_index = 0;
                else next_row_index++;
                if(grid.at(next_row_index).at(cell_index) != '.') next_row_index = row_index;

                next_grid.at(row_index).at(cell_index) = '.';
                next_grid.at(next_row_index).at(cell_index) = 'v';
            }
        }   
    }
    grid = next_grid;
    return grid;
}

void part1() {

    std::ifstream read_file("sample.txt");
    std::string read_text;

    std::vector <std::string> grid;
    std::vector <std::string> next_grid;

    while(getline(read_file, read_text)) grid.push_back(read_text);

    unsigned int step = 0;
    std::vector <std::string> last_grid = grid;
    while(true) {

        last_grid = grid;
        grid = seaCucumber(grid);
        step++;
        if(last_grid == grid) break;
    }     
    
    read_file.close();

    std::string answer = std::to_string(step);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("sample.txt");
    std::string read_text;

    while(getline(read_file, read_text)) {

    }

    read_file.close();

    std::string answer = "GGs!";
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}