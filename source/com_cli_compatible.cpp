/**
   @date 2019/05/21
   @version 2.1
**/
#include "com.h"
#include "cli.h"
#include "com_cli.hpp"

#include <cstring>

template <typename T>
void CLread(char* text, T* ptr)
{
    com_cli::read_value<T>((std::string)text, ptr);
}
template void CLread<int>(char* text, int* ptr);
template void CLread<unsigned int>(char* text, unsigned int* ptr);
template void CLread<unsigned short int>(char* text, unsigned short int* ptr);
template void CLread<short int>(char* text, short int* ptr);
template void CLread<long int>(char* text, long int* ptr);
template void CLread<float>(char* text, float* ptr);
template void CLread<double>(char* text, double* ptr);
void CLintrd(char *prompt, int *value)
{
    com_cli::read_value<int>((std::string)prompt, value);
}
void CLintrdL(char *prompt, int *value, [[maybe_unused]] int lower, [[maybe_unused]] int upper)
{
    com_cli::read_value<int>((std::string)prompt, value);
}
void CLintrdX(char *prompt, int *value, [[maybe_unused]] char *text, [[maybe_unused]] int text_size)
{
    com_cli::read_value<int>((std::string)prompt, value);
}
void CLhexrd(char *prompt, int *value)
{
    com_cli::read_value<int>((std::string)prompt, value);
}
void CLhexrdL(char *prompt, int *value, int lower, int upper)
{
}
void CLhexrdX(char *prompt, int *value, char *text, int text_size)
{
}
void CLfltrd(char *prompt, float *value)
{
    com_cli::read_value<float>((std::string)prompt, value);
}
void CLfltrdL(char *prompt, float *value, [[maybe_unused]] double lo, [[maybe_unused]] double hi)
{
    com_cli::read_value<float>((std::string)prompt, value);
}
void CLfltrdX(char *prompt, float *value, [[maybe_unused]] char *text, [[maybe_unused]] int text_size)
{
    com_cli::read_value<float>((std::string)prompt, value);
}
void CLfdprd(char *prompt, double *value)
{
    com_cli::read_value<double>((std::string)prompt, value);
}
void CLfdprdL(char *prompt, double *value, [[maybe_unused]] double lower, [[maybe_unused]] double upper)
{
    com_cli::read_value<double>((std::string)prompt, value);
}
void CLfdprdX(char *prompt, double *value, [[maybe_unused]] char *text, [[maybe_unused]] int text_size)
{
    com_cli::read_value<double>((std::string)prompt, value);
}
void CLtxtrd(char *prompt, char *text, [[maybe_unused]] int text_size)
{
    std::string strtext(text);
    com_cli::read_value<std::string>((std::string)prompt, &strtext);
    strcpy(text, strtext.c_str());
}
void CLtitrd(char *prompt, char *text, [[maybe_unused]] int text_size)
{
    std::string strtext(text);
    com_cli::read_text((std::string)prompt, &strtext);
    strcpy(text, strtext.c_str());
}
void CLlogrd(char *prompt, int *value)
{
    com_cli::ask_yesno((std::string)prompt, (bool*)value);
}
void CLkeyrd([[maybe_unused]] int mode, char *prompt, char *word, char **table, int ntable, int *choice, [[maybe_unused]] int word_size)
{
    using namespace std;
    vector<string> strtable;
    for(int i=0; i<ntable; ++i){
	strtable.emplace_back((std::string)table[i]);
    }
    com_cli::read_keyword((std::string)prompt, strtable, choice);
}
void CMinicom(char *prompt)
{
    com_cli::init((std::string)prompt, "");
}
