/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 1
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // untuk min

using namespace std;

// Struct data hewan
struct Pet {
    int id;
    string name;
    string species;
    double price;
};

// Fungsi swap menggunakan dereferensi pointer
void swapPet(Pet* a, Pet* b) {
    Pet temp = *a;
    *a = *b;
    *b = temp;
}

// Menampilkan menu utama
void tampilkanMenu() {
    cout << endl << "=== Pawcare Petshop ===" << endl;
    cout << "1. Tambah data hewan" << endl;
    cout << "2. Tampilkan semua data hewan (menggunakan pointer)" << endl;
    cout << "3. Cari hewan berdasarkan nama (Linear Search)" << endl;
    cout << "4. Cari hewan berdasarkan ID (Fibonacci Search)" << endl;
    cout << "5. Urutkan berdasarkan nama (Bubble Sort A-Z)" << endl;
    cout << "6. Urutkan berdasarkan harga (Selection Sort termurah)" << endl;
    cout << "7. Keluar" << endl;
}

// Menambah data hewan – menggunakan referensi pointer (Pet*&) agar dapat mengubah alamat array saat resize
void tambahData(Pet*& pets, int& count, int& capacity) {
    if (count == capacity) {
        int newCap = capacity * 2;
        Pet* newPets = new Pet[newCap];
        for (int i = 0; i < count; ++i) {
            newPets[i] = pets[i];
        }
        delete[] pets;
        pets = newPets;
        capacity = newCap;
        cout << "Kapasitas diperbesar menjadi " << capacity << "." << endl;
    }

    Pet baru;

    // ID otomatis berurutan
    baru.id = count + 1;

    cout << "Nama hewan: ";
    getline(cin, baru.name);
    cout << "Species: ";
    getline(cin, baru.species);
    cout << "Harga: ";
    cin >> baru.price;
    cin.ignore();

    pets[count] = baru;
    count++;
    cout << "Data hewan berhasil ditambahkan dengan ID: " << baru.id << endl;
}

// Menampilkan semua data – menggunakan pointer aritmatika (pets + i)
void tampilkanSemua(const Pet* pets, int count) {
    if (count == 0) {
        cout << "Belum ada data hewan.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(20) << "Nama"
         << setw(15) << "Species" << setw(10) << "Harga" << endl;
    cout << string(50, '-') << endl;
    for (int i = 0; i < count; ++i) {
        const Pet* p = pets + i;
        cout << left << setw(5) << p->id
             << setw(20) << p->name
             << setw(15) << p->species
             << setw(10) << p->price << endl;
    }
}

// Linear Search berdasarkan nama – menampilkan tiap iterasi
int linearSearchByName(const Pet* pets, int count, const string& name) {
    cout << "Proses Linear Search:\n";
    for (int i = 0; i < count; ++i) {
        const Pet* p = pets + i;
        cout << "Iterasi " << i+1 << ": Bandingkan \"" << p->name
             << "\" dengan \"" << name << "\"\n";
        if (p->name == name) {
            cout << "Ditemukan pada indeks " << i << endl;
            return i;
        }
    }
    cout << "Tidak ditemukan setelah " << count << " iterasi.\n";
    return -1;
}

// Bubble Sort berdasarkan nama (A-Z): menggunakan swap dengan pointer
void bubbleSortByName(Pet* pets, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            Pet* a = pets + j;
            Pet* b = pets + j + 1;
            if (a->name > b->name) {
                swapPet(a, b);
            }
        }
    }
}

// Selection Sort berdasarkan harga (termurah ke termahal): menggunakan swap dengan pointer
void selectionSortByPrice(Pet* pets, int count) {
    for (int i = 0; i < count - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < count; ++j) {

            if ((pets + j)->price < (pets + minIdx)->price) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapPet(pets + i, pets + minIdx);
        }
    }
}

// Sortir berdasarkan ID (bubble sort): digunakan agar Fibonacci search dapat bekerja
void sortById(Pet* pets, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if ((pets + j)->id > (pets + j + 1)->id) {
                swapPet(pets + j, pets + j + 1);
            }
        }
    }
}

// Fibonacci Search berdasarkan ID:  menampilkan tiap iterasi
int fibonacciSearchById(const Pet* pets, int count, int id) {
    cout << "Proses Fibonacci Search (data sudah terurut berdasarkan ID):" << endl;

    int fib2 = 0; // (m-2)
    int fib1 = 1; // (m-1)
    int fib = fib2 + fib1; // m

    // Cari bilangan Fibonacci terbesar yang <= count
    while (fib < count) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;
    int iter = 1;

    while (fib > 1) {
        int i = min(offset + fib2, count - 1);
        cout << "Iterasi " << iter++ << ": Bandingkan ID " << id
             << " dengan elemen indeks " << i << " (ID=" << (pets + i)->id << ")" << endl;

        if ((pets + i)->id < id) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }

        else if ((pets + i)->id > id) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }

        else {
            cout << "Ditemukan pada indeks " << i << " setelah " << iter-1 << " iterasi." << endl;
            return i;
        }
    }

    // Pengecekan terakhir
    if (fib1 == 1 && (pets + offset + 1)->id == id) {
        cout << "Ditemukan pada indeks " << offset+1 << " setelah " << iter << " iterasi." << endl;
        return offset + 1;
    }

    cout << "Tidak ditemukan setelah " << iter << " iterasi." << endl;
    return -1;
}

int main() {
    // kapasitas awal
    int capacity = 5;
    
    // jumlah data saat ini
    int count = 0;         

    // array dinamis
    Pet* pets = new Pet[capacity];  

    int pilihan;
    do {
        tampilkanMenu();
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahData(pets, count, capacity);
                break;

            case 2:
                tampilkanSemua(pets, count);
                break;

            case 3: {
                string nama;
                cout << "Masukkan nama hewan: ";
                getline(cin, nama);
                int idx = linearSearchByName(pets, count, nama);

                if (idx != -1) {
                    cout << "Ditemukan: " << pets[idx].name
                         << " (ID: " << pets[idx].id
                         << ", Species: " << pets[idx].species
                         << ", Harga: " << pets[idx].price << ")" << endl;
                }

                else {
                    cout << "Hewan dengan nama \"" << nama << "\" tidak ditemukan." << endl;
                }

                break;
            }

            // Fibonacci search membutuhkan data terurut berdasarkan ID
            case 4: {
                int id;
                cout << "Masukkan ID hewan: ";
                cin >> id;
                sortById(pets, count);
                int idx = fibonacciSearchById(pets, count, id);

                if (idx != -1) {
                    cout << "Ditemukan: " << pets[idx].name
                         << " (ID: " << pets[idx].id
                         << ", Species: " << pets[idx].species
                         << ", Harga: " << pets[idx].price << ") << endl";
                }

                else {
                    cout << "Hewan dengan ID " << id << " tidak ditemukan." << endl;
                }

                break;
            }

            case 5:
                bubbleSortByName(pets, count);
                cout << "Data telah diurutkan berdasarkan nama (A-Z)." << endl;
                break;

            case 6:
                selectionSortByPrice(pets, count);
                cout << "Data telah diurutkan berdasarkan harga (termurah ke termahal)." << endl;
                break;

            case 7:
                cout << "Terima kasih telah menggunakan Pawcare Petshop!" << endl;
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
        }

    }

    while (pilihan != 7);
    delete[] pets;
    return 0;
}
