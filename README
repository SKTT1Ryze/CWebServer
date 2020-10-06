# A Web Server written with C
This project is developed for my computer network lab in HUST.  
But I want to make it better to be not only my task for one point.  

## Dependencies
Only socket library in linux.  

## Installation
>\$ git clone https://github.com/SKTT1Ryze/CWebServer.git

## Build
>\$ cd CWebServer
>\$ make build  

## Run Server and Client
First:  
>\$ make build

One terminal:  
>\$ ./target/server

Another terminal:  
>\$ ./target/client

## Run Server and Request Server in Chrome
Open a termianl and run:  
>\$ make run

Then open chrome and type:  
> 127.0.0.1:8000

A html file will be rendered in the chrome.  

Or you can try other urls:  
> 127.0.0.1:8000/home
> 127.0.0.1:8000/rust
> 127.0.0.1:8000/riscv

If you type an error url with the right IP address and port,  
a 404 html page will be rendered in the chrome.  
Just try:  
> 127.0.0.1:8000/error

## Configure
You can change the IP address and port those the server listen to by changing the source code, in `src/config.h`.  
```cpp
#define AF_LISTENED AF_INET
const int PORT = 8000;
```

## TODO
+ Add thread pool

## **Welcome to communicate and contribute!**