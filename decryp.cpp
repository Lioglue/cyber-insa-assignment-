//insa camp was wonderfull and i like it , but i miss you all 
// ctc-3586-26
// what a boring time in home offff 

using namespace std;

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <stdexcept>


class RC4 {
private:
      vector<unsigned char> S;
    void ksa(const   string& key) {
        S.resize(256);
        for (int i = 0; i < 256; ++i) S[i] = i;
        int j = 0;
        int key_length = key.length();
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + static_cast<unsigned char>(key[i % key_length])) % 256;
              swap(S[i], S[j]);
        }
    }
public:
    void process(const   string& key,   vector<unsigned char>& data) {
        ksa(key);
        int i = 0, j = 0;
        for (size_t k = 0; k < data.size(); ++k) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
              swap(S[i], S[j]);
            unsigned char keystream_byte = S[(S[i] + S[j]) % 256];
            data[k] ^= keystream_byte;
        }
    }
};

std::vector<unsigned char> readFile(const   string& filename) {
      ifstream file(filename.c_str(),   ios::binary |   ios::ate);
    if (!file.is_open()) throw std::runtime_error("Could not open file: " + filename);
      streamsize size = file.tellg();
    file.seekg(0,   ios::beg);
      vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return buffer;
}

void writeFile(const std::string& filename, const   vector<unsigned char>& buffer) {
      ofstream file(filename.c_str(),   ios::binary);
    if (!file.is_open()) throw   runtime_error("Could not open file for writing: " + filename);
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

int main() {
      string key = "Mysecretkeyisfkremaryaminsa"; 
     string targetFile = "file.txt";

    try {
        RC4 cipher;
        cout << "Reading encrypted file.txt..." << endl;
        vector<unsigned char> buffer = readFile(targetFile);


        cipher.process(key, buffer); 

      
        writeFile(targetFile, buffer);

        cout << "Decryption successful! File restored." << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}

