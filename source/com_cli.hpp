/**
   @file com_cli.hpp
   @author Goro Yabu
   @date 2019/03/18
   @version 2.0
**/
#ifndef com_cli_hpp
#define com_cli_hpp

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

#include <readline/readline.h>
#include <readline/history.h>

namespace com_cli
{
    const int CLI_OK = 0;
    const int CLI_NG = -1;
    
    /* for users */
    int init(std::string prompt, std::string history_file);
    int end();
    template<typename T> int read_value(std::string quest, T* value);
    template<typename T> int read_value(std::string quest, std::vector<std::string> table, std::vector<T>* value);
    int read_keyword(std::string quest, std::vector<std::string> table, int* answer);
    int read_keyword(std::string quest, std::vector<std::string> table, int nreply, std::vector<int>* answer);
    int read_text(std::string quest, std::string* text);
    int ask_yesno(std::string quest, bool* yes);
    /* */
    
    int find_keyword(const std::vector<std::string>& table, std::string word, int* index);
    int show_keyword(std::string message, const std::vector<std::string>& table);
    
    /* readline */
    int enable_custom_complete();
    int disable_custom_complete();
    template<typename... Arg> int set_candidates(Arg... arg);
    int set_candidates(std::vector<std::string> list);

    /* misc */
    int cli_error(int level, std::string place, std::string message);
    int to_upper(std::string* str);
    int to_upper(char* str);
    int erase_endspace(std::string* str);
    int remove_comment(std::string* str, std::string sign="#");
    int is_only_integer(std::string& str);    
}
#endif
