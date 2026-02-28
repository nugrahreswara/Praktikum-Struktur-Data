/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 1
*/


#include <iostream>
using namespace std;

// Fungsi untuk membalik urutan array.
int* reverseArray(int* array, int jumlahElemen) {
    int* mulai = array;
    int* akhir = array + jumlahElemen - 1;

    // Tukar elemen dari kedua ujung hingga bertemu di tengah
    while (mulai < akhir) {
        // Tukar nilai
        int temp = *mulai;
        *mulai = *akhir;
        *akhir = temp;

        // Geser pointer
        mulai = mulai + 1;
        akhir = akhir - 1;
    }

    return array;
}

// Prosedur untuk menampilkan isi array
void printArray(int* array, int jumlahElemen) {
    for (int i = 0; i < jumlahElemen; i++) {
        cout << *(array + i) << " "; 
    }
    cout << endl;
}

// Prosedur untuk menampilkan alamat dan nilai setiap elemen menggunakan pointer
void printAddresses(int* array, int jumlahElemen) {
    cout << "Alamat dan nilai setiap elemen:" << endl;
    for (int i = 0; i < jumlahElemen; i++) {
        cout << "Elemen ke-" << i << ": alamat = " << (array+ i)
             << ", nilai = " << *(array + i) << endl;
    }
}

int main() {
    int bilanganPrima[7] = {2, 3, 5, 7, 11, 13, 17};
    int jumlahElemen = 7;

    cout << "=== Sebelum dibalik ===" << endl;
    cout << "Isi array: ";

    // Panggil prosedur printArray dan printAddresses
    printArray(bilanganPrima, jumlahElemen);
    printAddresses(bilanganPrima, jumlahElemen);

    // Panggil fungsi reverseArray
    reverseArray(bilanganPrima, jumlahElemen);

    cout << endl << "=== Sesudah dibalik ===" << endl;
    cout << "Isi array: ";

    // Panggil prosedur printArray dan printAddresses
    printArray(bilanganPrima, jumlahElemen);
    printAddresses(bilanganPrima, jumlahElemen);

    return 0;
}
