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
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

#include <readline/readline.h>
#include <readline/history.h>

namespace com_cli
{
    const int CLI_OK = 0;
    const int CLI_NG = -1;
    
    /**
       Basic Functions
    **/
    
    /* For Setting */
    int init(std::string progname, std::string history_file);
    int end();

    /* For Reading */
    template<typename T> int read_value(std::string quest, T* value);
    template<typename T> int read_value(std::string quest, std::vector<std::string> table, std::vector<T>* value);
    int read_keyword(std::string quest, std::vector<std::string> table, int* answer);
    int read_keyword(std::string quest, std::vector<std::string> table, int nreply, std::vector<int>* answer);
    int read_text(std::string quest, std::string* text);
    int ask_yesno(std::string quest, bool* yes);

    /*--------------------*/
    
    /**
       Extended Functions
    **/
    
    /* For Manipulating Strings */
    int to_upper(std::string* str);
    int to_upper(char* str);
    int erase_endspace(std::string* str);
    int remove_comment(std::string* str, std::string sign="#");
    int is_only_integer(std::string& str);
    int find_keyword(const std::vector<std::string>& table, std::string word, int* index);
    
    /* For Show Messages */
    int cli_error(int level, std::string place, std::string message);
    int show_keyword(std::string message, const std::vector<std::string>& table);
    
    /* For Setting of the Custom Tab-Completion */
    int enable_custom_complete();
    int disable_custom_complete();
    template<typename... Arg> int set_candidates(Arg... arg);
    int set_candidates(const std::vector<std::string>& list);

    /*--------------------*/
    
    /**
       Classical Name 
    **/

    /* CLI */
    template <typename T>
    void CLread(const std::string& text, T* ptr);
    void CLintrd(char *prompt, int *value);
    void CLintrdL(char *prompt, int *value, int lower, int upper);
    void CLintrdX(char *prompt, int *value, char *text, int text_size);
    void CLhexrd(char *prompt, int *value);
    void CLhexrdL(char *prompt, int *value, int lower, int upper);
    void CLhexrdX(char *prompt, int *value, char *text, int text_size);
    void CLfltrd(char *prompt, float *value);
    void CLfltrdL(char *prompt, float *value, double lo, double hi);
    void CLfltrdX(char *prompt, float *value, char *text, int text_size);
    void CLfdprd(char *prompt, double *value);
    void CLfdprdL(char *prompt, double *value, double lower, double upper);
    void CLfdprdX(char *prompt, double *value, char *text, int text_size);
    void CLtxtrd(char *prompt, char *text, int text_size);
    void CLtitrd(char *prompt, char *text, int text_size);
    void CLlogrd(char *prompt, int *value);
    void CLkeyrd(int mode, char *prompt, char *word, char **table, int ntable, int *choice, int word_size);

    /* COM */
    void CMchval(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
    void CMinicom(char *prompt);
    void CMcrange(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
    void CMinquir(char *quest, int nval, char *names[], char *help[], int nreply, int lord[]);
    void CMmodbit(char *quest, int nbits, char *names[], char *help[], int *bits);
    void CMmodval(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
    void CMshowit(char *quest, int nval, char *names[], char *help[]);
    void CMswitch(char *quest, int nval, char *names[], char *help[], char *vartyp, int array[]);
}
#endif
