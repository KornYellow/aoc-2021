#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>

struct Graph {

    std::list <std::string> path_traverse;

    std::unordered_map <std::string, bool> is_visited;
    std::unordered_map <std::string, std::vector <std::string>> adjacent;
    void addEdge(std::string root, std::string child) {
        
        if(this->is_visited.find(root) == 0) this->is_visited.insert(std::make_pair(root, false));
        if(this->is_visited.find(child) == 0) this->is_visited.insert(std::make_pair(child, false));

        if(this->adjacent.find(root) == 0) {
            std::vector <std::string> empty_vector;
            this->adjacent.insert(std::make_pair(root, empty_vector));
        }
        this->adjacent.at(root).push_back(child);

        if(this->adjacent.find(child) == 0) {
            std::vector <std::string> empty_vector;
            this->adjacent.insert(std::make_pair(child, empty_vector));
        }
        this->adjacent.at(child).push_back(root);
    }
    std::vector <std::string> getPair(std::string root) {

        return this->adjacent.at(root);
    }
    unsigned int dfs(std::string cave) {
        
        unsigned int answer = 0;
        if(cave == "end") {
            return 1;
        }
        if(islower(cave.at(0)) && this->is_visited.at(cave)) return 0;
        if(islower(cave.at(0))) this->is_visited.at(cave) = true;

        for(std::string child : this->adjacent.at(cave)) {
            if(child == "start") continue;
            answer += dfs(child);
        }

        if(islower(cave.at(0))) this->is_visited.at(cave) = false;
        return answer;
    }
};

struct Graph2 {

    std::list <std::string> path_traverse;

    std::unordered_map <std::string, unsigned int> is_visited;
    std::unordered_map <std::string, std::vector <std::string>> adjacent;
    void addEdge(std::string root, std::string child) {
        
        if(this->is_visited.find(root) == 0) this->is_visited.insert(std::make_pair(root, 0));
        if(this->is_visited.find(child) == 0) this->is_visited.insert(std::make_pair(child, 0));

        if(this->adjacent.find(root) == 0) {
            std::vector <std::string> empty_vector;
            this->adjacent.insert(std::make_pair(root, empty_vector));
        }
        this->adjacent.at(root).push_back(child);

        if(this->adjacent.find(child) == 0) {
            std::vector <std::string> empty_vector;
            this->adjacent.insert(std::make_pair(child, empty_vector));
        }
        this->adjacent.at(child).push_back(root);
    }
    std::vector <std::string> getPair(std::string root) {

        return this->adjacent.at(root);
    }
    unsigned int dfs(std::string cave) {
        
        unsigned int answer = 0;
        if(cave == "end") {
            return 1;
        }

        unsigned int is_visit_twice = 2;
        for(auto &visit : this->is_visited) {
            
            if(visit.second == 2) {
                is_visit_twice = 1;
            }
        }

        if(islower(cave.at(0)) && this->is_visited.at(cave) >= is_visit_twice) return 0;
        if(islower(cave.at(0))) this->is_visited.at(cave)++;

        for(std::string child : this->adjacent.at(cave)) {
            if(child == "start") continue;
            answer += dfs(child);
        }

        if(islower(cave.at(0))) this->is_visited.at(cave)--;
        return answer;
    }
};

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    Graph graph;

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        std::vector <std::string> pairs;
        while(ss.good()) {
            std::string pair; 
            getline(ss, pair, '-');
            pairs.push_back(pair);
        }
        graph.addEdge(pairs.at(0), pairs.at(1));
    }
    read_file.close();

    unsigned int count = graph.dfs("start");

    std::string answer = std::to_string(count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    Graph2 graph;

    while(getline(read_file, read_text)) {

        std::stringstream ss(read_text);
        std::vector <std::string> pairs;
        while(ss.good()) {
            std::string pair; 
            getline(ss, pair, '-');
            pairs.push_back(pair);
        }
        graph.addEdge(pairs.at(0), pairs.at(1));
    }
    read_file.close();

    unsigned int count = graph.dfs("start");

    std::string answer = std::to_string(count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    part1();
    part2();

    return 0;
}