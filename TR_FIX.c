#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bagian ini agar fungsi delay/sleep bisa jalan 
#ifdef _WIN32
    #include <windows.h>
    void delay(int milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    void delay(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif

// --- DEFINISI WARNA 
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_PURPLE  "\x1b[35m"
#define COLOR_WHITE   "\x1b[37m"
#define BG_RED        "\x1b[41m"
#define BG_WHITE      "\x1b[47m"

struct Barang {
    int kode;
    char nama[50];
    int harga;
    int stok;
};

struct Transaksi {
    int noTransaksi;
    char tanggal[20];
    int kodeBarang[10];
    char namaBarang[10][50];
    int hargaBarang[10];
    int jumlahBeli[10];
    int subtotal[10];
    int itemCount;
    int totalKotor;
    int diskon;
    int totalBayar;
    int uangDibayar;
    int kembalian;
    int metodePembayaran; // 1 = Cash, 2 = QRIS
};

struct Barang daftarBarang[100];
int jumlahBarang = 5;

struct Transaksi riwayatTransaksi[100];
int jumlahTransaksi = 0;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char user[50], pass[50];
    int pilih;
    int coba = 0;

    daftarBarang[0].kode = 1; strcpy(daftarBarang[0].nama, "Indomie Goreng"); daftarBarang[0].harga = 3500; daftarBarang[0].stok = 50;
    daftarBarang[1].kode = 2; strcpy(daftarBarang[1].nama, "Aqua 600ml"); daftarBarang[1].harga = 3000; daftarBarang[1].stok = 100;
    daftarBarang[2].kode = 3; strcpy(daftarBarang[2].nama, "Teh Pucuk"); daftarBarang[2].harga = 4000; daftarBarang[2].stok = 75;
    daftarBarang[3].kode = 4; strcpy(daftarBarang[3].nama, "Chitato"); daftarBarang[3].harga = 10000; daftarBarang[3].stok = 30;
    daftarBarang[4].kode = 5; strcpy(daftarBarang[4].nama, "Susu Ultra 250ml"); daftarBarang[4].harga = 5500; daftarBarang[4].stok = 40;

    // --- LOGIN 
    while(coba < 3) {
        clearScreen();
        printf("===== LOGIN MINIMARKET =====\n\n");
        printf("Username : "); scanf("%s", user);
        printf("Password : "); scanf("%s", pass);

        if(strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
            printf("\n" COLOR_GREEN "Login Berhasil!" COLOR_RESET "\n");
            printf("Tekan enter...");
            cleanBuffer(); getchar();
            break;
        } else {
            coba++;
            printf("\n" COLOR_RED "Username atau Password salah!" COLOR_RESET "\n");
            printf("Kesempatan tersisa: %d kali\n", 3-coba);
            cleanBuffer();
            if(coba < 3) {
                printf("Tekan enter untuk coba lagi...");
                getchar();
            }
        }
    }

    if(coba == 3) {
        printf("\nAnda sudah salah 3x. Program ditutup demi keamanan.\n");
        return 0;
    }

    // --- MENU UTAMA ---
    while(1) {
        clearScreen();
        printf("===== PROGRAM MINIMARKET =====\n");
        printf("User: Admin | Waktu: 30/11/2025\n\n");
        printf("1. Kelola Data Barang (CRUD)\n");
        printf("2. Transaksi Penjualan\n");
        printf("3. Lihat Detail Transaksi (Struk)\n");
        printf("4. Fitur Return Barang\n");
        printf("5. Rumah Pola (ANIMASI)\n");
        printf("6. Bendera Negara\n");
        printf("7. Author\n");
        printf("8. Exit\n");
        printf("\nPilih menu: ");
        if (scanf("%d", &pilih) != 1) { // Validasi input angka
            cleanBuffer();
            continue;
        }

        // 1. KELOLA BARANG
        if(pilih == 1) {
            int pilihBarang;
            while(1) {
                clearScreen();
                printf("===== KELOLA DATA BARANG =====\n\n");
                printf("1. Tambah Barang Baru\n");
                printf("2. Lihat Daftar Barang\n");
                printf("3. Edit Barang\n");
                printf("4. Hapus Barang\n");
                printf("5. Kembali ke Menu Utama\n");
                printf("\nPilih menu: ");
                scanf("%d", &pilihBarang);

                if(pilihBarang == 1) { // CREATE
                    clearScreen();
                    printf("=== TAMBAH BARANG BARU ===\n\n");
                    int kodeInput;
                    printf("Kode Barang (0 kembali): ");
                    scanf("%d", &kodeInput);
                    if(kodeInput == 0) continue;

                    int duplicate = 0;
                    for(int i=0; i<jumlahBarang; i++) {
                        if(daftarBarang[i].kode == kodeInput) duplicate = 1;
                    }

                    if(duplicate) {
                        printf("\n" COLOR_RED "Error: Kode barang sudah ada!" COLOR_RESET "\n");
                        cleanBuffer(); getchar();
                        continue;
                    }

                    daftarBarang[jumlahBarang].kode = kodeInput;
                    printf("Nama Barang: ");
                    scanf(" %[^\n]", daftarBarang[jumlahBarang].nama);
                    printf("Harga Barang: ");
                    scanf("%d", &daftarBarang[jumlahBarang].harga);
                    printf("Stok Barang: ");
                    scanf("%d", &daftarBarang[jumlahBarang].stok);

                    jumlahBarang++;
                    printf("\n" COLOR_GREEN "Barang berhasil ditambahkan!" COLOR_RESET "\nTekan enter...");
                    cleanBuffer(); getchar();
                }
                else if(pilihBarang == 2) { // READ
                    clearScreen();
                    printf("=== DAFTAR BARANG ===\n\n");
                    printf("%-5s %-5s %-25s %-10s %-5s\n", "No", "Kode", "Nama", "Harga", "Stok");
                    printf("----------------------------------------------------------\n");
                    for(int i=0; i<jumlahBarang; i++) {
                        printf("%-5d %-5d %-25s Rp%-8d %-5d\n", i+1, daftarBarang[i].kode, daftarBarang[i].nama, daftarBarang[i].harga, daftarBarang[i].stok);
                    }
                    printf("\nTotal Item: %d\nTekan enter...", jumlahBarang);
                    cleanBuffer(); getchar();
                }
                else if(pilihBarang == 3) { // UPDATE
                    clearScreen();
                    printf("=== EDIT BARANG ===\n");
                    int kodeEdit, found=0;
                    printf("Masukkan kode barang: ");
                    scanf("%d", &kodeEdit);

                    for(int i=0; i<jumlahBarang; i++){
                        if(daftarBarang[i].kode == kodeEdit){
                            found = 1;
                            printf("\nData Lama -> Nama: %s | Harga: %d | Stok: %d\n", daftarBarang[i].nama, daftarBarang[i].harga, daftarBarang[i].stok);
                            printf("Nama Baru: "); scanf(" %[^\n]", daftarBarang[i].nama);
                            printf("Harga Baru: "); scanf("%d", &daftarBarang[i].harga);
                            printf("Stok Baru: "); scanf("%d", &daftarBarang[i].stok);
                            printf("\n" COLOR_GREEN "Data berhasil diupdate!" COLOR_RESET "\n");
                        }
                    }
                    if(!found) printf("\n" COLOR_RED "Barang tidak ditemukan." COLOR_RESET "\n");
                    cleanBuffer(); getchar();
                }
                else if(pilihBarang == 4) { // DELETE
                    clearScreen();
                    printf("=== HAPUS BARANG ===\n");
                    int kodeHapus, found=0;
                    printf("Masukkan kode barang: ");
                    scanf("%d", &kodeHapus);

                    for(int i=0; i<jumlahBarang; i++){
                        if(daftarBarang[i].kode == kodeHapus){
                            found=1;
                            char yakin;
                            printf("Yakin hapus %s? (y/n): ", daftarBarang[i].nama);
                            scanf(" %c", &yakin);

                            if(yakin == 'y' || yakin == 'Y'){
                                for(int j=i; j<jumlahBarang-1; j++){
                                    daftarBarang[j] = daftarBarang[j+1];
                                }
                                jumlahBarang--;
                                printf("Barang terhapus.\n");
                            } else {
                                printf("Batal menghapus.\n");
                            }
                            break;
                        }
                    }
                    if(!found) printf("\n" COLOR_RED "Barang tidak ditemukan." COLOR_RESET "\n");
                    cleanBuffer(); getchar();
                }
                else if(pilihBarang == 5) break;
            }
        }

        // 2. TRANSAKSI PENJUALAN
        else if(pilih == 2) {
            clearScreen();
            printf("===== TRANSAKSI PENJUALAN =====\n\n");

            struct Transaksi trans;
            trans.noTransaksi = jumlahTransaksi + 1;
            strcpy(trans.tanggal, "30/11/2025");
            trans.itemCount = 0;
            trans.totalKotor = 0;
            trans.diskon = 0;
            trans.totalBayar = 0;

            while(1) {
                int kodeInput, jumlah, found=0;
                printf("\nInput Kode Barang (0 selesai): ");
                scanf("%d", &kodeInput);

                if(kodeInput == 0) break;

                for(int i=0; i<jumlahBarang; i++) {
                    if(daftarBarang[i].kode == kodeInput) {
                        found = 1;
                        printf("Nama: %s | Harga: %d | Stok: %d\n", daftarBarang[i].nama, daftarBarang[i].harga, daftarBarang[i].stok);
                        printf("Jumlah Beli: ");
                        scanf("%d", &jumlah);

                        if(jumlah > 0 && jumlah <= daftarBarang[i].stok) {
                            trans.kodeBarang[trans.itemCount] = daftarBarang[i].kode;
                            strcpy(trans.namaBarang[trans.itemCount], daftarBarang[i].nama);
                            trans.hargaBarang[trans.itemCount] = daftarBarang[i].harga;
                            trans.jumlahBeli[trans.itemCount] = jumlah;
                            trans.subtotal[trans.itemCount] = daftarBarang[i].harga * jumlah;

                            trans.totalKotor += trans.subtotal[trans.itemCount];
                            daftarBarang[i].stok -= jumlah; // Kurangi stok sementara
                            trans.itemCount++;
                            printf(COLOR_BLUE "Item ditambahkan ke keranjang." COLOR_RESET "\n");
                        } else {
                            printf(COLOR_RED "Stok tidak cukup atau jumlah tidak valid!" COLOR_RESET "\n");
                        }
                        break;
                    }
                }
                if(!found) printf("Barang tidak ditemukan!\n");
            }

            if(trans.itemCount > 0) {
                if(trans.totalKotor > 50000) {
                    trans.diskon = (int)(trans.totalKotor * 0.1);
                    printf("\n" COLOR_GREEN "Selamat! Diskon 10%% (Belanja > 50.000)" COLOR_RESET "\n");
                }
                trans.totalBayar = trans.totalKotor - trans.diskon;

                printf("\n--------------------------\n");
                printf("Total Belanja : Rp %d\n", trans.totalKotor);
                printf("Diskon        : Rp %d\n", trans.diskon);
                printf("TOTAL BAYAR   : Rp %d\n", trans.totalBayar);
                printf("--------------------------\n");

                printf("Metode Pembayaran:\n1. Cash\n2. QRIS\nPilih: ");
                scanf("%d", &trans.metodePembayaran);

                int transaksiSah = 0;

                if(trans.metodePembayaran == 1) { // CASH
                    printf("Bayar (Cash): Rp ");
                    scanf("%d", &trans.uangDibayar);

                    if(trans.uangDibayar >= trans.totalBayar) {
                        trans.kembalian = trans.uangDibayar - trans.totalBayar;
                        printf("Kembalian: Rp %d\n", trans.kembalian);
                        transaksiSah = 1;
                    } else {
                        printf(COLOR_RED "Uang kurang! Transaksi Dibatalkan." COLOR_RESET "\n");
                    }
                }
                else if(trans.metodePembayaran == 2) { // QRIS
                    printf("\n" COLOR_BLUE "Instruksi QRIS: Silakan input nominal yang PAS." COLOR_RESET "\n");
                    while(1) {
                        printf("Masukkan Nominal Bayar (Wajib Rp %d): ", trans.totalBayar);
                        scanf("%d", &trans.uangDibayar);

                        if(trans.uangDibayar == trans.totalBayar) {
                            printf("\n" COLOR_GREEN "Pembayaran QRIS Berhasil Tervalidasi!" COLOR_RESET "\n");
                            trans.kembalian = 0;
                            transaksiSah = 1;
                            break;
                        } else {
                            printf(COLOR_RED "Nominal tidak sesuai! QRIS harus uang pas." COLOR_RESET "\n");
                        }
                    }
                } else {
                    printf("Metode tidak valid.\n");
                }

                if(transaksiSah) {
                    riwayatTransaksi[jumlahTransaksi] = trans;
                    jumlahTransaksi++;
                    printf("\n" COLOR_GREEN "TRANSAKSI BERHASIL DISIMPAN!" COLOR_RESET "\n");
                } else {
                    for(int k=0; k<trans.itemCount; k++) {
                        for(int b=0; b<jumlahBarang; b++) {
                            if(daftarBarang[b].kode == trans.kodeBarang[k]) {
                                daftarBarang[b].stok += trans.jumlahBeli[k];
                            }
                        }
                    }
                }
            }
            printf("Tekan enter...");
            cleanBuffer(); getchar();
        }

        // 3. LIHAT DAFTAR TRANSAKSI
        else if(pilih == 3) {
            clearScreen();
            printf("===== RIWAYAT TRANSAKSI (STRUK) =====\n\n");
            if(jumlahTransaksi == 0) {
                printf("Belum ada transaksi.\n");
            } else {
                for(int i=0; i<jumlahTransaksi; i++) {
                    printf("No. Transaksi : %d (Tgl: %s)\n", riwayatTransaksi[i].noTransaksi, riwayatTransaksi[i].tanggal);
                    printf("Metode        : %s\n", (riwayatTransaksi[i].metodePembayaran == 1) ? "CASH" : "QRIS");
                    printf("Item:\n");
                    for(int j=0; j<riwayatTransaksi[i].itemCount; j++){
                        printf(" - %s x%d (Rp %d)\n",
                            riwayatTransaksi[i].namaBarang[j],
                            riwayatTransaksi[i].jumlahBeli[j],
                            riwayatTransaksi[i].subtotal[j]);
                    }
                    printf("Total: %d | Diskon: %d | Bayar: %d\n",
                        riwayatTransaksi[i].totalKotor,
                        riwayatTransaksi[i].diskon,
                        riwayatTransaksi[i].totalBayar);
                    printf("----------------------------------------\n");
                }
            }
            printf("\nTekan enter...");
            cleanBuffer(); getchar();
        }

        // 4. FITUR RETURN BARANG
        else if(pilih == 4) {
            clearScreen();
            printf("===== RETURN BARANG =====\n\n");
            int noTrans, kodeBarangReturn, foundTrans = -1;

            printf("Masukkan No Transaksi: ");
            scanf("%d", &noTrans);

            for(int i=0; i<jumlahTransaksi; i++) {
                if(riwayatTransaksi[i].noTransaksi == noTrans) {
                    foundTrans = i;
                    break;
                }
            }

            if(foundTrans != -1) {
                if(riwayatTransaksi[foundTrans].metodePembayaran == 2) {
                    printf("\n" COLOR_RED "MAAF! Transaksi QRIS tidak dapat direturn (Kebijakan Toko)." COLOR_RESET "\n");
                } else {
                    printf("\nDetail Transaksi Ditemukan (CASH).\n");
                    printf("Masukkan Kode Barang yang ingin direturn: ");
                    scanf("%d", &kodeBarangReturn);

                    int foundItem = 0;
                    for(int j=0; j<riwayatTransaksi[foundTrans].itemCount; j++) {
                        if(riwayatTransaksi[foundTrans].kodeBarang[j] == kodeBarangReturn) {
                            for(int b=0; b<jumlahBarang; b++) {
                                if(daftarBarang[b].kode == kodeBarangReturn) {
                                    daftarBarang[b].stok += riwayatTransaksi[foundTrans].jumlahBeli[j];
                                    printf("\n" COLOR_GREEN "Stok %s dikembalikan ke gudang (+%d)." COLOR_RESET "\n",
                                        daftarBarang[b].nama, riwayatTransaksi[foundTrans].jumlahBeli[j]);
                                }
                            }
                            printf("Silakan kembalikan uang customer sebesar: Rp %d\n",
                                riwayatTransaksi[foundTrans].subtotal[j]);
                            foundItem = 1;
                            break;
                        }
                    }
                    if(!foundItem) printf("Barang tidak ada dalam transaksi tersebut.\n");
                }
            } else {
                printf("Nomor transaksi tidak ditemukan.\n");
            }
            printf("\nTekan enter...");
            cleanBuffer(); getchar();
        }

        // 5. RUMAH POLA (INTEGRASI ANIMASI LENGKAP)
        else if(pilih == 5) {
            char ulangRumah;
            do {
                clearScreen();
                printf("=============================================================\n");
                printf("|       Rumah Pola (Animasi Slow Motion & Rapi)             |\n");
                printf("=============================================================\n\n");

                int tinggiRumah;
                char bahanInput[50];
                char bahan;

                printf("Masukkan Tinggi Rumah : ");
                scanf("%d", &tinggiRumah);

                printf("Masukkan Karakter Bahan (misal * atau #): ");
                scanf("%s", bahanInput);
                bahan = bahanInput[0];

                printf("\nSedang membangun...");
                printf("\n\n");

                //  KONFIGURASI ANIMASI 
                int slow = 1000; // 500ms = 0.5 detik (Lambat & Halus)
                char* marginLayar = "\t\t";

                // 1. ATAP ATAS (CEROBONG)
                for (int i = 0; i < tinggiRumah; i++) {
                    printf("%s", marginLayar);
                    // Spasi agar cerobong di tengah
                    for(int s=0; s < (tinggiRumah - 1); s++) printf(" ");

                    printf(COLOR_WHITE);
                    for (int j = 0; j < 5; j++) printf("%c", bahan);
                    printf(COLOR_RESET "\n");

                    delay(slow);
                }

                // 2. ATAP TENGAH (HIJAU & PUTIH)
                for (int i = 0; i < tinggiRumah; i++) {
                    printf("%s", marginLayar);
                    // Spasi segitiga
                    for (int s = 0; s < (tinggiRumah - i - 1); s++) printf(" ");

                    printf(COLOR_GREEN);
                    for (int j = 0; j < (2 * i + 3); j++) printf("%c", bahan);
                    printf(COLOR_RESET);

                    printf(COLOR_WHITE);
                    for (int k = 0; k < 15; k++) printf("%c", bahan);
                    printf(COLOR_RESET "\n");

                    delay(slow);
                }

                // 3. BADAN RUMAH (MERAH & UNGU)
                for (int i = 0; i < tinggiRumah; i++) {
                    printf("%s", marginLayar);
                    printf(COLOR_RED);
                    for (int j = 0; j < 11; j++) printf("%c", bahan);
                    printf(COLOR_RESET);

                    printf(COLOR_PURPLE);
                    for (int j = 0; j < 15; j++) printf("%c", bahan);
                    printf(COLOR_RESET "\n");

                    delay(slow);
                }

                printf("\nRumah Selesai Dibangun!\n");
                printf("Ulangi bangun rumah? (y/n): ");
                cleanBuffer();
                scanf("%c", &ulangRumah);

            } while(ulangRumah == 'y' || ulangRumah == 'Y');
        }

        // 6. BENDERA NEGARA (INDONESIA)
        else if(pilih == 6) {
            clearScreen();
            printf("===== BENDERA INDONESIA =====\n\n");

            int tinggi = 8;
            int lebar = 24;

            for(int i=0; i<tinggi; i++) {
                for(int j=0; j<lebar; j++) {
                    if(i < tinggi/2) {
                        printf(BG_RED " " COLOR_RESET);
                    } else {
                        printf(BG_WHITE " " COLOR_RESET);
                    }
                }
                printf("\n");
            }
            printf("\nNKRI HARGA MATI!\n");
            printf("\nTekan enter untuk kembali...");
            cleanBuffer(); getchar();
        }

        // 7. AUTHOR
        else if(pilih == 7) {
            clearScreen();
            printf("==============================\n");
            printf("            AUTHOR            \n");
            printf("==============================\n\n");
            printf("1. Dhea Adventri - 672021275\n");
            printf("2. Nathaniel Ananta Putra - 672024042\n"); // EDIT DISINI
            printf("3. Alfine Argracia Tonapa - 672025233\n");
            printf("4. Haryono Wibowo - 672025196\n");
            printf("5. Kornelius Ani - 672025190\n");
            printf("\nTekan enter untuk kembali...");
            cleanBuffer(); getchar();
        }

        // 8. EXIT
        else if(pilih == 8) {
            char yakin;
            printf("\nApakah anda yakin ingin keluar? (y/n): ");
            scanf(" %c", &yakin);
            if (yakin == 'y' || yakin == 'Y') {
                printf("\nTerima kasih! Sampai Jumpa.\n");
                break;
            } else {
                printf("Batal keluar.\n");
                cleanBuffer();
            }
        }
        else {
            printf("Pilihan salah!\n");
            cleanBuffer();
        }
    }

    return 0;
}


