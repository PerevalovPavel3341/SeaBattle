#ifndef TERMINAL_INPUT_PROCESSOR_H
#define TERMINAL_INPUT_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <unordered_map>

class TerminalInputProcessor {
private:
    std::unordered_map<char, std::string> command_map;
    void load_commands_from_file(const std::string& filename){
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening command file, using default controls." << std::endl;
            command_map = {{'a', "attack"}, {'l', "load"}, {'s', "save"}, {'u', "use_ability"}, {'q', "quit"}};
            return;
        }

        char key;
        std::string command;
        while (file >> key >> command) {
            command_map[key] = command;
        }
    }

public:
    TerminalInputProcessor(const std::string& filename){
        load_commands_from_file(filename);
    }   

    char get_command(){
        char input;
        std::cin >> input;
        return input;
    }
};

#endif