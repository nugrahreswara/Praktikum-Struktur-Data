/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 1
*/

#include <iostream>
#include <string>
using namespace std;

// Struct Mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int jumlahMahasiswa = 5;	

    // Deklarasi array of struct
    Mahasiswa mahasiswa[jumlahMahasiswa];	
    cout << "=== Masukkan data mahasiswa ===" << endl;

    // Input data 5 mahasiswa
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << ":" << endl;
        cout << "Nama: ";
        getline(cin, mahasiswa[i].nama);

        cout << "NIM: ";
	cin >> mahasiswa[i].nim;

        cout << "IPK (0.00 - 4.00): ";
        cin >> mahasiswa[i].ipk;

	// Membersihkan buffer newline setelah (cin >>) agar getline berikutnya tidak terlewat
	cin.ignore();
    }

    // Cari mahasiswa dengan IPK tertinggi
    int indexTertinggi = 0;
    for (int i = 1; i < jumlahMahasiswa; i++) {
        if (mahasiswa[i].ipk > mahasiswa[indexTertinggi].ipk) {
            indexTertinggi = i;
        }
    }

    cout << endl << "=== Mahasiswa dengan IPK tertinggi ===" << endl;
    cout << "Nama: " << mahasiswa[indexTertinggi].nama << endl;
    cout << "NIM : " << mahasiswa[indexTertinggi].nim << endl;
    cout << "IPK : " << mahasiswa[indexTertinggi].ipk << endl;

    return 0;
}
