#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Position {
    long x;
    long y;
    long z;
};

struct Reboot {

    bool status;
    Position pos1;
    Position pos2;
    Reboot(bool status, Position pos1, Position pos2) {
        this->status = status;
        this->pos1 = pos1;
        this->pos2 = pos2;
    }
};

long clamp(long x, long a, long b) {

    if(x <= a) return a;
    if(x >= b) return b;
    return x;
}

void doReboot(std::unordered_map <std::string, bool> *reactor_status, Position pos1, Position pos2, bool status) {

    std::vector <std::string> positions;
    std::vector <std::string> x_str, y_str, z_str;

    for(long x = clamp(pos1.x, -50, 50); x <= clamp(pos2.x, -50, 50); x++) {
        if(pos1.x < -50 || pos2.x > 50) continue;
        for(long y = clamp(pos1.y, -50, 50); y <= clamp(pos2.y, -50, 50); y++) {
            if(pos1.y < -50 || pos2.y > 50) continue;
            for(long z = clamp(pos1.z, -50, 50); z <= clamp(pos2.z, -50, 50); z++) {
                if(pos1.z < -50 || pos2.z > 50) continue;
                
                std::string pos;
                pos += std::to_string(x) + ',';
                pos += std::to_string(y) + ',';
                pos += std::to_string(z) + ',';
                positions.push_back(pos);
            }
        }
    }

    for(std::string pos : positions) {
        if(reactor_status->find(pos) == reactor_status->end()) {
            reactor_status->insert(std::make_pair(pos, status));
        }
        reactor_status->at(pos) = status;
    }
}

void part1() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <Reboot> reboots;
    std::unordered_map <std::string, bool> reactor_status;

    while(getline(read_file, read_text)) {

        std::vector <std::string> texts;
        
        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string text;
            getline(ss, text, ' ');

            texts.push_back(text);
        }

        std::vector <std::string> read_positions;
        std::stringstream sss(texts.at(1));
        while(sss.good()) {

            std::string read_position;
            getline(sss, read_position, ',');
            read_positions.push_back(read_position);
        }

        std::string read_x1, read_x2, read_y1, read_y2, read_z1, read_z2;
        long x1, x2, y1, y2, z1, z2;

        read_x1 = read_positions.at(0).substr(2, read_positions.at(0).find('.') - 2);
        read_x2 = read_positions.at(0).substr(read_positions.at(0).find('.') + 2, read_positions.at(0).find(' '));
        read_y1 = read_positions.at(1).substr(2, read_positions.at(1).find('.') - 2);
        read_y2 = read_positions.at(1).substr(read_positions.at(1).find('.') + 2, read_positions.at(1).find(' '));
        read_z1 = read_positions.at(2).substr(2, read_positions.at(2).find('.') - 2);
        read_z2 = read_positions.at(2).substr(read_positions.at(2).find('.') + 2, read_positions.at(2).find(' '));

        std::stringstream ss_x1(read_x1), ss_x2(read_x2), ss_y1(read_y1), ss_y2(read_y2), ss_z1(read_z1), ss_z2(read_z2);
        ss_x1 >> x1; ss_x2 >> x2;
        ss_y1 >> y1; ss_y2 >> y2;
        ss_z1 >> z1; ss_z2 >> z2;

        Position p1, p2;
        p1.x = x1;
        p1.y = y1;
        p1.z = z1;
        p2.x = x2;
        p2.y = y2;
        p2.z = z2;

        bool status;
        if(texts.at(0) == "on") status = true;
        else if(texts.at(0) == "off") status = false;

        reboots.push_back(Reboot(status, p1, p2));
    }

    for(Reboot reboot : reboots) {
        doReboot(&reactor_status, reboot.pos1, reboot.pos2, reboot.status); 
    }

    unsigned int count = 0;
    for(auto status : reactor_status) {
        if(status.second) count++;
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 1 Answer: " << answer << std::endl;
}

void part2() {

    std::ifstream read_file("input.txt");
    std::string read_text;

    std::vector <Reboot> reboots;

    std::vector <long> X;
    std::vector <long> Y;
    std::vector <long> Z;

    while(getline(read_file, read_text)) {

        std::vector <std::string> texts;
        
        std::stringstream ss(read_text);
        while(ss.good()) {

            std::string text;
            getline(ss, text, ' ');

            texts.push_back(text);
        }

        std::vector <std::string> read_positions;
        std::stringstream sss(texts.at(1));
        while(sss.good()) {

            std::string read_position;
            getline(sss, read_position, ',');
            read_positions.push_back(read_position);
        }

        std::string read_x1, read_x2, read_y1, read_y2, read_z1, read_z2;
        long x1, x2, y1, y2, z1, z2;

        read_x1 = read_positions.at(0).substr(2, read_positions.at(0).find('.') - 2);
        read_x2 = read_positions.at(0).substr(read_positions.at(0).find('.') + 2, read_positions.at(0).find(' '));
        read_y1 = read_positions.at(1).substr(2, read_positions.at(1).find('.') - 2);
        read_y2 = read_positions.at(1).substr(read_positions.at(1).find('.') + 2, read_positions.at(1).find(' '));
        read_z1 = read_positions.at(2).substr(2, read_positions.at(2).find('.') - 2);
        read_z2 = read_positions.at(2).substr(read_positions.at(2).find('.') + 2, read_positions.at(2).find(' '));

        std::stringstream ss_x1(read_x1), ss_x2(read_x2), ss_y1(read_y1), ss_y2(read_y2), ss_z1(read_z1), ss_z2(read_z2);
        ss_x1 >> x1; ss_x2 >> x2;
        ss_y1 >> y1; ss_y2 >> y2;
        ss_z1 >> z1; ss_z2 >> z2;

        Position p1, p2;
        p1.x = x1;
        p1.y = y1;
        p1.z = z1;
        p2.x = x2 + 1;
        p2.y = y2 + 1;
        p2.z = z2 + 1;

        X.push_back(x1);
        X.push_back(x2 + 1);
        Y.push_back(y1);
        Y.push_back(y2 + 1);
        Z.push_back(z1);
        Z.push_back(z2 + 1);

        bool status;
        if(texts.at(0) == "on") status = true;
        else if(texts.at(0) == "off") status = false;

        reboots.push_back(Reboot(status, p1, p2));
    }

    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());
    std::sort(Z.begin(), Z.end());
    unsigned int n = X.size(); 
    
    std::vector <std::vector <std::vector <bool>>> status(n, std::vector <std::vector <bool>> (n, std::vector <bool> (n, false)));

    for(Reboot reboot : reboots) {

        unsigned int x1 = std::lower_bound(X.begin(), X.end(), reboot.pos1.x) - X.begin();
        unsigned int x2 = std::lower_bound(X.begin(), X.end(), reboot.pos2.x) - X.begin();
        unsigned int y1 = std::lower_bound(Y.begin(), Y.end(), reboot.pos1.y) - Y.begin();
        unsigned int y2 = std::lower_bound(Y.begin(), Y.end(), reboot.pos2.y) - Y.begin();
        unsigned int z1 = std::lower_bound(Z.begin(), Z.end(), reboot.pos1.z) - Z.begin();
        unsigned int z2 = std::lower_bound(Z.begin(), Z.end(), reboot.pos2.z) - Z.begin();

        for(unsigned int x = x1; x < x2; x++) {
            for(unsigned int y = y1; y < y2; y++) {
                for(unsigned int z = z1; z < z2; z++) {
                    
                    status[x][y][z] = reboot.status;
                }
            }
        }
    }

    unsigned long int count = 0;
    for(unsigned int x = 0; x < n - 1; x++) {
        for(unsigned int y = 0; y < n - 1; y++) {
            for(unsigned int z = 0; z < n - 1; z++) {

                count += status[x][y][z] * (X[x+1] - X[x]) * (Y[y+1] - Y[y]) * (Z[z+1] - Z[z]);
            }
        }
    }

    read_file.close();

    std::string answer = std::to_string(count);
    std::cout << "Part 2 Answer: " << answer << std::endl;
}

int main() {

    //part1();
    part2();

    return 0;
}