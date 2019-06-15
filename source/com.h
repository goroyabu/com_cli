/**
   @file com.h
   @author Goro Yabu
   @date 2019/06/15
   @version 1.0
**/
#ifndef com_h
#define com_h

void CMchval(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
void CMinicom(char *prompt);
void CMcrange(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
void CMinquir(char *quest, int nval, char *names[], char *help[], int nreply, int lord[]);
void CMmodbit(char *quest, int nbits, char *names[], char *help[], int *bits);
void CMmodval(char *quest, int nval, char *names[], char *help[], char *vartyp, void *array);
void CMshowit(char *quest, int nval, char *names[], char *help[]);
void CMswitch(char *quest, int nval, char *names[], char *help[], char *vartyp, int array[]);

#endif
