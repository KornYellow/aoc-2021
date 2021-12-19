#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

void sortString(std::string &str) {
   
   sort(str.begin(), str.end());
}

std::string getUnmatchString(std::string str_1, std::string str_2) {
    
    std::string unmatch_str;
    for(char substr_1 : str_1) {

        bool is_match = false;
        for(char substr_2 : str_2) if(substr_1 == substr_2) is_match = true;
        if(!is_match) unmatch_str.push_back(substr_1);
    }
    return unmatch_str;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    unsigned long int answer_count = 0;

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);

        unsigned int pointer = 0;
        while(ss.good()) {

            std::string read_chunk;
            getline(ss, read_chunk, ' ');

            if(pointer < 11) {
                
                pointer++;
                continue;
            } 
            if(read_chunk.size() == 2 || read_chunk.size() == 4 || read_chunk.size() == 3 || read_chunk.size() == 7) answer_count++;
        }
    }

    read_file.close();

    std::string answer = std::to_string(answer_count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::vector <std::vector <std::string>>> problems;

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);

        std::vector <std::string> left;
        std::vector <std::string> right;

        unsigned int pointer = 0;
        while(ss.good()) {

            std::string read_chunk;
            getline(ss, read_chunk, ' ');
            sortString(read_chunk);

            if(pointer < 10) left.push_back(read_chunk);
            else if(pointer == 10) {
                
                pointer++;
                continue;
            }
            else right.push_back(read_chunk);
            pointer++;
        }

        std::vector <std::vector <std::string>> problem;
        problem.push_back(left);
        problem.push_back(right);

        problems.push_back(problem);
    }

    unsigned long int sum = 0;
    for(std::vector <std::vector <std::string>> problem : problems) {
        
        std::string digit_map(7, '-');
        std::vector <std::string> number_map(10, "-");

        std::vector <std::string> left = problem.at(0);
        std::vector <std::string> right = problem.at(1);

        std::string unmatch_str;
        std::vector <std::string> number_with_5_digit;
        std::vector <std::string> number_with_6_digit;
        for(std::string number : left) {
            if(number.size() == 2) number_map.at(1) = number;
            else if(number.size() == 3) number_map.at(7) = number;
            else if(number.size() == 4) number_map.at(4) = number;
            else if(number.size() == 7) number_map.at(8) = number;
            else if(number.size() == 5) number_with_5_digit.push_back(number);
            else if(number.size() == 6) number_with_6_digit.push_back(number);
        }

        digit_map.at(0) = getUnmatchString(number_map.at(7), number_map.at(1)).at(0);

        for(unsigned long int number_index = 0; number_index < number_with_6_digit.size(); number_index++) {
            
            std::string number = number_with_6_digit.at(number_index);
            std::string unmatch_str = getUnmatchString(number, number_map.at(4) + digit_map.at(0));
            if(unmatch_str.size() == 1) {
                number_map.at(9) = number;
                digit_map.at(6) = unmatch_str.at(0);
                number_with_6_digit.erase(number_with_6_digit.begin() + number_index);
                break;
            }
        }

        for(unsigned long int number_index = 0; number_index < number_with_5_digit.size(); number_index++) {
            
            std::string number = number_with_5_digit.at(number_index);
            std::string unmatch_str = getUnmatchString(number, number_map.at(1) + digit_map.at(0) + digit_map.at(6));
            if(unmatch_str.size() == 1) {
                number_map.at(3) = number;
                digit_map.at(3) = unmatch_str.at(0);
                number_with_5_digit.erase(number_with_5_digit.begin() + number_index);
                break;
            }
        }

        for(unsigned long int number_index = 0; number_index < number_with_5_digit.size(); number_index++) {
            
            std::string number = number_with_5_digit.at(number_index);
            std::string unmatch_str = getUnmatchString(number, number_map.at(9));
            if(unmatch_str.size() == 1) {
                number_map.at(2) = number;
                digit_map.at(4) = unmatch_str.at(0);
                number_with_5_digit.erase(number_with_5_digit.begin() + number_index);
                break;
            }
        }

        for(unsigned long int number_index = 0; number_index < number_with_6_digit.size(); number_index++) {
            
            std::string number = number_with_6_digit.at(number_index);
            std::string unmatch_str = getUnmatchString(number_map.at(8), number + digit_map.at(3));
            if(unmatch_str.size() == 0) {
                number_map.at(0) = number;
                number_with_6_digit.erase(number_with_6_digit.begin() + number_index);
                break;
            }
        }

        unmatch_str = getUnmatchString(number_map.at(8), number_with_6_digit.at(0));
        number_map.at(6) = number_with_6_digit.at(0);
        digit_map.at(2) = unmatch_str.at(0);

        number_map.at(5) = number_with_5_digit.at(0);

        unmatch_str = getUnmatchString(number_map.at(8), number_map.at(3) + digit_map.at(4));
        digit_map.at(1) = unmatch_str.at(0);

        unmatch_str = getUnmatchString(number_map.at(8), number_map.at(2) + digit_map.at(1));
        digit_map.at(5) = unmatch_str.at(0);

        std::string answer_problem;
        for(std::string right_number : right) { 
            for(unsigned int number_index = 0; number_index < number_map.size(); number_index++) {
                if(number_map.at(number_index) == right_number) {
                    answer_problem.push_back(number_index + '0');
                }
            }
        }

        std::stringstream ss(answer_problem);
        unsigned long int answer;
        ss >> answer;
        sum += answer;
    }

    read_file.close();

    std::string answer = std::to_string(sum);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}