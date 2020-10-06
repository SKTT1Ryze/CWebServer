// Lib for Reading HTML File

#include <iostream>
#include <fstream>
#include <string.h>

#define html_rust "./html/rust.html"
#define html_root "./html/root.html"
#define html_home "./html/home.html"
#define html_riscv "./html/riscv.html"
#define html_404 "./html/404.html"

int read_html(const char *file, char *buf) {
    std::ifstream read_obj;
    read_obj.open(file, std::ios::in);
    read_obj.seekg(0, std::ios::end);
    int len = read_obj.tellg();
    std::cout << "Read HTML: " << len << " words." << std::endl;
    read_obj.seekg(0, std::ios::beg);
    read_obj.read(buf, len);
    read_obj.close();
    return len;
}

