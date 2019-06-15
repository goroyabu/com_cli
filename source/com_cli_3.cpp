/**
   @file com_cli_3.cpp
   @author Goro Yabu
   @date 2019/03/18
   @version 2.0
**/
#include "com_cli.hpp"
#include "com_cli_private.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>

int com_cli::cli_error(int level, std::string place, std::string message)
{
    if(level==0){
	std::cout << "CLI-Information in ";
    }else if(level==1){
	std::cout << "CLI-WARNING in ";
    }else if(level==2){
	std::cout << "CLI-ERROR in ";
    }
    std::cout << place << " : " << message << std::endl;
    return CLI_NG;
}
int com_cli::to_upper(std::string* str)
{
    std::transform(str->begin(), str->end(), str->begin(), ::toupper);
    return CLI_OK;
}
int com_cli::to_upper(char* str)
{
    for(int i=0;i<=(int)strlen(str);i++){
	if(str[i]>=97&&str[i]<=122) str[i]=str[i]-32;
    }
    return CLI_OK;
}
int com_cli::erase_endspace(std::string* str)
{
    while( *str->rbegin()==' ' || *str->rbegin()=='\t' ) str->erase( str->size()-1 );
    return CLI_OK;
}
int com_cli::remove_comment(std::string* str, std::string sign)
{
    std::string temp = *str;
    int pos_sign = str->find(sign);
    if( pos_sign<0 ) return CLI_OK;
    *str = temp.substr(0, pos_sign);
    return CLI_OK;
}
int com_cli::is_only_integer(std::string& str)
{
    try { [[maybe_unused]] int n = std::stoi(str); }
    catch (std::exception &e) { return CLI_NG; }
    return CLI_OK;
}
