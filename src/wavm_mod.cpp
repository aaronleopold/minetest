// Contents of wavm_mod.cpp
// Takes the chat message, parses it for the file specified, and runs the NodeJS
// executable, returning that result
// Written by Bryan Rooke and Eric Daff - 2/6/19
// Last modified - 4/9/19
// Senior Project

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <serverenvironment.h>
#include <itemdef.h>
#include <nodedef.h>
#include <server.h>

// Function Prototypes
std::string retrieve_output_from_file(std::string);

// wasm_mod main function
std::string wasm_mod(std::string message, IWritableItemDefManager* idef) {
	std::string output_file_name = "node_output.txt";
	int result;

	// Message contains the '-wasm' part, so just get the filename
	std::string filename = message.substr(6);

	// Get the current path
	char path_buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path_buffer);

	//result = system(path_command.c_str());
	std::string current_path = path_buffer;
	current_path = current_path.substr(0, current_path.size()-3);

	// Find the path to the WAVM executable
        std::string node_exe = current_path + "\\NodeJS\\node.exe";

	// Find the path to the specified file
        std::string path = current_path + "\\bin\\WAST_files\\" + filename;

	// Run the executable and pipe the output to a text file
        std::string command = node_exe + " " + path + " > " + output_file_name;
        result = system(command.c_str());

	// Populate ItemDefinition instance with output of the text file
	ItemDefinition *def = new ItemDefinition();
	def->name = "Gator_Block";
	def->type = ITEM_NODE;
	def->description = "Gator_Block Description";
	def->inventory_image = "default_diamond_block.png";
	def->wield_image = "default_diamond_block.png";

	// Call registerItem on ItemDefinition
	idef->registerItem(def);

        return retrieve_output_from_file(output_file_name);
}

// Citation: www.cplusplus.com/doc/tutorial/files/
// Below code to read from a file was influenced by the sample code provided by the above link
// Grab the content of the text file and return it
std::string retrieve_output_from_file(std::string filename) {
	std::string content;
	std::ifstream output(filename.c_str());
	if(output.is_open()){
		std::getline(output, content);
	}
	output.close();

	return content;
}
