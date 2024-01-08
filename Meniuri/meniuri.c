#include "meniuri.h"
#include "../Date/date.h"
#include "../Conturi/structuri.h"
#include "../Design/design.h"
#include "../Utilitati/utilitati.h"
#include <stdio.h>
#include <setjmp.h>
#include <string.h>

jmp_buf exception_buffer;

int contor = 0; int numar_cont = 0;
void try() {
    if (setjmp(exception_buffer) == 0) {
        
    } else {
        
        printf("Exceptie prinsa cu succes!\n");
    }
}

void throw_exception() {
    longjmp(exception_buffer, 1);
}
void meniu_principal(){
    try();
    int c, ok = 0, optiune;
    while(ok == 0) {
        meniu_utilizare();
        printf("Introduceti optiunea conform meniului de utilzare:");
        scanf("%d", &optiune);
        while ((c = getchar()) != '\n' && c != EOF) {}
        switch (optiune) {
            case 0:
                ok = 1;
                printf("Bye!\n");
                break;
            case 1:
                InregistrareUser();
                break;
            case 2:
                LogareUser();
                break;
            case 3:
                RecuperareParola();
                break;
            case 4:
                StergereCont();
                break;
            default:
                printf("Optiune invalida\n");
                throw_exception();
                break;
        }
    }
}
void functionalitati_meniu_activat(int indice_user){
    // Afiseaza meniul cu functionalitati dupa autentificarea utilizatorului si gestioneaza optiunile
    
    try();
    int ok = 0, optiune;int t;
    while(ok == 0){ int ok_credit = 0;
        meniu_functionalitati();
        for(int i = 0; i < accounts[indice_user].numar_tip; i++){
            if(strcmp(accounts[indice_user].Info_User[i].type_account, "credit") == 0 && ok_credit == 0){
                ok_credit = 1;
                accounts[indice_user].Info_User[i].total_value = -accounts[indice_user].Info_User[i].total_value;
                printf("Balanta actuala in fiecare cont este: %f\n", accounts[indice_user].Info_User[i].total_value);
            }else{
            printf("Balanta actuala in fiecare cont este: %f\n", accounts[indice_user].Info_User[i].total_value);}
        }
        printf("Introduceti optiunea dorita:\n");
        scanf("%d", &optiune);int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        
        switch(optiune){
            case 0:
                ok = 1;
                printf("Bye!\n");
                break;
            case 1:
                modify_infomrations(indice_user); 
                break;
            case 2:
                account_details(indice_user);
                break; 
            case 3: 
                transfer_to_user(indice_user);
                break;
            case 4:
                retragere_adaugare_tranzactie(indice_user);
                break;
            case 5:
                detalied_history(indice_user);
                break;
            case 6:
                export_data(indice_user);
                break;
            case 7:
                accounts[indice_user].numar_tip = make_new_type_account(indice_user);
                break;
            case 8:
                //logout();
                ok = 1;
                break;
            default:
                printf("Optiune dorita este invalida!\n");
                throw_exception();
                break;
        }
    }
}
