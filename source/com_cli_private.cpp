/**
   @file com_cli_private.cpp
   @author Goro Yabu
   @date 2019/06/13
   @version 2.0
**/
#include "com_cli_private.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>

namespace com_cli
{
    namespace com_cli_private
    {
	std::string gHistoryFile = "~/.cli_history";
	std::string gProgName = ">";
	std::vector<std::string> gLineBuffer;
    }
}
namespace ccp = com_cli::com_cli_private;
void com_cli::com_cli_private::set_progname(std::string progname)
{
    gProgName = progname;
}
void com_cli::com_cli_private::set_historyfile(std::string historyfile)
{
    gHistoryFile = historyfile;
}
std::string com_cli::com_cli_private::get_progname()
{
    return gProgName;
}
std::string com_cli::com_cli_private::get_historyfile()
{
    return gHistoryFile;
}
/**
   @brief Split a line into each words and output as a vector of strings
   @param[in] line Input string
   @param[out] out A vector of words in the line
   @param[in] delim Default delimitator is space
**/
int com_cli::com_cli_private::word_split(std::string line, std::vector<std::string>* out, std::string delim)
{
    using namespace std;
    stringstream ss(line);
    string word;
    while( getline(ss, word, delim.c_str()[0]) ){
        out->push_back(word);
    }
    return CLI_OK;
}
/**
   @brief Get 1 line from interactive interface
   @param[in] quest Question or Instruction for user
   @param[out] line
**/
int com_cli::com_cli_private::get_line(std::string quest, std::string* line)
{
    using namespace std;
    string prompt=">";
    ccp::make_prompt(quest, *line, &prompt);

    if( ccp::gLineBuffer.size()!=0 ){
        *line = ccp::gLineBuffer[0];
        cout << prompt << *line << endl;
	ccp::gLineBuffer.erase(ccp::gLineBuffer.begin());
    }else{
	//cout << prompt;
        //*line = readline("");// prompt.c_str() );
	*line = (string)readline( prompt.c_str() );
	com_cli::remove_comment(line);
	com_cli::erase_endspace(line);
        add_history(line->c_str());
    }

    while(true){
        int status = CLI_OK;
        if( line->substr(0,1)=="@" ){
            status = ccp::load_command(line);
        }else break;
        if(status!=CLI_OK) break;
    }
    return CLI_OK;
}
int com_cli::com_cli_private::make_prompt(std::string quest, std::string answer, std::string* prompt)
{
    com_cli::erase_endspace(&quest);
    if(quest=="") { *prompt = " > "; return CLI_OK; }
    if(answer!="") *prompt = " "+quest + " : " + answer + " ? ";
    //else *prompt = " "+quest+"\n"+ccp::get_progname()+"> ";
    else *prompt = " "+quest+" > ";
    return CLI_OK;
}
/*
  @param[in,out] command Command including a name of .com file. Return the first line in .com file.
*/
int com_cli::com_cli_private::load_command(std::string* command)
{
    using namespace std;
    string filename;
    if(command->substr(0,1)=="@") filename = command->substr(1, command->size()-1);
    com_cli::erase_endspace(&filename);

    ifstream ifs(filename);
    if(ifs.fail()) return cli_error(2, "load_command", "Command file "+filename+" is not found.");

    vector<string> temp_buffer = ccp::gLineBuffer;
    ccp::gLineBuffer.clear();
    int i = 0; string str;
    while( getline(ifs, str) ){
	com_cli::remove_comment(&str);
        if(i==0) *command = str;
        else ccp::gLineBuffer.push_back(str);
        i++;
    }
    for(auto buf : temp_buffer) ccp::gLineBuffer.push_back(buf);

    return com_cli::CLI_OK;
}







