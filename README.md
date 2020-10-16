# A Web Server written with C
This project is developed for my computer network lab in HUST.  
But I want to make it better to be not only my task for one point.  

## Dependencies
+ Socket library in linux.  
+ ThreadPool lib

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

Run multithreading web server (default with 3 threads):  
>\$ ./target/tp_server  

## Run Multithreading Server and Request Server in Chrome
Open a termianl and run:  
>\$ make run

(This command actually runs ./target/tp_server)  

Then open chrome and type:  
> 127.0.0.1:8000

A html file will be rendered in the chrome.  

Or you can try other urls:  
> 127.0.0.1:8000/home # port 8000 can be replace with the ports in the config file ./config
> 127.0.0.1:8000/rust
> 127.0.0.1:8000/riscv
> 127.0.0.1:8000/ref_rain # A video on youtube uploaded by myself

If you type an error url with the right IP address and port,  
a 404 html page will be rendered in the chrome.  
Just try:  
> 127.0.0.1:8000/error

## Configure
You can change the IP address and port those the server listen to by changing the `./config`.  
Such as:  
```
[IP_Address]
127.0.0.1

[Ports]
7000
8000
9000
```

## TODO
+ Error handler
+ Best performance
+ Best core

## **Welcome to communicate and contribute!**