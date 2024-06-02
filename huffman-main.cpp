#include "huffman.h"

int main(int argc, char const *argv[])
{
    int choice;

    while(true) {
        clear_screen();
        std::cout<<"1. Compress File"<<std::endl;
        std::cout<<"2. Decompress File"<<std::endl;
        std::cout<<"3. Exit"<<std::endl;
        std::cout<<"Enter your choice: ";
        choice = take_integer_input_between(1, 3);

        switch (choice)
        {
            case 1:
                compress_file();
                break;
            case 2:
                decompress_file();
                break;
            case 3:
                return 0;   
        }
        std::cout<<std::endl;
        getchar();
        getchar();
    }
}
