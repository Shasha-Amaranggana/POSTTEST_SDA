/*SOAL 2  
STRUCT + ARRAY DATA MAHASISWA

Buat program C++ menggunakan struct Mahasiswa yang memiliki field: nama (string), nim (string), dan ipk (float).

Deklarasikan array of struct sesuai jumlah mahasiswa yang diminta, lakukan input data, lalu tampilkan hasil sesuai ketentuan.
 
• Input data 5 mahasiswa (nama, NIM, IPK).
• Cari dan tampilkan mahasiswa dengan IPK tertinggi.*/


//               JAWABAN
//=========================================================
#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int FindIPKMax (Mahasiswa data[], int n) {
    int indeks = 0;
    for (int i = 1; i < n; i++) {
        if (data[i].ipk > data[indeks].ipk) {
            indeks = i;
        }
    }
    return indeks;
}

int main() { 
    Mahasiswa data[5];

    for (int i = 0; i < 5; i++) {
        cout << "Masukkan data Mahasiswa ke " << i + 1 << ": " << endl;

        cout << "\nNama: ";
        getline(cin, data[i].nama);
        cout << "NIM: ";
        cin >> data[i].nim;
        cout << "IPK: ";
        cin >> data[i].ipk;
        cin.ignore();
        cout << "==================================";
        cout << endl;
    }

    int indeks = FindIPKMax (data, 5);

    cout << "Mahasiswa dengan IPK tertinggi yaitu: " << endl;
    cout << "\nNama: " << data[indeks].nama << endl;
    cout << "NIM: " << data[indeks].nim << endl;
    cout << "IPK: " << data[indeks].ipk << endl;

    return 0;
}
