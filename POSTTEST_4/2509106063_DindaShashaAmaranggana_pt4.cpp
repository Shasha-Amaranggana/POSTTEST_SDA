#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <limits>
using namespace std;

/* STRUCT
════════════════════════════════════════════════════*/
struct Pasien {
    int idPasien;
    string namaPasien;
    int umurPasien;
    string jenisPasien;};
struct NodePasien {
    Pasien data;
    NodePasien* next;};
NodePasien* headPasien = NULL;
NodePasien* tailPasien = NULL;

struct Perawatan {
    int idPerawatan;
    string namaPerawatan;
    float harga;};
struct NodePerawatan {
    Perawatan data;
    NodePerawatan* next;};
NodePerawatan* headPerawatan = NULL;
NodePerawatan* tailPerawatan = NULL;

struct Kunjungan {
    int idKunjungan;
    int idPasien;
    int idPerawatan[5];
    int jumlahPerawatan;};
struct NodeKunjungan {
    Kunjungan data;
    NodeKunjungan* next;};
NodeKunjungan* headKunjungan = NULL;
NodeKunjungan* tailKunjungan = NULL;

struct Antrian {
    int nomorAntrian;
    int idPasien;
    string namaPasien;};
struct NodeAntrian {
    Antrian data;
    NodeAntrian* next;};
NodeAntrian* front = NULL;
NodeAntrian* rear = NULL;

struct Riwayat {
    int idPasien;
    string namaPasien;
    string hasil;};
struct NodeRiwayat {
    Riwayat data;
    NodeRiwayat* next;};
NodeRiwayat* top = NULL;


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

bool isEmptyPasien() {
    return headPasien == NULL;}
bool isEmptyPerawatan() {
    return headPerawatan == NULL;}
bool isEmptyKunjungan() {
    return headKunjungan == NULL;}
bool isEmptyAntrian() {
    return front == NULL;}
bool isEmptyRiwayat() {
    return top == NULL;}


/* PROSEDUR DAN FUNGSI BANTUAN
════════════════════════════════════════════════════*/
int bikinId(string jenis) {
    if (jenis == "Pasien") {
        if (isEmptyPasien()) return 9001;
        return tailPasien->data.idPasien + 1;}

    else if (jenis == "Perawatan") {
        if (isEmptyPerawatan()) return 401;
        return tailPerawatan->data.idPerawatan + 1;}

    else if (jenis == "Kunjungan") {
        if (isEmptyKunjungan()) return 60001;
        return tailKunjungan->data.idKunjungan + 1;}

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


int fibonacciSearchIdPasien(Pasien *arr, int jumlah, int target) {
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

        if ((arr + i)->idPasien < target) {
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        else if ((arr + i)->idPasien > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        else {
            return i;}}

    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idPasien == target){
        return offset + 1;}

    return -1;
}

int fibonacciSearchIdPerawatan(Perawatan *arr, int jumlah, int target) {
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

        if ((arr + i)->idPerawatan < target) {
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        else if ((arr + i)->idPerawatan > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        else {
            return i;}}

    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idPerawatan == target){
        return offset + 1;}

    return -1;
}

int fibonacciSearchIdKunjungan(Kunjungan *arr, int jumlah, int target) {
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

        if ((arr + i)->idKunjungan < target) {
            fib = fib1; fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;}
        else if ((arr + i)->idKunjungan > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;}
        else {
            return i;}}

    if (fib1 && offset + 1 < jumlah && (arr + offset + 1)->idKunjungan == target){
        return offset + 1;}

    return -1;
}

void linkedList_ArrayPasien(NodePasien *head, Pasien arr[], int &jumlah) {
    jumlah = 0;
    while (head != NULL) {
        arr[jumlah++] = head->data;
        head = head->next;}}

void linkedList_ArrayPerawatan(NodePerawatan *head, Perawatan arr[], int &jumlah) {
    jumlah = 0;
    while (head != NULL) {
        arr[jumlah++] = head->data;
        head = head->next;}}

void linkedList_ArrayKunjungan(NodeKunjungan *head, Kunjungan arr[], int &jumlah) {
    jumlah = 0;
    while (head != NULL) {
        arr[jumlah++] = head->data;
        head = head->next;}}


NodePasien* linearSearchNamaPasien(string target) {
    NodePasien* temp = headPasien;

    while (temp != NULL) {
        if (temp->data.namaPasien == target) {
            return temp;}
       temp = temp->next;}
    return NULL;
}

NodePerawatan* linearSearchNamaPerawatan(string target) {
    NodePerawatan* temp = headPerawatan;

    while (temp != NULL) {
        if (temp->data.namaPerawatan == target) {
            return temp;}
        temp = temp->next;}
    return NULL;
}


void tambahPasienManual(int id, string nama, int umur, string jenis) {
    NodePasien* baru = new NodePasien;
    baru->data = {id, nama, umur, jenis};
    baru->next = NULL;
    if (headPasien == NULL) headPasien = tailPasien = baru;
    else {
        tailPasien->next = baru;
        tailPasien = baru;}}

void tambahPerawatanManual(int id, string nama, float harga) {
    NodePerawatan* baru = new NodePerawatan;
    baru->data = {id, nama, harga};
    baru->next = NULL;
    if (headPerawatan == NULL) headPerawatan = tailPerawatan = baru;
    else {
        tailPerawatan->next = baru;
        tailPerawatan = baru;}}

void tambahKunjunganManual(int idKunjungan, int idPasien, int perawatan[], int jumlah) {
    NodeKunjungan* baru = new NodeKunjungan;
    baru->data.idKunjungan = idKunjungan;
    baru->data.idPasien = idPasien;
    baru->data.jumlahPerawatan = jumlah;
    for (int i = 0; i < jumlah; i++) {
        baru->data.idPerawatan[i] = perawatan[i];}
    baru->next = NULL;
    if (headKunjungan == NULL) headKunjungan = tailKunjungan = baru;
    else {
        tailKunjungan->next = baru;
        tailKunjungan = baru;}}

void tambahAntrianManual(int no, int idPasien, string nama) {
    NodeAntrian* baru = new NodeAntrian;
    baru->data = {no, idPasien, nama};
    baru->next = NULL;
    if (front == NULL) front = rear = baru;
    else {
        rear->next = baru;
        rear = baru;}}

void pushRiwayatManual(int id, string nama, string hasil) {
    NodeRiwayat* baru = new NodeRiwayat;
    baru->data = {id, nama, hasil};
    baru->next = top;
    top = baru;}

void dataDummy() {
    tambahPasienManual(9001, "Oyin", 6, "Kucing");
    tambahPasienManual(9002, "Ayen", 6, "Kucing");
    tambahPasienManual(9003, "Embul", 6, "Kucing");
    tambahPasienManual(9004, "Bella", 16, "Kucing");
    tambahPasienManual(9005, "Ochi", 36, "Kucing");

    tambahPerawatanManual(401, "Grooming", 150000);
    tambahPerawatanManual(402, "Vaksinasi", 200000);
    tambahPerawatanManual(403, "Konsultasi", 100000);
    tambahPerawatanManual(404, "Penitipan", 50000);
    tambahPerawatanManual(405, "Sterilisasi", 500000);

    int p1[] = {401, 402};
    tambahKunjunganManual(60001, 9001, p1, 2);
    int p2[] = {403};
    tambahKunjunganManual(60002, 9002, p2, 1);
    int p3[] = {404, 405};
    tambahKunjunganManual(60003, 9003, p3, 2);

    tambahAntrianManual(1, 9001, "Oyin");
    tambahAntrianManual(2, 9002, "Ayen");

    pushRiwayatManual(9005, "Ochi", "Sehat");
    pushRiwayatManual(9003, "Embul", "Demam");
}


/* CRUD
════════════════════════════════════════════════════*/
void tambahPasien() {
    NodePasien* baru = new NodePasien;
    baru->data.idPasien = bikinId("Pasien");

    string jenisPasien[] = {"Anjing", "Kucing", "Kelinci"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("✚ PASIEN BARU");

        cout << "ID Otomatis : " << baru->data.idPasien << endl;
        cout << "Jenis        : " << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << ">  " << jenisPasien[i] << endl;}
            else {
                cout << "   " << jenisPasien[i] << endl;}}
        int hasil = scrollMenu(pilih, 3);

        if (hasil == -1) {
            baru->data.jenisPasien = jenisPasien[pilih];
            break;}}

    system("cls"); judul_subjudul("✚ PASIEN BARU"); cout << endl;

    cout << "ID Otomatis  : " << baru->data.idPasien << endl;
    cout << "Jenis        : " << baru->data.jenisPasien << endl;
    cout << "Nama : "; cin >> baru->data.namaPasien;
    cout << "Umur : "; cin >> baru->data.umurPasien;
    if (baru->data.umurPasien <= 0) {
        tampilPeringatan(24, "Umur tidak valid!");
        delete baru;
        return;}

    baru->next = NULL;
    if (headPasien == NULL) {
        headPasien = tailPasien = baru;}
    else {
        tailPasien->next = baru;
        tailPasien = baru;}

    tampilPesan(34, "Data pasien berhasil ditambahkan!");
}

void tambahPerawatan() {
    NodePerawatan* baru = new NodePerawatan;
    baru->data.idPerawatan = bikinId("Perawatan");

    cout << "ID Otomatis : " << baru->data.idPerawatan << endl;
    cout << "Nama        : "; cin >> baru->data.namaPerawatan;
    cout << "Harga       : "; cin >> baru->data.harga;
    if (baru->data.harga <= 0) {
        tampilPeringatan(28, "Harga tidak valid!");
        delete baru;
        return;}

    baru->next = NULL;
    if (headPerawatan == NULL) {
        headPerawatan = tailPerawatan = baru;}
    else {
        tailPerawatan->next = baru;
        tailPerawatan = baru;}

    tampilPesan(36, "Data perawatan berhasil ditambahkan!");
}

void tambahKunjungan() {
    NodeKunjungan* baru = new NodeKunjungan;
    baru->data.idKunjungan = bikinId("Kunjungan");
    baru->data.jumlahPerawatan = 0;
    baru->next = NULL;

    string submenuKunjungan[] = {
        "    1 | Tambah Perawatan",
        "    2 | Simpan Data",
        "    3 | Kembali"};
    int idCari;
    int pilih = 0;

    Pasien arrPasien[100];
    Perawatan arrPerawatan[100];
    int jumlahPasien, jumlahPerawatan;
    linkedList_ArrayPasien(headPasien, arrPasien, jumlahPasien);
    linkedList_ArrayPerawatan(headPerawatan, arrPerawatan, jumlahPerawatan);

    system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;

    cout << "ID Otomatis    : " << baru->data.idKunjungan << endl;
    cout << "ID Pasien: "; cin >> idCari;
    int indexPasien = fibonacciSearchIdPasien(arrPasien, jumlahPasien, idCari);
    if (indexPasien == -1) {
        tampilPeringatan(58, "ID pasien tidak ditemukan! Data kunjungan gagal disimpan."); system("pause");
        delete baru;
        return;}

    baru->data.idPasien = arrPasien[indexPasien].idPasien;

    while (true) {
        system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;

        cout << "ID Otomatis    : " << baru->data.idKunjungan << endl;
        cout << "Pasien         : " << arrPasien[indexPasien].namaPasien << endl;
        cout << "ID Perawatan   : ";
        if (baru->data.jumlahPerawatan == 0) {
            cout << "Belum ada perawatan ditambahkan\n";}
        else {
            for (int i = 0; i < baru->data.jumlahPerawatan; i++) {
                cout << baru->data.idPerawatan[i];
                if (i < baru->data.jumlahPerawatan - 1) {
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
            if (pilih == 0 && baru->data.jumlahPerawatan >= 5) {
                tampilPeringatan(32, "Jumlah perawatan sudah maksimal!"); system("pause");}

            // B. TAMBAH PERAWATAN
            else if (pilih == 0) {
                system("cls"); judul_subjudul("✚ KUNJUNGAN BARU"); cout << endl;
                cout << "ID Otomatis    : " << baru->data.idKunjungan << endl;
                cout << "Pasien         : " << arrPasien[indexPasien].namaPasien << endl;
                cout << "ID Perawatan   : ";
                if (baru->data.jumlahPerawatan == 0) {
                    cout << "Belum ada perawatan ditambahkan" << endl;}
                else {
                    for (int i = 0; i < baru->data.jumlahPerawatan; i++) {
                        cout << baru->data.idPerawatan[i];
                        if (i < baru->data.jumlahPerawatan - 1) {
                            cout << ", ";}}
                    cout << endl;}

                cout << "\nID Perawatan " << baru->data.jumlahPerawatan + 1 << " : "; cin >> idCari;
                int indexPerawatan = fibonacciSearchIdPerawatan(arrPerawatan, jumlahPerawatan, idCari);

                if (indexPerawatan != -1) {
                    baru->data.idPerawatan[baru->data.jumlahPerawatan] = arrPerawatan[indexPerawatan].idPerawatan;
                    baru->data.jumlahPerawatan++;}
                else {
                    tampilPeringatan(30, "ID perawatan tidak ditemukan!");system("pause");}}

            // C. SIMPAN DATA
            else if (pilih == 1) {
                if (baru->data.jumlahPerawatan == 0) {
                    tampilPeringatan(20, "Belum ada perawatan!"); system("pause");}
                else {
                    if (headKunjungan == NULL) {
                        headKunjungan = tailKunjungan = baru;}
                    else {
                        tailKunjungan->next = baru;
                        tailKunjungan = baru;}
                    tampilPesan(36, "Data kunjungan berhasil ditambahkan!");
                    system("pause");
                    return;}}

            // D. KEMBALI
            else if (pilih == 2) {
                delete baru;
                return;}}
    }
}

void tambahAntrian() {
    NodeAntrian* baru = new NodeAntrian;
    int idCari;

    Pasien arrPasien[100]; int jumlahPasien;
    linkedList_ArrayPasien(headPasien, arrPasien, jumlahPasien);

    cout << "Masukkan ID Pasien: "; cin >> idCari;
    int indexPasien = fibonacciSearchIdPasien(arrPasien, jumlahPasien, idCari);
    if (indexPasien == -1) {
        tampilPeringatan(26, "ID pasien tidak ditemukan!"); system("pause");
        delete baru;
        return;}

    if (rear == NULL) {
        baru->data.nomorAntrian = 1;}
    else {
        baru->data.nomorAntrian = rear->data.nomorAntrian + 1;}

    baru->data.idPasien = arrPasien[indexPasien].idPasien;
    baru->data.namaPasien = arrPasien[indexPasien].namaPasien;
    baru->next = NULL;

    if (front == NULL) {
        front = rear = baru;}
    else {
        rear->next = baru;
        rear = baru;}
    tampilPesan(24, "Berhasil masuk antrian!"); system("pause");
}


void tampilPasien() {
    if (isEmptyPasien()) {
        tampilPesan(32, "Anda belum memiliki data pasien.");}
    else {
        NodePasien* temp = headPasien;
        cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
        cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
        while (temp != NULL) {
            cout << left
                << setw(8) << temp->data.idPasien << "│ " << setw(27) << temp->data.namaPasien << "│ "
                << setw(13) << temp->data.umurPasien << "│ " << setw(15) << temp->data.jenisPasien << endl;
            cout << right;
            temp = temp->next;}
        cout << endl;}
}

void tampilPerawatan() {
    if (isEmptyPerawatan()) {
        tampilPesan(36, "Anda belum memiliki data perawatan.");}
    else {
        NodePerawatan* temp = headPerawatan;
        cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
        cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
        while (temp != NULL) {
            cout << left
                << setw(8) << temp->data.idPerawatan << "│ " << setw(44) << temp->data.namaPerawatan << "│ "
                << setw(13) << temp->data.harga << endl;
            cout << right;
            temp = temp->next;}
        cout << endl;}
}

void tampilKunjungan() {
    if (isEmptyKunjungan()) {
        tampilPesan(36, "Anda belum memiliki data kunjungan.");}
    else {
        NodeKunjungan* temp = headKunjungan;
        cout << "   ID   │ ID PASIEN │         ID PERAWATAN         │ JUMLAH PERAWATAN " << endl;
        cout << "────────╋───────────╋──────────────────────────────╋──────────────────" << endl;
        while (temp != NULL) {
            cout << left
                << setw(8) << temp->data.idKunjungan << "│ " << setw(10) << temp->data.idPasien << "│ ";
            string daftar = "";
            for (int j = 0; j < temp->data.jumlahPerawatan; j++) {
                daftar += to_string(temp->data.idPerawatan[j]);
                if (j < temp->data.jumlahPerawatan - 1) {
                    daftar += ", ";}}
            cout << setw(29) << daftar << "│ " << setw(15) << temp->data.jumlahPerawatan << endl;
            cout << right;
            temp = temp->next;}
        cout << endl;}
}

void tampilAntrian() {
    if (isEmptyAntrian()) {
        tampilPesan(22, "Antrian masih kosong.");}
    else {
        NodeAntrian* temp = front;
        cout << "   NO ANTRI   │   ID PASIEN   │             NAMA PASIEN              " << endl;
        cout << "──────────────╋───────────────╋──────────────────────────────────────" << endl;
        while (temp != NULL) {
            cout << left
                << setw(13) << temp->data.nomorAntrian << " │ " << setw(13) << temp->data.idPasien << " │ " << temp->data.namaPasien << endl;
            cout << right;
            temp = temp->next;}
        cout << endl;}
}

void peekAntrian() {
    if (isEmptyAntrian()) {
        tampilPesan(22, "Antrian masih kosong.");}
    else {
        cout << "ANTRIAN TERDEPAN:\n";
        cout << "   NO ANTRI   │   ID PASIEN   │             NAMA PASIEN              " << endl;
        cout << "──────────────╋───────────────╋──────────────────────────────────────" << endl;
        cout << left
            << setw(13) << front->data.nomorAntrian << " │ " << setw(13) << front->data.idPasien << " │ " << front->data.namaPasien << endl;
        cout << right;}
}

void tampilRiwayat() {
    if (isEmptyRiwayat()) {
        tampilPesan(22, "Riwayat masih kosong.");}
    else {
        NodeRiwayat* temp = top;
        cout << "   ID PASIEN   │      NAMA PASIEN       │            HASIL           " << endl;
        cout << "───────────────╋────────────────────────╋────────────────────────────" << endl;
        while (temp != NULL) {
            cout << left
                << setw(14) << temp->data.idPasien << " │ " << setw(22) << temp->data.namaPasien << " │ " << setw(13) << temp->data.hasil << endl;
            cout << right;
            temp = temp->next;}
        cout << endl;}
}

void peekRiwayat() {
    if (isEmptyRiwayat()) {
        tampilPesan(22, "Riwayat masih kosong.");}
    else {
        cout << "RIWAYAT TERAKHIR:\n";
        cout << "   ID PASIEN   │      NAMA PASIEN       │            HASIL           " << endl;
        cout << "───────────────╋────────────────────────╋────────────────────────────" << endl;
        cout << left
            << setw(14) << top->data.idPasien << " │ " << setw(22) << top->data.namaPasien << " │ " << setw(13) << top->data.hasil << endl;
        cout << right;}
}


void pushRiwayat(int id, string nama, string hasil) {
    NodeRiwayat* baru = new NodeRiwayat;
    baru->data.idPasien = id;
    baru->data.namaPasien = nama;
    baru->data.hasil = hasil;
    baru->next = top;
    top = baru;}

void popRiwayat() {
    if (isEmptyRiwayat()) {
        tampilPesan(22, "Riwayat masih kosong.");}
    else {
        NodeRiwayat* hapus = top;
        cout << "Menghapus riwayat: " << hapus->data.namaPasien << endl;
        top = top->next;
        delete hapus;
        tampilPesan(26, "Riwayat berhasil dihapus!");}
}

void panggilAntrian() {
    string hasil;

    if (isEmptyAntrian()) {
        tampilPesan(22, "Antrian masih kosong.");}
    else {
        NodeAntrian* hapus = front;

        cout << "Memanggil: ";
        cout << hapus->data.namaPasien << " (ID: " << hapus->data.idPasien << ")" << endl;
        front = front->next;
        if (front == NULL){
            rear = NULL;}
        tampilPesan(18, "Pasien dipanggil!");

        cout << "Pasien diperiksa...\n";
        Sleep(2000);
        tampilPesan(28, "Pasien selesai diperiksa!");

        cout << "Masukkan hasil pemeriksaan: "; getline(cin >> ws, hasil);

        if (hasil.length() > 30) {
            hasil = hasil.substr(0, 30);}
        pushRiwayat(hapus->data.idPasien, hapus->data.namaPasien, hasil);
        delete hapus;

        tampilPesan(48, "Hasil pemeriksaan berhasil disimpan ke riwayat!");}
}


void menuDataPasien() {
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
        cout << endl << endl; tampilPasien();

        int hasil = scrollMenu(pilih, 4);
        if (hasil == -1) {

            // A. CARI ID PASIEN
            if (pilih == 0) {
                system("cls"); judul_subjudul("CARI ID PASIEN"); cout << endl;
                cout << "\nMasukkan ID Pasien: "; int idPasien; cin >> idPasien;
                cout << "Mencari...\n" << endl;
                Pasien arr[100]; int jumlahPasien;
                linkedList_ArrayPasien(headPasien, arr, jumlahPasien);
                int indexPasien = fibonacciSearchIdPasien(arr, jumlahPasien, idPasien);
                if (indexPasien != -1) {
                    tampilPesan(20, "ID pasien ditemukan!"); cout << endl;
                    cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
                    cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
                    cout << left
                        << setw(8) << arr[indexPasien].idPasien << "│ " << setw(27) << arr[indexPasien].namaPasien << "│ "
                        << setw(13) << arr[indexPasien].umurPasien << "│ " << setw(15) << arr[indexPasien].jenisPasien << endl;
                    cout << right << endl;}
                else {
                    tampilPesan(26, "ID pasien tidak ditemukan!");}
                cout << endl; system("pause");}

            // B. CARI NAMA PASIEN
            else if (pilih == 1) {
                system("cls"); judul_subjudul("CARI NAMA PASIEN"); cout << endl;
                cout << "\nMasukkan Nama Pasien: "; string nama; cin >> nama;
                cout << "Mencari...\n" << endl;
                NodePasien* hasil = linearSearchNamaPasien(nama);
                if (hasil != NULL) {
                    tampilPesan(22, "Nama pasien ditemukan!"); cout << endl;
                    cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
                    cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
                    cout << left
                        << setw(8) << hasil->data.idPasien << "│ " << setw(27) << hasil->data.namaPasien << "│ "
                        << setw(13) << hasil->data.umurPasien << "│ " << setw(15) << hasil->data.jenisPasien << endl;
                    cout << right << endl;}
                else {
                    tampilPesan(28, "Nama pasien tidak ditemukan!");}
                cout << endl; system("pause");}

            // C. URUTKAN NAMA PASIEN
            else if (pilih == 2) {
                system("cls"); judul_subjudul("URUTKAN NAMA PASIEN"); cout << endl;
                Pasien arr[100]; int jumlah;
                linkedList_ArrayPasien(headPasien, arr, jumlah);
                bubbleSortNamaPasien(arr, jumlah);
                cout << "   ID   │            NAMA            │ UMUR (BULAN) │      JENIS      " << endl;
                cout << "────────╋────────────────────────────╋──────────────╋─────────────────" << endl;
                for (int i = 0; i < jumlah; i++) {
                    cout << left
                        << setw(8) << arr[i].idPasien << "│ " << setw(27) << arr[i].namaPasien << "│ "
                        << setw(13) << arr[i].umurPasien << "│ " << setw(15) << arr[i].jenisPasien << endl;}
                cout << right << endl;
                system("pause");}

            // D. KEMBALI
            else if (pilih == 3) {
                break;}}
    }
}

void menuDataPerawatan() {
    string menu[] = {
        "    1 | Tambah Perawatan",
        "    2 | Cari ID Perawatan",
        "    3 | Cari Nama Perawatan",
        "    4 | Urutkan Nama Perawatan",
        "    5 | Urutkan Harga Perawatan",
        "    6 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU PERAWATAN"); cout << endl;

        for (int i = 0; i < 6; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}
        cout << endl << endl; tampilPerawatan();

        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {

            // A. TAMBAH PERAWATAN
            if (pilih == 0) {
                system("cls"); judul_subjudul("✚ PERAWATAN BARU"); cout << endl;
                tambahPerawatan();
                system("pause");}

            // B. CARI ID PERAWATAN
            else if (pilih == 1) {
                system("cls"); judul_subjudul("CARI ID PERAWATAN"); cout << endl;
                cout << "\nMasukkan ID Perawatan: "; int idPerawatan; cin >> idPerawatan;
                cout << "Mencari...\n" << endl;
                Perawatan arr[100]; int n;
                linkedList_ArrayPerawatan(headPerawatan, arr, n);
                int indexPerawatan = fibonacciSearchIdPerawatan(arr, n, idPerawatan);
                if (indexPerawatan != -1) {
                    tampilPesan(24, "ID perawatan ditemukan!"); cout << endl;
                    cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                    cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                    cout << left
                        << setw(8) << arr[indexPerawatan].idPerawatan << "│ " << setw(44) << arr[indexPerawatan].namaPerawatan << "│ "
                        << setw(13) << arr[indexPerawatan].harga << endl;
                    cout << right << endl;}
                else {
                    tampilPesan(30, "ID perawatan tidak ditemukan!");}
                cout << endl; system("pause");}

            // C. CARI NAMA PERAWATAN
            else if (pilih == 2) {
                system("cls"); judul_subjudul("CARI NAMA PERAWATAN"); cout << endl;
                cout << "\nMasukkan Nama Perawatan: "; string namaPerawatan; cin >> namaPerawatan;
                cout << "Mencari...\n" << endl;
                NodePerawatan* hasil = linearSearchNamaPerawatan(namaPerawatan);
                if (hasil != NULL) {
                    tampilPesan(26, "Nama perawatan ditemukan!");  cout << endl;
                    cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                    cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                    cout << left
                        << setw(8) << hasil->data.idPerawatan << "│ " << setw(44) << hasil->data.namaPerawatan << "│ "
                        << setw(13) << hasil->data.harga << endl;
                    cout << right << endl;}
                else {
                    tampilPesan(32, "Nama perawatan tidak ditemukan!");}
                cout << endl; system("pause");}

            // D. URUTKAN NAMA PERAWATAN
            else if (pilih == 3) {
                system("cls"); judul_subjudul("URUTKAN NAMA PERAWATAN"); cout << endl;
                Perawatan arr[100]; int jumlah;
                linkedList_ArrayPerawatan(headPerawatan, arr, jumlah);
                bubbleSortNamaPerawatan(arr, jumlah);
                cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                for (int i = 0; i < jumlah; i++) {
                    cout << left
                        << setw(8) << arr[i].idPerawatan << "│ " << setw(44) << arr[i].namaPerawatan << "│ "
                        << setw(13) << arr[i].harga << endl;}
                cout << right << endl;
                system("pause");}

            // E. URUTKAN HARGA PERAWATAN
            else if (pilih == 4) {
                system("cls"); judul_subjudul("URUTKAN HARGA PERAWATAN"); cout << endl;
                Perawatan arr[100]; int jumlah;
                linkedList_ArrayPerawatan(headPerawatan, arr, jumlah);
                selectionSortHargaPerawatan(arr, jumlah);
                cout << "   ID   │                    NAMA                     │     HARGA     " << endl;
                cout << "────────╋─────────────────────────────────────────────╋───────────────" << endl;
                for (int i = 0; i < jumlah; i++) {
                    cout << left
                        << setw(8) << arr[i].idPerawatan << "│ " << setw(44) << arr[i].namaPerawatan << "│ "
                        << setw(13) << arr[i].harga << endl;}
                cout << right; cout << endl;
                system("pause");}

            // F. KEMBALI
            else if (pilih == 5) {
                break;}}
    }
}

void menuDataKunjungan() {
    string menu[] = {
        "   1 | Tambah Kunjungan",
        "   2 | Cari ID Kunjungan",
        "   3 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU CARI KUNJUNGAN"); cout << endl;

        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}
        cout << endl << endl; tampilKunjungan();

        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {

            // A. TAMBAH KUNJUNGAN
            if (pilih == 0) {
                tambahKunjungan();}

            // B. CARI ID KUNJUNGAN
            else if (pilih == 1) {
                system("cls"); judul_subjudul("CARI ID KUNJUNGAN"); cout << endl;
                cout << "\nMasukkan ID Kunjungan: "; int idKunjungan; cin >> idKunjungan;
                cout << "Mencari...\n" << endl;
                Kunjungan arr[100]; int jumlah;
                linkedList_ArrayKunjungan(headKunjungan, arr, jumlah);
                int indexKunjungan = fibonacciSearchIdKunjungan(arr, jumlah, idKunjungan);
                if (indexKunjungan != -1) {
                    tampilPesan(24, "ID kunjungan ditemukan!"); cout << endl;
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

            // C. KEMBALI
            else if (pilih == 2) {
                break;}}
    }
}

void menuDataAntrian() {
    string menu[] = {
        "   1 | Panggil Antrian",
        "   2 | Lihat Antrian Lengkap",
        "   3 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("MENU ANTRIAN"); cout << endl;

        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}
        cout << endl << endl; peekAntrian();

        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {

            // A. PANGGIL ANTRIAN
            if (pilih == 0) {
                system("cls"); judul_subjudul("PANGGIL ANTRIAN"); cout << endl;
                panggilAntrian();
                system("pause");}

            // B. LIHAT ANTRIAN LENGKAP
            else if (pilih == 1) {
                system("cls"); judul_subjudul("LIHAT ANTRIAN LENGKAP"); cout << endl;
                tampilAntrian();
                system("pause");}

            // C. KEMBALI
            else if (pilih == 2) {
                break;}}
    }
}

void menuDataRiwayat() {
    string menu[] = {
        "   1 | Hapus Riwayat Terakhir",
        "   2 | Lihat Riwayat Lengkap",
        "   3 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("RIWAYAT PEMERIKSAAN"); cout << endl;

        for (int i = 0; i < 3; i++) {
            if (i == pilih) {
                cout << ">  " << menu[i] << endl;}
            else {
                cout << "   " << menu[i] << endl;}}
        cout << endl << endl; peekRiwayat();

        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {

            // A. HAPUS RIWAYAT TERAKHIR
            if (pilih == 0) {
                system("cls"); judul_subjudul("HAPUS RIWAYAT TERAKHIR"); cout << endl;
                popRiwayat();
                system("pause");}

            // B. LIHAT RIWAYAT LENGKAP
            else if (pilih == 1) {
                system("cls"); judul_subjudul("LIHAT RIWAYAT LENGKAP"); cout << endl;
                tampilRiwayat();
                system("pause");}

            // C. KEMBALI
            else if (pilih == 2) {
                break;}}
    }
}


/* PROGRAM UTAMA
════════════════════════════════════════════════════*/
int main() {
    SetConsoleOutputCP(65001);
    dataDummy();
    string menuMain[] = {
        "    『   + Pasien Baru    』",
        "    『   + Antrian Baru   』",
        "    【   Antrian Pasien   】",
        "    【 Riwayat  Kunjungan 】",
        "     1  |  Data Kunjungan",
        "     2  |  Data Pasien",
        "     3  |  Data Perawatan ",
        "    『       KELUAR       』"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("SELAMAT DATANG! PELIHARAAN ANDA DIJAMIN BAHAGIA SENTOSA" ); cout << endl;
        
        for (int i = 0; i < 8; i++) {
            if (i == pilih) {
                cout << "> " << menuMain[i] << endl;}
            else {
                cout << "  " << menuMain[i] << endl;}
            if ( i == 1 || i == 3 || i == 6) {
                cout << endl;}}
        int hasil = scrollMenu(pilih, 8);
        if (hasil == -1) {

            // A. PASIEN BARU
            if (pilih == 0) {
                tambahPasien();
                system("pause");}

            // B. ANTRIAN BARU
            else if (pilih == 1) {
                system("cls"); judul_subjudul("✚ ANTRIAN BARU"); cout << endl;
                tambahAntrian();}
            
            // C. ANTRIAN PASIEN
            else if (pilih == 2) {
                system("cls"); judul_subjudul("DATA ANTRIAN"); cout << endl;
                menuDataAntrian();}

            // D. RIWAYAT PEMERIKSAAN
            else if (pilih == 3) {
                system("cls"); judul_subjudul("DATA RIWAYAT"); cout << endl;
                menuDataRiwayat();}

            // E. DATA KUNJUNGAN
            else if (pilih == 4) {
                system("cls"); judul_subjudul("DATA KUNJUNGAN"); cout << endl;
                menuDataKunjungan();}

            // F. DATA PASIEN
            else if (pilih == 5) {
                system("cls"); judul_subjudul("DATA PASIEN"); cout << endl;
                menuDataPasien();}
 
            // G. DATA PERAWATAN
            else if (pilih == 6) {
                system("cls"); judul_subjudul("DATA PERAWATAN"); cout << endl;
                menuDataPerawatan();}

            // H. KELUAR
            else if (pilih == 7) {
                system("cls"); judul_subjudul("TERIMA KASIH DAN SAMPAI JUMPA LAGI KAWAN!");
                break;}}
    }
    return 0;
}