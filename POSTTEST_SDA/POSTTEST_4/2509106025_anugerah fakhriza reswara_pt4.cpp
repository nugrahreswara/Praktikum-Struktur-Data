/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 4
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

// Queue & Stack (SINGLE LINKED LIST)
// Data untuk antrian (ditambah pointer next)
struct QueuePet {
    int id;
    string name;
    QueuePet* next; // pointer ke node berikutnya
};

// Data untuk riwayat tindakan medis (ditambah pointer next)
struct MedicalRecord {
    int petId;
    string petName;
    string action; // deskripsi tindakan
    MedicalRecord* next; // pointer ke node berikutnya
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
    cout << "11. Tampilkan semua antrian (Pointer aritmatika)" << endl;
    cout << "12. Tampilkan semua riwayat (Pointer aritmatika)" << endl;
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

// ========== FUNGSI QUEUE & STACK BERBASIS SINGLE LINKED LIST ==========

// Enqueue: tambah hewan ke antrian (di belakang)
void enqueue(QueuePet*& front, QueuePet*& rear, const Pet* pets, int count, int petId) {
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

    QueuePet* newNode = new QueuePet;
    newNode->id = (pets + idx)->id;
    newNode->name = (pets + idx)->name;
    newNode->next = nullptr;

    if (front == nullptr) { // antrian kosong
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Hewan " << newNode->name << " (ID " << newNode->id << ") ditambahkan ke antrian." << endl;
}

// Push ke stack riwayat (catat tindakan medis)
void pushHistory(MedicalRecord*& top, int petId, const string& petName, const string& action) {
    MedicalRecord* newNode = new MedicalRecord;
    newNode->petId = petId;
    newNode->petName = petName;
    newNode->action = action;
    newNode->next = top;
    top = newNode;
}

// Dequeue: panggil pasien, hapus dari antrian, dan catat ke stack (push)
void dequeue(QueuePet*& front, QueuePet*& rear, MedicalRecord*& stackTop, const string& action) {
    if (front == nullptr) {
        cout << "Antrian kosong." << endl;
        return;
    }

    QueuePet* temp = front;
    int petId = temp->id;
    string petName = temp->name;
    cout << "Memanggil pasien: " << petName << " (ID " << petId << ")" << endl;

    // Hapus node depan
    front = front->next;
    if (front == nullptr) rear = nullptr; // antrian menjadi kosong
    delete temp;

    // Catat ke stack riwayat (push)
    pushHistory(stackTop, petId, petName, action);
    cout << "Riwayat dicatat: " << petName << " - " << action << endl;
}

// Pop riwayat: hapus tindakan terakhir
void popHistory(MedicalRecord*& stackTop) {
    if (stackTop == nullptr) {
        cout << "Tidak ada riwayat tindakan." << endl;
        return;
    }
    MedicalRecord* temp = stackTop;
    cout << "Menghapus riwayat terakhir: " << temp->petName << " - " << temp->action << endl;
    stackTop = stackTop->next;
    delete temp;
}

// Tampilkan semua antrian (iterasi linked list)
void displayQueue(const QueuePet* front) {
    if (front == nullptr) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "=== DAFTAR ANTRIAN (depan ke belakang) ===" << endl;
    const QueuePet* current = front;
    int pos = 1;
    while (current != nullptr) {
        cout << pos++ << ". " << current->name << " (ID " << current->id << ")" << endl;
        current = current->next;
    }
}

// Tampilkan semua riwayat (dari terbaru ke terlama)
void displayHistory(const MedicalRecord* top) {
    if (top == nullptr) {
        cout << "Belum ada riwayat tindakan." << endl;
        return;
    }
    cout << "=== RIWAYAT TINDAKAN MEDIS (terbaru di awal) ===" << endl;
    const MedicalRecord* current = top;
    int pos = 1;
    while (current != nullptr) {
        cout << pos++ << ". " << current->petName << " (ID " << current->petId << ") -> " << current->action << endl;
        current = current->next;
    }
}

// Peek: tampilkan depan antrian dan atas stack tanpa menghapus
void peek(const QueuePet* front, const MedicalRecord* stackTop) {
    cout << "=== PEEK ===" << endl;
    if (front == nullptr) {
        cout << "Antrian kosong." << endl;
    } else {
        cout << "Pasien terdepan di antrian: " << front->name << " (ID " << front->id << ")" << endl;
    }
    if (stackTop == nullptr) {
        cout << "Stack riwayat kosong." << endl;
    } else {
        cout << "Tindakan terakhir di riwayat: " << stackTop->petName << " - " << stackTop->action << endl;
    }
}

// Fungsi untuk membersihkan memori antrian
void clearQueue(QueuePet*& front) {
    while (front != nullptr) {
        QueuePet* temp = front;
        front = front->next;
        delete temp;
    }
}

// Fungsi untuk membersihkan memori stack
void clearStack(MedicalRecord*& top) {
    while (top != nullptr) {
        MedicalRecord* temp = top;
        top = top->next;
        delete temp;
    }
}

int main() {
    // kapasitas awal
    int capacity = 5;
    
    // jumlah data saat ini
    int count = 0;         

    // array dinamis
    Pet* pets = new Pet[capacity];  

    // Inisialisasi queue (linked list)
    QueuePet* queueFront = nullptr;
    QueuePet* queueRear = nullptr;

    // Inisialisasi stack riwayat (linked list)
    MedicalRecord* stackTop = nullptr;

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
                cout << "Masukkan ID hewan yang akan diantrikan: ";
                cin >> id;
                enqueue(queueFront, queueRear, pets, count, id);
                break;
            }

            case 8: { // Dequeue + push riwayat
                if (queueFront == nullptr) {
                    cout << "Antrian kosong." << endl;
                    break;
                }
                string tindakan;
                cout << "Masukkan tindakan medis yang dilakukan: ";
                getline(cin, tindakan);
                dequeue(queueFront, queueRear, stackTop, tindakan);
                break;
            }

            case 9: // Pop riwayat
                popHistory(stackTop);
                break;

            case 10: // Peek
                peek(queueFront, stackTop);
                break;

            case 11: // Tampilkan antrian
                displayQueue(queueFront);
                break;

            case 12: // Tampilkan riwayat
                displayHistory(stackTop);
                break;

            case 13:
                cout << "Terima kasih telah menggunakan Pawcare Petshop!" << endl;
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
        }

    } while (pilihan != 13);

    // Bersihkan memori
    delete[] pets;
    clearQueue(queueFront);
    clearStack(stackTop);

    return 0;
}
