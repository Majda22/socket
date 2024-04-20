#ifndef MED_H
#define MED_H
int add(int a,int b);
extern char polyGenerateur[6]; // Polynome Generateur: x^4+x+1
extern char tmp[6] ;
extern int mine;


void CrcTrasnfert(char * trame,char *message);
int CrcRecieve(char *msgShouldBeSent);
void exor(char *polyGenerateur, char * tmp);
void decaler(char *tmp, char nexBit);
void GetMessage(char * msgSansFanion,int msgLength,char * trame);
void MultiParPolyGenerateur(char * msgSansFanion,int msgLength);
void concatainerRest(char* msgSansFanion, char * rest ,char * message, int);
void complateTrame(char *msgShouldBeSent,char* trame);
void Division(char *dividende,char * trame);
int checkRest(char *tmp);
void GetMessagePlusRest(char * msgPlusRest,int messageLength,char * trame);
#endif
