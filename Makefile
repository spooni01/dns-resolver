#############################################################
# Project:     	DNS resolver								#
# File:        	Makefile									#
# Date:        	7.10.2023									#
# Author: 		Adam Ližičiar <xlizic00@stud.fit.vutbr.cz>	#
#############################################################	
OUTPUT_NAME = dns
SRC_FILES = src/main.cpp
CXX = g++
CXX_FLAGS = -std=c++20 -Wall -pedantic -Werror -static-libstdc++
DOC=manual
OBJ_DIR = obj
BIN_DIR = bin
DOC_DIR = doc
TESTS_DIR = tests
MKDIR_P = mkdir -p
RMDIR = rm -rf

#############################################################

.PHONY: all doc test clean cleanall

### Build BIN file
all: build
build: $(BIN_DIR)
	$(CXX) $(CXX_FLAGS) $(SRC_FILES) -o $(BIN_DIR)/$(OUTPUT_NAME)

### Create directories 
create_directories: $(OBJ_DIR) $(BIN_DIR)

# Create object directory
$(OBJ_DIR):
	$(MKDIR_P) $(OBJ_DIR)

# Create binary directory
$(BIN_DIR):
	$(MKDIR_P) $(BIN_DIR)

### Tests
test: all
	bash ./$(TESTS_DIR)/run_tests.sh

### Create documentation
doc: $(OBJ_DIR) $(DOC_DIR)/$(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd $(DOC_DIR) && pdflatex $(DOC).tex
	cd ../
	if [ -e $(DOC_DIR)/$(DOC).aux ]; then mv $(DOC_DIR)/$(DOC).aux $(OBJ_DIR)/$(DOC).aux; fi
	if [ -e $(DOC_DIR)/$(DOC).dvi ]; then mv $(DOC_DIR)/$(DOC).dvi $(OBJ_DIR)/$(DOC).dvi; fi
	if [ -e $(DOC_DIR)/$(DOC).log ]; then mv $(DOC_DIR)/$(DOC).log $(OBJ_DIR)/$(DOC).log; fi
	if [ -e $(DOC_DIR)/$(DOC).ps ]; then mv $(DOC_DIR)/$(DOC).ps $(OBJ_DIR)/$(DOC).ps; fi
	if [ -e $(DOC_DIR)/$(DOC).synctex.gz ]; then mv $(DOC_DIR)/$(DOC).synctex.gz $(OBJ_DIR)/$(DOC).synctex.gz; fi
	if [ -e $(DOC_DIR)/$(DOC).fls ]; then mv $(DOC_DIR)/$(DOC).fls $(OBJ_DIR)/$(DOC).fls; fi
	if [ -e $(DOC_DIR)/$(DOC).fdb_latexmk ]; then mv $(DOC_DIR)/$(DOC).fdb_latexmk $(OBJ_DIR)/$(DOC).fdb_latexmk; fi
	if [ -e $(DOC_DIR)/$(DOC).bbl ]; then mv $(DOC_DIR)/$(DOC).bbl $(OBJ_DIR)/$(DOC).bbl; fi
	if [ -e $(DOC_DIR)/$(DOC).blg ]; then mv $(DOC_DIR)/$(DOC).blg $(OBJ_DIR)/$(DOC).blg; fi
	if [ -e $(DOC_DIR)/$(DOC).out ]; then mv $(DOC_DIR)/$(DOC).out $(OBJ_DIR)/$(DOC).out; fi
	if [ -e $(DOC_DIR)/$(DOC).toc ]; then mv $(DOC_DIR)/$(DOC).toc $(OBJ_DIR)/$(DOC).toc; fi
	if [ -e $(DOC_DIR)/$(DOC).pdf.filepart ]; then mv $(DOC_DIR)/$(DOC).pdf.filepart $(OBJ_DIR)/$(DOC).pdf.filepart; fi

### Clean 
# Clean all object files
clean:
	$(RMDIR) $(OBJ_DIR) 2> nul || true
	$(RMDIR) nul
	$(RMDIR) nul

# Clean all object and binary files
cleanall: clean
	$(RMDIR) $(BIN_DIR) 2> nul || true
	$(RMDIR) $(DOC_DIR)/$(DOC).pdf
	$(RMDIR) $(TESTS_DIR)/spec/*.programOut
	$(RMDIR) nul
	$(RMDIR) nul
