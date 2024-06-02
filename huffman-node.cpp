#include "huffman.h"

Node::Node(): freq{0.0}, letter{'\0'} {}

Node::Node(const char &l): freq{0.0}, letter{l} {}

Node::Node(const float &f): freq{f}, letter{'\0'} {}

Node::Node(const float& f, const char& l): freq{f}, letter{l} {}

void Node::setFreq(const float& f) {
    freq = f;
}

float Node::getFreq() const {
    return freq;
}

void Node::setLetter(const char& l) {
    letter = l;
}

char Node::getLetter() const {
    return letter;
}

void Node::setLeft(std::shared_ptr<Node> l) {
    left = l;
}

void Node::setRight(std::shared_ptr<Node> r) {
    right = r;
}

std::shared_ptr<Node> Node::getLeft() const {
    return left;
}

std::shared_ptr<Node> Node::getRight() const {
    return right;
}

std::string input_file_details(std::string& file_input,char option) {
    std::cin>>file_input;
    while(!check_file_exists(file_input)) {
        std::cout<<"\n"<<file_input<<" does not exist."<<std::endl;
        std::cout<<"Please re-enter file name: ";
        std::cin>>file_input;
    }
    
	switch(option) {
		case 'c':
			return {file_input.substr(0,file_input.find_last_of('.'))+".dat"};
		case 'd':
			return {file_input.substr(0,file_input.find_last_of('.'))+".txt"};
	}
}

bool check_file_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0); 
}

int take_integer_input_between(const int& beg, const int& end) {
    int num;
    std::cin>>num;
    while (!std::cin.good() || num<beg || num>end)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"\nInvalid Input! Enter an integer in range "<<beg<<"-"<<end<<" :";
        std::cin>>num;
    }
    return num;
}

void print_file_details(const std::string& file_name)
{
    struct stat stat_buf;
    int rc = stat(file_name.c_str(), &stat_buf);

    std::cout<<"Name: "<<file_name<<std::endl;
    std::cout<<"Size: "<<((rc == 0)? stat_buf.st_size : -1)<<" bytes\n"<<std::endl;
}

void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}