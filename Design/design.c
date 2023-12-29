#include <string.h>
#include <stdio.h>
#include "design.h"
// Functii de afisare folostie in procesul de logare, asignare, etc. + meniu 
void meniu_utilizare(){
    printf("Buna ziua!\n");
    printf("Va rog sa va autentificati pentru a putea face tranzactii!\n");
    printf("Optiuni valabile:\n");
    printf("0. Iesire din aplicatie!\n");
    printf("1. Creare cont!\n");
    printf("2. Logare cont!\n");
    printf("3. Recuperare cont!\n");
    printf("4. Stergere cont!\n");
}


void meniu_functionalitati(){
    printf("Functionalitati disponibile in aplicatie:\n"
           "1. Modificare informatii cont!\n"
           "2. Vizualizare detalii cont!\n"
           "3. Transfer bancar!\n"
           "4. Efectuare tranzactie(adaugare/retragere)!\n"
           "5. Istoric tranzactii!\n"
           "6. Incarcare date in fisier!\n"
           "7. Creare cont tip nou!\n"
           "8.Deconectare!\n");
}

void type_account(){
    printf("Tipurile contului sunt: economii, credit, normal\n");

    printf("Contul ales este de tip:\n");

}
void username_text(){
    printf("Introduceti username: \n");
}

void data_nastere_text(){
    printf("Data nastere:\n");
}

void parola_text(){
    printf("Introduceti parola:\n");
}
void parola_verificare_text(){
    printf("Introduceti parola pt a fi verificata:\n");
}

void first_name_text(){
    printf("Introduceti numele:\n");
}

void last_name_text(){
    printf("Introduceti prenumele:\n");
}

void transfer_bani_user(){
    printf("Catre cine doriti sa trmiteti bani, va rugam introduceti usernameul:\n");
}

void read_string(char *str, size_t size){
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}