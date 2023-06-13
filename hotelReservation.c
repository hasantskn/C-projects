#include <stdio.h>      // Standart giriş/çıkış işlemleri için
#include <stdlib.h>     // Genel yardımcı işlemler için
#include <string.h>     // Dizi işlemleri için
#include <curses.h>     // Konsol giriş/çıkış işlemleri için
#include <unistd.h>     // POSIX işletim sistemi işlemleri için
#include <fcntl.h>      // Dosya işlemleri için
#include <fstream>      // Dosya giriş/çıkış işlemleri için (C++ kütüphanesi)
#include <ncurses.h>

void gotoxy(int x, int y);
struct hotel
{
	int room_no;
	char name[30];
	char address[50];
	char phone[10];

};


void main_menu();		//to dispay the main menu
void add();			//to book a room
void display(); 		//to display the customer record
void rooms();			//to display alloted rooms
void edit();			//to edit the customer record
int check(int);			//to check room status
void modify(int);		//to modify the record
void delete_rec(int);		//to delete the record
void bill(int);                 //for the bill of a record

void main_menu() {
    int choice;

    while (choice != 5) {
        system("clear");
        gotoxy(65, 5);
        printf("\n\n");
        for (int i = 0; i < 40; i++)
            printf("\xB2");
        printf("\n");
        gotoxy(70, 7);
        printf("\t\t\tHotel Management System\n");
        gotoxy(65, 9);
        for (int i = 0; i < 40; i++)
            printf("\xB2");
        printf("\n\n");
        gotoxy(50, 13);
        printf("1. Book A Room\n");
        gotoxy(50, 14);
        printf("2. Customer Records\n");
        gotoxy(50, 15);
        printf("3. Rooms Allotted\n");
        gotoxy(50, 16);
        printf("4. Edit Record\n");
        gotoxy(50, 17);
        printf("5. Exit\n\n");
        gotoxy(50, 20);
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5: {
            gotoxy(45, 26);
            printf("\nThanks for using our Service, hope this helps you in your daily life\n\n\n");
            exit(0);
            break;
        }
        default: {
            printf("\nWrong choice.....!!!");
            printf("\nPress any key to continue....!!");
            getchar();
        }
        }
    }
}

void add() {
    system("clear");
    int r, flag;
    FILE* fp = fopen("Record.dat", "ab");
    gotoxy(65, 1);
    printf("\xB2\xB2 Please enter the details \xB2\xB2\n\n");
    gotoxy(55, 6);
    printf("Total no. of Rooms - 50\n");
    gotoxy(55, 7);
    printf("Ordinary Rooms from 1 - 30\n");
    gotoxy(55, 8);
    printf("Luxuary Rooms from 31 - 45\n");
    gotoxy(55, 9);
    printf("Royal Rooms from 46 - 50\n");
    gotoxy(55, 15);
    printf("Enter the room no. you want to stay in : ");
    scanf("%d", &r);
    flag = check(r);
    if (flag)
        printf("\n Sorry..!!! Room is already booked");
    else {
        struct hotel h;
        h.room_no = r;
        printf("Name: ");
        scanf("%s", h.name);
        printf("Address: ");
        scanf("%s", h.address);
        printf("Phone No: ");
        scanf("%s", h.phone);
        fwrite(&h, sizeof(struct hotel), 1, fp);
        printf("\n Room is booked...!!!");
    }
    printf("\n Press any key to continue.....!!");
    getchar();
    fclose(fp);
}
//END OF BOOKING FUNCTION

//FUNCTION FOR DISPLAYING A PURTICULAR CUSTOMER`S RECORD

void display() {
    system("clear");
    FILE* fp = fopen("Record.dat", "rb");
    int r, flag = 0;
    printf("\n Enter room no. for a particular customer's details: ");
    scanf("%d", &r);
    struct hotel h;
    while (fread(&h, sizeof(struct hotel), 1, fp)) {
        if (h.room_no == r) {
            system("clear");
            printf("\n Customer Details");
            printf("\n ----------------");
            printf("\n\n Room no: %d", h.room_no);
            printf("\n Name: %s", h.name);
            printf("\n Address: %s", h.address);
            printf("\n Phone no: %s", h.phone);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("\n Sorry Room no. not found or vacant....!!");
    printf("\n\n Press any key to continue....!!");
    getchar();
    fclose(fp);
}
//END OF DISPLAY FUNCTION

//FUNCTION TO DISPLAY ALL ROOMS OCCUPIED
void rooms() {
    system("clear");
    FILE* fp = fopen("Record.dat", "rb");
    printf("\n\t\t\t    List Of Rooms Allotted");
    printf("\n\t\t\t    ----------------------");
    printf("\n\n Room No.\tName\t\tAddress\t\t\t\tPhone No.\n");
    struct hotel h;
    while (fread(&h, sizeof(struct hotel), 1, fp)) {
        printf("\n\n %d\t\t%s", h.room_no, h.name);
        printf("\t\t%s\t\t%s", h.address, h.phone);
    }
    printf("\n\n\n\t\t\tPress any key to continue.....!!");
    getchar();
    fclose(fp);
}

//FUNCTION FOR EDITING RECORDS AND FOR BILL

void edit() {
    system("clear");

    int choice, r;
    printf("\n EDIT MENU");
    printf("\n ---------");
    printf("\n\n 1.Modify Customer Record");
    printf("\n 2.Delete Customer Record");
    printf("\n 3. Bill Of Customer");
    printf("\n Enter your choice: ");
    scanf("%d", &choice);
    system("clear");
    printf("\n Enter room no: ");
    scanf("%d", &r);

    switch (choice) {
    case 1: modify(r); break;
    case 2: delete_rec(r); break;
    case 3: bill(r); break;
    default: printf("\n Wrong Choice.....!!");
    }

    printf("\n Press any key to continue....!!");
    getchar();
}

int check(int r) {
    int flag = 0;
    FILE* fp = fopen("Record.dat", "rb");

    struct hotel h;
    while (fread(&h, sizeof(struct hotel), 1, fp)) {
        if (h.room_no == r) {
            flag = 1;
            break;
        }
    }

    fclose(fp);
    return flag;
}

//FUNCTION TO MODIFY CUSTOMERS RECORD
void modify(int r) {
    long pos;
    int flag = 0;

    FILE* fp = fopen("Record.dat", "rb+");
    struct hotel h;

    while (fread(&h, sizeof(struct hotel), 1, fp)) {
        pos = ftell(fp) - sizeof(struct hotel);

        if (h.room_no == r) {
            printf("\n Enter New Details");
            printf("\n -----------------");
            printf("\n Name: ");
            scanf("%s", h.name);
            printf(" Address: ");
            scanf("%s", h.address);
            printf(" Phone no: ");
            scanf("%s", h.phone);

            fseek(fp, pos, SEEK_SET);
            fwrite(&h, sizeof(struct hotel), 1, fp);
            printf("\n Record is modified....!!");
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("\n Sorry Room no. not found or vacant...!!");
    fclose(fp);
}
//END OF MODIFY FUNCTION

//FUNCTION FOR DELETING RECORD

void delete_rec(int r) {
    int flag = 0;
    char ch;

    FILE* fin = fopen("Record.dat", "rb");
    FILE* fout = fopen("temp.dat", "wb");

    struct hotel h;
    while (fread(&h, sizeof(struct hotel), 1, fin)) {
        if (h.room_no == r) {
            printf("\n Name: %s", h.name);
            printf("\n Address: %s", h.address);
            printf("\n Phone No: %s", h.phone);
            printf("\n\n Do you want to delete this record (y/n): ");
            scanf(" %c", &ch);

            if (ch == 'n')
                fwrite(&h, sizeof(struct hotel), 1, fout);
            flag = 1;
        }
        else {
            fwrite(&h, sizeof(struct hotel), 1, fout);
        }
    }

    fclose(fin);
    fclose(fout);

    if (flag == 0)
        printf("\n Sorry room no. not found or vacant...!!");
    else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}
//END OF DELETE FUNCTION

//FUNCTION FOR CUSTOMER`S BILL

void bill(int r) {
    struct hotel h1;

    FILE* f1 = fopen("record.dat", "rb");
    if (!f1) {
        printf("Cannot open the file.");
    }
    else {
        fread(&h1, sizeof(struct hotel), 1, f1);
        while (!feof(f1)) {
            fread(&h1, sizeof(struct hotel), 1, f1);
        }

        if (h1.room_no == r) {
            if (h1.room_no >= 1 && h1.room_no <= 30)
                printf("Your bill = 2000");
            else if (h1.room_no >= 35 && h1.room_no <= 45)
                printf("Your bill = 5000");
            else
                printf("Your bill = 7000");
        }
        else {
            printf("Room no. not found");
        }
    }

    fclose(f1);
    getchar();
}
//END OF BILLING FUNCTION
//START OF MAIN PROGARM

int main() {
    struct hotel h;

    system("clear");
    gotoxy(65, 5);
    for (int i = 0; i < 25; i++)
        printf("\xD2");
    printf("\n");
    gotoxy(70, 7);
    printf("\tAuthentication\n");
    gotoxy(65, 9);
    for (int i = 0; i < 25; i++)
        printf("\xD2");

    char id[10], pass[10];
    gotoxy(50, 15);
    printf("\n\n\xB2\xB2 Username => ");
    scanf("%s", id);
    gotoxy(50, 17);
    printf("\n\xB2\xB2 Password => ");
    scanf("%s", pass);

    if (strcmp(id, "admin") == 0 && strcmp(pass, "hasan") == 0) {
        gotoxy(60, 20);
        printf("\n\nLogin Successful...");
        getchar();
    }
    else {
        gotoxy(60, 20);
        printf("\n\nSorry, you are not authorized...");
        getchar();
        exit(-1);
    }

    getchar();

    main_menu();
    return 0;
}
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}
