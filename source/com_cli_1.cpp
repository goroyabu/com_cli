/**
   @file com_cli_1.cpp
   @author Goro Yabu                                                                                                                      
   @date 2019/03/18                                                                                                                    
   @version 2.0                                                                                                                        
**/
#include "com_cli.hpp"
#include "com_cli_private.hpp"
/** 
    @brief Initialization
**/
int com_cli::init(std::string prompt, std::string his_name)
{
    using namespace com_cli_private;
    //gPrompt = prompt;
    set_progname(prompt);
    using_history();
    //gHistoryFile = his_name;
    set_historyfile(his_name);
    read_history( his_name.c_str() );
    rl_bind_key('\t',rl_complete);
    
    return CLI_OK;
}
/**
   @brief 
**/
int com_cli::end()
{
    using namespace com_cli_private;
    write_history( get_historyfile().c_str() );
    return CLI_OK;
}
/**
   @brief Read a value from standard input.
   @param[in] quest Question or description of value for app users.
   @param[in,out] value A variable modifed to new input value.
**/
template<typename T> int com_cli::read_value(std::string quest, T* value)
{
    T buf = *value;
    std::stringstream ss; ss << *value;
    std::string line = ss.str();
    
    com_cli::com_cli_private::get_line(quest, &line);
    try{
	std::istringstream(line) >> *value;
	return CLI_OK;
    }
    catch(std::exception &e){
	*value = buf;
	return CLI_NG;
    }
}
template int com_cli::read_value<int>(std::string quest, int* value);
template int com_cli::read_value<float>(std::string quest, float* value);
template int com_cli::read_value<double>(std::string quest, double* value);
template int com_cli::read_value<std::string>(std::string quest, std::string* value);
int com_cli::read_text(std::string quest, std::string* text)
{
    com_cli_private::get_line(quest, text);
    return CLI_OK;
}
int com_cli::ask_yesno(std::string quest, bool* yes)
{
    std::string default_answer;
    if(*yes) default_answer = "yes";
    else default_answer = "no";
    
    quest = quest+"(y/n)";
    std::string answer = default_answer;
    read_value<std::string>(quest, &answer);
    if(answer=="yes" || answer=="y" || answer=="YES" || answer=="Y"){
	*yes = true;
    }else if(answer=="no" || answer=="n" || answer=="NO" || answer=="N"){
	*yes = false;
    }
    
    return CLI_OK;
}

template<typename T> int com_cli::read_value(std::string quest, std::vector<std::string> table, std::vector<T>* value)
{
    using namespace std;
    using namespace com_cli::com_cli_private;

    int ntab = (int)table.size();
    int nval = (int)value->size();
    if(nval<=0 || nval!=ntab) return com_cli::CLI_NG;
    cout << " " << quest << endl;
    cout << endl;

    for(int i=0; i<nval; ++i){
        read_value<T>(table[i], &(*value)[i]);
    }
    return com_cli::CLI_OK;
}
template int com_cli::read_value<int>(std::string quest, std::vector<std::string> table, std::vector<int>* value);
template int com_cli::read_value<float>(std::string quest, std::vector<std::string> table, std::vector<float>* value);
template int com_cli::read_value<double>(std::string quest, std::vector<std::string> table, std::vector<double>* value);
template int com_cli::read_value<std::string>(std::string quest, std::vector<std::string> table, std::vector<std::string>* value);

int com_cli::read_keyword(std::string quest, std::vector<std::string> table, int* answer)
{
    std::vector<int> vanswer(1, *answer); int nreply = 1;
    if( read_keyword(quest, table, nreply, &vanswer)==com_cli::CLI_NG ) return com_cli::CLI_NG;
    if( vanswer.size()<=0 ) return com_cli::CLI_NG;
    *answer = vanswer[0];
    return com_cli::CLI_OK;
}
/**
   @param quest
   @param table Table of string
   @param nreply This function tries to pick-up exactly nreply answers when nreply>0, and equal to or more than nreply when nreply<=0.
   @param answer Array of index that corresponding to elements of options
**/
int com_cli::read_keyword(std::string quest, std::vector<std::string> table, int nreply, std::vector<int>* answer)
{
    using namespace std;
    namespace ccp = com_cli::com_cli_private;

    com_cli::enable_custom_complete();
    com_cli::set_candidates(table);
    
    string prompt = ccp::get_progname();
    if(prompt.size()!=0) prompt = prompt+": ";
    stringstream ss;    
    if(nreply<=0) ss << prompt << "Select " << setw(3) << -nreply << " or More, Then OK";
    else ss << prompt << "Select " << setw(3) << nreply << " Option";

    
    string line; int nwords; vector<string> words;
    while(true){	
        line = ""; nwords = 0; words.clear();
	
        if( com_cli::show_keyword(quest, table)==com_cli::CLI_NG )
	    return com_cli::cli_error(2, "com_cli::read_keyword", "Size of table <= 0");
	cout << endl;
	cout << ss.str() << endl;
        ccp::get_line("", &line);
	ccp::word_split(line, &words);
	
        nwords = (int)words.size();
        if(nwords<=0) continue;

	if(nreply>0 && nwords==nreply) break;
	
	com_cli::to_upper(&words[nwords-1]);
        if(nreply<=0 && strcmp(words[nwords-1].c_str(),"OK")==0) break;
	
        cout << endl;
    }
    
    int itemp; answer->clear();
    for(auto word : words){
        if(com_cli::find_keyword(table, word, &itemp)==com_cli::CLI_OK) answer->push_back(itemp);
    }
    com_cli::disable_custom_complete();
    cout << endl;

    if((int)answer->size()!=nreply) return com_cli::CLI_NG;
    return com_cli::CLI_OK;
}
int com_cli::find_keyword(const std::vector<std::string>& table, std::string word, int* index)
{
    std::string elem_up = word; com_cli::to_upper(&elem_up);
    int ntab = table.size(); *index = ntab;    
    for(int i=0; i<ntab; ++i){
        std::string buf = table[i]; com_cli::to_upper(&buf);
        if( strcmp(elem_up.c_str(),buf.c_str())==0 ){ *index = i; return CLI_OK; }
    }
    return com_cli::CLI_NG;
}
int com_cli::show_keyword(std::string message, const std::vector<std::string>& table)
{
    using namespace std;
    cout << " " << message << endl; cout << endl;
    
    int nopt = (int)table.size();
    stringstream ss; ss << " ";
    int ss_line = 0;
    
    for(int i=0; i<nopt; ++i){
        if(ss.str().length()+table[i].length()-ss_line*44>44){ ss << "\n " << table[i]+" "; ss_line++;}
	else ss << table[i]+" ";
    }
    cout << ss.str() << endl;
    return com_cli::CLI_OK;
}
