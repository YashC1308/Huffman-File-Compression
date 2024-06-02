#include "huffman.h"

void read_and_map_freq(std::ifstream &input,std::map<char,int>& character_frequency) {
    char letter;
    while(input.peek() != EOF) {
        input.get(letter);
        if(character_frequency.find(letter) != character_frequency.end()) 
            character_frequency[letter]++;
        else
            character_frequency.insert(std::make_pair(letter, 1));
    }    
}

void make_node_vector(const std::map<char,int>& character_frequency, std::vector< std::shared_ptr<Node> >& node_vector) {
    for(std::map<char,int>::const_iterator i=character_frequency.begin(); i!=character_frequency.end();i++)
        node_vector.push_back(std::make_shared<Node>((*i).second,(*i).first));
}

void build_huffman_tree(std::vector< std::shared_ptr<Node> >& node_vector) {
    if(node_vector.size() == 1)
        return;

    std::sort(node_vector.begin(), node_vector.end(), [](std::shared_ptr<Node> n1, std::shared_ptr<Node> n2){ return n1->getFreq() < n2->getFreq(); });
    std::shared_ptr<Node> parent = std::make_shared<Node>(node_vector[0]->getFreq() + node_vector[1]->getFreq());
    parent->setLeft(node_vector[0]);
    parent->setRight(node_vector[1]);

    node_vector.erase(node_vector.begin(),node_vector.begin()+2);
    node_vector.push_back(parent);
    build_huffman_tree(node_vector);
}

void build_encoding_map(std::shared_ptr<Node> root, std::unordered_map<char,std::string>& encoding_map, std::string code) {
    if(root->getLetter() != '\0')
        encoding_map.insert(std::make_pair(root->getLetter(), code));
    else {
        build_encoding_map(root->getLeft(), encoding_map, code+"0");
        build_encoding_map(root->getRight(), encoding_map, code+"1");
    }
}

void create_compressed_file(std::ifstream &input,std::ofstream &output,std::unordered_map<char,std::string>& encoding_map) {
    char letter;
    int len_end = 8;
    std::string buffer = "";
    std::stringstream s_buffer;
    s_buffer<<std::noskipws;
    while(input.peek() != EOF) {
        input.get(letter);
        buffer+=encoding_map[letter];
        while(buffer.size()>=8) {
            print_to_buffer(s_buffer, buffer.substr(0,8));
            buffer.erase(buffer.begin(),buffer.begin()+8);
        }
    }
    if(buffer.size()>0) {
        len_end=buffer.size();
        print_to_buffer(s_buffer, buffer.substr(0,buffer.size()));
        buffer.erase(buffer.begin(),buffer.begin()+buffer.size());
    }
    output<<len_end;

    while(s_buffer.rdbuf()->in_avail() != 0) {
        s_buffer>>letter;
        output.put(letter);
    }
}

void print_to_buffer(std::stringstream& s_buffer, std::string value) {
    std::bitset<8> byte(value);
    char byte_char = byte.to_ulong();
    s_buffer.write(&byte_char, 1);
}

void encode_tree(std::ofstream& output, std::shared_ptr<Node> root) {
    if(root->getLeft() == nullptr && root->getRight()== nullptr) {
        output<<'1'<<root->getLetter();
    } else {
        output<<'0';
        encode_tree(output,root->getLeft());
        encode_tree(output,root->getRight());
    }
}

void compress_file() {
    std::ifstream input;
    std::ofstream output;
    std::map<char,int> character_frequency;
    std::string file_input;
    std::string file_output;
    std::shared_ptr<Node> root = nullptr;
    std::vector< std::shared_ptr<Node> > node_vector;
    std::unordered_map<char,std::string> encoding_map;
    
    std::cout<<"Enter input file: ";
    file_output = input_file_details(file_input,'c');
    
    input.open(file_input, std::ios::in);
    output.open(file_output, std::ios::out);
    
    read_and_map_freq(input,character_frequency);

    make_node_vector(character_frequency, node_vector);

    build_huffman_tree(node_vector);
    root = node_vector[0];

    build_encoding_map(root, encoding_map, "");
    
    encode_tree(output,root);

    input.seekg(0,std::ios::beg);
    create_compressed_file(input,output,encoding_map);
    
    input.close();
    output.close();

    std::cout<<"\nYour file has been compressed suceesfully."<<std::endl;
    std::cout<<"File before compression:\n";
    print_file_details(file_input);
    std::cout<<"File after compression:\n";
    print_file_details(file_output);
    
    remove(file_input.c_str());
}