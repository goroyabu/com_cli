/**
   @file com_cli_2.cpp
   @author Goro Yabu
   @date 2019/03/18
   @version 2.0
**/
#include "com_cli.hpp"
#include "com_cli_private.hpp"

namespace com_cli
{
    namespace com_cli_private
    {
	std::vector<char*> gCandidates = {NULL};
    }
}
namespace ccp = com_cli::com_cli_private;

int com_cli::enable_custom_complete()
{
    rl_attempted_completion_function = com_cli_private::on_function;
    return CLI_OK;
}
int com_cli::disable_custom_complete()
{
    rl_attempted_completion_function = com_cli_private::off_function;
    return CLI_OK;
}
int com_cli::set_candidates(const std::vector<std::string>& list)
{
    using namespace std;
    ccp::gCandidates.clear();
    
    for(auto word : list){
        char* cstr = new char[word.size() + 1];
        std::strcpy(cstr, word.c_str() );
	ccp::gCandidates.push_back( strdup(cstr) );
    }

    ccp::gCandidates.push_back(NULL);
    return CLI_OK;
}
template<typename... Arg>
int com_cli::set_candidates(Arg... arg)
{
    using namespace std;
    ccp::gCandidates.clear();

    for(auto word : std::initializer_list<std::string>{arg...}){
        char* cstr = new char[word.size() + 1];
        std::strcpy(cstr, word.c_str() );
	ccp::gCandidates.push_back( strdup(cstr) );
    }

    ccp::gCandidates.push_back(NULL);
    return CLI_OK;
}
template int com_cli::set_candidates<const char*>(const char*);
template int com_cli::set_candidates<const char*, const char*>(const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*>(const char*, const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*, const char* >
(const char*, const char*, const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*, const char*, const char*>
(const char*, const char*, const char*, const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*, const char*, const char*, const char*>
(const char*, const char*, const char*, const char*, const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*, const char*, const char*, const char*, const char*>
(const char*, const char*, const char*, const char*, const char*, const char*, const char*);
template int com_cli::set_candidates<const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*>
(const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*);

/**
@brief readline用の補完関数
@param text インターフェイスから読み込んだ文字列(たぶん)
**/
char** com_cli::com_cli_private::on_function(const char* text, int start, int end)
{
    //std::string t = text;// start = end;//unused
    return rl_completion_matches(text, word_generator);
}
/**
   @brief readline用の補完関数. NULLを返すのでデフォルトの補完だけ行う.
**/
char** com_cli::com_cli_private::off_function(const char* text, int start, int end)
{
    //std::string t = text;// start = end;//unused
    return NULL;
}
/**
   @brief readline用の関数
**/
char* com_cli::com_cli_private::word_generator(const char* text, int state)
{
    using namespace std;
    static int index, wordlen;
    char* name;

    if(state == 0){
        wordlen = strlen(text);
        index = 0;
    }

    string buf(text);
    to_upper(&buf);
    const char* text2 = buf.c_str();

    while( (name = gCandidates[index]) ){
        index++;

        string buf_name(name);
        to_upper(&buf_name);
        const char* name2 = buf_name.c_str();

        if(!strncmp(text2, name2, wordlen)){
            return strdup(name);
        }
    }

    return NULL;
}
