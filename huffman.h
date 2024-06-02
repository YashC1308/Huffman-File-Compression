#ifndef COMPRESS_DEC_H
#define COMPRESS_DEC_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <bitset>
#include <sstream>
#include <sys/stat.h>
#include <limits>

class Node {
    public:
        Node();
        Node(const char&);
        Node(const float&);
        Node(const float&,const char&);
        void setFreq(const float&);
        void setLetter(const char&);
        char getLetter() const;
        float getFreq() const;
        void setLeft(std::shared_ptr<Node>);
        void setRight(std::shared_ptr<Node>);
        std::shared_ptr<Node> getLeft() const;
        std::shared_ptr<Node> getRight() const;
    private:
        float freq;
        char letter;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
};

// utility functions
void clear_screen();
void print_file_details(const std::string&);
bool check_file_exists(const std::string&);
int take_integer_input_between(const int&, const int&);
std::string input_file_details(std::string&,char);

// functions used for compression
void read_and_map_freq(std::ifstream&,std::map<char,int>&);
void make_node_vector(const std::map<char,int>&, std::vector< std::shared_ptr<Node> >&);
void build_huffman_tree(std::vector< std::shared_ptr<Node> >&);
void build_encoding_map(std::shared_ptr<Node>, std::unordered_map<char,std::string>&,std::string);
void create_compressed_file(std::ifstream&,std::ofstream&,std::unordered_map<char,std::string>&);
void encode_tree(std::ofstream&, std::shared_ptr<Node>);
void compress_file();

// functions used for decompression
void decode_compressed_file(std::ifstream&,std::ofstream&,std::shared_ptr<Node>,int&);
char get_char_from_tree(std::shared_ptr<Node>,std::stringstream&);
std::shared_ptr<Node> decode_tree(std::ifstream&,std::shared_ptr<Node>);
void print_to_buffer(std::stringstream&, std::string);
void decompress_file();

#endif
