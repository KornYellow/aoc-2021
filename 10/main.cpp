#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

short braceCheck(char brace) {
    std::string open_brace = "([{<";
    for(unsigned short i = 0; i < 4; i++) {
        if(open_brace.at(i) == brace) return i;
    }  
    return -1;
}
short closeBraceCheck(char brace) {
    std::string open_brace = ")]}>";
    for(unsigned short i = 0; i < 4; i++) {
        if(open_brace.at(i) == brace) return i;
    }  
    return -1;
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string open_braces = "([{<";
    std::string close_braces = ")]}>";
    std::vector <short> braces_queue;

    std::vector <short> scores = {3, 57, 1197, 25137};
    std::vector <std::string> braces_set;

    unsigned long int sum = 0;

    while(getline(read_file, read_text)) {

        bool is_corrupted = false;
        for(char read_char : read_text) {

            if(braceCheck(read_char) != -1) braces_queue.push_back(braceCheck(read_char));
            else if(close_braces.at(braces_queue.at(braces_queue.size() - 1)) == read_char) {
                
                braces_queue.erase(braces_queue.end() - 1);
            }
            else {

                is_corrupted = true;
                sum += scores.at(closeBraceCheck(read_char));
                break;
            }
        }
        if(is_corrupted) continue;
        braces_queue.clear();
    }

    read_file.close();

    std::string answer = std::to_string(sum);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string open_braces = "([{<";
    std::string close_braces = ")]}>";
    std::vector <short> braces_queue;

    std::vector <unsigned long int> sum_set;

    while(getline(read_file, read_text)) {

        bool is_corrupted = false;
        for(char read_char : read_text) {

            if(braceCheck(read_char) != -1) braces_queue.push_back(braceCheck(read_char));
            else if(close_braces.at(braces_queue.at(braces_queue.size() - 1)) == read_char) {
                
                braces_queue.erase(braces_queue.end() - 1);
            }
            else {
                
                braces_queue.clear();
                is_corrupted = true;
                break;
            }
        }
        if(is_corrupted) continue;

        unsigned long int sum = 0;
        while(!braces_queue.empty()) {

            sum *= 5;   
            sum += braces_queue.at(braces_queue.size() - 1) + 1;
            braces_queue.erase(braces_queue.end() - 1);
        }
        sum_set.push_back(sum);
    }
    
    sort(sum_set.begin(), sum_set.end());

    read_file.close();

    std::string answer = std::to_string(sum_set.at(sum_set.size() / 2));
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}
