# Makefile for build cWebServer

GCC			:= g++
OPT			:= -o
source_path	:= ./src
target_path	:= ./target
server_src	:= ${source_path}/server.cpp
client_src	:= ${source_path}/client.cpp
socket		:= $(source_path)/socket.cpp
error		:= ${source_path}/error.cpp
server		:= ${target_path}/server
client		:= $(target_path)/client


server:
	$(GCC) $(OPT) $(server) $(server_src) $(error) $(socket)

client:
	$(GCC) $(OPT) $(client) $(client_src) $(error) $(socket)

build: server client

run: build
	@echo 'runing server...'
	@$(server)
	
clean:
	@rm $(target_path)/*