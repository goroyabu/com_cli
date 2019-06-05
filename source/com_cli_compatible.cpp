/**
   @date 2019/05/21
   @version 2.1
**/
#include "com_cli.hpp"
#include "com_cli_private.hpp"
template <typename T>
void com_cli::CLread(const std::string& text, T* ptr)
{
    read_value<T>(text, ptr);
}
void com_cli::CLintrd(char *prompt, int *value)
{
    read_value<int>((std::string)prompt, value);
}
void com_cli::CLintrdL(char *prompt, int *value, int lower, int upper)
{
}
void com_cli::CLintrdX(char *prompt, int *value, char *text, int text_size)
{
}
void com_cli::CLhexrd(char *prompt, int *value)
{
    read_value<int>((std::string)prompt, value);
}
void com_cli::CLhexrdL(char *prompt, int *value, int lower, int upper)
{
}
void com_cli::CLhexrdX(char *prompt, int *value, char *text, int text_size)
{
}
void com_cli::CLfltrd(char *prompt, float *value)
{
    read_value<float>((std::string)prompt, value);
}
void com_cli::CLfltrdL(char *prompt, float *value, double lo, double hi)
{
}
void com_cli::CLfltrdX(char *prompt, float *value, char *text, int text_size)
{
}
void com_cli::CLfdprd(char *prompt, double *value)
{
    read_value<double>((std::string)prompt, value);
}
void com_cli::CLfdprdL(char *prompt, double *value, double lower, double upper)
{
}
void com_cli::CLfdprdX(char *prompt, double *value, char *text, int text_size)
{
}
void com_cli::CLtxtrd(char *prompt, char *text, int text_size)
{
    std::string strtext(text);
    read_value<std::string>((std::string)prompt, &strtext);
    text = strdup(strtext.c_str());
}
void com_cli::CLtitrd(char *prompt, char *text, int text_size)
{
    std::string strtext(text);
    read_text((std::string)prompt, &strtext);
    text = strdup(strtext.c_str());
}
void com_cli::CLlogrd(char *prompt, int *value)
{
    ask_yesno((std::string)prompt, (bool*)value);
}
void com_cli::CLkeyrd(int mode, char *prompt, char *word, char **table, int ntable, int *choice, int word_size)
{
    using namespace std;
    vector<string> strtable;
    for(int i=0; i<ntable; ++i){
	strtable.emplace_back((std::string)table[i]);
    }
    read_keyword((std::string)prompt, strtable, choice);
}
