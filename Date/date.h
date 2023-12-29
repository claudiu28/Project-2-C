#ifndef DATE_H
#define DATE_H

// Sterge un cont existent
void StergereCont();

// Logarea a unui utilizator
void LogareUser();

// Recuperare a parolei pentru un utilizator
void RecuperareParola();

// Inregistreaza un nou utilizator
void InregistrareUser();

int register_new_user(char* username, char* f_name, char* l_name, char *pwd, char *vpwd, int zi, int luna, int an);
int logging_account(char* username, char* pwd, char* vpwd);
int forgive_password(char *username, char *f_name, char *l_name);
int delete_cont(char* username, char* f_name, char* pwd, char* vpwd);

// Variabile externe care tin evidenta numarului de conturi si utilizatori
extern int numar_accounts, numar_users;

#endif