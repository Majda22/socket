#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "majda.h"

int mine=5;
char polyGenerateur[6]= "10110"; // Polynome Generateur: x^4+x+1
char tmp[6] ="";

int add(int a,int b){
	printf("%d",a+b);
	printf("%d",mine);
	
}


void exor(char *polyGenerateur, char * tmp){
    /*
        Objectif :cette fonction permet de calculer le xor de 5 premiers bits de PolyGenerateur
        et 5 bit du tmp est stoke le resultat dans tmp.
        Entrer: char *polyGenerateur : le polynome génerateur || char * tmp : chaîne temporaire.
        Sortie: void
     */
	for(int i = 0 ; i<5;i++){
		if(tmp[i]==polyGenerateur[i] ){
			tmp[i] = '0';
		}
		else{
			tmp[i] = '1';
		}
	}
}
void GetMessage(char * msgSansFanion,int msgLength,char * trame){
    /*
        Objectif :cette fonction permet de prendre le message du trame.
        Entrer: char * msgSansFanion:tableau de message || int msgLength: la longeur du msg || char * trame: la trame
        Sortie: void
     */
     printf("%d",mine);
    for(int i=0;i<msgLength;i++){// 8*6 = 48 bits
            msgSansFanion[i] = trame[8*3+i];
        }
}
void MultiParPolyGenerateur(char * msgSansFanion,int msgLength){
    /*
        Objectif :cette fonction permet de multiplier le message par x*4.
        Entrer: char * msgSansFanion:tableau de message || int msgLength: la longeur du msg
        Sortie: void
     */
    for(int i =msgLength;i<msgLength+4;i++ ){
		msgSansFanion[i] ='0';
    }
}
void decaler(char *tmp, char nextBit){
    /*
        Objectif :cette fonction permet de decaler les bits par un bit et ajouter le bite suivant a la fin.
        Entrer: char nextBit : le bit suivant || char * tmp : chaîne temporaire.
        Sortie: void
     */
	for(int i=0; i<4;i++){
		tmp[i] = tmp[i+1];
	}
	tmp[4] = nextBit;
}
void Division(char *dividende,char * trame){
    /*
        Objectif :cette fonction permet de faire la division binaire modulo-2.
        Entrer: char *dividende: le dividende || char * trame :trame.
        Sortie: void
     */
	for(int i=0; i<5;i++){
		tmp[i] = trame[i]; //tmp : this variable take the first 5 bits of the trame without Fanion Octet, for the division with the PolyneGenerator
	}
	tmp[5]='\0';
	for(int i=0;i< strlen(dividende)-strlen(tmp) ;i++){
		if(tmp[0]=='0'){
			decaler(tmp,dividende[5+i]);
		}
		else {
			exor(polyGenerateur,tmp);
			decaler(tmp,dividende[5+i]);
		}}
	if(tmp[0]=='1'){
		exor(polyGenerateur,tmp);

	}
	//Here we Have the Rest of the division in the variable tmp
}
void GetMessagePlusRest(char * msgPlusRest,int messageLength,char * trame){
        /*
        Objectif :cette fonction permet de extraire le (message + rest de la division) du trame.
        Entrer: char * msgPlusRest : msg + rest  || int messageLength :longeur msg|| char * trame;trame
        Sortie: void
        */
        for(int i=0;i<28;i++){
            if(i<messageLength){
                msgPlusRest[i] = trame[8*3+i];// 8*3 PASSE the 3 bytes(fanion ,@dest,cmd)
            }
        }
        msgPlusRest[24]=trame[8*6+4];
        msgPlusRest[25]=trame[8*6+5];
        msgPlusRest[26]=trame[8*6+6];
        msgPlusRest[27]=trame[8*6+7];
        msgPlusRest[28] = '\0';
	}
int CrcRecieve(char *trame){
    /*
        Objectif :cette fonction permet de verifier la validiter d'une trame reçu.
        Entrer: char * trame: la trame
        Sortie: void
    */
	char msgPlusRest[29];
	int messageLength = 24;
    	GetMessagePlusRest(msgPlusRest,messageLength,trame);
	Division(msgPlusRest,trame);
	printf("RECEIVE : \n  Rest  : %s    || MsgPlusRest : %s \n",tmp, msgPlusRest);
	return checkRest(tmp);
}
int checkRest(char *tmp){
	for(int i =0;i<5;i++){
		if(tmp[i]!='0')return 0;
	}
	return 1;
}
void CrcTrasnfert(char * trame,char *msgShouldBeSent){
    /*
        Objectif :cette fonction permet de calculer le reste et l'ajouter à la fin de la trame a envoyer.
        Entrer: char * trame: la trame || char *msgShouldBeSent;msg
        Sortie: void
    */
    char msgSansFanion[8*3+1+4]; // 8*6 + \0 = 49  || +4 bits (X^4 * msgSansFanion)
    int msgLength = 3*8;// 3*8 msglength
    msgSansFanion[8*3]='\0';
    GetMessage(msgSansFanion,msgLength,trame);
    MultiParPolyGenerateur(msgSansFanion,msgLength);
    msgSansFanion[msgLength+4]='\0';
    printf("msgSansFanion : %s \n", msgSansFanion);
    Division(msgSansFanion,trame);
	printf("TRANSFER : \n  Rest  : %s    || msgSansFanion : %s \n",tmp, msgSansFanion);
	for(int i = 0;i<4;i++){
		trame[48+4+i]=tmp[i+1] ;
	}
	printf("Msg Should be send %s \n",trame);
}
