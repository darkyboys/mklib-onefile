/*
 * Copyright (c) ghgltggamers 2024
 * MKLIB - A Library Building System which allows you to define rules for building the let MKLIB Create your library of all the project files in one.
 * Cross Platform and Cross Language.
 * Licensed under the MIT License
 * Compile with magma build system
 * Checkout the README.md for exact compilation information
*/

// Source

// Headers
// Std Cxx17 STL
#include <iostream>
#include  <fstream>
#include  <sstream>
#include   <vector>
#include   <string>

// Local
// #include "lexer.hh"
// #include "ir.hh"
// #include "functions.hh"
// #include "executer.hh"
// #include "parser.hh"

// ir
// Headers
bool show_logs = false;
bool is_IR_Made = false;

// IR
std::string INCLUDE=""; // temp only
std::string EXTENSION=""; // temp only
std::string OUTPUT="libxmklib"; // temp only
std::string SRC_PATH=""; // temp only
std::string OUT_DIR=""; // temp only
std::string IR = ""; // Real IR


std::vector <std::string> lexer (std::string code){
    std::vector <std::string> tokens;
    bool is_function_open = false,
         is_comment_started = false;
    std::string temp_function_name,
                temp_function_data,
                cache_function_name;
                // cache_function_data;
    for (std::size_t i = 0;i < code.length();i++){
        // std::cout << "'"<<code[i]<<"'\n"; // For debugging purpose only
        // Syntax Unit
        if (code[i] == '\n' and is_comment_started) 
            is_comment_started = false,
            code = code.substr(i+1),
            i = 0;
        if (is_comment_started) continue;
        if (code[i] == '#' or (code[i] == '/' and code[i+1] == '/') and not is_comment_started) {
            if (is_function_open) std::cout<< "Error _> Lexer Err: Invalid Syntax detected. '#' character can't be placed inside the function arguments.\n\n Critical Syntax Exception Failed: Autofixer Can't Fix Critical Syntax Error [2]\n", std::exit ( 3 );
            else is_comment_started = true;
        }
        if (code[i] == ';'){
            if (is_function_open) std::cout<< "Error _> Lexer Err: Invalid Syntax detected. ';' character can't be placed inside the function arguments.\n\n Critical Syntax Exception Failed: Autofixer Can't Fix Critical Syntax Error [1]\n", std::exit ( 3 );
            if (not is_function_open) tokens.push_back (std::string (temp_function_name + ":" + temp_function_data)), // Process the tokens in a way the parser can de-tokenise them.
                // std::cout <<"function_name: "<<temp_function_name<<", "<<temp_function_data<<"\n", // For debugging purpose only
                temp_function_name.clear(), 
                temp_function_data.clear(), 
                cache_function_name.clear(), // Clean the configurations to prevent any wrong tokenisation
                code = code.substr (i+1), // core manipulation for exact & expected tokens
                i = 0; // reset the i now
        }
        else if (code[i] == ')' and is_function_open) is_function_open = false;
        // Argument processing unit
        else if (is_function_open) temp_function_data += code[i];
        else if (code[i] == '(' and not is_function_open) {
            for (std::size_t x = i-1;true;x--) {
                cache_function_name += code [x];
                if (x == 0) break;
            }
            for (std::size_t y = cache_function_name.length()-1;true;y--) {
                if (cache_function_name[y] == ' ') {} // do nothing
                else temp_function_name += cache_function_name [y];
                if (y == 0) break;
            }
            is_function_open = true;
            // std::cout<<"function found: "  << temp_function_name<<"\n";  // For Debiggung Purpose only      
        }

    }
    return tokens;
}


void function (std::string name, std::string arg){
    if (name == "show_logs"){
        if (show_logs) std::cout << "Function -> Setting the show_logs to "<<arg<<"\n";
        if (arg == "true") show_logs = true;
        else if (arg == "false") show_logs = false;
        else std::cout<<"Error _> Function Err: show_logs can only understand boolean values (true/false)\n", std::exit (3);
    }
    else if (name == "source_path"){
        if (show_logs) std::cout << "Function -> Setting the source_path to "<<arg<<"\n";
        SRC_PATH=arg;
    }
    else if (name == "extension"){
        if (show_logs) std::cout << "Function -> Setting the extension to "<<arg<<"\n";
        EXTENSION=arg;
    }
    else if (name == "output"){
        if (show_logs) std::cout << "Function -> Setting the output to "<<arg<<"\n";
        OUTPUT = arg;
    }
    else if (name == "include"){
        if (show_logs) std::cout << "Function -> Setting the include to "<<arg<<"\n";
        INCLUDE+="LIBXINC "+SRC_PATH+"/"+arg+"."+EXTENSION+"\n";
    }
    else if (name == "output_directory"){
        if (show_logs) std::cout << "Function -> Setting the output_directory to "<<arg<<"\n";
        std::ifstream directory (arg+"/dirconfig.mklib");
        if (not directory.is_open()) std::system (std::string ("mkdir " + arg).c_str());
        else std::system (std::string ("rm -rf "+ arg+"/dirconfig.mklib").c_str());
        OUT_DIR=arg;
    }
    else if (name == "make"){
        if (is_IR_Made)
        {
            if (show_logs) std::cout << "Function -> Updating the IR (Intermediate Reprensentation) "<<"\n";
            IR+="SIGNAL " + OUTPUT + "." + EXTENSION + "\n"
                + INCLUDE +
                "SIGN-SIGNAL\n";
        }
        else {
            if (show_logs) std::cout << "Function -> Making the IR (Intermediate Reprensentation) "<<"\n";
            IR="SIGNAL " + OUTPUT + "." + EXTENSION + "\n"
               + INCLUDE + 
               "SIGN-SIGNAL\n";
            is_IR_Made = true;
        }
        INCLUDE="";
        OUTPUT="libxmklib";
        EXTENSION="";
        if (show_logs) std::cout<<"Generated IR _> \n"<<IR<<"\n";
    }
    else std::cout<<"Error _> Function Err: Unknown function "<<name<<"\n", std::exit (3);
}


void executer (){
    std::stringstream irstream(IR);
    std::string temp;
    std::string signal, libxinc;
    std::vector <std::string> files_captured = {};
    while (std::getline(irstream, temp)){
        // std::cout<<temp<<"\n";
        if (show_logs) std::cout <<"Executer -> De-Tokenising the IR "<<temp<<"\n";
        std::string temp_name, temp_arguments;
        temp_name = temp.substr(0, temp.find(" "));
        temp_arguments = temp.substr(temp.find(" ")+1);
        
        if (show_logs) std::cout <<"Executer -> Executing the temps ["<<temp_name<<","<<temp_arguments<<"]\n";
        if (temp_name == "SIGNAL"){
            if (show_logs) std::cout <<"Executer -> Making the SIGNAL "<<temp_arguments<<"\n";
            signal = temp_arguments;
        }
        
        else if (temp_name == "LIBXINC"){
            if (show_logs) std::cout <<"Executer -> Checking the includes for "<<temp_arguments<<"\n";
            bool is_file_captured = false;
            for (std::size_t i = 0;i < files_captured.size();i++){
                if (files_captured[i] == temp_arguments) is_file_captured = true;
            }
            if (is_file_captured) std::cout <<"Warning _> Executer IO: File "<<temp_arguments<<" was already processed!, Ignoring it now.\n";
            else {
                std::ifstream i_include (temp_arguments); // input includes
                if (not i_include.is_open()) std::cout <<"Error _> Executer Err: included file <"<<temp_arguments<<"> was not found.\n\nCritical IO Error found: Can-not ignore this error.\n", std::exit ( 3 );

                std::string temp_file_data = "";
                while (std::getline (i_include, temp_file_data)) libxinc += temp_file_data + "\n";
                files_captured.push_back (temp_arguments);
            }
        }

        else if (temp_name == "SIGN-SIGNAL") {
            if (show_logs) std::cout << "Signing the signal "<<signal<<"\n...";
            std::ofstream sign_signal_out_file (OUT_DIR+"/"+signal);
            sign_signal_out_file<<libxinc;
            if (show_logs) std::cout <<"Done!\nClosing the signal "<<signal<<"!";
            signal =  "";
            libxinc = "";
            files_captured.clear();
            if (show_logs) std::cout <<"The signal was closed successfully\n\nThe Library was successully created!\n";
        }

    }
}


void parser (std::vector <std::string> tokens){
    for (std::size_t i = 0;i < tokens.size();i++) {
        // std::cout<<tokens[i]<<"\n";
        if (show_logs) std::cout << "Parser -> Processing the token ["<<tokens[i]<<"] token number, "<< i<<"\n"
                                 << "Parser -> Making the valid token...\n";
        // Function processing
        std::string valid_token = "";
        for (std::size_t x = 0;x < tokens[i].length();x++){
            if (tokens[i][x] == '\n') {}
            else valid_token += tokens[i][x];
        }
        if (show_logs) std::cout << "Parser -> Done processing valid token which is ["<<valid_token<<"] token number, "<< i<<"\n";
        function (valid_token.substr(0, valid_token.find(":")), valid_token.substr(valid_token.find(":")+1));
    }
    if (show_logs) std::cout <<"Parser -> Parsing the IR (Intermediate Representation) to the executer...\n";
    executer();
}



int main (int argc, char * argv[]){
    if (argc == 2 and (std::string(argv[1]) == "--version" or std::string (argv[1]) == "-v")) std::cout <<"MKLIB 1.0 (Community Edition)\n\n", std::exit ( 3 );
    if (argc == 2 and (std::string(argv[1]) == "--help" or std::string (argv[1]) == "-h")) std::cout <<"MKLIB 1.0 (Community Edition) - Help\n\n"
                                                                                                     <<"Standard Usage-> mklib in the directory with build.mklib file or mklib path/to/build.mklib/file or mklib --version , -v for version and mklib --help, -h for help\n", std::exit ( 3 );
    // std::cout <<"Exec...\n";
    // std::string temp = "", code = "";
    // std::ifstream file ("example/build.mklib");
    // while (std::getline(file, temp)) code += temp + "\n";
    // std::vector <std::string> a = lexer (code);
    // parser (a);
    if (argc == 2 and not (std::string(argv[1]) == "--version" or std::string (argv[1]) == "-v") and not (std::string(argv[1]) == "--help" or std::string (argv[1]) == "-h")) {
        std::string temp = "", code = "";
        std::ifstream file (std::string(argv[1]) + "/build.mklib");
        if (not file.is_open()) std::cout <<"Error _> File IO Err: No build file was found at the specified path\n.", std::exit ( 3 );
        while (std::getline(file, temp)) code += temp + "\n";
        parser (lexer (code));
        std::exit ( 3 );
    }

    std::string temp = "", code = "";
    std::ifstream file ("build.mklib");
    if (not file.is_open()) std::cout <<"Error _> File IO Err: No build file was found at the specified path\n.", std::exit ( 3 );
    while (std::getline(file, temp)) code += temp + "\n";
    parser (lexer (code));

    
}

// Entier project finished at 5:45pm friday, 28th feb 2025