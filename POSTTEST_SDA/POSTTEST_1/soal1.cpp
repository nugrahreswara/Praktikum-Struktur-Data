/*
Nama: Anugerah Fakhriza Reswara
NIM: 2509106025
Kelas: Informatika A2'25
Praktikum: Struktur Data
Posttest: 1
*/

#include <iostream>
using namespace std;


/*
1. Analisis kompleksitas algoritma:
- Best case: ketika elemen pertama adalah yang terkecil, sehingga assignment min tidak pernah dieksekusi. Jumlah operasi: 
  Tmin(n) = (C3 + C4 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C6). Dengan asumsi setiap instruksi memiliki biaya 1, maka Tmin(n) = 4n + 2.
  Sehingga kompleksitas waktu best case adalah O(n).
- Worst case: ketika elemen terurut menurun (atau elemen terkecil di akhir), sehingga assignment dieksekusi setiap iterasi. 
  Tmax(n) = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C5 - C6) = 5n + 1.
  Sehingga kompleksitas waktu worst case adalah O(n).
  Jadi algoritma ini memiliki kompleksitas linear O(n) untuk semua kasus.
*/

// 2. Implementasi Fungsi FindMin untuk mencari nilai minimum dalam array
int FindMin(int array[], int jumlahElemen) {
    int min = array[0];			// C2: 1 kali
    for (int i = 1; i < jumlahElemen; i++) {	// C3: n kali (termasuk perbandingan terakhir)
        if (array[i] < min) {		// C4: n-1 kali
            min = array[i];			// C5: tergantung kasus
        }				// C6: n-1 kali (end if)
    }					// C7: n kali (end for)
    return min;				// C8: 1 kali
}

/* 3. Tabel perhitungan T-min dan T-max
| Pseudocode		| Cost	| Tmin 	| Tmax	|
| procedure FindMin	| C1 	| 1	| 1	|
| min ← A[0] 		| C2 	| 1 	| 1	|
| for i ← 1 to n - 1	| C3 	| n	| n	|
| if A[i] < min		| C4 	| n-1 	| n-1	|
| min ← A[i]		| C5 	| 0 	| n-1	|
| end if		| C6 	| n-1 	| n-1	|
| end for		| C7 	| n 	| n	|
| return min		| C8 	| 1 	| 1	|
| end procedure		| C9 	| 1 	| 1	|

Perhitungan Tmin(n) - Best Case:
T(n) = C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
     = C1 + C2 + C3n + C4n - C4 + C6n - C6 + C7n + C8 + C9
     = (C3 + C4 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C6)
     = (1 + 1 + 1 + 1)n + (1 + 1 + 1 + 1 - 1 - 1)
     = 4n + 2

Big-O Best Case: O(n)

Perhitungan Tmax(n) - Worst Case:
T(n) = C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8 + C9
     = C1 + C2 + C3n + C4n - C4 + C5n - C5 + C6n - C6 + C7n + C8 + C9
     = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C5 - C6)
     = (1 + 1 + 1 + 1 + 1)n + (1 + 1 + 1 + 1 - 1 - 1 - 1)
     = 5n + 1

Big-O Worst Case: O(n)

4. Hasil Analisis
- Best Case: O(n) - Linear
- Worst Case: O(n) - Linear
- Kedua kasus memiliki kompleksitas yang sama karena algoritma tetap harus memeriksa semua n-1 elemen array.
*/


int main() {
    // Array dengan 8 bilangan Fibonacci
    int array[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int jumlahElemen = 8;
    
    // Cari nilai minimum
    int min = FindMin(array, jumlahElemen);
    
    // Cari indeks pertama yang memiliki nilai minimum
    int index = 0;
    for (int i = 0; i < jumlahElemen; i++) {
        if (array[i] == min) {
            index = i;
            break;
        }
    }
    
    cout << "Nilai minimum: " << min << endl;
    cout << "Indeks pertama: " << index << endl;
    
    return 0;
}
