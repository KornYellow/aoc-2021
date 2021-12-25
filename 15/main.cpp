#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

std::vector <std::vector <unsigned int>> doFindPath(std::vector <std::vector <unsigned int>> risk_map, std::vector <std::vector <unsigned int>> risk_map_sum) {

	using Position = std::pair<unsigned int, unsigned int>;
	for(unsigned y = 0; y < risk_map.size(); y++) {
		for(unsigned x = 0; x < risk_map.size(); x++) {

			std::vector <Position> neighbours;
			if(x < risk_map.size() - 1) neighbours.push_back({x + 1, y});
			if(y < risk_map.size() - 1) neighbours.push_back({x, y + 1});
			if(x > 0) neighbours.push_back({x - 1, y});
			if(y > 0) neighbours.push_back({x, y - 1});

			for(Position pos : neighbours) {
				
				risk_map_sum.at(y).at(x) = std::min(risk_map_sum.at(y).at(x), risk_map_sum.at(pos.second).at(pos.first) + risk_map.at(y).at(x));
			}
		} 
	}
	return risk_map_sum;
}

std::vector <std::vector <unsigned int>> inputUpScale(std::vector <std::vector <unsigned int>> grid) {

	unsigned int n = grid.size() * 5;
	grid.resize(n);
	for(unsigned int row_index = 0; row_index < grid.size(); row_index++) grid.at(row_index).resize(n);

	for(unsigned int y = 0; y < n / 5; y++) {
		for(unsigned int x = 0; x < n / 5; x++) {
			for(unsigned int j = 0; j < 5; j++) {
				for(unsigned int i = 0; i < 5; i++) {

					unsigned int val = grid.at(y).at(x) + j + i;
					grid.at(y + (n/5) * j).at(x + (n/5) * i) = val >= 10 ? val % 10 + 1 : val;
				}
			}
		}
	}
	return grid;
}

void part1() {

	std::ifstream read_file("input.txt");
	std::string read_text;

	std::vector <std::vector <unsigned int>> risk_map;
	while(getline(read_file, read_text)) {
		
		std::vector <unsigned int> row;
		for(char cell : read_text) {
			row.push_back(cell - '0');
		}
		risk_map.push_back(row);
	}

	std::vector <std::vector <unsigned int>> risk_map_sum;
	risk_map_sum = risk_map;
	for(unsigned int y = 0; y < risk_map_sum.size(); y++) {
		for(unsigned int x = 0; x < risk_map_sum.at(y).size(); x++) {
			risk_map_sum.at(y).at(x) = 99999999;
		}
	}
	risk_map_sum.at(0).at(0) = 0;
	
	for(unsigned int i = 0; i < 3; i++) {
		risk_map_sum = doFindPath(risk_map, risk_map_sum);
	}

	read_file.close();

	std::string answer = std::to_string(risk_map_sum.at(risk_map.size() - 1).at(risk_map.size() - 1));
	std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

	std::ifstream read_file("input.txt");
	std::string read_text;

	std::vector <std::vector <unsigned int>> risk_map;
	while(getline(read_file, read_text)) {
		
		std::vector <unsigned int> row;
		for(char cell : read_text) {
			row.push_back(cell - '0');
		}
		risk_map.push_back(row);
	}
	risk_map = inputUpScale(risk_map);

	std::vector <std::vector <unsigned int>> risk_map_sum;
	risk_map_sum = risk_map;
	for(unsigned int y = 0; y < risk_map_sum.size(); y++) {
		for(unsigned int x = 0; x < risk_map_sum.at(y).size(); x++) {
			risk_map_sum.at(y).at(x) = 99999999;
		}
	}
	risk_map_sum.at(0).at(0) = 0;
	
	for(unsigned int i = 0; i < 3; i++) {
		risk_map_sum = doFindPath(risk_map, risk_map_sum);
	}

	read_file.close();

	std::string answer = std::to_string(risk_map_sum.at(risk_map.size() - 1).at(risk_map.size() - 1));
	std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

	part1();
	part2();

	return 0;
}