#############################################################
# Project:     	DNS resolver								#
# File:        	Makefile									#
# Date:        	23.9.2023									#
# Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	#
#############################################################	
OUTPUT_NAME=dns
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic

.PHONY: all makeGithub clean

all: src/main.c
	$(CC) $(CFLAGS) -o $(OUTPUT_NAME) src/main.c

makeGithub:
	$(CC) $(CFLAGS) -D_POSIX_C_SOURCE=200809L -o $(OUTPUT_NAME) src/main.c


clean:
	del $(OUTPUT_NAME).exe