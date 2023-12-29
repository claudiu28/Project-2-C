#ifndef STRUCTURI_H
#define STRUCTURI_H

#define MAX_ACCOUNTS 100
#define INFO_USER 100
#define NUM_TRANSACTION 100

// Structura pentru tranzactii
typedef struct {
    float value; // Valoarea tranzactiei
    char type[100]; // Tipul tranzactiei 
    char description[100]; // Descrierea tranzactiei
} transaction;

// Structura pentru data nasterii utilizatorului
typedef struct {
    int day, month, year; // Ziua, luna, anul
} b_day_user;

// Structura pentru informatii despre utilizator
typedef struct {
    char username[255]; // Numele de utilizator
    char first_name[255]; // Prenumele utilizatorului
    char last_name[255]; // Numele de familie al utilizatorului
    char password[100]; // Parola
    char verify_password[100]; // Verificare parola
    b_day_user User_BDay; // Data nasterii
    char type_account[100]; // Tipul de cont 
    int transaction_num; // Numarul de tranzactii
    float total_value; // Valoarea totala a contului
    transaction transaction_value[NUM_TRANSACTION]; // Tranzactiile utilizatorului
} info_user;

// Structura pentru conturile bancare
typedef struct {
    int numar_tip; // Numarul de tipuri de conturi
    info_user Info_User[INFO_USER]; // Informatiile utilizatorilor
} account;

extern account accounts[MAX_ACCOUNTS]; // global

#endif
