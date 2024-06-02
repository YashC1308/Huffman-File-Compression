#include "huffman.h"

void decode_compressed_file(std::ifstream &input,std::ofstream &output,std::shared_ptr<Node> root,int& len_end) {
    std::stringstream buffer;
    char ch;
    while(true) {
        input.get(ch);
        std::bitset<8> byte(ch);
        std::string byte_str = byte.to_string(); 
    
        if(input.peek()!=EOF)
            buffer<<byte_str;
        else {
            buffer<<byte_str.substr(byte_str.size()-len_end,byte_str.size());
            break;
        }
    }
    
    while(buffer.rdbuf()->in_avail() != 0) 
        output.put(get_char_from_tree(root,buffer));
}

std::shared_ptr<Node> decode_tree(std::ifstream& input,std::shared_ptr<Node> root) {
    char ch;
    input.get(ch);
    if(ch == '1') {
        input.get(ch);
        root = std::make_shared<Node>(ch);
    } else {
        root = std::make_shared<Node>();
        root->setLeft(decode_tree(input,root->getLeft()));
        root->setRight(decode_tree(input,root->getRight()));
    }
    return root;
}

char get_char_from_tree(std::shared_ptr<Node> root,std::stringstream &buffer) {
    if(root->getLetter()!='\0')
        return root->getLetter();
    char bit;
    buffer>>bit;
    if(bit=='0')
        return get_char_from_tree(root->getLeft(),buffer);
    else
        return get_char_from_tree(root->getRight(),buffer);  
}

void decompress_file() {
    std::ifstream input;
    std::ofstream output;
    std::string file_input;
    std::string file_output;
    int len_end;
    std::shared_ptr<Node> root = nullptr;

    std::cout<<"Enter input file: ";
    file_output = input_file_details(file_input,'d');
    
    input.open(file_input, std::ios::in);
    output.open(file_output, std::ios::out);
    
    root=decode_tree(input,root);
    
    input>>len_end;
    
    decode_compressed_file(input, output, root, len_end);
    
    input.close();
    output.close();

    std::cout<<"\nYour file has been de-compressed suceesfully."<<std::endl;
    std::cout<<"File before de-compression:\n";
    print_file_details(file_input);
    std::cout<<"File after de-compression:\n";
    print_file_details(file_output);

    remove(file_input.c_str());
}