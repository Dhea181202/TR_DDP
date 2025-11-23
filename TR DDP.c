#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct untuk data barang
struct Barang {
    int kode;
    char nama[50];
    int harga;
    int stok;
};

// struct untuk transaksi
struct Transaksi {
    int noTransaksi;
    char tanggal[20];
    int kodeBarang[10];
    char namaBarang[10][50];
    int hargaBarang[10];
    int jumlahBeli[10];
    int subtotal[10];
    int itemCount;
    int totalBayar;
    int uangDibayar;
    int kembalian;
};

struct Barang daftarBarang[100];
int jumlahBarang = 5;

struct Transaksi riwayatTransaksi[100];
int jumlahTransaksi = 0;

int main() {
    char user[50], pass[50];
    int pilih;
    int coba = 0;

    // data barang awal
    daftarBarang[0].kode = 1;
    strcpy(daftarBarang[0].nama, "Indomie Goreng");
    daftarBarang[0].harga = 3500;
    daftarBarang[0].stok = 50;

    daftarBarang[1].kode = 2;
    strcpy(daftarBarang[1].nama, "Aqua 600ml");
    daftarBarang[1].harga = 3000;
    daftarBarang[1].stok = 100;

    daftarBarang[2].kode = 3;
    strcpy(daftarBarang[2].nama, "Teh Pucuk");
    daftarBarang[2].harga = 4000;
    daftarBarang[2].stok = 75;

    daftarBarang[3].kode = 4;
    strcpy(daftarBarang[3].nama, "Chitato");
    daftarBarang[3].harga = 10000;
    daftarBarang[3].stok = 30;

    daftarBarang[4].kode = 5;
    strcpy(daftarBarang[4].nama, "Susu Ultra 250ml");
    daftarBarang[4].harga = 5500;
    daftarBarang[4].stok = 40;

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

    // menu utama
    while(1) {
        system("cls");
        printf("===== PROGRAM MINIMARKET =====\n\n");
        printf("1. Kelola Data Barang \n");
        printf("2. Transaksi Penjualan\n");
        printf("3. Lihat Detail Transaksi \n");
        printf("4. Fitur Return Barang\n");
        printf("5. Rumah Pola\n");
        printf("6. Bendera Negara\n");
        printf("7. Author\n");
        printf("8. Exit\n");
        printf("\nPilih menu: ");
        scanf("%d", &pilih);

        if(pilih == 1) {
            int pilihBarang;
            while(1) {
                system("cls");
                printf("===== KELOLA DATA BARANG =====\n\n");
                printf("1. Tambah Barang Baru\n");
                printf("2. Lihat Daftar Barang\n");
                printf("3. Edit Barang\n");
                printf("4. Hapus Barang\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("\nPilih menu: ");
                scanf("%d", &pilihBarang);

                if(pilihBarang == 1) {
                    system("cls");
                    printf("=== TAMBAH BARANG BARU ===\n\n");
                    printf("(Ketik 0 untuk kembali)\n\n");

                    int kodeInput;
                    printf("Kode Barang: ");
                    scanf("%d", &kodeInput);

                    if(kodeInput == 0) {
                        printf("\nKembali ke menu...\n");
                        getchar();
                        continue;
                    }

                    // cek kode duplikat
                    int kodeDuplikat = 0;
                    int i;
                    for(i = 0; i < jumlahBarang; i++) {
                        if(daftarBarang[i].kode == kodeInput) {
                            kodeDuplikat = 1;
                            break;
                        }
                    }

                    if(kodeDuplikat == 1) {
                        printf("\nKode barang sudah digunakan! Gunakan kode lain.\n");
                        printf("Tekan enter...");
                        getchar();
                        getchar();
                        continue;
                    }

                    daftarBarang[jumlahBarang].kode = kodeInput;

                    printf("Nama Barang: ");
                    getchar();
                    gets(daftarBarang[jumlahBarang].nama);

                    printf("Harga Barang: ");
                    scanf("%d", &daftarBarang[jumlahBarang].harga);

                    printf("Stok Barang: ");
                    scanf("%d", &daftarBarang[jumlahBarang].stok);

                    jumlahBarang++;

                    printf("\nBarang berhasil ditambahkan!\n");
                    printf("Tekan enter...");
                    getchar();
                    getchar();
                }
                else if(pilihBarang == 2) {
                    system("cls");
                    printf("=== DAFTAR BARANG ===\n\n");

                    if(jumlahBarang == 0) {
                        printf("Belum ada barang yang ditambahkan.\n");
                    } else {
                        printf("---------------------------------------------------------------\n");
                        printf("| No | Kode |      Nama Barang      |   Harga   |   Stok   |\n");
                        printf("---------------------------------------------------------------\n");

                        int i;
                        for(i = 0; i < jumlahBarang; i++) {
                            printf("| %-2d | %-4d | %-21s | Rp %-6d | %-8d |\n",
                                   i+1,
                                   daftarBarang[i].kode,
                                   daftarBarang[i].nama,
                                   daftarBarang[i].harga,
                                   daftarBarang[i].stok);
                        }

                        printf("---------------------------------------------------------------\n");
                        printf("\nTotal Barang: %d\n", jumlahBarang);
                    }

                    printf("\nTekan enter...");
                    getchar();
                    getchar();
                }
                else if(pilihBarang == 3) {
                    system("cls");
                    printf("=== EDIT BARANG ===\n\n");

                    if(jumlahBarang == 0) {
                        printf("Belum ada barang yang bisa diedit.\n");
                        printf("\nTekan enter...");
                        getchar();
                        getchar();
                    } else {
                        int kodeEdit, ketemu = 0, i;

                        printf("(Ketik 0 untuk kembali)\n\n");
                        printf("Masukkan kode barang yang ingin diedit: ");
                        scanf("%d", &kodeEdit);

                        if(kodeEdit == 0) {
                            printf("\nKembali ke menu...\n");
                            getchar();
                            getchar();
                            continue;
                        }

                        for(i = 0; i < jumlahBarang; i++) {
                            if(daftarBarang[i].kode == kodeEdit) {
                                ketemu = 1;

                                printf("\nData barang saat ini:\n");
                                printf("Kode: %d\n", daftarBarang[i].kode);
                                printf("Nama: %s\n", daftarBarang[i].nama);
                                printf("Harga: Rp %d\n", daftarBarang[i].harga);
                                printf("Stok: %d\n", daftarBarang[i].stok);

                                printf("\n--- Masukkan data baru ---\n");
                                printf("Nama Barang: ");
                                getchar();
                                gets(daftarBarang[i].nama);

                                printf("Harga Barang: ");
                                scanf("%d", &daftarBarang[i].harga);

                                printf("Stok Barang: ");
                                scanf("%d", &daftarBarang[i].stok);

                                printf("\nData barang berhasil diupdate!\n");
                                printf("Tekan enter...");
                                getchar();
                                getchar();
                                break;
                            }
                        }

                        if(ketemu == 0) {
                            printf("\nBarang dengan kode %d tidak ditemukan!\n", kodeEdit);
                            printf("Tekan enter...");
                            getchar();
                            getchar();
                        }
                    }
                }
                else if(pilihBarang == 4) {
                    system("cls");
                    printf("=== HAPUS BARANG ===\n\n");

                    if(jumlahBarang == 0) {
                        printf("Belum ada barang yang bisa dihapus.\n");
                        printf("\nTekan enter...");
                        getchar();
                        getchar();
                    } else {
                        int kodeHapus, ketemu = 0, i, j;

                        printf("(Ketik 0 untuk kembali)\n\n");
                        printf("Masukkan kode barang yang ingin dihapus: ");
                        scanf("%d", &kodeHapus);

                        if(kodeHapus == 0) {
                            printf("\nKembali ke menu...\n");
                            getchar();
                            getchar();
                            continue;
                        }

                        for(i = 0; i < jumlahBarang; i++) {
                            if(daftarBarang[i].kode == kodeHapus) {
                                ketemu = 1;

                                printf("\nBarang yang akan dihapus:\n");
                                printf("Kode: %d\n", daftarBarang[i].kode);
                                printf("Nama: %s\n", daftarBarang[i].nama);
                                printf("Harga: Rp %d\n", daftarBarang[i].harga);
                                printf("Stok: %d\n", daftarBarang[i].stok);

                                char konfirmasi;
                                printf("\nYakin ingin menghapus? (y/n): ");
                                scanf(" %c", &konfirmasi);

                                if(konfirmasi == 'y' || konfirmasi == 'Y') {
                                    // geser data barang ke kiri
                                    for(j = i; j < jumlahBarang - 1; j++) {
                                        daftarBarang[j] = daftarBarang[j + 1];
                                    }
                                    jumlahBarang--;

                                    printf("\nBarang berhasil dihapus!\n");
                                } else {
                                    printf("\nPenghapusan dibatalkan.\n");
                                }

                                printf("Tekan enter...");
                                getchar();
                                getchar();
                                break;
                            }
                        }

                        if(ketemu == 0) {
                            printf("\nBarang dengan kode %d tidak ditemukan!\n", kodeHapus);
                            printf("Tekan enter...");
                            getchar();
                            getchar();
                        }
                    }
                }
                else if(pilihBarang == 5) {
                    break;
                }
                else {
                    printf("\nPilihan tidak ada!\n");
                    printf("Tekan enter...");
                    getchar();
                    getchar();
                }
            }
        }
        else if(pilih == 2) {
            system("cls");
            printf("===== TRANSAKSI PENJUALAN =====\n\n");

            struct Transaksi trans;
            trans.noTransaksi = jumlahTransaksi + 1;
            strcpy(trans.tanggal, "23/11/2025");
            trans.itemCount = 0;
            trans.totalBayar = 0;

            int lanjut = 1;

            while(lanjut) {
                int kodeInput, jumlah, i, ketemu = 0;

                printf("\n--- Item ke-%d ---\n", trans.itemCount + 1);
                printf("(Ketik 0 untuk selesai belanja)\n");
                printf("Kode Barang: ");
                scanf("%d", &kodeInput);

                if(kodeInput == 0) {
                    break;
                }

                // cari barang
                for(i = 0; i < jumlahBarang; i++) {
                    if(daftarBarang[i].kode == kodeInput) {
                        ketemu = 1;

                        printf("Nama Barang: %s\n", daftarBarang[i].nama);
                        printf("Harga: Rp %d\n", daftarBarang[i].harga);
                        printf("Stok tersedia: %d\n", daftarBarang[i].stok);
                        printf("Jumlah beli: ");
                        scanf("%d", &jumlah);

                        if(jumlah > daftarBarang[i].stok) {
                            printf("\nStok tidak cukup!\n");
                        } else if(jumlah <= 0) {
                            printf("\nJumlah tidak valid!\n");
                        } else {
                            // simpan ke transaksi
                            trans.kodeBarang[trans.itemCount] = daftarBarang[i].kode;
                            strcpy(trans.namaBarang[trans.itemCount], daftarBarang[i].nama);
                            trans.hargaBarang[trans.itemCount] = daftarBarang[i].harga;
                            trans.jumlahBeli[trans.itemCount] = jumlah;
                            trans.subtotal[trans.itemCount] = daftarBarang[i].harga * jumlah;
                            trans.totalBayar += trans.subtotal[trans.itemCount];

                            // kurangi stok
                            daftarBarang[i].stok -= jumlah;

                            trans.itemCount++;
                            printf("\nBarang ditambahkan ke keranjang!\n");
                        }
                        break;
                    }
                }

                if(ketemu == 0) {
                    printf("\nBarang tidak ditemukan!\n");
                }
            }

            if(trans.itemCount == 0) {
                printf("\nTidak ada barang yang dibeli.\n");
                printf("Tekan enter...");
                getchar();
                getchar();
            } else {
                // tampilkan ringkasan
                system("cls");
                printf("===== RINGKASAN BELANJA =====\n\n");
                printf("---------------------------------------------------------------\n");
                printf("| No | Nama Barang           | Harga     | Qty | Subtotal    |\n");
                printf("---------------------------------------------------------------\n");

                int i;
                for(i = 0; i < trans.itemCount; i++) {
                    printf("| %-2d | %-21s | Rp %-6d | %-3d | Rp %-8d |\n",
                           i+1,
                           trans.namaBarang[i],
                           trans.hargaBarang[i],
                           trans.jumlahBeli[i],
                           trans.subtotal[i]);
                }

                printf("---------------------------------------------------------------\n");
                printf("TOTAL BAYAR: Rp %d\n\n", trans.totalBayar);

                // pilih metode pembayaran
                int metode;
                printf("Pilih Metode Pembayaran:\n");
                printf("1. CASH\n");
                printf("2. QRIS\n");
                printf("Pilih (1/2): ");
                scanf("%d", &metode);

                if(metode == 1) {
                    // pembayaran cash
                    printf("\n=== PEMBAYARAN ===\n");
                    printf("Uang tunai: Rp ");
                    scanf("%d", &trans.uangDibayar);

                    if(trans.uangDibayar < trans.totalBayar) {
                        printf("\nUang tidak cukup! Transaksi dibatalkan.\n");
                        // kembalikan stok
                        for(i = 0; i < trans.itemCount; i++) {
                            int j;
                            for(j = 0; j < jumlahBarang; j++) {
                                if(daftarBarang[j].kode == trans.kodeBarang[i]) {
                                    daftarBarang[j].stok += trans.jumlahBeli[i];
                                    break;
                                }
                            }
                        }
                        printf("Tekan enter...");
                        getchar();
                        getchar();
                    } else {
                        trans.kembalian = trans.uangDibayar - trans.totalBayar;
                        printf("\nKembalian: Rp %d\n", trans.kembalian);

                        // simpan transaksi
                        riwayatTransaksi[jumlahTransaksi] = trans;
                        jumlahTransaksi++;

                        printf("\n=== TRANSAKSI BERHASIL ===\n");
                        printf("No. Transaksi: %d\n", trans.noTransaksi);
                        printf("Tekan enter...");
                        getchar();
                        getchar();
                    }
                } else if(metode == 2) {
                    printf("\nFitur QRIS belum tersedia.\n");
                    printf("Transaksi dibatalkan.\n");
                    // kembalikan stok
                    for(i = 0; i < trans.itemCount; i++) {
                        int j;
                        for(j = 0; j < jumlahBarang; j++) {
                            if(daftarBarang[j].kode == trans.kodeBarang[i]) {
                                daftarBarang[j].stok += trans.jumlahBeli[i];
                                break;
                            }
                        }
                    }
                    printf("Tekan enter...");
                    getchar();
                    getchar();
                } else {
                    printf("\nPilihan tidak valid! Transaksi dibatalkan.\n");
                    // kembalikan stok
                    for(i = 0; i < trans.itemCount; i++) {
                        int j;
                        for(j = 0; j < jumlahBarang; j++) {
                            if(daftarBarang[j].kode == trans.kodeBarang[i]) {
                                daftarBarang[j].stok += trans.jumlahBeli[i];
                                break;
                            }
                        }
                    }
                    printf("Tekan enter...");
                    getchar();
                    getchar();
                }
            }
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
            printf("==============================\n");
            printf("           AUTHOR             \n");
            printf("==============================\n\n");

            printf("Author :\n");
            printf("1. Dhea Adventri-672021275\n");
            printf("2. \n");
            printf("3. \n");
            printf("4. \n");
            printf("5. \n\n");

            printf("==============================\n");
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
