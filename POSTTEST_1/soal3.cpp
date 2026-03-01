/*SOAL 3
ARRAY & POINTER - OPERASI DASAR

Buat program C++ yang menyimpan sejumlah data integer dalam array, lalu gunakan pointer untuk mengakses dan memanipulasi elemen-elemen tersebut.

Deklarasikan array sesuai ketentuan masing-masing, lalu buat fungsi dengan parameter pointer untuk operasi yang diminta.
 
• Deklarasikan array berisi 7 elemen yang diisi dengan bilangan prima (2, 3, 5, 7, 11, 13, 17).
• Buat fungsi reverseArray(int* arr, int n) menggunakan pointer (bukan indeks) untuk membalik urutan array.
• Tampilkan array sebelum dan sesudah dibalik.

Tampilkan pula alamat memori setiap elemen menggunakan pointer.*/


//               JAWABAN
//=========================================================
#include <iostream>
using namespace std;

void reverseArray(int *arr, int n) {
    int *awal = arr;
    int *akhir = arr + n - 1;

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        awal = awal + 1;
        akhir = akhir - 1;
    }
}

int main() {
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "==================================";
    cout << "\nArray sebelum di-Reverse: \n" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(prima + i) << " dengan alamat: " << (prima + i) << endl;
    }

    reverseArray(prima, 7);

    cout << "\n==================================";
    cout << "\nArray setelah di-Reverse: \n" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(prima + i) << " dengan alamat: " << (prima + i) << endl;
    }

    return 0;
}
