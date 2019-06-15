/**
   @file cli.h
   @author Goro Yabu
   @date 2019/06/15
   @version 1.0
**/
#ifndef cli_h
#define cli_h

template <typename T> void CLread(char* text, T* ptr);
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

#endif
