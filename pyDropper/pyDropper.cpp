#include <iostream>

#include "pyDrop.h"

int main(int argc, char* argv[]) {
    // Check if the user provided a file to encode
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <executable to drop>" << std::endl;
        return 1;
    }
	pyDrop(argv[1]); // Put the important code into a function in a header so I can reuse it in other stuff :)
    return 0;
}