//insa camp was wonderfull and i like it , but i miss you all 
// ctc-3586-26
// what a boring time in home offff 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>


class RC4 {
private:
    std::vector<unsigned char> S;
    void ksa(const std::string& key) {
        S.resize(256);
        for (int i = 0; i < 256; ++i) S[i] = i;
        int j = 0;
        int key_length = key.length();
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + static_cast<unsigned char>(key[i % key_length])) % 256;
            std::swap(S[i], S[j]);
        }
    }
public:
    void process(const std::string& key, std::vector<unsigned char>& data) {
        ksa(key);
        int i = 0, j = 0;
        for (size_t k = 0; k < data.size(); ++k) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            std::swap(S[i], S[j]);
            unsigned char keystream_byte = S[(S[i] + S[j]) % 256];
            data[k] ^= keystream_byte;
        }
    }
};

std::vector<unsigned char> readFile(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::binary | std::ios::ate);
    if (!file.is_open()) throw std::runtime_error("Could not open file: " + filename);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

void writeFile(const std::string& filename, const std::vector<unsigned char>& buffer) {
    std::ofstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Could not open file for writing: " + filename);
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

int main() {
    std::string key = "MySecretKey123"; 
    std::string targetFile = "file.txt";

    try {
        RC4 cipher;
        std::cout << "Reading encrypted file.txt..." << std::endl;
        std::vector<unsigned char> buffer = readFile(targetFile);

       // std::cout << "Decrypting file contents..." << std::endl;
       //i do not want to display for now it looks like borring
        cipher.process(key, buffer); 

      //  std::cout << "Restoring file.txt to original format..." << std::endl;
      // this line too , i dont want it , wen deded i remove it 
        writeFile(targetFile, buffer);

        std::cout << "Decryption successful! File restored." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

