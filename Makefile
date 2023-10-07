#############################################################
# Project:     	DNS resolver								#
# File:        	Makefile									#
# Date:        	7.10.2023									#
# Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	#
#############################################################	
OUTPUT_NAME = dns
SRC_FILES = src/main.cpp
CXX = g++
CXX_FLAGS = -std=c++20 -Wall -Wextra -pedantic

all: $(OUTPUT_NAME)

$(OUTPUT_NAME): $(SRC_FILES)
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) -o $(OUTPUT_NAME)

clean:
	rm -f $(OUTPUT_NAME)