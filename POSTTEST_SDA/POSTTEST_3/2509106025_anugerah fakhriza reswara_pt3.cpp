/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 2
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

// Queue & Stack
const int MAX = 100; // kapasitas maksimal queue & stack

// Data untuk antrian
struct QueuePet {
    int id;
    string name;
};

// Data untuk riwayat tindakan medis
struct MedicalRecord {
    int petId;
    string petName;
    string action; // deskripsi tindakan
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
    cout << "7. Tambah hewan ke antrian (Enqueue)" << endl;
    cout << "8. Panggil pasien (Dequeue) & catat riwayat (Push)" << endl;
    cout << "9. Batalkan tindakan terakhir (Pop riwayat)" << endl;
    cout << "10. Peek: depan antrian & atas riwayat" << endl;
    cout << "11. Tampilkan semua antrian (pointer aritmatika)" << endl;
    cout << "12. Tampilkan semua riwayat (pointer aritmatika)" << endl;
    cout << "13. Keluar" << endl;
}

// Menambah data hewan
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

// Menampilkan semua data
void tampilkanSemua(const Pet* pets, int count) {
    if (count == 0) {
        cout << "Belum ada data hewan.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(20) << "Nama" << setw(15) << "Species" << setw(10) << "Harga" << endl;
    cout << string(50, '-') << endl;

    for (int i = 0; i < count; ++i) {
        const Pet* p = pets + i;
        cout << left << setw(5) << p->id << setw(20) << p->name << setw(15) << p->species << setw(10) << p->price << endl;
    }
}

// Linear Search berdasarkan nama dan menampilkan tiap iterasi
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

// Bubble Sort berdasarkan nama (A-Z)
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
        int minimalIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if ((pets + j)->price < (pets + minimalIndex)->price) {minimalIndex = j;}
        }

        if (minimalIndex != i) {
            swapPet(pets + i, pets + minimalIndex);
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

// Enqueue: tambah hewan ke antrian (berdasarkan ID dari data pets)
void enqueue(QueuePet* queue, int& front, int& rear, const Pet* pets, int count, int petId) {
    if ((rear + 1) % MAX == front) {
        cout << "Antrian penuh! Tidak bisa menambah." << endl;
        return;
    }

    // cari hewan dengan id tersebut di array pets
    int idx = -1;
    for (int i = 0; i < count; ++i) {
        if ((pets + i)->id == petId) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "ID hewan tidak ditemukan." << endl;
        return;
    }

    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    (queue + rear)->id = (pets + idx)->id;
    (queue + rear)->name = (pets + idx)->name;
    cout << "Hewan " << (queue + rear)->name << " (ID " << (queue + rear)->id << ") ditambahkan ke antrian." << endl;
}

// Dequeue: panggil pasien, hapus dari antrian, dan catat ke stack (push)
void dequeue(QueuePet* queue, int& front, int& rear, MedicalRecord* stack, int& top, const string& action) {
    if (front == -1) {
        cout << "Antrian kosong." << endl;
        return;
    }

    QueuePet pasien = *(queue + front);
    cout << "Memanggil pasien: " << pasien.name << " (ID " << pasien.id << ")" << endl;

    // Catat ke stack riwayat (push)
    if (top == MAX - 1) {
        cout << "Stack riwayat penuh!" << endl;
    } else {
        top++;
        (stack + top)->petId = pasien.id;
        (stack + top)->petName = pasien.name;
        (stack + top)->action = action;
        cout << "Riwayat dicatat: " << pasien.name << " - " << action << endl;
    }
    // Hapus dari queue
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

// Pop riwayat: hapus tindakan terakhir
void popHistory(MedicalRecord* stack, int& top) {
    if (top == -1) {
        cout << "Tidak ada riwayat tindakan." << endl;
        return;
    }
    cout << "Menghapus riwayat terakhir: " << (stack + top)->petName << " - " << (stack + top)->action << endl;
    top--;
}

// Tampilkan semua antrian menggunakan pointer aritmatika
void displayQueue(const QueuePet* queue, int front, int rear) {
    if (front == -1) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "=== DAFTAR ANTRIAN (depan ke belakang) ===" << endl;
    int i = front;
    int pos = 1;
    while (true) {
        cout << pos++ << ". " << (queue + i)->name << " (ID " << (queue + i)->id << ")" << endl;
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
}

// Tampilkan semua riwayat menggunakan pointer aritmatika
void displayHistory(const MedicalRecord* stack, int top) {
    if (top == -1) {
        cout << "Belum ada riwayat tindakan." << endl;
        return;
    }
    cout << "=== RIWAYAT TINDAKAN MEDIS (terbaru di akhir) ===" << endl;
    for (int i = 0; i <= top; ++i) {
        const MedicalRecord* rec = stack + i;
        cout << i+1 << ". " << rec->petName << " (ID " << rec->petId << ") -> " << rec->action << endl;
    }
}

// Peek: tampilkan depan antrian dan atas stack tanpa menghapus
void peek(const QueuePet* queue, int front, const MedicalRecord* stack, int top) {
    cout << "=== PEEK ===" << endl;
    if (front == -1) {
        cout << "Antrian kosong." << endl;
    } else {
        cout << "Pasien terdepan di antrian: " << (queue + front)->name << " (ID " << (queue + front)->id << ")" << endl;
    }
    if (top == -1) {
        cout << "Stack riwayat kosong." << endl;
    } else {
        cout << "Tindakan terakhir di riwayat: " << (stack + top)->petName << " - " << (stack + top)->action << endl;
    }
}

int main() {
    // kapasitas awal
    int capacity = 5;
    
    // jumlah data saat ini
    int count = 0;         

    // array dinamis
    Pet* pets = new Pet[capacity];  

    // Inisialisasi queue (circular queue)
    QueuePet queue[MAX];
    int front = -1, rear = -1;

    // Inisialisasi stack riwayat
    MedicalRecord history[MAX];
    int top = -1;

    int pilihan;
    do {
        tampilkanMenu();
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: // Tambah
                tambahData(pets, count, capacity);
                break;

            case 2: // Tampilkan semua data
                tampilkanSemua(pets, count);
                break;

            case 3: { // Mencari pet
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

            case 4: { // Fibonacci Search
                int id;
                cout << "Masukkan ID hewan: ";
                cin >> id;
                sortById(pets, count);
                int idx = fibonacciSearchById(pets, count, id);

                if (idx != -1) {
                    cout << "Ditemukan: " << pets[idx].name
                         << " (ID: " << pets[idx].id
                         << ", Species: " << pets[idx].species
                         << ", Harga: " << pets[idx].price << ")" << endl;
                }

                else {
                    cout << "Hewan dengan ID " << id << " tidak ditemukan." << endl;
                }

                break;
            }

            case 5: // Bubble Sort
                bubbleSortByName(pets, count);
                cout << "Data telah diurutkan berdasarkan nama (A-Z)." << endl;
                break;

            case 6: // Selection Sort
                selectionSortByPrice(pets, count);
                cout << "Data telah diurutkan berdasarkan harga (termurah ke termahal)." << endl;
                break;

            case 7: { // Enqueue
                if (count == 0) {
                    cout << "Belum ada data hewan. Tambahkan data terlebih dahulu." << endl;
                    break;
                }
                int id;
        	tampilkanMenu();
                cout << "Masukkan ID hewan yang akan diantrikan: ";
                cin >> id;
                enqueue(queue, front, rear, pets, count, id);
                break;
            }

            case 8: { // Dequeue + push riwayat
                if (front == -1) {
                    cout << "Antrian kosong." << endl;
                    break;
                }
                string tindakan;
                cout << "Masukkan tindakan medis yang dilakukan: ";
                getline(cin, tindakan);
                dequeue(queue, front, rear, history, top, tindakan);
                break;
            }

            case 9: // Pop riwayat
                popHistory(history, top);
                break;

            case 10: // Peek
                peek(queue, front, history, top);
                break;

            case 11: // Tampilkan antrian (pointer aritmatika)
                displayQueue(queue, front, rear);
                break;

            case 12: // Tampilkan riwayat (pointer aritmatika)
                displayHistory(history, top);
                break;

            case 13:
                cout << "Terima kasih telah menggunakan Pawcare Petshop!" << endl;
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
        }

    } while (pilihan != 13);

    delete[] pets;
    return 0;
}
