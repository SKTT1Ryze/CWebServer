// Lib for Prase HTTP Request

#include <string.h>
#include <iostream>
#include <vector>


std::vector<std::string> prase_request(std::string request) {
    // The request format like this:
    // ----------------------------------------
    // GET / HTTP/1.1
    // Host: 127.0.0.1:8000
    // Connection: keep-alive
    // Cache-Control: max-age=0
    // Upgrade-Insecure-Requests: 1
    // User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36
    // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
    // Sec-Fetch-Site: none
    // Sec-Fetch-Mode: navigate
    // Sec-Fetch-User: ?1
    // Sec-Fetch-Dest: document
    // Accept-Encoding: gzip, deflate, br
    // Accept-Language: en-US,en;q=0.9,ja;q=0.8
    // ----------------------------------------
    // We only need the first six lines
    // Return Host, Path, Protocol, User-Agent
    
    std::vector<std::string> result = std::vector<std::string> {};
    int i, j;
    i = request.find("Host:");
    j = request.find(':', i);
    result.push_back(request.substr(i, j));
    i = request.find("GET");
    j = request.find("HTTP");
    result.push_back(request.substr(i + 4, j - i -5));
    i = request.find("HTTP");
    j = request.find('\n', i);
    result.push_back(request.substr(i, j));
    return result;
}
