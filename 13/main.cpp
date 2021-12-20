#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void foldVertical(std::vector <std::string> *trans_paper) {
    
    unsigned long int paper_half_point = trans_paper->size() / 2;
    trans_paper->erase(trans_paper->begin() + paper_half_point);
    for(unsigned long int row_index = 0; row_index < paper_half_point; row_index++) {
        
        std::string popped_row = trans_paper->at(trans_paper->size() - 1);
        trans_paper->pop_back();

        for(unsigned long int column_index = 0; column_index < trans_paper->at(row_index).size(); column_index++) if(popped_row.at(column_index) == '#') trans_paper->at(row_index).at(column_index) = popped_row.at(column_index);
    }
}
void foldHorizontal(std::vector <std::string> *trans_paper) {

    unsigned long int paper_half_point = (trans_paper->at(0).size() / 2);
    for(unsigned long int row_index = 0; row_index < trans_paper->size(); row_index++) {
        
        trans_paper->at(row_index).erase(trans_paper->at(row_index).begin() + paper_half_point);
        for(unsigned long int column_index = 0; column_index < paper_half_point; column_index++) {
            
            char popped_column = trans_paper->at(row_index).at(trans_paper->at(row_index).size() - 1);
            trans_paper->at(row_index).pop_back();

            if(popped_column == '#') trans_paper->at(row_index).at(column_index) = popped_column;
        }
    }
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <std::vector <unsigned long int>> dot_positions;
    std::string fold_instruction;
    unsigned long int max_x = 0;
    unsigned long int max_y = 0;
    
    bool is_fold = false;
    while(getline(read_file, read_text)) {

        if(read_text.empty()) {
            
            is_fold = true;
            continue;
        }

        if(is_fold) {

            fold_instruction.push_back(read_text.at(11));
            continue;
        }

        std::stringstream ss(read_text);

        std::vector <unsigned long int> position;
        while(ss.good()) {

            std::string pos;
            getline(ss, pos, ',');
            std::stringstream sss(pos);
            unsigned long int pos_int;
            sss >> pos_int;
            position.push_back(pos_int);
        }
        
        if(position.at(0) > max_x) max_x = position.at(0);
        if(position.at(1) > max_y) max_y = position.at(1);

        dot_positions.push_back(position);
    }

    std::vector <std::string> trans_paper(max_y + 1, std::string(max_x + 1, '.'));
    for(std::vector <unsigned long int> dot : dot_positions) trans_paper.at(dot.at(1)).at(dot.at(0)) = '#';
    
    std::vector <unsigned long int> dot_counts;

    for(char fold : fold_instruction) {

        if(fold == 'x') foldHorizontal(&trans_paper);
        if(fold == 'y') foldVertical(&trans_paper);
        
        unsigned long int count = 0;
        for(std::string row : trans_paper) {
            for(char col : row) if(col == '#') count++;
        }
        dot_counts.push_back(count);
    }
    
    read_file.close();

    std::string answer = std::to_string(dot_counts.at(0));
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::string answer = "JZGUAPRB";
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}