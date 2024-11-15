#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

struct tanggal{
	int bulan;
	int tanggal;
	int tahun;
};

struct Dompet {
   	tanggal tanggal;
    int nomorDompet;
    float saldo;
    Dompet* next;
};

struct Stack {
    Dompet* top;
};

struct Queue {
    Dompet* front;
    Dompet* rear;
};

void push(Stack& stack, Dompet* dompetBaru) {
    dompetBaru->next = stack.top;
    stack.top = dompetBaru;
    cout << "Pengeluaran berhasil ditambahkan ke stack.\n";
}

void pop(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Dompet* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
    cout << "Pengeluaran berhasil dihapus dari stack.\n";
}

void enqueue(Queue& queue, Dompet* dompetBaru) {
    dompetBaru->next = nullptr;
    if (queue.rear == nullptr) {
        queue.front = dompetBaru;
        queue.rear = dompetBaru;
    } else {
        queue.rear->next = dompetBaru;
        queue.rear = dompetBaru;
    }
    cout << "Pengeluaran berhasil ditambahkan ke queue.\n";
}

void dequeue(Queue& queue) {
    if (queue.front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Dompet* temp = queue.front;
    queue.front = queue.front->next;
    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }
    delete temp;
    cout << "Pengeluaran berhasil dihapus dari queue.\n";
}

void tambahPengeluaran(Stack& stack, Queue& queue, int& currentNumber) {
    Dompet* dompetStack = new Dompet;
    Dompet* dompetQueue = new Dompet;

    cout << "Masukkan Tanggal Pengeluaran:\n";
    do {
        cout << "  Hari (dd): ";
        cin >> dompetStack->tanggal.tanggal;
        if (cin.fail() || dompetStack->tanggal.tanggal < 1 || dompetStack->tanggal.tanggal > 31) {
            cout << "  Input tidak valid. Masukkan hari antara 1 dan 31.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    do {
        cout << "  Bulan (mm): ";
        cin >> dompetStack->tanggal.bulan;
        if (cin.fail() || dompetStack->tanggal.bulan < 1 || dompetStack->tanggal.bulan > 12) {
            cout << "  Input tidak valid. Masukkan bulan antara 1 dan 12.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    do {
        cout << "  Tahun (yyyy): ";
        cin >> dompetStack->tanggal.tahun;
        if (cin.fail()) {
            cout << "  Input tidak valid. Masukkan tahun yang benar.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    cout << "Masukkan jumlah pengeluaran: ";
    while (!(cin >> dompetStack->saldo)) {
        cout << "Input tidak valid. Masukkan jumlah dalam bentuk angka.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    dompetStack->saldo = -abs(dompetStack->saldo); 
    dompetStack->nomorDompet = currentNumber++;
    *dompetQueue = *dompetStack;

    push(stack, dompetStack);
    enqueue(queue, dompetQueue);
}

void tampilkanPengeluaran(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Belum ada catatan pengeluaran di stack.\n";
        return;
    }

    Dompet* temp = stack.top;
    int nomorDompet = 1;
    cout << "\n--- Histori Pengeluaran (Stack) ---\n";
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Pengeluaran: " << temp->tanggal.bulan << "/"
             << temp->tanggal.tanggal << "/" << temp->tanggal.tahun << endl;
        cout << "Jumlah Pengeluaran: " << -temp->saldo << endl << endl;
        temp = temp->next;
        nomorDompet++;
    }
}

void tampilkanPengeluaranQueue(Queue& queue) {
    if (queue.front == nullptr) {
        cout << "Belum ada catatan pengeluaran di queue.\n";
        return;
    }

    Dompet* temp = queue.front;
    int nomorDompet = 1;
    cout << "\n--- Histori Pengeluaran (Queue) ---\n";
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Pengeluaran: " << temp->tanggal.bulan << "/"
             << temp->tanggal.tanggal << "/" << temp->tanggal.tahun << endl;
        cout << "Jumlah Pengeluaran: " << -temp->saldo << endl << endl;
        temp = temp->next;
        nomorDompet++;
    }
}

void perbaruiPengeluaran(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Belum ada catatan pengeluaran di stack.\n";
        return;
    }

    int nomorDompet;
    cout << "Masukkan nomor catatan pengeluaran yang ingin diperbarui (stack): ";
    cin >> nomorDompet;

    Dompet* temp = stack.top;
    int posisi = 1;
    while (temp != nullptr && posisi < nomorDompet) {
        temp = temp->next;
        posisi++;
    }

    if (temp == nullptr || temp->saldo >= 0) {
        cout << "Catatan pengeluaran tidak ditemukan di stack.\n";
        return;
    } else {
        cout << "Masukkan jumlah pengeluaran baru: ";
        cin >> temp->saldo;
        temp->saldo = -abs(temp->saldo); 
        cout << "Pengeluaran berhasil diperbarui di stack.\n";
    }
}

void hapusPengeluaranStack(Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Dompet* temp = stack.top;
    stack.top = stack.top->next;
    cout << "Menghapus pengeluaran: " << -temp->saldo << endl;
    delete temp;
}


void hapusPengeluaranQueue(Queue& queue) {
    if (queue.front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }
    Dompet* temp = queue.front;
    queue.front = queue.front->next;
    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }
    cout << "Menghapus pengeluaran: " << -temp->saldo << endl;
    delete temp; 
}


    void tambahDompet(Dompet*& head, int& currentNumber) {
        Dompet* dompetBaru = new Dompet;
        cout << "Masukkan Tanggal:\n";
        do {
            cout << "  Hari (dd): ";
            cin >> dompetBaru->tanggal.tanggal;

            if (cin.fail() || dompetBaru->tanggal.tanggal < 1 || dompetBaru->tanggal.tanggal > 31) {
                cout << "  Input tidak valid. Masukkan hari antara 1 dan 31.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);

        do {
            cout << "  Bulan (mm): ";
            cin >> dompetBaru->tanggal.bulan;

            if (cin.fail() || dompetBaru->tanggal.bulan < 1 || dompetBaru->tanggal.bulan > 12) {
                cout << "  Input tidak valid. Masukkan bulan antara 1 dan 12.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);
        
        do {
            cout << "  Tahun (yyyy): ";
            cin >> dompetBaru->tanggal.tahun;

            if (cin.fail()) {
                cout << "  Input tidak valid. Masukkan tahun yang benar.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);

        cout << "Masukkan saldo awal: ";
        while (!(cin >> dompetBaru->saldo)) {
            cout << "Input tidak valid. Masukkan saldo dalam bentuk angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        dompetBaru->nomorDompet = currentNumber++;
        dompetBaru->next = nullptr;

        if (head == nullptr) {
            head = dompetBaru;
        } else {
            Dompet* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = dompetBaru;
        }
        cout << "Dompet berhasil ditambahkan.\n";
    }

//function sorting untuk tampilkan dompet//

//Modul sorting
void split(Dompet* source, Dompet** front, Dompet** back) {
    Dompet* fast = source->next;
    Dompet* slow = source;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Merge two sorted lists for Merge Sort (Ascending order)
Dompet* sortedMerge(Dompet* a, Dompet* b) {
    if (!a) return b;
    if (!b) return a;

    Dompet* result = nullptr;
    if (a->saldo <= b->saldo) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

// Merge Sort helper function (Ascending order)
void mergeSort(Dompet** headRef) {
    if (!*headRef || !(*headRef)->next) return;

    Dompet* a;
    Dompet* b;
    split(*headRef, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

// Shell Sort function for sorting linked list in descending order
void shellSort(Dompet* head) {
    if (!head) return;

    // Step 1: Find the length of the list
    int n = 0;
    Dompet* temp = head;
    while (temp) {
        n++;
        temp = temp->next;
    }

    // Step 2: Start with a large gap, then reduce it
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Step 3: Perform a gapped insertion sort
        for (int i = 0; i < gap; i++) {
            Dompet* current = head;
            Dompet* prev = nullptr;
            Dompet* next = nullptr;
            Dompet* nextGap = nullptr;

            // Traverse the list with a gap
            while (current != nullptr) {
                int count = 0;
                Dompet* innerCurrent = current;
                
                // Find the node that is gap away
                while (count < gap && innerCurrent != nullptr) {
                    innerCurrent = innerCurrent->next;
                    count++;
                }

                if (innerCurrent != nullptr && current->saldo < innerCurrent->saldo) {
                    // Swap nodes
                    // We need to swap data (saldo, tanggal, nomorDompet) between current and innerCurrent
                    swap(current->saldo, innerCurrent->saldo);
                    swap(current->tanggal, innerCurrent->tanggal);
                    swap(current->nomorDompet, innerCurrent->nomorDompet);
                }
                
                current = current->next;
            }
        }
    }
}
//======================================//

void tampilkanDompet(Dompet* &head) {
    if (head == nullptr) {
        cout << "Belum ada dompet yang ditambahkan.\n";
        return;
    }

    int pilihan;
    cout << "Pilih Metode Sort: " << endl; 
    cout << "1. Descending (Shell Sort)" << endl;
    cout << "2. Ascending (Merge Sort)" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;

    // Display the list before sorting
    cout << "Sebelum sorting:\n";
    Dompet* temp = head;
    int nomorDompet = 1;
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Ditambahkan " << temp->tanggal.bulan << "/"
                                        << temp->tanggal.tanggal << "/"
                                        << temp->tanggal.tahun << endl;
        cout << "Saldo: " << temp->saldo << endl << endl;
        
        temp = temp->next;
        nomorDompet++;
    }

    // Sort the list based on user input
    if (pilihan == 1) {
        shellSort(head); // Ensure head is updated by reference
    } else if (pilihan == 2) {
        mergeSort(&head); // Head is passed by reference
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    // Display the list after sorting
    cout << "\nSetelah sorting:\n";
    temp = head;
    nomorDompet = 1; // Reset nomorDompet
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Ditambahkan " << temp->tanggal.bulan << "/"
                                        << temp->tanggal.tanggal << "/"
                                        << temp->tanggal.tahun << endl;
        cout << "Saldo: " << temp->saldo << endl << endl;
        
        temp = temp->next;
        nomorDompet++; // Increment position
    }
}

//function perbarui data
void perbaruiDompet(Dompet* head) {
    if (head == nullptr) {
        cout << "Belum ada dompet yang ditambahkan.\n";
        return;
    }

    Dompet* temp = head;
    int nomorDompet = 1;
    cout << "\n--- Daftar Catatan Dompet ---\n";
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Ditambahkan: " << temp->tanggal.bulan << "/"
             << temp->tanggal.tanggal << "/" 
             << temp->tanggal.tahun << endl;
        cout << "Saldo: " << temp->saldo << endl << endl;
        temp = temp->next;
        nomorDompet++;
    }

    cout << "Masukkan nomor dompet yang ingin diperbarui: ";
    cin >> nomorDompet;

    if (nomorDompet <= 0) {
        cout << "Nomor dompet tidak valid.\n";
        return;
    }

    temp = head;
    int posisi = 1;

    while (temp != nullptr && posisi < nomorDompet) {
        temp = temp->next;
        posisi++;
    }

    if (temp == nullptr) {
        cout << "Dompet tidak ditemukan.\n";
    } else {
        cout << "Masukkan saldo baru: ";
        cin >> temp->saldo;
        cout << "Saldo berhasil diperbarui untuk Dompet ke-" << nomorDompet << ".\n";
    }
}

void hapusDompet(Dompet*& head) {
    if (head == nullptr) {
        cout << "Belum ada dompet yang ditambahkan.\n";
        return;
    }

    Dompet* temp = head;
    int nomorDompet = 1;
    cout << "\n--- Daftar Catatan Dompet ---\n";
    while (temp != nullptr) {
        cout << "Catatan ke-" << nomorDompet << endl;
        cout << "Tanggal Ditambahkan: " << temp->tanggal.bulan << "/"
             << temp->tanggal.tanggal << "/" 
             << temp->tanggal.tahun << endl;
        cout << "Saldo: " << temp->saldo << endl << endl;
        temp = temp->next;
        nomorDompet++;
    }

    cout << "Masukkan nomor dompet yang ingin dihapus: ";
    cin >> nomorDompet;

    temp = head;
    Dompet* prev = nullptr;
    int posisi = 1;
    while (temp != nullptr && posisi < nomorDompet) {
        prev = temp;
        temp = temp->next;
        posisi++;
    }

    if (temp == nullptr) {
        cout << "Dompet tidak ditemukan.\n";
    } else {
        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Dompet berhasil dihapus.\n";
    }
}

int fibonacciSearch(Dompet* head, float x) {
    int fibMMm2 = 0;   
    int fibMMm1 = 1;    
    int fibM = fibMMm2 + fibMMm1;  

    int n = 0;
    Dompet* temp = head;
    while (temp) {
        n++;
        temp = temp->next;
    }

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = std::min(offset + fibMMm2, n - 1);

        Dompet* target = head;
        for (int j = 0; j < i && target; j++) {
            target = target->next;
        }

        if (!target) break;

        if (target->saldo < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (target->saldo > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i + 1;
        }
    }

    if (fibMMm1 && offset + 1 < n) {
        Dompet* target = head;
        for (int j = 0; j < offset + 1 && target; j++) {
            target = target->next;
        }
        if (target && fabs(target->saldo - x) < 1e-5) { 
            return offset + 2; 
        }
    }

    return -1; 
}

int jumpSearch(Dompet* head, float x) {
    int n = 0;
    Dompet* temp = head;
    while (temp) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);
    int prev = 0;


    Dompet* stepNode = head; 
    temp = head;             

    if (head && head->saldo == x) return 1;

    while (stepNode && stepNode->saldo < x) {
        prev += step;

        for (int i = 0; i < step && stepNode; i++) {
            stepNode = stepNode->next;
        }

        if (!stepNode) break;

        for (int i = 0; i < step && temp->next; i++) {
            temp = temp->next;
        }
    }

    while (temp) {
        if (temp->saldo == x) return prev + 1;

        prev++;
        temp = temp->next;
    }

    return -1;
}

int boyerMooreSearch(Dompet* head, float saldoCari) {
    Dompet* temp = head;
    int posisi = 1;

    while (temp != nullptr) {
        if (temp->saldo == saldoCari) {
            return posisi;
        }
        temp = temp->next;
        posisi++;
    }
    return -1;
}

void cariTanggal(Dompet* head) {
    if (head == nullptr) {
        cout << "Belum ada dompet yang ditambahkan.\n";
        return;
    }

    int tanggal, bulan, tahun;
    cout << "Masukkan Tanggal Pemasukan yang ingin dicari:\n";
    cout << "Tanggal (dd): ";
    cin >> tanggal;
    cout << "Bulan (mm): ";
    cin >> bulan;
    cout << "Tahun (yyyy): ";
    cin >> tahun;

    Dompet* temp = head;
    bool ditemukan = false;
    while (temp != nullptr) {
        if (temp->tanggal.tanggal == tanggal && temp->tanggal.bulan == bulan && temp->tanggal.tahun == tahun) {
            cout << "Dompet ditemukan pada tanggal " 
                 << temp->tanggal.tanggal << "/" 
                 << temp->tanggal.bulan << "/" 
                 << temp->tanggal.tahun << endl;
            cout << "Saldo: " << temp->saldo << endl << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Data dengan tanggal tersebut tidak ditemukan.\n";
    }
}

int main() {
    Dompet* head = nullptr;
    Stack stack{nullptr};  // Initialize Stack for expenses
    Queue queue{nullptr, nullptr};  // Initialize Queue for expenses
    int currentNumber = 1;
    int pilihan;
    do {
        cout << "\n--- Menu Manajemen Dompet ---\n";
        cout << "1. Tambah Catatan Pemasukan\n";
        cout << "2. Histori Catatan\n";
        cout << "3. Perbarui Catatan\n";
        cout << "4. Hapus Catatan\n";
        cout << "5. Tambah Catatan Pengeluaran\n";
        cout << "6. Histori Pengeluaran\n";
        cout << "7. Perbarui Pengeluaran\n";
        cout << "8. Hapus Catatan Pengeluaran\n";
        cout << "9. Cari data\n";
        cout << "10. Search Catatan\n";
        cout << "11. Keluar\n";
        cout << "Pilih menu (1-11): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahDompet(head, currentNumber);
                break;
            case 2:
                tampilkanDompet(head);
                break;
            case 3:
                perbaruiDompet(head);
                break;
            case 4:
                hapusDompet(head);
                break;
            case 5: {
                tambahPengeluaran(stack, queue, currentNumber);
                break;
            }
            case 6: {
                cout << "\nHistori Pengeluaran dalam Stack:\n";
                tampilkanPengeluaran(stack);
                cout << "\nHistori Pengeluaran dalam Queue:\n";
                tampilkanPengeluaranQueue(queue);
                break;
            }
            case 7: {
                perbaruiPengeluaran(stack);
                break;
            }
            case 8: {
                int pilihHapus;
                cout << "\nPilih struktur data untuk menghapus pengeluaran:\n";
                cout << "1. Stack\n";
                cout << "2. Queue\n";
                cout << "Pilihan: ";
                cin >> pilihHapus;
                
                if (pilihHapus == 1) {
                    hapusPengeluaranStack(stack);
                } else if (pilihHapus == 2) {
                    hapusPengeluaranQueue(queue);
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 9: {
                cariTanggal(head);
                break;
            }
            case 10: {
                int searchOption;
                cout << "\n--- Pilih Metode Pencarian ---\n";
                cout << "1. Fibonacci Search\n";
                cout << "2. Jump Search\n";
                cout << "3. Boyer-Moore Search\n";
                cout << "Pilih metode pencarian (1-3): ";
                cin >> searchOption;
            
                float pemasukanCari;
                cout << "Masukkan pemasukan yang ingin dicari: ";
                cin >> pemasukanCari;
            
                int posisi = -1;
                if (searchOption == 1) {
                    posisi = fibonacciSearch(head, pemasukanCari);
                } else if (searchOption == 2) {
                    posisi = jumpSearch(head, pemasukanCari);
                } else if (searchOption == 3) {
                    posisi = boyerMooreSearch(head, pemasukanCari);
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
            
                if (posisi != -1) {
                    cout << "Pemasukan ditemukan di posisi: " << posisi << endl;
                } else {
                    cout << "Pemasukan tidak ditemukan.\n";
                }
                break; 
            }
            case 11:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 11);

    return 0;
}
