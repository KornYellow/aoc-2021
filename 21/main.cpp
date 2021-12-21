#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>

unsigned int sum(unsigned int number) {

    return (number * 3) - 3;
}

void part1() {

    unsigned int player_1_pos = 10;
    unsigned int player_2_pos = 9;

    unsigned int player_1_score = 0;
    unsigned int player_2_score = 0;

    unsigned int dice = 0;
    bool is_player_1_turns = true;
    while(player_1_score < 1000 && player_2_score < 1000) {

        dice += 3;
        if(is_player_1_turns) {

            player_1_pos += sum(dice);
            player_1_pos--;
            player_1_pos %= 10;
            player_1_pos++;
            player_1_score += player_1_pos;
        }
        else {

            player_2_pos += sum(dice);
            player_2_pos--;
            player_2_pos %= 10;
            player_2_pos++;
            player_2_score += player_2_pos;
        }
        is_player_1_turns = !is_player_1_turns;
    }

    unsigned int losing_player = std::min(player_1_score, player_2_score);

    std::string answer = std::to_string(losing_player * dice);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

std::vector <unsigned long int> countWin(std::unordered_map <std::string, std::vector <unsigned long int>> *mark, unsigned int player_1, unsigned int player_2, unsigned int score_1, unsigned int score_2) {
    
    if(score_1 >= 21) return std::vector <unsigned long int> {1, 0};
    if(score_2 >= 21) return std::vector <unsigned long int> {0, 1};

    std::string key;
    key += std::to_string(player_1);    
    key += std::to_string(player_2);
    key += std::to_string(score_1);
    key += std::to_string(score_2);
    if(mark->find(key) != mark->end()) return mark->at(key);
    
    std::vector <unsigned long int> answer = {0, 0};

    for(int dice_1 = 1; dice_1 <= 3; dice_1++) {
        for(int dice_2 = 1; dice_2 <= 3; dice_2++) {
            for(int dice_3 = 1; dice_3 <= 3; dice_3++) {

                unsigned int new_player_1 = (player_1 + dice_1 + dice_2 + dice_3) % 10;
                unsigned int new_score_1 = score_1 + new_player_1 + 1;

                std::vector <unsigned long int> wins = countWin(mark, player_2, new_player_1, score_2, new_score_1);
                answer.at(0) += wins.at(1);
                answer.at(1) += wins.at(0);
            }
        }
    }
    if(mark->find(key) == mark->end()) {
        mark->insert(std::make_pair(key, answer));
    }
    mark->at(key) = answer;

    return answer;
}

void part2() {

    unsigned int player_1_pos = 10 - 1;
    unsigned int player_2_pos = 9 - 1;

    std::unordered_map <std::string, std::vector <unsigned long int>> mark;
    std::vector <unsigned long int> answer_count = countWin(&mark, player_1_pos, player_2_pos, 0, 0);
    unsigned long int count = std::max(answer_count.at(0), answer_count.at(1));

    std::string answer = std::to_string(count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}