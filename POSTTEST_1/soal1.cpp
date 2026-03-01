/*SOAL 1
KOMPLEKSITAS WAKTU ANALISIS ALGORITMA

Pseodocode Pencarian Elemen Minimum dalam Sebuah Array:
procedure FindMin(A : array of n elements)
    min ← A[0]
    for i ← 1 to n - 1 do
        if A[i] < min then
            min ← A[i]
        end if
    end for
    return min
end procedure
 
Berdasarkan algoritma di atas, implementasikan dan analisis kompleksitasnya!
 
A. Implementasikan fungsi FindMin di C++ menggunakan array bertipe integer dengan 8 elemen, diisi dengan bilangan Fibonacci (1, 1, 2, 3, 5, 8, 13, 21).
B. Hitung Tmin(n) dan Tmax(n) secara manual seperti contoh pada modul (tabel pseudocode + cost).
C. Tuliskan hasil analisis sebagai komentar di dalam kode (Big-O dari best case dan worst case).
Jalankan program dan tampilkan nilai minimum beserta indeksnya.*/


//               JAWABAN A
//=========================================================
#include <iostream>
using namespace std;

int FindMin(int A[], int n) {
    int min = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
        }
    }
    return min;
}

int IndMin (int A[], int n) {
    int min = A[0];
    int indeks = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            indeks = i;
        }
    }
    return indeks;
}

int main() { 
    int Fibonacci[8] = {1, 1, 2, 3, 5, 8, 13, 21};

    int Nmin = FindMin(Fibonacci, 8);
    int Imin = IndMin(Fibonacci, 8);

    cout << "Dalam array Fibonacci di bawah ini: " << endl;
    for (int i = 0; i < 8; i++) {
        cout << Fibonacci[i] << " ";
    }

    cout << "\n\nElemen terkecilnya adalah " << Nmin << " di indeks " << Imin << ".";
    return 0;
}


//               JAWABAN B
//=========================================================
/*  Pseudocode             |  Cost  |  Tmin  |  Tmax  |
__________________________________________________________
    procedure FindMin      |   C1   |    1   |    1   |
    min ← A[0]             |   C2   |    1   |    1   |
    for i ← 1 to n - 1 do  |   C3   |    n   |    n   |
    if A[i] < min then     |   C4   |  n - 1 |  n - 1 |
    min ← A[i]             |   C5   |    0   |  n - 1 |
    end if                 |   C6   |  n - 1 |  n - 1 |
    end for                |   C7   |    n   |    n   |
    return min             |   C8   |    1   |    1   |
    end procedure          |   C9   |    1   |    1   |
__________________________________________________________
    Total Waktu (Tn)                |  O(n)  |  O(n)  |
*/


//               JAWABAN C
//=========================================================
/* BEST CASE:
      C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
    = C1 + C2 + C3n + C4n - C4 + C6n - C6 + C7n + C8 + C9
    = (C3 + C4 + C6 + C7)n + (C1 + C2 - C4 - C6 + C8 + C9)
    = (4)n + (2)
    = 4n + 2
    Karena membentuk fungsi linier, maka Big-O adalah O(n).

 WORST CASE:
      C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8 + C9
    = C1 + C2 + C3n + C4n - C4 + C5n - C5 + C6n - C6 + C7n + C8 + C9
    = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 - C4 - C5 - C6 + C8 + C9)
    = (5)n + (1)
    = 5n + 1
    Karena membentuk fungsi linier, maka Big-O adalah O(n).

 Kesimpulan:
 Best Case = O(n)
 Worst Case = O(n)

*/