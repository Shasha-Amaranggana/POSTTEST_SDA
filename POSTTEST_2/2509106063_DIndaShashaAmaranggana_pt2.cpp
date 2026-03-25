#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

/* STRUCT
════════════════════════════════════════════════════*/
struct Pasien {
    int idPasien;
    string namaPasien;
    int umurPasien;
    string jenisPasien;};

struct Perawatan {
    int idPerawatan;
    string namaPerawatan;
    float harga;};

struct Kunjungan {
    int idKunjungan;
    int idPasien;
    int idPerawatan[5];
    int jumlahPerawatan;};

Pasien daftarPasien[100] {
    {9001, "Oyin", 6, "Kucing"},
    {9002, "Ayen", 6, "Kucing"},
    {9003, "Embul", 6, "Kucing"}};
    
Perawatan daftarPerawatan[10] = {
    {401, "Grooming", 150000},
    {402, "Vaksinasi", 200000},
    {403, "Konsultasi", 100000},
    {404, "Penitipan", 50000},
    {405, "Sterilisasi", 500000}};

Kunjungan daftarKunjungan[100] = {
    {60001, 9001, {401, 402}, 2},
    {60002, 9002, {403}, 1},
    {60003, 9003, {404, 405}, 2}};

int jumlahPasien = 3;
int jumlahPerawatan = 5;
int jumlahKunjungan = 3;


/* FUNGSI BANTUAN TAMPILAN DOANG
════════════════════════════════════════════════════*/
void judul_subjudul(string subjudul) {
    int spasiKiri = (70 - subjudul.length()) / 2;
    cout << "══════════════════════════════════════════════════════════════════════" << endl;
    cout << "│                     🐱   PAWCARE__PETSHOP   🐱                     │" << endl;
    cout << "══════════════════════════════════════════════════════════════════════" << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;
    cout << string(spasiKiri, ' ') << subjudul << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;}

void tampilPesan(int nilai, string pesan) {
    cout << "" << endl;
    cout << setw((70 + 26) / 2) << "=========================" << endl;
    cout << setw((70 + nilai) / 2) << pesan << endl;
    cout << setw((70 + 26) / 2) << "=========================" << endl;
    cout << "" << endl;}

void tampilPeringatan(int nilai, string pesan) {
    cout << "" << endl;
    cout << setw((70 + 34) / 2) << "---------------------------------" << endl;
    cout << setw((70 + nilai) / 2) << pesan << endl;
    cout << setw((70 + 34) / 2) << "---------------------------------" << endl;
    cout << "" << endl;}

int scrollMenu(int &pilih, int jumlahMenu) {
    int tombol = getch();

    if (tombol == 224 || tombol == 0) {
        tombol = getch();
        if (tombol == 72) {
            pilih = (pilih - 1 + jumlahMenu) % jumlahMenu;}
        else if (tombol == 80) {
            pilih = (pilih + 1) % jumlahMenu;}}
    else if (tombol == 13) {
        return -1;}

    return pilih;} 


/* PROSEDUR DAN FUNGSI BANTUAN
════════════════════════════════════════════════════*/
int bikinId(string jenis) {
    if (jenis == "Pasien") {
        if (jumlahPasien == 0){
            return 9001;}
        return daftarPasien[jumlahPasien - 1].idPasien + 1;}
    else if (jenis == "Perawatan") {
        if (jumlahPerawatan == 0){
            return 401;}
        return daftarPerawatan[jumlahPerawatan - 1].idPerawatan + 1;}
    else if (jenis == "Kunjungan") {
        if (jumlahKunjungan == 0) {
            return 60001;}
        return daftarKunjungan[jumlahKunjungan - 1].idKunjungan + 1;}
    return -1;
}


void swapNamaPasien(Pasien *a, Pasien *b) {
    Pasien temp = *a;
    *a = *b;
    *b = temp;}

void swapNamaPerawatan(Perawatan *a, Perawatan *b) {
    Perawatan temp = *a;
    *a = *b;
    *b = temp;}

void swapHargaPerawatan(Perawatan *a, Perawatan *b) {
    Perawatan temp = *a;
    *a = *b;
    *b = temp;}


void bubbleSortNamaPasien(Pasien *arr, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->namaPasien > (arr + j + 1)->namaPasien) {
                swapNamaPasien(&arr[j], &arr[j + 1]);}}}
}

void bubbleSortNamaPerawatan(Perawatan *arr, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if ((arr + j)->namaPerawatan > (arr + j + 1)->namaPerawatan) {
                swapNamaPerawatan(&arr[j], &arr[j + 1]);}}}
}

void selectionSortHargaPerawatan(Perawatan *arr, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlah; j++) {
            if ((arr + j)->harga < (arr + minIndex)->harga) {
                minIndex = j;}}
        if (minIndex != i) {
            swapHargaPerawatan(&arr[i], &arr[minIndex]);}}
}


/*PENJELASAN ITERASI FIBONACCI SEARCH
1. Program membuat deret Fibonacci sampai nilainya >= jumlah data.
2. Fibonacci digunakan untuk membagi array menjadi beberapa bagian untuk di cek.
3. Pada setiap iterasi:
   - Program mengecek index = offset + fib2
   - Jika nilai lebih kecil → cari ke kanan
   - Jika nilai lebih besar → cari ke kiri
4. Range pencarian diperkecil menggunakan bilangan Fibonacci berikutnya.
5. Proses diulang sampai data ditemukan atau range habis.
6. Jika tersisa 1 elemen, dilakukan pengecekan terakhir.*/

int fibonacciSearchIdPasien(Pasien *arr, int jumlah, int target) {
    int iterasi = 1; // Inisialisasi iterasi untuk di tampilan terminal
    int fib2 = 0, fib1 = 1, fib = fib2 + fib1; // Inisialisasi untuk menentukan posisi index yang akan dicek
    
    // Membuat bilangan Fibonacci sampai >= jumlah data. Tujuannya agar range pencarian bisa mencakup seluruh array//
    while (fib < jumlah) {
        fib2 = fib1; fib1 = fib; fib = fib2 + fib1;}
    // Inisialisasi offset untuk menentukan batas kiri pencarian (index terakhir yang sudah dicek)
    int offset = -1;

    // Selagi masih ada range Fibonacci yang bisa dicek
    while (fib > 1) {
        int i;

        // Menentukan index yang akan dicek. Offset + fib2 = posisi pembagian array berdasarkan Fibonacci
        if (offset + fib2 < jumlah - 1) {
            i = offset + fib2;}
        else {
            i = jumlah - 1;}
        cout << "[Iterasi ke-" << iterasi++ << "]"<< endl;
        cout << "Cek index: " << i << " | ID: " << (arr + i)->idPasien << endl;

        // Kalau ID di index lebih kecil dari target, berarti target ada di sebelah kanan
        if ((arr + i)->idPasien < target) {
            cout << "⤷ ID lebih besar → geser ke kanan\n\n";
            // Geser range pencarian ke kanan
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        // Kalau ID di index lebih besar dari target, berarti target ada di sebelah kiri
        else if ((arr + i)->idPasien > target) {
            cout << "⤷ ID lebih kecil → geser ke kiri\n\n";
            // Geser range ke kiri
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        // Kalau ID di index sama dengan target, berarti target ditemukan
        else {
            cout << "⤷ ID ditemukan!\n";
            return i;}}

    // Pengecekan terakhir jaga-jaga jika masih tersisa 1 elemen
    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idPasien == target){
        cout << "Cek terakhir di index: " << offset + 1 << endl;
        cout << "ID ditemukan!\n";
        return offset + 1;}

    // Jika target tidak ditemukan
    cout << "ID tidak ditemukan!\n";
    return -1;
}

int fibonacciSearchIdPerawatan(Perawatan *arr, int jumlah, int target) {
    int iterasi = 1;
    int fib2 = 0, fib1 = 1, fib = fib2 + fib1;

    while (fib < jumlah) {
        fib2 = fib1; fib1 = fib; fib = fib2 + fib1;}
    int offset = -1;

    while (fib > 1) {
        int i;
        if (offset + fib2 < jumlah - 1) {
            i = offset + fib2;}
        else {
            i = jumlah - 1;}
        cout << "[Iterasi ke-" << iterasi++ << "]"<< endl;
        cout << "Cek index: " << i << " | ID: " << (arr + i)->idPerawatan << endl;

        if ((arr + i)->idPerawatan < target) {
            cout << "⤷ ID lebih besar → geser ke kanan\n\n";
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        else if ((arr + i)->idPerawatan > target) {
            cout << "⤷ ID lebih kecil → geser ke kiri\n\n";
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        else {
            cout << "⤷ ID ditemukan!\n";
            return i;}}

    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idPerawatan == target){
        cout << "Cek terakhir di index: " << offset + 1 << endl;
        cout << "ID ditemukan!\n";
        return offset + 1;}

    cout << "ID tidak ditemukan!\n";
    return -1;
}

int fibonacciSearchIdKunjungan(Kunjungan *arr, int jumlah, int target) {
    int iterasi = 1;
    int fib2 = 0, fib1 = 1, fib = fib2 + fib1;
    
    while (fib < jumlah) {
        fib2 = fib1; fib1 = fib; fib = fib2 + fib1;}
    int offset = -1;

    while (fib > 1) {
        int i;
        if (offset + fib2 < jumlah - 1) {
            i = offset + fib2;}
        else {
            i = jumlah - 1;}
        cout << "[Iterasi ke-" << iterasi++ << "]"<< endl;
        cout << "Cek index: " << i << " | ID: " << (arr + i)->idKunjungan << endl;

        if ((arr + i)->idKunjungan < target) {
            cout << "⤷ ID lebih besar → geser ke kanan\n\n";
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        else if ((arr + i)->idKunjungan > target) {
            cout << "⤷ ID lebih kecil → geser ke kiri\n\n";
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        else {
            cout << "⤷ ID ditemukan!\n";
            return i;}}

    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idKunjungan == target){
        cout << "Cek terakhir di index: " << offset + 1 << endl;
        cout << "ID ditemukan!\n";
        return offset + 1;}

    cout << "ID tidak ditemukan!\n";
    return -1;
}


/*PENJELASAN ALGORITMA/ITERASI LINEAR SEARCH
1. Linear Search mencari data dari index pertama sampai terakhir.
2. Setiap iterasi akan mengecek satu per satu elemen array.
3. Jika data sama dengan target, pencarian berhenti.
4. Jika belum sama, lanjut ke index berikutnya.
5. Jika semua data sudah dicek dan tidak ditemukan, maka fungsi mengembalikan -1.*/

int linearSearchNamaPasien(Pasien *arr, int jumlah, string target) {
    for (int i = 0; i < jumlah; i++) { // Perulangan dari index 0 sampai jumlah data
        cout << "[Iterasi ke-" << i + 1 << "]"<< endl;
        cout << "Cek index: " << i << " | Nama: " << (arr + i)->namaPasien << endl;

        // Kalau nama di index sama dengan target, berarti target ditemukan
        if ((arr + i)->namaPasien == target) {
            cout << "⤷ Nama ditemukan!\n";
            return i;} // Mengembalikan index nama

        // Kalau nama di index belum sama dengan target, berarti target belum ditemukan
        cout << "⤷ Nama belum ditemukan!\n\n";}

    // Kalau semua data dicek tapi masih belum ada yang sama dengan target, berarti target tidak ditemukan
    cout << "⤷ Nama tidak ditemukan!\n\n";
    return -1;}

int linearSearchNamaPerawatan(Perawatan *arr, int jumlah, string target) {
    for (int i = 0; i < jumlah; i++) {
        cout << "[Iterasi ke-" << i + 1 << "]"<< endl;
        cout << "Cek index: " << i << " | Nama: " << (arr + i)->namaPerawatan << endl;

        if ((arr + i)->namaPerawatan == target) {
            cout << "⤷ Nama ditemukan!\n";
            return i;}
        cout << "⤷ Nama belum ditemukan!\n\n";}
        
    cout << "⤷ Nama tidak ditemukan!\n\n";
    return -1;}


/* CRUD
════════════════════════════════════════════════════*/
void tambahPasien(Pasien *arr, int &jumlah) {
    string jenisPasien[] = {"    Anjing", "    Kucing", "    Kelinci"};
    int pilih = 0;

    (arr + jumlah)->idPasien = bikinId("Pasien");

    while (true) {
        system("cls"); judul_subjudul("✚ PASIEN BARU"); cout << endl;

        cout << "ID Otomatis  : " << (arr + jumlah)->idPasien << endl;
        cout << "Jenis        : " << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << ">  " << jenisPasien[i] << endl;}
            else {
                cout << "   " << jenisPasien[i] << endl;}}
        int hasil = scrollMenu(pilih, 3);
        
        if (hasil == -1) {
            if (pilih == 0) {
                (arr + jumlah)->jenisPasien = "Anjing";}
            else if (pilih == 1) {
                (arr + jumlah)->jenisPasien = "Kucing";}
            else if (pilih == 2) {
                (arr + jumlah)->jenisPasien = "Kelinci";}
            break;}
    }

    system("cls"); judul_subjudul("✚ PASIEN BARU"); cout << endl;

    cout << "ID Otomatis  : " << (arr + jumlah)->idPasien << endl;
    cout << "Jenis        : " << (arr + jumlah)->jenisPasien << endl;
    cout << "Nama         : "; cin >> (arr + jumlah)->namaPasien;
    cout << "Umur         : "; cin >> (arr + jumlah)->umurPasien;
    if ((arr + jumlah)->umurPasien <= 0) {
        tampilPeringatan(24, "Umur pasien tidak valid!");
        return;}

    jumlah++;
    tampilPesan(34,  "Data pasien berhasil ditambahkan!");
}

void tambahPerawatan(Perawatan *arr, int &jumlah) {
    (arr + jumlah)->idPerawatan = bikinId("Perawatan");

    cout << "ID Otomatis  : " << (arr + jumlah)->idPerawatan << endl;
    cout << "Nama         : "; cin >> (arr + jumlah)->namaPerawatan;
    cout << "Harga        : "; cin >> (arr + jumlah)->harga;
    if ((arr + jumlah)->harga <= 0) {
        tampilPeringatan(28, "Harga perawatan tidak valid!");
        return;}

    jumlah++;
    tampilPesan(36,  "Data perawatan berhasil ditambahkan!");
}

void tambahKunjungan(Kunjungan *arr, int &jumlah, Pasien *daftarPasien, int jumlahPasien, Perawatan *daftarPerawatan, int jumlahPerawatan) {
    string submenuKunjungan[] = {
        "    1 | Tambah Perawatan",
        "    2 | Simpan Data",
        "    3 | Kembali"};
    int pilih = 0;
    int idCari;

    (arr + jumlah)->idKunjungan = bikinId("Kunjungan");
    (arr + jumlah)->jumlahPerawatan = 0;

    system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;

    cout << "ID Otomatis    : " << (arr + jumlah)->idKunjungan << endl;
    cout << "ID Pasien      : "; cin >> idCari;
    int indexPasien = fibonacciSearchIdPasien(daftarPasien, jumlahPasien, idCari);
    if (indexPasien == -1) {
        tampilPeringatan(58, "ID pasien tidak ditemukan! Data kunjungan gagal disimpan."); system("pause");
        return;}

    (arr + jumlah)->idPasien = daftarPasien[indexPasien].idPasien;

    while (true) {
        system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;

        cout << "ID Otomatis    : " << (arr + jumlah)->idKunjungan << endl;
        cout << "Pasien         : " << daftarPasien[indexPasien].namaPasien << endl;
        cout << "ID Perawatan   : ";
        if ((arr + jumlah)->jumlahPerawatan == 0) {
            cout << "Belum ada perawatan ditambahkan" << endl;}
        else {
            for (int i = 0; i < (arr + jumlah)->jumlahPerawatan; i++) {
                cout << (arr + jumlah)->idPerawatan[i];
                if (i < (arr + jumlah)->jumlahPerawatan - 1) {
                    cout << ", ";}}
            cout << endl;}
        cout << endl;

        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << "> " << submenuKunjungan[i] << endl;}
            else {
                cout << "  " << submenuKunjungan[i] << endl;}}
        int hasil = scrollMenu(pilih, 3);
        
        if (hasil == -1) {

            // A. JUMLAH PERAWATAN SUDAH MAKSIMAL
            if (pilih == 0 && (arr + jumlah)->jumlahPerawatan >= 5) {
                tampilPeringatan(32, "Jumlah perawatan sudah maksimal!"); system("pause");}

            // B. TAMBAH PERAWATAN
            else if (pilih == 0) {
                system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;
                cout << "ID otomatis    : " << (arr + jumlah)->idKunjungan << endl;
                cout << "Pasien         : " << daftarPasien[indexPasien].namaPasien << endl;
                cout << "ID Perawatan   : ";
                if ((arr + jumlah)->jumlahPerawatan == 0) {
                    cout << "Belum ada perawatan ditambahkan" << endl;}
                else {
                    for (int i = 0; i < (arr + jumlah)->jumlahPerawatan; i++) {
                        cout << (arr + jumlah)->idPerawatan[i];
                        if (i < (arr + jumlah)->jumlahPerawatan - 1) {
                            cout << ", ";}}
                    cout << endl;}

                cout << "\nID Perawatan " << (arr + jumlah)->jumlahPerawatan + 1 << " : "; cin >> idCari;
                int indexPerawatan = fibonacciSearchIdPerawatan(daftarPerawatan, jumlahPerawatan, idCari);

                if (indexPerawatan != -1) {
                    (arr + jumlah)->idPerawatan[(arr + jumlah)->jumlahPerawatan] = daftarPerawatan[indexPerawatan].idPerawatan;
                    (arr + jumlah)->jumlahPerawatan++;}
                else {
                    tampilPeringatan(30, "ID perawatan tidak ditemukan!"); system("pause");}}

            // C. SIMPAN DATA
            else if (pilih == 1) {
                if ((arr + jumlah)->jumlahPerawatan == 0) {
                    tampilPeringatan(68, "Belum ada perawatan yang ditambahkan! Data kunjungan gagal disimpan."); system("pause");}
                else {
                    jumlah++;
                    tampilPesan(36, "Data kunjungan berhasil ditambahkan!"); system("pause");
                    return;}}

            // D. KEMBALI
            else if (pilih == 2) {
                return;}}
    }
}



void tampilPasien(Pasien *arr, int jumlah) {
    if (jumlah == 0) {
        tampilPesan(28, "Anda belum memiliki data pasien.");}
    else {
        cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
        cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
        for(int i = 0; i < jumlah; i++){
            cout << left
                << setw(8) << (arr + i)->idPasien << "│ "<< setw(27) << (arr + i)->namaPasien << "│ "
                << setw(13) << (arr + i)->umurPasien << "│ " << setw(15) << (arr + i)->jenisPasien << endl;
            cout << right;}
        cout << endl;}
}

void tampilPerawatan(Perawatan *arr, int jumlah) {
    if (jumlah == 0) {
        tampilPesan(28, "Anda belum memiliki data perawatan.");}
    else {
        cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
        cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
        for(int i = 0; i < jumlah; i++){
            cout << left
                << setw(8) << (arr + i)->idPerawatan << "│ "<< setw(44) << (arr + i)->namaPerawatan << "│ "
                << setw(13) << (arr + i)->harga << endl;
            cout << right;}
        cout << endl;}
}

void tampilKunjungan(Kunjungan *arr, int jumlah) {
    if (jumlah == 0) {
        tampilPesan(28, "Anda belum memiliki data kunjungan.");}
    else {
        cout << "   ID   │ ID PASIEN │         ID PERAWATAN         │ JUMLAH PERAWATAN " << endl;
        cout << "────────╋───────────╋──────────────────────────────╋──────────────────" << endl;
        for(int i = 0; i < jumlah; i++){
            cout << left
                << setw(8) << (arr + i)->idKunjungan << "│ "<< setw(10) << (arr + i)->idPasien << "│ ";
            string daftar = "";
                for (int j = 0; j < (arr + i)->jumlahPerawatan; j++) {
                    daftar += to_string((arr + i)->idPerawatan[j]);
                    if (j < (arr + i)->jumlahPerawatan - 1) {
                        daftar += ", ";}}
            cout << setw(29) << daftar << "│ " << setw(15) << (arr + i)->jumlahPerawatan << endl;
            cout << right;}
        cout << endl;}
}


void menuDataPasien(Pasien *arr, int jumlah) {
    string menu[] = {
        "    1 | Cari ID Pasien",
        "    2 | Cari Nama Pasien",
        "    3 | Urutkan Nama Pasien",
        "    4 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU CARI HEWAN"); cout << endl;

        for (int i = 0; i < 4; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}

        cout << endl << endl; tampilPasien(arr, jumlah);

        int hasil = scrollMenu(pilih, 4);
        if (hasil == -1) {

            // A. CARI ID PASIEN
            if (pilih == 0) {
                system("cls"); judul_subjudul("CARI ID PASIEN"); cout << endl;
                cout << "\nMasukkan ID Pasien: "; int idPasien; cin >> idPasien;
                cout << "Mencari...\n" << endl;
                int indexPasien = fibonacciSearchIdPasien(arr, jumlah, idPasien);
                if (indexPasien != -1) {
                    tampilPesan(20, "ID pasien ditemukan!"); cout << endl;
                    cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
                    cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
                    cout << left
                        << setw(8) << (arr + indexPasien)->idPasien << "│ "<< setw(27) << (arr + indexPasien)->namaPasien << "│ "
                        << setw(13) << (arr + indexPasien)->umurPasien << "│ " << setw(15) << (arr + indexPasien)->jenisPasien << endl;
                    cout << right; cout << endl;}
                else {
                    tampilPesan(26, "ID pasien tidak ditemukan!");}
                cout << endl; system("pause");}

            // B. CARI NAMA PASIEN
            else if (pilih == 1) {
                system("cls"); judul_subjudul("CARI NAMA PASIEN"); cout << endl;
                cout << "\nMasukkan Nama Pasien: "; string namaPasien; cin >> namaPasien;
                cout << "Mencari...\n" << endl;
                int indexPasien = linearSearchNamaPasien(arr, jumlah, namaPasien);
                if (indexPasien != -1) {
                    tampilPesan(22, "Nama pasien ditemukan!"); cout << endl;
                    cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
                    cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
                    cout << left
                        << setw(8) << (arr + indexPasien)->idPasien << "│ "<< setw(27) << (arr + indexPasien)->namaPasien << "│ "
                        << setw(13) << (arr + indexPasien)->umurPasien << "│ " << setw(15) << (arr + indexPasien)->jenisPasien << endl;
                    cout << right; cout << endl;}
                else {
                    tampilPesan(28, "Nama pasien tidak ditemukan!");}
                cout << endl; system("pause");}

            // C. URUTKAN NAMA PASIEN
            else if (pilih == 2) {
                system("cls"); judul_subjudul("URUTKAN NAMA PASIEN"); cout << endl;
                Pasien *arrPasien = new Pasien[jumlah];
                for (int i = 0; i < jumlah; i++) {
                    arrPasien[i] = arr[i];}
                bubbleSortNamaPasien(arrPasien, jumlah);
                tampilPasien(arrPasien, jumlah);
                delete[] arrPasien;
                system("pause");}

            // D. KEMBALI
            else if (pilih == 3) {
                break;}}
    }
}

void menuDataPerawatan(Perawatan *arr, int jumlah) {
    string menu[] = {
        "    1 | Cari ID Perawatan",
        "    2 | Cari Nama Perawatan",
        "    3 | Urutkan Nama Perawatan",
        "    4 | Urutkan Harga Perawatan",
        "    5 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU CARI PERAWATAN"); cout << endl;

        for (int i = 0; i < 5; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}

        cout << endl << endl; tampilPerawatan(arr, jumlah);

        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {

            // A. CARI ID PERAWATAN
            if (pilih == 0) {
                system("cls"); judul_subjudul("CARI ID PERAWATAN"); cout << endl;
                cout << "\nMasukkan ID Perawatan: "; int idPerawatan; cin >> idPerawatan;
                cout << "Mencari...\n" << endl;
                int indexPerawatan = fibonacciSearchIdPerawatan(arr, jumlah, idPerawatan);
                if (indexPerawatan != -1) {
                    tampilPesan(24, "ID perawatan ditemukan!"); cout << endl;
                    cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                    cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                    cout << left
                        << setw(8) << (arr + indexPerawatan)->idPerawatan << "│ "<< setw(44) << (arr + indexPerawatan)->namaPerawatan << "│ "
                        << setw(13) << (arr + indexPerawatan)->harga << endl;
                    cout << right; cout << endl;}
                else {
                    tampilPesan(30, "ID perawatan tidak ditemukan!");}
                cout << endl; system("pause");}

            // B. CARI NAMA PERAWATAN
            else if (pilih == 1) {
                system("cls"); judul_subjudul("CARI NAMA PERAWATAN"); cout << endl;
                cout << "\nMasukkan Nama Perawatan: "; string namaPerawatan; cin >> namaPerawatan;
                cout << "Mencari...\n" << endl;
                int indexPerawatan = linearSearchNamaPerawatan(arr, jumlah, namaPerawatan);
                if (indexPerawatan != -1) {
                    tampilPesan(26, "Nama perawatan ditemukan!"); cout << endl;
                    cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                    cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                    cout << left
                        << setw(8) << (arr + indexPerawatan)->idPerawatan << "│ "<< setw(44) << (arr + indexPerawatan)->namaPerawatan << "│ "
                        << setw(13) << (arr + indexPerawatan)->harga << endl;
                    cout << right; cout << endl;}
                else {
                    tampilPesan(32, "Nama perawatan tidak ditemukan!");}
                cout << endl; system("pause");}

            // C. URUTKAN NAMA PERAWATAN
            else if (pilih == 2) {
                system("cls"); judul_subjudul("URUTKAN NAMA PERAWATAN"); cout << endl;
                Perawatan *arrPerawatan = new Perawatan[jumlah];
                for (int i = 0; i < jumlah; i++) {
                    arrPerawatan[i] = arr[i];}
                bubbleSortNamaPerawatan(arrPerawatan, jumlah);
                tampilPerawatan(arrPerawatan, jumlah);
                delete[] arrPerawatan;
                system("pause");}

            // D. URUTKAN HARGA PERAWATAN
            else if (pilih == 3) {
                system("cls"); judul_subjudul("URUTKAN HARGA PERAWATAN"); cout << endl;
                Perawatan *arrPerawatan = new Perawatan[jumlah];
                for (int i = 0; i < jumlah; i++) {
                    arrPerawatan[i] = arr[i];}
                selectionSortHargaPerawatan(arrPerawatan, jumlah);
                tampilPerawatan(arrPerawatan, jumlah);
                delete[] arrPerawatan;
                system("pause");}

            // D. KEMBALI
            else if (pilih == 4) {
                break;}}
    }
}

void menuDataKunjungan(Kunjungan *arr, int jumlah) {
    string menu[] = {
        "   1 | Cari ID Kunjungan",
        "   2 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU CARI KUNJUNGAN"); cout << endl;

        for (int i = 0; i < 2; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}

        cout << endl << endl; tampilKunjungan(arr, jumlah);

        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {

            // A. CARI ID KUNJUNGAN
            if (pilih == 0) {
                system("cls"); judul_subjudul("CARI ID KUNJUNGAN"); cout << endl;
                cout << "\nMasukkan ID Kunjungan: "; int idKunjungan; cin >> idKunjungan;
                cout << "Mencari...\n" << endl;
                int indexKunjungan = fibonacciSearchIdKunjungan(arr, jumlah, idKunjungan);
                if (indexKunjungan != -1) {
                    tampilPesan(24, "ID kunjungan ditemukan!");
                    cout << endl;
                    cout << "   ID   │ ID PASIEN │         ID PERAWATAN         │ JUMLAH PERAWATAN " << endl;
                    cout << "────────╋───────────╋──────────────────────────────╋──────────────────" << endl;
                    cout << left
                        << setw(8) << (arr + indexKunjungan)->idKunjungan << "│ "<< setw(10) << (arr + indexKunjungan)->idPasien << "│ ";
                    string daftar = "";
                        for (int j = 0; j < (arr + indexKunjungan)->jumlahPerawatan; j++) {
                            daftar += to_string((arr + indexKunjungan)->idPerawatan[j]);
                            if (j < (arr + indexKunjungan)->jumlahPerawatan - 1) {
                                daftar += ", ";}}
                    cout << setw(29) << daftar << "│ " << setw(15) << (arr + indexKunjungan)->jumlahPerawatan << endl;
                    cout << right;}
                else {
                    tampilPesan(30, "ID kunjungan tidak ditemukan!");}
                cout << endl; system("pause");}

            // B. KEMBALI
            else if (pilih == 1) {
                break;}}
    }
}


/* PROGRAM UTAMA
════════════════════════════════════════════════════*/
int main() {
    SetConsoleOutputCP(65001);
    string menuMain[] = {
        "    『 ✚  Kunjungan Baru 』",
        "    『 ✚  Pasien Baru    』",
        "    『 ✚  Perawatan Baru 』",
        "     1 | Data Kunjungan",
        "     2 | Data Pasien",
        "     3 | Data Perawatan ",
        "    『       KELUAR       』"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("SELAMAT DATANG! PELIHARAAN ANDA DIJAMIN BAHAGIA SENTOSA" ); cout << endl;
        
        for (int i = 0; i < 7; i++) {
            if (i == pilih) {
                cout << "> " << menuMain[i] << endl;}
            else {
                cout << "  " << menuMain[i] << endl;}
            if ( i == 2 || i == 5) {
                cout << endl;}}
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {

            // A. KUNJUNGAN BARU
            if (pilih == 0) {
                tambahKunjungan(daftarKunjungan, jumlahKunjungan, daftarPasien, jumlahPasien, daftarPerawatan, jumlahPerawatan);}
            
            // B. PASIEN BARU
            else if (pilih == 1) {
                tambahPasien(daftarPasien, jumlahPasien);
                system("pause");}

            // C. PERAWATAN BARU
            else if (pilih == 2) {
                system("cls"); judul_subjudul("✚ PERAWATAN BARU"); cout << endl;
                tambahPerawatan(daftarPerawatan, jumlahPerawatan);
                system("pause");}
            
            // D. DATA KUNJUNGAN
            else if (pilih == 3) {
                system("cls"); judul_subjudul("DATA KUNJUNGAN"); cout << endl;
                menuDataKunjungan(daftarKunjungan, jumlahKunjungan);}

            // E. DATA PASIEN
            else if (pilih == 4) {
                system("cls"); judul_subjudul("DATA PASIEN"); cout << endl;
                menuDataPasien(daftarPasien, jumlahPasien);}

            // F. DATA PERAWATAN
            else if (pilih == 5) {
                system("cls"); judul_subjudul("DATA PERAWATAN"); cout << endl; 
                menuDataPerawatan(daftarPerawatan, jumlahPerawatan);}

            // G. KELUAR
            else if (pilih == 6) {
                system("cls");
                judul_subjudul("TERIMA KASIH DAN SAMPAI JUMPA LAGI KAWAN!");
                break;}}
    }

    return 0;
}