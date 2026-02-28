/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 1
*/

#include <iostream>
using namespace std;

// Fungsi untuk menukar dua variabel integer menggunakan pointer
// Fungsi ini mengembalikan nilai 0 sebagai penanda sukses (sesuai ketentuan harus mengembalikan sesuatu)
int swap(int* a, int* b) {
    int temp = *a;	// Simpan nilai yang ditunjuk a
    *a = *b;		// Menukar nilai b ke a
    *b = temp;		// Menukar nilai temp ke b
    return 0;
}

int main() {
    int x, y;

    cout << "=== Masukkan dua bilangan bulat ===" << endl;
    cout << "Masukkan bilangan pertama: ";
    cin >> x;

    cout << "Masukkan bilangan kedua: ";
    cin >> y;

    // Tampilkan sebelum pertukaran
    cout << endl << "=== Sebelum pertukaran ===" << endl;
    cout << "x = " << x << endl << "y = " << y << endl;

    // Panggil fungsi swap dengan alamat variabel
    swap(&x, &y);

    // Tampilkan setelah pertukaran
    cout << endl << "=== Setelah pertukaran ===" << endl;
    cout << "x = " << x << endl << "y = " << y << endl;

    return 0;
}
