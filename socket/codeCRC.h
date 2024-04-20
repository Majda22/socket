#pragma message("Inclusion de codeCRC.h")

#ifdef CODE_CRC
#define CODE_CRC

char polyGenerateur[6]; // Polynome Generateur: x^4+x+1
char tmp[6] ;
int mine=5;
/* Definir les prototypes des fonctions */
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
/* Definir les prototypes des fonctions */

#endif //code CRC

