#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string polymer;
    std::vector <std::string> pairs;

    bool init = false;
    while(getline(read_file, read_text)) {

        if(read_text.empty()) continue;

        if(init) {

            std::string pair;
            pair.push_back(read_text.at(0));
            pair.push_back(read_text.at(1));
            pair.push_back(read_text.at(6));

            pairs.push_back(pair);
        } 
        else { 
            
            polymer = read_text;
            init = true;
        }
    }

    unsigned long int max_step = 10;
    for(unsigned long int step = 0; step < max_step; step++) {

        for(unsigned long int poly_index = 0; poly_index < polymer.size() - 1; poly_index++) {
            
            for(std::string pair : pairs) {
                if(polymer.substr(poly_index, 2) == pair.substr(0, 2)) {
                    polymer.insert(polymer.begin() + poly_index + 1, pair.at(2));
                    poly_index++;
                    break;
                } 
            }
        }
    }

    read_file.close();

    std::vector <unsigned long int> answer_set('Z', 0);
    for(char poly : polymer) answer_set.at(poly)++;
    sort(answer_set.begin(), answer_set.end());
    while(answer_set.at(0) == 0) answer_set.erase(answer_set.begin());

    std::string answer = std::to_string(answer_set.at(answer_set.size() - 1) - answer_set.at(0));
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::string> pairs;

    std::string poly_template;

    bool init = false;
    while(getline(read_file, read_text)) {

        if(read_text.empty()) continue;

        if(init) {

            std::string pair;
            pair.push_back(read_text.at(0));
            pair.push_back(read_text.at(1));
            pair.push_back(read_text.at(6));

            pairs.push_back(pair);
        } 
        else { 
            
            poly_template = read_text;
            init = true;
        }
    }

    std::vector <unsigned long int> polymer_pairs(pairs.size(), 0);

    for(unsigned long int poly = 0; poly < poly_template.size() - 1; poly++) {
        for(unsigned long int pair_index = 0; pair_index < pairs.size(); pair_index++) {
            if(poly_template.substr(poly, 2) == pairs.at(pair_index).substr(0, 2)) polymer_pairs.at(pair_index) ++;
        }
    }

    unsigned long int max_step = 40;
    for(unsigned long int step = 0; step < max_step; step++) {

        std::vector <unsigned long int> new_polymer_pairs(pairs.size(), 0);
        
        for(unsigned long int poly = 0; poly < new_polymer_pairs.size(); poly++) {

            unsigned long int old_count = polymer_pairs.at(poly);
            if(old_count == 0) continue;

            std::string first_pair;
            first_pair.push_back(pairs.at(poly).at(0));
            first_pair.push_back(pairs.at(poly).at(2));
            std::string second_pair;
            second_pair.push_back(pairs.at(poly).at(2));
            second_pair.push_back(pairs.at(poly).at(1)); 

            for(unsigned long int pair_index = 0; pair_index < pairs.size(); pair_index++) {
                if(first_pair == pairs.at(pair_index).substr(0, 2)) new_polymer_pairs.at(pair_index) += old_count;
                if(second_pair == pairs.at(pair_index).substr(0, 2)) new_polymer_pairs.at(pair_index) += old_count;
            }
        }

        polymer_pairs = new_polymer_pairs;
    }

    std::vector <unsigned long int> answer_set('Z', 0);
    
    for(unsigned long int pair_index = 0; pair_index < pairs.size(); pair_index++) {
        answer_set.at(pairs.at(pair_index).at(0)) += polymer_pairs.at(pair_index);
        answer_set.at(pairs.at(pair_index).at(1)) += polymer_pairs.at(pair_index);
    }  
    
    sort(answer_set.begin(), answer_set.end());
    while(answer_set.at(0) == 0) answer_set.erase(answer_set.begin());

    for(unsigned long int index = 0; index < answer_set.size(); index++) answer_set.at(index) = ceil((double)answer_set.at(index) / 2);

    std::string answer = std::to_string(answer_set.at(answer_set.size() - 1) - answer_set.at(0));
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}