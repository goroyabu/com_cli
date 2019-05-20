/**
   @file com_cli_private.hpp
   @author Goro Yabu
   @date 2019/03/18
   @version 2.0
**/
#ifndef com_cli_private_hpp
#define com_cli_private_hpp
#include "com_cli.hpp"

namespace com_cli
{
    namespace com_cli_private
    {
	//extern std::string gHistoryFile;
	//extern std::string gPrompt;
	void set_progname(std::string progname);	
	void set_historyfile(std::string historyfile);
	std::string get_progname();
	std::string get_historyfile();

	/* clword.f */
	int get_word(std::string line, int index, std::string* out);
        int word_split(std::string line, std::vector<std::string>* out, std::string delim=" ");
	
	/* clgetl.f */
	int get_line(std::string quest, std::string* line);
        int make_prompt(std::string quest, std::string answer, std::string* prompt);
	int load_command(std::string* command);
	
	/* readline custom completion */
        char** on_function(const char* text, int start, int end);
        char** off_function(const char* text, int start, int end);
        char* word_generator(const char* text, int state);
	
    }
    
}


#endif

