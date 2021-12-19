#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> check_number_set;
    std::vector <std::vector <std::vector <std::string>>> bingo_board_data;
    
    std::vector <std::vector <std::string>> read_board(5);
    unsigned int read_row_index = 0;

    int line_number = -2;
    while(getline(read_file, read_text)) {

        if(line_number == -2) {

            std::stringstream ss(read_text);

            while(ss.good()) {

                std::string check_number;
                getline(ss, check_number, ',');
                check_number_set.push_back(check_number);
            }
        }
        else if(line_number >= 0 && (line_number + 1) % 6 == 0) {
            
            read_row_index = 0;
            bingo_board_data.push_back(read_board);
        }
        else if(line_number >= 0) {

            std::stringstream ss(read_text);
            
            std::vector <std::string> read_row;
            while(ss.good()) {

                std::string number;
                getline(ss, number, ' ');
                if(number.empty()) continue;
                read_row.push_back(number);
            }

            read_board.at(read_row_index) = read_row;

            read_row_index++;
        }

        line_number++;
    }
    bingo_board_data.push_back(read_board);

    unsigned int answer_sum = 0;
    unsigned int round = 5;
    bool bingo = false;

    while(!bingo) {

        for(unsigned int board_index = 0; board_index < bingo_board_data.size(); board_index++) {
            
            std::vector <std::vector <bool>> board_mark(5, std::vector <bool> (5, false));

            for(unsigned int number_index = 0; number_index < round; number_index++) {
                for(unsigned int row_index = 0; row_index < bingo_board_data.at(board_index).size(); row_index++) {
                    for(unsigned int column_index = 0; column_index < bingo_board_data.at(board_index).at(row_index).size(); column_index++) {

                        if(bingo_board_data.at(board_index).at(row_index).at(column_index) == check_number_set.at(number_index)) board_mark.at(row_index).at(column_index) = true;
                    }
                }
            }

            bool is_bingo = false;
            for(unsigned int check_row = 0; check_row < 5; check_row++) {
                bool is_bingo_row = true;
                for(unsigned int check_column = 0; check_column < 5; check_column++) {
                    if(!board_mark.at(check_row).at(check_column)) is_bingo_row = false;
                }
                if(is_bingo_row) is_bingo = true;
            }
            for(unsigned int check_column = 0; check_column < 5; check_column++) {
                bool is_bingo_column = true;
                for(unsigned int check_row = 0; check_row < 5; check_row++) {
                    if(!board_mark.at(check_row).at(check_column)) is_bingo_column = false;
                }
                if(is_bingo_column) is_bingo = true;
            }

            if(is_bingo) {

                unsigned int winner_number;
                std::stringstream ss(check_number_set.at(round - 1));
                ss >> winner_number;

                unsigned int un_marked_sum = 0;
                for(unsigned int row_index = 0; row_index < bingo_board_data.at(board_index).size(); row_index++) {
                    for(unsigned int column_index = 0; column_index < bingo_board_data.at(board_index).at(row_index).size(); column_index++) {

                        if(!board_mark.at(row_index).at(column_index)) {
                            
                            std::string read_string_item = bingo_board_data.at(board_index).at(row_index).at(column_index);  
                            int int_item;
                            std::stringstream ss(read_string_item);
                            ss >> int_item;
                            un_marked_sum += int_item;
                        }
                    }
                }
                answer_sum = un_marked_sum * winner_number;

                bingo = true;
                break;
            }
        }
        round++;
    }

    read_file.close();

    std::string answer = std::to_string(answer_sum);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> check_number_set;
    std::vector <std::vector <std::vector <std::string>>> bingo_board_data;
    
    std::vector <std::vector <std::string>> read_board(5);
    unsigned int read_row_index = 0;

    int line_number = -2;
    while(getline(read_file, read_text)) {

        if(line_number == -2) {

            std::stringstream ss(read_text);

            while(ss.good()) {

                std::string check_number;
                getline(ss, check_number, ',');
                check_number_set.push_back(check_number);
            }
        }
        else if(line_number >= 0 && (line_number + 1) % 6 == 0) {
            
            read_row_index = 0;
            bingo_board_data.push_back(read_board);
        }
        else if(line_number >= 0) {

            std::stringstream ss(read_text);
            
            std::vector <std::string> read_row;
            while(ss.good()) {

                std::string number;
                getline(ss, number, ' ');
                if(number.empty()) continue;
                read_row.push_back(number);
            }

            read_board.at(read_row_index) = read_row;

            read_row_index++;
        }

        line_number++;
    }
    bingo_board_data.push_back(read_board);

    unsigned int answer_sum = 0;
    unsigned int round = 5;
    bool last_bingo = false;

    while(bingo_board_data.size() != 0) {

        for(unsigned int board_index = 0; board_index < bingo_board_data.size(); board_index++) {
            
            std::vector <std::vector <bool>> board_mark(5, std::vector <bool> (5, false));

            for(unsigned int number_index = 0; number_index < round; number_index++) {
                for(unsigned int row_index = 0; row_index < bingo_board_data.at(board_index).size(); row_index++) {
                    for(unsigned int column_index = 0; column_index < bingo_board_data.at(board_index).at(row_index).size(); column_index++) {

                        if(bingo_board_data.at(board_index).at(row_index).at(column_index) == check_number_set.at(number_index)) board_mark.at(row_index).at(column_index) = true;
                    }
                }
            }

            bool is_bingo = false;
            for(unsigned int check_row = 0; check_row < 5; check_row++) {
                bool is_bingo_row = true;
                for(unsigned int check_column = 0; check_column < 5; check_column++) {
                    if(!board_mark.at(check_row).at(check_column)) is_bingo_row = false;
                }
                if(is_bingo_row) is_bingo = true;
            }
            for(unsigned int check_column = 0; check_column < 5; check_column++) {
                bool is_bingo_column = true;
                for(unsigned int check_row = 0; check_row < 5; check_row++) {
                    if(!board_mark.at(check_row).at(check_column)) is_bingo_column = false;
                }
                if(is_bingo_column) is_bingo = true;
            }

            if(is_bingo) {

                unsigned int winner_number;
                std::stringstream ss(check_number_set.at(round - 1));
                ss >> winner_number;

                unsigned int un_marked_sum = 0;
                for(unsigned int row_index = 0; row_index < bingo_board_data.at(board_index).size(); row_index++) {
                    for(unsigned int column_index = 0; column_index < bingo_board_data.at(board_index).at(row_index).size(); column_index++) {

                        if(!board_mark.at(row_index).at(column_index)) {
                            
                            std::string read_string_item = bingo_board_data.at(board_index).at(row_index).at(column_index);  
                            int int_item;
                            std::stringstream ss(read_string_item);
                            ss >> int_item;
                            un_marked_sum += int_item;
                        }
                    }
                }
                answer_sum = un_marked_sum * winner_number;
                
                bingo_board_data.erase(bingo_board_data.begin() + board_index);
            }
        }
        round++;
    }

    read_file.close();

    std::string answer = std::to_string(answer_sum);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}