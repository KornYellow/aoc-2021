#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

struct Node {
    Node* left;
    Node* right;
    unsigned int value;
    unsigned int type;
    ~Node() {
        if(this->left != nullptr) delete this->left;
        if(this->right != nullptr) delete this->right;
    }
    std::string print() {
        if(this->value != 99) return std::to_string(this->value);
        return "[" + this->left->print() + "," + this->right->print() + "]";
    }
    void reduce() {

        std::string last_print = "";
        int i = 0;
        while(i <= 2) {
            i ++;
            //std::cout << this->print() << std::endl;
            //last_print = this->print();
            this->left->explode(1);
            this->right->explode(1);
            this->left->split();
            this->right->split();
        }
    }
    void split() {

        if(this->value == 99) {
            this->left->split();
            this->right->split();
            return;
        }
        if(this->value <= 9) return;

        unsigned int old_value = this->value;
        this->left = new Node();
        this->right = new Node();
        this->left->value = this->value / 2;
        this->right->value = (this->value / 2) + 1;
        this->value = 99;
    }
    int explode(unsigned int nested_times) {

        if(this->left == nullptr || this->right == nullptr) return -1;
        
        int is_left_explode = -1, is_right_explode = -1;
        if(nested_times < 4) {
            is_left_explode = this->left->explode(nested_times + 1);
            is_right_explode = this->right->explode(nested_times + 1);
        }
        else return 0;

        if(is_left_explode >= 0) {
            
            if(is_left_explode == 0) {
                
                unsigned int left_value = this->left->left->value;
                unsigned int right_value = this->left->right->value;
                this->left->left = nullptr;
                this->left->right = nullptr;
                this->left->value = 0;
                this->right->value += right_value;
                return left_value;
            }
            else this->right->value += is_left_explode;
            return -1;
        }
        if(is_right_explode >= 0) {
            
            std::cout << is_right_explode << ":" << this->print() << std::endl;
            if(is_right_explode == 0) {
                
                unsigned int left_value = this->right->left->value;
                unsigned int right_value = this->right->right->value;
                this->right->left = nullptr;
                this->right->right = nullptr;
                this->right->value = 0;
                this->left->value += left_value;
                return right_value;
            }
            else this->left->value += is_right_explode;
            std::cout << is_right_explode << ":" << this->print() << std::endl;
            return -1;
        }

        return -1;
    }
};

Node* parse(std::string* read_text) {
    
    Node* node = new Node();
    node->value = 99;
    node->type = 0;

    if(!read_text->empty()) {
        if(read_text->at(0) == '[') {
            read_text->erase(read_text->begin());
            node->left = parse(read_text);
            node->left->type = 1;
        }
    }
    if(!read_text->empty()) {
        if(read_text->at(0) == ',') {
            read_text->erase(read_text->begin());
            node->right = parse(read_text);
            node->right->type = 1;
        }
    }
    if(!read_text->empty()) {
        if(read_text->at(0) != '[' && read_text->at(0) != ']' && read_text->at(0) != ',') {  
            node->value = read_text->at(0) - '0';
            read_text->erase(read_text->begin());
            while(!read_text->empty() && read_text->at(0) == ']') read_text->erase(read_text->begin());
            return node;
        }
    }
    return node;
}

Node* combineNode(Node* left_node, Node* right_node) {

    Node* node = new Node();
    node->value = 99;

    node->left = left_node;
    node->right = right_node;
    return node;
}   

void part1() {

    std::ifstream read_file("sample.txt");
    std::string read_text;

    std::vector <Node*> homeworks;
    while(getline(read_file, read_text)) {

        std::string text = read_text;
        Node* root = parse(&text);
        homeworks.push_back(root);
    }
    read_file.close();

    Node* new_node = combineNode(homeworks.at(0), homeworks.at(1));
    new_node->reduce();
    std::cout << new_node->print() << std::endl;

    // Node* old_node = homeworks.at(0);
    // for(unsigned int i = 1; i < homeworks.size(); i++) {
    
    //     Node* new_node = combineNode(old_node, homeworks.at(i));
    //     new_node->reduce();
    //     std::cout << new_node->print() << std::endl;
    //     old_node = new_node;
    // }

    std::string answer = "none";
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("sample.txt");
    std::string read_text;

    while(getline(read_file, read_text)) {

    }

    read_file.close();

    std::string answer = "none";
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}