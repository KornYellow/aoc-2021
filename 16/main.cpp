#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

std::string hexToBin(std::string hex)
{
    std::string bin;
    for(char c : hex) {
        switch(c) {
            case '0': bin += "0000"; break;
            case '1': bin += "0001"; break;
            case '2': bin += "0010"; break;
            case '3': bin += "0011"; break;
            case '4': bin += "0100"; break;
            case '5': bin += "0101"; break;
            case '6': bin += "0110"; break;
            case '7': bin += "0111"; break;
            case '8': bin += "1000"; break;
            case '9': bin += "1001"; break;
            case 'A': case 'a':  bin += "1010"; break;
            case 'B': case 'b':  bin += "1011"; break;
            case 'C': case 'c':  bin += "1100"; break;
            case 'D': case 'd':  bin += "1101"; break;
            case 'E': case 'e':  bin += "1110"; break;
            case 'F': case 'f':  bin += "1111"; break;
        }
    }
    return bin;
}

std::vector <unsigned long int> getPacketVersionSum(std::string binary) {

    unsigned long int version_count = 0;

    unsigned long int pointer = 0;
    
    unsigned long int version_number = std::stol(binary.substr(pointer, 3), 0, 2);
    pointer += 3;

    version_count += version_number;

    unsigned long int type_id = std::stol(binary.substr(pointer, 3), 0, 2);
    pointer += 3;
    
    if(type_id == 4) {
        while(binary[pointer] != '0') pointer += 5;
        pointer += 5;
        return {version_count, pointer};
    }

    char length_type_id = binary[pointer];
    pointer++;

    if(length_type_id == '0') {
        
        unsigned long int sub_length = std::stol(binary.substr(pointer, 15), 0, 2);
        pointer += 15;

        unsigned long int max_length = pointer + sub_length;
        while(pointer < max_length) {
            std::vector <unsigned long int> output = getPacketVersionSum(binary.substr(pointer, binary.size() - pointer));
            version_count += output[0];
            pointer += output[1];
        }
    }
    if(length_type_id == '1') {

        unsigned long int sub_count = std::stol(binary.substr(pointer, 11), 0, 2);
        pointer += 11;
        for(unsigned long int i = 0; i < sub_count; i++) {
            std::vector <unsigned long int> output = getPacketVersionSum(binary.substr(pointer, binary.size() - pointer));
            version_count += output[0];
            pointer += output[1];
        }
    }
    return {version_count, pointer};
}

std::vector <unsigned long int> getPacketSum(std::string binary) {

    std::vector <unsigned long int> packet_values;

    unsigned long int pointer = 0;
    
    unsigned long int version_number = std::stol(binary.substr(pointer, 3), 0, 2);
    pointer += 3;

    unsigned long int type_id = std::stol(binary.substr(pointer, 3), 0, 2);
    pointer += 3;
    
    if(type_id == 4) {

        std::string literal_number_bin;
        while(binary[pointer - 5] != '0' || pointer == 6) {
            pointer++;
            literal_number_bin += binary.substr(pointer, 4);
            pointer+=4;
        }
        return {(unsigned long int)std::stol(literal_number_bin, 0, 2), pointer};
    }

    char length_type_id = binary[pointer];
    pointer++;

    if(length_type_id == '0') {
        
        unsigned long int sub_length = std::stol(binary.substr(pointer, 15), 0, 2);
        pointer += 15;

        unsigned long int max_length = pointer + sub_length;
        while(pointer != max_length) {
            std::vector <unsigned long int> output = getPacketSum(binary.substr(pointer, binary.size() - pointer));
            packet_values.push_back(output[0]);
            pointer += output[1];
        }
    }
    if(length_type_id == '1') {

        unsigned long int sub_count = std::stol(binary.substr(pointer, 11), 0, 2);
        pointer += 11;
        for(unsigned long int i = 0; i < sub_count; i++) {
            std::vector <unsigned long int> output = getPacketSum(binary.substr(pointer, binary.size() - pointer));
            packet_values.push_back(output[0]);
            pointer += output[1];
        }
    }

    unsigned long int packet_sum = 0;
    switch(type_id) {
        case 1:
            packet_sum = 1;
            for(unsigned long int value : packet_values) packet_sum *= value;
            return {packet_sum, pointer};

        case 2:
            std::sort(packet_values.begin(), packet_values.end());
            return {packet_values[0], pointer};

        case 3:
            std::sort(packet_values.begin(), packet_values.end());
            return {packet_values[packet_values.size() - 1], pointer};

        case 5:
            return {packet_values[0] > packet_values[1], pointer};
        
        case 6:
            return {packet_values[0] < packet_values[1], pointer};

        case 7:
            return {packet_values[0] == packet_values[1], pointer};
    }
    for(unsigned long int value : packet_values) packet_sum += value;
    return {packet_sum, pointer};
}

void part1() {
 
    std::ifstream read_file("input.txt");
    std::string read_text;
    getline(read_file, read_text);
    std::string binary = hexToBin(read_text);
    read_file.close();

    std::string answer = std::to_string(getPacketVersionSum(binary)[0]);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;
    getline(read_file, read_text);
    std::string binary = hexToBin(read_text);
    read_file.close();

    std::string answer = std::to_string(getPacketSum(binary)[0]);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}