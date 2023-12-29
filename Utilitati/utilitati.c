// utilitati.c
#include "../Validare/validare.h"
#include "../Conturi/structuri.h"
#include "../Design/design.h"
#include "../Date/date.h"
#include "utilitati.h"
#include "../Meniuri/meniuri.h"
#include <stdio.h>
#include "vcpkg/packages/libxlsxwriter_x64-windows/include/xlsxwriter.h"
#include "vcpkg/packages/libharu_x64-windows/include/hpdf.h"
#include <string.h>
#include <stdlib.h>

int make_new_type_account(int indice){
    char new_type[100];
    
    type_account();
    read_string(new_type, sizeof(new_type));
    if (validare_tip_cont(new_type) == 0) {
        printf("Tip invalid! \n");
        return -1;  
    }
    int numar = accounts[indice].numar_tip; 
    strcpy(accounts[indice].Info_User[numar].type_account,new_type);
    strcpy(accounts[numar_accounts].Info_User[numar].username, accounts[numar_accounts].Info_User[0].username);
    strcpy(accounts[numar_accounts].Info_User[numar].first_name, accounts[numar_accounts].Info_User[0].first_name);
    strcpy(accounts[numar_accounts].Info_User[numar].last_name, accounts[numar_accounts].Info_User[0].first_name);
    strcpy(accounts[numar_accounts].Info_User[numar].password, accounts[numar_accounts].Info_User[0].password);
    strcpy(accounts[numar_accounts].Info_User[numar].verify_password, accounts[numar_accounts].Info_User[0].verify_password);
    accounts[numar_accounts].Info_User[numar].User_BDay.day = accounts[numar_accounts].Info_User[0].User_BDay.day;
    accounts[numar_accounts].Info_User[numar].User_BDay.month = accounts[numar_accounts].Info_User[0].User_BDay.month;
    accounts[numar_accounts].Info_User[numar].User_BDay.year = accounts[numar_accounts].Info_User[0].User_BDay.year;   
    accounts[indice].numar_tip++;
    printf("Cont de tip nou creat cu succes!!!");
    return accounts[indice].numar_tip;
}

void modify_infomrations(int indice){
    char username[255], vpwd[100], pwd[100],f_name[100], l_name[100];

    printf("Introduceti noul username: \n");
    read_string(username, sizeof(username));
    if (validare_username(username) == 0) {
        printf("Username invalid!\n");
        return;  
    }


    printf("Introduceti noua parola: \n");
    read_string(pwd, sizeof(pwd));
    if (validare_password(pwd) == 0) {
        printf("Parola invalida!\n");
        return;  
    }

    printf("Introduceti noul nume de familie: \n");
    read_string(f_name, sizeof(f_name));
    if (validare_firstname(f_name) == 0) {
        printf("Numele este invalid!\n");
        return;  
    }

    int ok = 0;

    for (int i = 0; i < accounts[indice].numar_tip + 1; ++i){
        strcpy(accounts[indice].Info_User[i].username, username);
        strcpy(accounts[indice].Info_User[i].password, pwd);
        strcpy(accounts[indice].Info_User[i].first_name, f_name);
        ok++;
    }

    if(ok == accounts[indice].numar_tip){
        printf("Contul a fost actualiat cu succes!\n");
    }else{
        printf("Contul NU a putut fii actualizat cu succes!\n");
    }
}
void account_details(int indice) {
    printf("Detaliile despre conturile dumneavoastra:\n");
    printf("________________________________________________________________________________\n");

    for (int i = 0; i < accounts[indice].numar_tip; ++i) {
        printf("Detalii pentru contul de tip %s:\n", accounts[indice].Info_User[i].type_account);

        printf("Username: %s\n", accounts[indice].Info_User[i].username);
        printf("Nume: %s\n", accounts[indice].Info_User[i].first_name);
        printf("Prenume: %s\n", accounts[indice].Info_User[i].last_name);
        printf("Data nasterii: %d/%d/%d\n", accounts[indice].Info_User[i].User_BDay.day, accounts[indice].Info_User[i].User_BDay.month, accounts[indice].Info_User[i].User_BDay.year);

        printf("________________________________________________________________________________\n");
    }
}
void transfer_to_user(int indice) {
    char my_tpcont[100], username_for_transfer_money[255], first_name_transferred[255], last_name_transferred[255], new_type[255];
    float suma;
    
    printf("Din tipul de cont: \n");
    read_string(my_tpcont, sizeof(my_tpcont));
    if (validare_tip_cont(my_tpcont) == 0) {
        printf("Tip invalid! \n");
        return;  
    }

    printf("Introduceti username-ul catre care doriti sa traferati banii: \n");
    read_string(username_for_transfer_money, sizeof(username_for_transfer_money));
    if (validare_username(username_for_transfer_money) == 0) {
        printf("Username invalid!\n");
        return;  
    }

    printf("Introduceti numele de familie catre care doriti sa traferati: \n");
    read_string(first_name_transferred, sizeof(first_name_transferred));
    if (validare_firstname(first_name_transferred) == 0) {
        printf("Numele este invalid!\n");
        return;  
    }

    printf("Introduceti pronumele catre care doriti sa traferati: \n");
    read_string(last_name_transferred, sizeof(last_name_transferred));
    if (validare_firstname(last_name_transferred) == 0) {
        printf("Prenumele este invalid!\n");
        return;  
    }


    printf("Tipul contolui in care doriti sa traferati: \n");
    read_string(new_type, sizeof(new_type));
    if (validare_tip_cont(new_type) == 0) {
        printf("Tip invalid! \n");
        return;  
    }

    for (int i = 0; i < MAX_ACCOUNTS; i++){
        for(int j = 0; j < accounts[i].numar_tip; j++){
            if(strcmp(username_for_transfer_money, accounts[i].Info_User[j].username) == 0 && strcmp(last_name_transferred, accounts[i].Info_User[j].last_name) == 0 && strcmp(first_name_transferred, accounts[i].Info_User[j].first_name) == 0 ){
                printf("Introduceti suma: ");
                scanf("%f", &suma);
                while ((getchar()) != '\n');
                accounts[i].Info_User[j].total_value = accounts[i].Info_User[j].total_value + suma;
                for (int k = 0; k < accounts[indice].numar_tip; k++){
                    if(strcmp(my_tpcont, accounts[indice].Info_User[k].type_account) == 0){
                        accounts[indice].Info_User[k].total_value-=suma;
                        printf("Transfer realizat cu succes!!!");
                        return; 
                    }
                }
                printf("Nu s-a putut realiza cu succes!!!");
                return;
            }
            printf("Nu s-a putut realiza cu succes traferul catre user-ul pe care il doriti, nu l-am putut gasii!");
            return;
        }
    }
}


void retragere_adaugare_tranzactie(int indice) {
    float suma;
    char tipTranzactie[100], descriere[100];
    char tipCont[100];

    type_account();
    read_string(tipCont, sizeof(tipCont));
    if (!validare_tip_cont(tipCont)) {
        printf("Tip invalid!\n");
        return;
    }

    for (int i = 0; i < accounts[indice].numar_tip; ++i) {
        if (strcmp(accounts[indice].Info_User[i].type_account, tipCont) == 0) {
            printf("Introduceti tipul tranzactiei (retragere/adaugare): ");
            fgets(tipTranzactie, sizeof(tipTranzactie), stdin);
            tipTranzactie[strcspn(tipTranzactie, "\n")] = 0;

            if (strcmp(tipTranzactie, "retragere") != 0 && strcmp(tipTranzactie, "adaugare") != 0) {
                printf("Tip tranzactie invalid!\n");
                return;
            }

            printf("Introduceti descrierea tranzactiei: ");
            fgets(descriere, sizeof(descriere), stdin);
            descriere[strcspn(descriere, "\n")] = 0;

            printf("Introduceti suma: ");
            scanf("%f", &suma);
            while ((getchar()) != '\n');

            if (strcmp(tipTranzactie, "retragere") == 0 && accounts[indice].Info_User[i].total_value < suma) {
                printf("Fonduri insuficiente pentru retragere!\n");
                return;
            }

            int nr = accounts[indice].Info_User[i].transaction_num;
            //printf("%d", nr);
            strcpy(accounts[indice].Info_User[i].transaction_value[nr].type, tipTranzactie);
            strcpy(accounts[indice].Info_User[i].transaction_value[nr].description, descriere);
            accounts[indice].Info_User[i].transaction_value[nr].value = suma;
            //printf("%f", (accounts[indice].Info_User[i].transaction_value[nr].value));
            if (strcmp("retragere", tipTranzactie) == 0){
                accounts[indice].Info_User[i].total_value-=suma;
                accounts[indice].Info_User[i].transaction_num++;
                printf("Tranzactie reusita cu success!!\n");
                return;
            }else{
                accounts[indice].Info_User[i].total_value += accounts[indice].Info_User[i].transaction_value[nr].value;
                accounts[indice].Info_User[i].transaction_num++;
                printf("Tranzactie resuita cu success!!\n");
                return;
            }
        }
    }

    printf("Contul specificat nu a fost gasit.\n");
    return;
}

   

void detalied_history(int indice) {
    for(int j = 0; j < accounts[indice].numar_tip; ++j){
        for (int i = 0; i < accounts[indice].Info_User[j].transaction_num; ++i) {
            printf("%d\n", i + 1);
            printf("Tip: %s\n", accounts[indice].Info_User[j].transaction_value[i].type);
            printf("Descriere: %s\n", accounts[indice].Info_User[j].transaction_value[i].description);
            printf("Valoare: %f\n", accounts[indice].Info_User[j].transaction_value[i].value);
            printf("________________________________________________________________\n");
        }
    }
}

void export_to_csv(indice){
    FILE *file = fopen("export.csv", "w");
    if (file == NULL) {
        printf("Nu s-a putut crea fisierul\n");
        return;
    }

    // Antet 
    fprintf(file, "Username, Password, Tip Cont, Balanta\n");


    for(int j = 0; j < accounts[indice].numar_tip; j++){
        fprintf(file, "%s,%s,%s,%f\n", accounts[indice].Info_User[j].username,accounts[indice].Info_User[j].password, accounts[indice].Info_User[j].type_account, accounts[indice].Info_User[j].total_value);
    }

    fclose(file);
    printf("Datele au fost exportate în CSV cu succes.\n");
}

void export_to_excel(int indice){
    lxw_workbook  *workbook  = workbook_new("export.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // antete
    worksheet_write_string(worksheet, 0, 0, "Username", NULL);
    worksheet_write_string(worksheet, 0, 1, "Parola", NULL);
    worksheet_write_string(worksheet, 0, 2, "Tip Cont", NULL);
    worksheet_write_string(worksheet, 0, 3, "Balanta", NULL);

    
    for (int i = 0; i < accounts[indice].numar_tip; i++) {
        worksheet_write_string(worksheet, i + 1, 0, accounts[indice].Info_User[i].username, NULL);
        worksheet_write_string(worksheet, i + 1, 1, accounts[indice].Info_User[i].password, NULL);
        worksheet_write_string(worksheet, i + 1, 2, accounts[indice].Info_User[i].type_account, NULL);
        worksheet_write_number(worksheet, i + 1, 3, accounts[indice].Info_User[i].total_value, NULL);
    }

    workbook_close(workbook);
    printf("Datele au fost exportate în Excel cu succes.\n");
}

void export_to_pdf(int indice){
    HPDF_Doc pdf = HPDF_New(error_handler, NULL);
    HPDF_Page page = HPDF_AddPage(pdf);

    // Configurarea paginii și adăugarea textului
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Scrierea datelor
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        char buffer[100];
        sprintf(buffer, "Username: %s, Parola: %s,  Tipul Contului: %s, Balance: %f", accounts[indice].Info_User[i].username, accounts[indice].Info_User[i].password,
                accounts[indice].Info_User[i].type_account, accounts[indice].Info_User[i].total_value);
        HPDF_Page_TextOut(page, x_position, y_position, buffer);
        y_position -= 20; // Mutarea la următorul rând
    }

    HPDF_Page_EndText(page);
    HPDF_SaveToFile(pdf, "export.pdf");
    HPDF_Free(pdf);

    printf("Datele au fost exportate în PDF cu succes.\n");
}

void export_data(int indice) {
    int choose_extension;
    printf("Alegeti formatul de export:\n1. CSV\n2. Excel\n3. PDF\nOptiunea dorita este: ");
    scanf("%d", &choose_extension);
    switch (choose_extension) {
        case 1:
            export_to_csv(indice);
            break;
        case 2:
            export_to_excel(indice);
            break;
        case 3:
            export_to_pdf(indice);
            break;
        default:
            printf("Optiune invalida!\n");
    }
}
