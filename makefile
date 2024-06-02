CXX= g++
RM= rm -f

SRCS= huffman-node.cpp huffman-encode.cpp huffman-decode.cpp huffman-main.cpp
OBJS= $(subst .cpp,.o, $(SRCS))

all: run-huffman

run-huffman: $(OBJS)
	$(CXX) -o run-huffman $(OBJS)

huffman-node.o: huffman-node.cpp huffman.h

huffman-encode.o: huffman-encode.cpp huffman.h

huffman-decode.o: huffman-decode.cpp huffman.h

huffman-main.o: huffman-main.cpp huffman.h

clean:
	$(RM) $(OBJS)