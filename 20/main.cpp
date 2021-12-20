#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void imgReserve(std::vector <std::string> *img, unsigned int times) {

    for(unsigned long int i = 0; i < img->size(); i++) {

        for(unsigned int n = 0; n < times; n++) img->at(i).insert(img->at(i).begin(), '.');
        for(unsigned int n = 0; n < times; n++) img->at(i).push_back('.');
    }
    for(unsigned int n = 0; n < times; n++) img->insert(img->begin(), std::string(img->at(0).size(), '.'));
    for(unsigned int n = 0; n < times; n++) img->push_back(std::string(img->at(0).size(), '.'));
}  

void imgEnchance(std::vector <std::string> *img, std::string iea) {

    std::vector <std::string> new_img;
    for(unsigned long int y = 0; y < img->size() - 2; y++) {

        std::string new_row;
        for(unsigned long int x = 0; x < img->at(y).size() - 2; x++) {

            std::string encoding = "";
            for(unsigned int i = 0; i < 3; i++) encoding += img->at(y + i).substr(x, 3); 
            for(unsigned int i = 0; i < encoding.size(); i++) if(encoding.at(i) == '.') encoding.at(i) = '0'; else encoding.at(i) = '1';
            
            unsigned int dec = std::stoi(encoding, 0, 2);
            new_row.push_back(iea.at(dec));
        }
        new_img.push_back(new_row);
    }
    *img = new_img;
} 

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string iea; 
    bool is_input = false;

    std::vector <std::string> img;

    while(getline(read_file, read_text)) {

        if(read_text.empty()) continue;

        if(is_input) img.push_back(read_text);
        else {

            iea = read_text;
            is_input = true;
        }
    }

    unsigned int times = 2;

    imgReserve(&img, 4);
    for(unsigned int i = 0; i < times; i++) {

        imgEnchance(&img, iea);
    } 

    unsigned count = 0;
    for(std::string row : img) {
        for(char ch : row) if(ch == '#') count++;
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::string iea; 
    bool is_input = false;

    std::vector <std::string> img;

    while(getline(read_file, read_text)) {

        if(read_text.empty()) continue;

        if(is_input) img.push_back(read_text);
        else {

            iea = read_text;
            is_input = true;
        }
    }

    unsigned int times = 50;

    imgReserve(&img, 100);
    for(unsigned int i = 0; i < times; i++) {

        imgEnchance(&img, iea);
    } 

    unsigned count = 0;
    for(std::string row : img) {
        for(char ch : row) if(ch == '#') count++;
        //std::cout << row << std::endl;
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}