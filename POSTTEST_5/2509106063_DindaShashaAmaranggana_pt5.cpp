/*Latihan Soal Circular Linked List

Soal 1: Inventaris Toko Sembako
Kamu diminta membuat fungsi untuk menampilkan daftar barang sembako beserta stoknya yang tersimpan dalam struktur data Circular Linked List. Berbeda dengan linked list biasa, pada Circular Linked List, pointer `next` dari node terakhir tidak menunjuk ke `nullptr`, melainkan kembali menunjuk ke node `head`. 
*/

#include <iostream>
#include <string>
using namespace std;

struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;}
};

BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;}
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;}
    temp->next = newNode;
    newNode->next = head;
    return head;
}


void tampilkanStokSembako(BarangNode* head) {

    // Mengecek, linked list nya kosong atau nggak
    if (head == nullptr) {
        cout << "Kosong melompong." << endl;
        return;}

    // Pointer sementara buat proses Traversal, mulai dari Head
    BarangNode* temp = head;

    /*
    Pakai Do-While, biar program eksekusi dulu, menampilkan daftar sembakonya.
    Selagi temp belum balik lagi ke Head, bakalan terus menampilkan daftar sembakonya.
    Kalau temp udah balik ke Head, baru berhenti menampilkan daftar sembakonya.
    Kenapa harus Head? Karena si daftar pertamanya itu Head,
    jadi kalau temp udah balik ke Head, berarti udah muter satu kali, berarti udah tampil semua daftar sembakonya.
     */
    do {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl;
        temp = temp->next;
    } while (temp != head);
}


int main() {
    BarangNode* head = nullptr;
    
    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head); 
    return 0;
}