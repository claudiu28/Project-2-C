// validare.c
#include <string.h>
#include "validare.h"
// validare input pentru date
int validare_data(int zi , int luna, int an){
    if((zi >= 1 && zi <= 30) && (luna >= 1 && luna <= 12) && (an >= 1900 && an <= 2030)){
        return 1;
    }
    return 0;
}

int validare_caractere(char* p){
    if (strcmp(p,"") == 0){
        return 0;
    }
    return 1;
}

int validare_username(char *username){
    if (strcmp(username,"") == 0) return 0;
    if (strlen(username) < 1 || strlen(username) > 255) return 0;
    return 1;
}

int validare_password(char *password){
    if(strcmp(password, "") == 0) return 0;
    if (strlen(password) < 1 || strlen(password) > 100) return 0;
    return 1;
}

int validare_firstname(char *firstname){
    if (strcmp(firstname,"") == 0) return 0;
    if (strlen(firstname) < 1 || strlen(firstname) > 255) return 0;
    return 1;
}

int validare_lastname(char *lastname){
    if (strcmp(lastname, "") == 0) return 0;
    if (strlen(lastname) < 1 || strlen(lastname) > 255) return 0;
    return 1;
}

int validare_tip_cont(char *tip){
    if(strcmp(tip, "credit") == 0) return 1;
    if(strcmp(tip, "normal") == 0) return 1;
    if(strcmp(tip, "economii") == 0) return 1;
    return 0;
}