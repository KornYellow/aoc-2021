#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

struct Position {
    unsigned int x;
    unsigned int y;
    Position(unsigned int x, unsigned int y) {

        this->x = x;
        this->y = y;
    }
};

int sign(int number) {

    if(number > 0) return 1;
    if(number < 0) return -1;
    return 0;
}
int abs(int number) {

    if(number < 0) return -number;
    return number;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <Position> positions_1;
    std::vector <Position> positions_2;

    unsigned int max_x = 0;
    unsigned int max_y = 0;

    while(getline(read_file, read_text)) {

        std::vector <std::string> read_chunks;

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_chunk;
            getline(ss, read_chunk, ' ');
            read_chunks.push_back(read_chunk);
        }

        std::string pos_1 = read_chunks.at(0);
        std::string pos_2 = read_chunks.at(2);

        std::string x_1_str = pos_1.substr(0, pos_1.find(','));
        std::string y_1_str = pos_1.substr(pos_1.find(',') + 1, pos_1.size());
        std::string x_2_str = pos_2.substr(0, pos_2.find(','));
        std::string y_2_str = pos_2.substr(pos_2.find(',') + 1, pos_2.size());

        unsigned int x_1;
        unsigned int y_1;
        unsigned int x_2;
        unsigned int y_2;

        std::stringstream ss_x_1(x_1_str);
        std::stringstream ss_y_1(y_1_str);
        std::stringstream ss_x_2(x_2_str);
        std::stringstream ss_y_2(y_2_str);

        ss_x_1 >> x_1;
        ss_y_1 >> y_1;
        ss_x_2 >> x_2;
        ss_y_2 >> y_2;

        Position position_1(x_1, y_1);
        Position position_2(x_2, y_2);

        if(x_1 > max_x) max_x = x_1;
        if(x_2 > max_x) max_x = x_2;
        if(y_1 > max_y) max_y = y_1;
        if(y_2 > max_y) max_y = y_2;

        positions_1.push_back(position_1);
        positions_2.push_back(position_2);
    }
    max_x++;
    max_y++;

    std::vector <std::vector <int>> grid(max_y, std::vector <int> (max_x, 0)); 

    for(unsigned int index = 0; index < positions_1.size(); index++) {

        unsigned int x_1 = positions_1.at(index).x;
        unsigned int y_1 = positions_1.at(index).y;
        unsigned int x_2 = positions_2.at(index).x;
        unsigned int y_2 = positions_2.at(index).y;

        if(x_1 != x_2 && y_1 != y_2) continue;

        if(x_1 == x_2) {

            grid.at(y_1).at(x_1)++;
            while(y_1 != y_2) {

                y_1 += sign(y_2 - y_1);
                grid.at(y_1).at(x_1)++;
            }
        }
        else if(y_1 == y_2) {

            grid.at(y_1).at(x_1)++;
            while(x_1 != x_2) {

                x_1 += sign(x_2 - x_1);
                grid.at(y_1).at(x_1)++;
            }
        }
        else {

            grid.at(y_1).at(x_1)++;
        }
    }

    unsigned int score = 0;
    for(unsigned int y = 0; y < max_y; y++) {
        for(unsigned int x = 0; x < max_x; x++) {

            if(grid.at(y).at(x) > 1) score++;
        }
    }

    read_file.close();

    std::string answer = std::to_string(score);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <Position> positions_1;
    std::vector <Position> positions_2;

    unsigned int max_x = 0;
    unsigned int max_y = 0;

    while(getline(read_file, read_text)) {

        std::vector <std::string> read_chunks;

        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string read_chunk;
            getline(ss, read_chunk, ' ');
            read_chunks.push_back(read_chunk);
        }

        std::string pos_1 = read_chunks.at(0);
        std::string pos_2 = read_chunks.at(2);

        std::string x_1_str = pos_1.substr(0, pos_1.find(','));
        std::string y_1_str = pos_1.substr(pos_1.find(',') + 1, pos_1.size());
        std::string x_2_str = pos_2.substr(0, pos_2.find(','));
        std::string y_2_str = pos_2.substr(pos_2.find(',') + 1, pos_2.size());

        unsigned int x_1;
        unsigned int y_1;
        unsigned int x_2;
        unsigned int y_2;

        std::stringstream ss_x_1(x_1_str);
        std::stringstream ss_y_1(y_1_str);
        std::stringstream ss_x_2(x_2_str);
        std::stringstream ss_y_2(y_2_str);

        ss_x_1 >> x_1;
        ss_y_1 >> y_1;
        ss_x_2 >> x_2;
        ss_y_2 >> y_2;

        Position position_1(x_1, y_1);
        Position position_2(x_2, y_2);

        if(x_1 > max_x) max_x = x_1;
        if(x_2 > max_x) max_x = x_2;
        if(y_1 > max_y) max_y = y_1;
        if(y_2 > max_y) max_y = y_2;

        positions_1.push_back(position_1);
        positions_2.push_back(position_2);
    }
    max_x++;
    max_y++;

    std::vector <std::vector <int>> grid(max_y, std::vector <int> (max_x, 0)); 

    for(unsigned int index = 0; index < positions_1.size(); index++) {

        unsigned int x_1 = positions_1.at(index).x;
        unsigned int y_1 = positions_1.at(index).y;
        unsigned int x_2 = positions_2.at(index).x;
        unsigned int y_2 = positions_2.at(index).y;

        if(x_1 == x_2) {

            grid.at(y_1).at(x_1)++;
            while(y_1 != y_2) {

                y_1 += sign(y_2 - y_1);
                grid.at(y_1).at(x_1)++;
            }
        }
        else if(y_1 == y_2) {

            grid.at(y_1).at(x_1)++;
            while(x_1 != x_2) {

                x_1 += sign(x_2 - x_1);
                grid.at(y_1).at(x_1)++;
            }
        }
        else if(abs(x_2 - x_1) == abs(y_2 - y_1)) {

            grid.at(y_1).at(x_1)++;
            while(x_1 != x_2 && y_1 != y_2) {

                x_1 += sign(x_2 - x_1);
                y_1 += sign(y_2 - y_1);
                grid.at(y_1).at(x_1)++;
            }
        }
        else if(x_1 == x_2 && y_1 == y_2) {

            grid.at(y_1).at(x_1)++;
        }
    }

    unsigned int score = 0;
    for(unsigned int y = 0; y < max_y; y++) {
        for(unsigned int x = 0; x < max_x; x++) {

            if(grid.at(y).at(x) > 1) score++;
        }
    }

    read_file.close();

    std::string answer = std::to_string(score);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}