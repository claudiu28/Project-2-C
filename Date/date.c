// date.c
#include "../Validare/validare.h"
#include <windows.h>
#include <stdio.h>
#include "../Conturi/structuri.h"
#include "../Design/design.h"
#include "../Meniuri/meniuri.h"
#include "date.h"

int numar_accounts = 0;
int numar_users = 0;

int register_new_user(char* username, char* f_name, char* l_name,char *pwd, char *vpwd, int zi, int luna, int an){
    // Inregistreaza un nou utilizator. Returneaza 1 daca este cu succes, altfel 0.
    // Logica de asignare:
    if (validare_data(zi, luna, an) == 1 && validare_caractere(username) && validare_caractere(f_name) &&
            validare_caractere(l_name)){
        strcpy(accounts[numar_accounts].Info_User[0].username, username);
        strcpy(accounts[numar_accounts].Info_User[0].first_name, f_name);
        strcpy(accounts[numar_accounts].Info_User[0].last_name, l_name);
        strcpy(accounts[numar_accounts].Info_User[0].password, pwd);
        strcpy(accounts[numar_accounts].Info_User[0].verify_password, vpwd);
        accounts[numar_accounts].Info_User[0].User_BDay.day = zi;
        accounts[numar_accounts].Info_User[0].User_BDay.month = luna;
        accounts[numar_accounts].Info_User[0].User_BDay.year = an;
        return 1;
    }
    return 0;
}

int logging_account(char* username, char* pwd, char* vpwd){
    // Incearca sa logheze un cont. Returneaza indexul contului daca este cu succes, altfel -1. Logica de logare:
    for(int i = 0; i < numar_accounts + 1; ++i){
        if(strcmp(accounts[i].Info_User[0].username, username) == 0 && strcmp(accounts[i].Info_User[0].password, pwd) == 0 && strcmp(accounts[i].Info_User[0].password, vpwd) == 0){
            return i;
        }
    }
    return -1;
}

int forgive_password(char *username, char *f_name, char *l_name){
    // Incearca sa recupereze o parola in baza numelui de utilizator si a numelui. Returneaza indexul contului daca este gasit, altfel -1.
    for (int i  = 0; i < numar_accounts + 1; ++i){
        if (strcmp(accounts[i].Info_User[0].username, username) == 0 && strcmp(accounts[i].Info_User[0].first_name, f_name) == 0 && strcmp(accounts[i].Info_User[0].last_name, l_name) == 0){
            return i;
        }
    }
    return -1;
}

int delete_cont(char* username, char* f_name, char* pwd, char* vpwd){
    // Sterge un cont. Returneaza noua cantitate de conturi daca este cu succes, altfel -1.
    for (int i = 0; i < numar_accounts + 1; ++i){
           if(strcmp(accounts[i].Info_User[0].username, username) == 0 && strcmp(accounts[i].Info_User[0].first_name, f_name) == 0 && strcmp(accounts[i].Info_User[0].password, vpwd) == 0 &&
                   strcmp(accounts[i].Info_User[0].password, pwd) == 0){
               for(int j = i; j < numar_accounts; ++j){
                   accounts[j] = accounts[j + 1];
               }
               return numar_accounts - 1;
           }
    }
    return -1;
}

// Stergerea a unui cont.
void StergereCont() {
    char username[255], f_name[255], pwd[100], vpwd[100];

    username_text();
    read_string(username, sizeof(username));
    if (validare_username(username) == 0) {
        printf("Username invalid!\n");
        return;  
    }

    first_name_text();
    read_string(f_name, sizeof(f_name));
    if (validare_firstname(f_name) == 0) {
        printf("Numele este invalid!\n");
        return;  
    }

    parola_text();
    read_string(pwd, sizeof(pwd));
    if (validare_password(pwd) == 0) {
        printf("Parola invalida!\n");
        return;  
    }

    parola_verificare_text();
    read_string(vpwd, sizeof(vpwd));
    if (strcmp(pwd, vpwd) != 0) {
        printf("Verificarea parolei a esuat!\n");
        return;  
    }

    int numar = delete_cont(username, f_name, pwd, vpwd);

    if (numar != -1) {
        numar_accounts = numar;
        printf("Stergere contului reusita cu succes!\n");
    } else {
        printf("Stergerea contului nu a reusit!\n");
    }
}

// Logarea unui cont
void LogareUser() {
    char username[255], pwd[100], vpwd[100], tp_account[100];
    
    username_text();
    read_string(username, sizeof(username));
    if (validare_username(username) == 0) {
        printf("Username invalid!\n");
        return;  
    }


    parola_text();
    read_string(pwd, sizeof(pwd));
    if (validare_password(pwd) == 0) {
        printf("Parola invalida!\n");
        return;  
    }

    parola_verificare_text();
    read_string(vpwd, sizeof(vpwd));
    if (strcmp(pwd, vpwd) != 0) {
        printf("Verificarea parolei a esuat!\n");
        return;  
    }

    if(logging_account(username, pwd, vpwd) != -1){
        system("cls");
        printf("Utilzatorul s-a putut conecta cu succes!!!\n");
        type_account();
        read_string(tp_account, sizeof(tp_account));
        if (validare_tip_cont(tp_account) == 0) {
            printf("Tipul contului este invalid!\n");
            return;  
        }
        system("cls");

        
        strcpy(accounts[numar_accounts].Info_User[accounts[numar_accounts].numar_tip].type_account, tp_account);
        accounts[numar_accounts].numar_tip++;
        functionalitati_meniu_activat(numar_accounts);
        numar_accounts++;

    }else{
        printf("Nu s-a putut autentifica!!!\n");
    }
}

// Recuperare parola unui cont
void RecuperareParola() {
    char username[100],f_name[100], l_name[100];
    username_text();
    read_string(username, sizeof(username));
    if (validare_username(username) == 0) {
        printf("Username invalid!\n");
        return;  
    }

    first_name_text();
    read_string(f_name, sizeof(f_name));
    if (validare_firstname(f_name) == 0) {
        printf("Numele este invalid!\n");
        return;  
    }

    last_name_text();
    read_string(l_name, sizeof(l_name));
    if (validare_firstname(l_name) == 0) {
        printf("Prenumele este invalid!\n");
        return;  
    }

    int index = forgive_password(username, f_name, l_name);
    if(index != -1){
        printf("Parola este:%s\n", accounts[index].Info_User[0].password);
        Sleep(5000); // 5 seconds
        LogareUser();
    }else{
        printf("Nu s-a gasit acest utilzator!!");
    }

}

// Asignare unui cont
void InregistrareUser() {
    char username[100], f_name[100], l_name[100], pwd[100], vpwd[100];
    int zi, luna, an;

    username_text();
    read_string(username, sizeof(username));
    if (validare_username(username) == 0) {
        printf("Username invalid!\n");;
        return;  
    }

    first_name_text();
    read_string(f_name, sizeof(f_name));
    if (validare_firstname(f_name) == 0) {
        printf("Nume invalid!\n");
        return;  
    }

    last_name_text();
    read_string(l_name, sizeof(l_name));
    if (validare_lastname(l_name) == 0) {
        printf("Prenume invalid!\n");
        return;  
    }

    parola_text();
    read_string(pwd, sizeof(pwd));
    if (validare_password(pwd) == 0) {
        printf("Parola invalida!\n");
        return;  
    }

    parola_verificare_text();
    read_string(vpwd, sizeof(vpwd));
    if (validare_password(vpwd) == 0) {
        printf("Verificare parolei a esuat!\n");
        return;  
    }

    data_nastere_text();
    scanf("%d %d %d", &zi, &luna, &an);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    if(validare_data(zi,luna,an) == 0){
        printf("Datele sunt gresit introduse!\n");
    }


    if(register_new_user(username, f_name, l_name, pwd, vpwd, zi, luna, an) == 1){ 
        system("cls");
        printf("S-a creat cu succes utilzatorul nou!!!\n");
        LogareUser();
    }else{
        printf("Utilzatorul nu s-a putut creea cu succes!!!\n");
    }
}