#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "lispp.h"

void NextInput(std::stringstream *ss){
    std::cout << "Lispp>> ";
        std::string old_input;
        getline(*ss, old_input);
        std::cout << old_input;
        ss->clear();
        std::string new_input;
        getline(std::cin, new_input);
        ss->str(old_input + new_input);
}


void InteractiveRunScenario() {
    std::stringstream in;
    Lispp lispp(&in, &std::cout);
    std::cout << "Lispp prompt\nFor exit press Ctrl+D\n\n";
    while (std::cin){
        try {
            NextInput(&in);
            lispp.Run();
        } catch (const std::exception& exception){
            std::cout << "     >> "  << exception.what() << std::endl;
        }
    }
}

void PrintTreeScenario() {
    std::stringstream in;
    auto tokenizer = std::make_shared<Tokenizer>(&in);
    auto parser = std::make_shared<Parser>(tokenizer);

    std::cout << "Lispp prompt\nFor exit press Ctrl+D\n\n";
    while (std::cin){
        try {
            NextInput(&in);
            auto node = parser->Parse();
            std::cout << node->ToString(0) << "\n";
        } catch (const std::exception& exception){
            std::cout << "     >> "  << exception.what() << std::endl;
        }
    }
}

void EraseNewLines(std::string& str) {
    std::string::size_type pos = 0; // Must initialize
    while ( ( pos = str.find ('\n', pos) ) != std::string::npos ) {
        str.erase (pos, 1);
    }
}

void FileRunScenario() {
    std::ifstream my_input_file;
    my_input_file.open("/home/stanislav/university/Semester6/MTran/length.txt");
    std::string str((std::istreambuf_iterator<char>(my_input_file)),
                    std::istreambuf_iterator<char>());
    EraseNewLines(str);
    std::cout << str << '\n';
    my_input_file.close();

    std::stringstream in;
    in.str(str);

    Lispp lispp(&in, &std::cout);
    std::cout << "Lispp program\n\n";
    while (in.rdbuf()->in_avail() != 0){
        try {
            lispp.Run(true);
        } catch (const std::exception& exception){
            std::cout << "     >> "  << exception.what() << std::endl;
        }
    }
}


int main() {
    FileRunScenario();
    return 0;
}
