# Makefile for build cWebServer

GCC			:= g++
FLAGSS		:= -o
Thread		:= -lpthread -pthread
source_path	:= ./src
target_path	:= ./target
server_src	:= ${source_path}/server.cpp
client_src	:= ${source_path}/client.cpp
socket		:= $(source_path)/socket.cpp
error		:= ${source_path}/error.cpp
tp_test_src	:= $(source_path)/threadpool_test.cpp
tpserver_src:= $(source_path)/tp_server_x.cpp
server		:= ${target_path}/server
client		:= $(target_path)/client
tp_test		:= $(target_path)/tp_test
tp_server	:= $(target_path)/tp_server

server:
	$(GCC) $(FLAGSS) $(server) $(server_src) $(error) $(socket)

client:
	$(GCC) $(FLAGSS) $(client) $(client_src) $(error) $(socket)

tp_test:
	$(GCC) $(Thread) $(FLAGSS) $(tp_test) $(tp_test_src)

tp_server:
	$(GCC) $(Thread) $(FLAGSS) $(tp_server) $(tpserver_src) $(error) $(socket)

build: server client tp_test tp_server

run: build
	@echo 'runing server...'
	@$(server)
	
clean:
	@rm $(target_path)/*