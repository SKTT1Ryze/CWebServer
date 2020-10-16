// Lib for Reading HTML File

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#define html_rust "./html/rust.html"
#define html_root "./html/root.html"
#define html_home "./html/home.html"
#define html_riscv "./html/riscv.html"
#define html_ref_rain "./html/ref_rain.html"
#define html_404 "./html/404.html"


struct Config
{
    std::string ip_addr;
    std::vector<int> ports;
};


int read_file(const char *file, char *buf) {
    std::ifstream read_obj;
    read_obj.open(file, std::ios::in);
    if(!read_obj.is_open()) {
        std::cout << "File " << file << " open error, exit." << std::endl;
        exit(-1);
    }
    read_obj.seekg(0, std::ios::end);
    int len = read_obj.tellg();
    read_obj.seekg(0, std::ios::beg);
    read_obj.read(buf, len);
    read_obj.close();
    return len;
}

struct Config read_config(const char *file) {
    struct Config result;
    std::ifstream read_obj;
    std::vector<std::string> config_data = std::vector<std::string> {};
    read_obj.open(file, std::ios::in);
    if(!read_obj.is_open()) {
        std::cout << "File " << file << " open error, exit." << std::endl;
        exit(-1);
    }
    while(1) {
        std::string line;
        if(!getline(read_obj, line)) break;
        if(line.empty()) continue;
        config_data.push_back(line);
    }
    
    for(int i = 0; i < config_data.size(); i++) {
        if(config_data[i].compare("[IP_Address]") == 0) {
            result.ip_addr = config_data[i + 1];
        }
        if(config_data[i].compare("[Ports]") == 0) {
            while (i + 1 < config_data.size())
            {
                result.ports.push_back(std::stoi(config_data[i + 1], nullptr, 10));
                i++;
            }
            
        }
    }
    /* std::cout << "IP: " << result.ip_addr << std::endl;
    std::cout << "Ports: " << std::endl;
    for(int i = 0; i < result.ports.size(); i++)
        std::cout << result.ports[i] << std::endl; */
    return result;
}