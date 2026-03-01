/*SOAL 4
POINTER PADA FUNGSI

Buat fungsi untuk menukar dua variabel integer.

· Gunakan pointer dalam fungsi untuk melakukan pertukaran nilai.
· Uji fungsi tersebut dengan dua nilai input dan tampilkan hasil sebelum dan sesudah pertukaran.*/


//               JAWABAN
//=========================================================

#include <iostream>
using namespace std;

void tukarElemen(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a;
    int b;

    cout << "Masukkan nilai a: ";
    cin >> a;
    cout << "Masukkan nilai b: ";
    cin >> b;

    cout << "\n==================================";
    cout << "\nSebelum keduanya ditukar: " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    tukarElemen(&a, &b);

    cout << "\n==================================";
    cout << "\nSetelah keduanya ditukar: " << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}
