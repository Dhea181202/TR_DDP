#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char user[50], pass[50];
    int pilih;
    int coba = 0;

    // login dulu
    while(coba < 3) {
        system("cls");
        printf("===== LOGIN MINIMARKET =====\n\n");
        printf("Username : ");
        scanf("%s", &user);
        printf("Password : ");
        scanf("%s", &pass);

        if(strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
            printf("\nLogin Berhasil!\n");
            printf("Tekan enter...");
            getchar();
            getchar();
            break;
        } else {
            coba++;
            printf("\nUsername atau Password salah!\n");
            printf("Kesempatan tersisa: %d kali\n", 3-coba);
            if(coba < 3) {
                printf("Tekan enter untuk coba lagi...");
                getchar();
                getchar();
            }
        }
    }

    if(coba == 3) {
        printf("\nAnda sudah salah 3x. Program ditutup.\n");
        return 0;
    }

    while(1) {
        system("cls");
        printf("===== PROGRAM MINIMARKET =====\n\n");
        printf("1. Kelola Data Barang \n");
        printf("2. Transaksi Penjualan\n");
        printf("3. Lihat Detail Transaksi \n");
        printf("4. Return Barang\n");
        printf("5. Rumah Pola\n");
        printf("6. Bendera Negara\n");
        printf("7. Author\n");
        printf("8. Exit\n");
        printf("\nPilih menu: ");
        scanf("%d", &pilih);

        if(pilih == 1) {
            // menu kelola data barang
        }
        else if(pilih == 2) {
            system("cls");
            printf("Menu Transaksi Penjualan\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 3) {
            system("cls");
            printf("Menu Lihat Struk\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 4) {
            system("cls");
            printf("Menu Return Barang\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 5) {
            system("cls");
            printf("Menu Rumah Pola\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 6) {
            system("cls");
            printf("Menu Bendera Negara\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 7) {
            system("cls");
            printf("Menu Author\n\n");
            printf("Fitur ini belum dibuat...\n");
            printf("\nTekan enter untuk kembali...");
            getchar();
            getchar();
        }
        else if(pilih == 8) {
            system("cls");
            printf("\nTerima kasih sudah menggunakan program ini!\n");
            break;
        }
        else {
            printf("\nPilihan tidak ada!\n");
            printf("Tekan enter...");
            getchar();
            getchar();
        }
    }

    return 0;
}


