# MalRa STRUKDAT

Tugas Besar Struktur Data — Sistem Keanggotaan Ekstrakurikuler (MLL & BST).

## Gambaran Proyek
Proyek C++ ini menerapkan konsep **Abstract Data Type (ADT)** dengan pemisahan file header (`.h`), file implementasi (`.cpp`), dan program utama (`main.cpp`):
- **MLL (Multi-Linked List - MLL-01)**: Mengelola data *Parent* (Siswa: NISN, nama, kelas), *Child* (Ekstrakurikuler: kode, nama ekskul, jam kegiatan, kuota), dan *Relasi* di dalam *parent*.
- **BST (Binary Search Tree)**: Mengelola data presensi menggunakan `NISN` sebagai *key*.
- **Fitur Tambahan**: Fungsionalitas khusus topik (seperti pengecekan kuota, pencegahan bentrok jam kegiatan ekskul, presensi via BST beserta daftar ekskul yang diikuti, serta informasi ekskul terpopuler dan yang belum memenuhi kuota minimal).

## Struktur Folder
```text
MalRa---STRUKDAT/
├── bst/            # File header (.h) & implementasi (.cpp) Binary Search Tree presensi
├── fitur/          # File header (.h) & implementasi (.cpp) fitur khusus sistem ekskul
├── mll/            # File header (.h) & implementasi (.cpp) Multi-Linked List
├── main.cpp        # Program utama / menu aplikasi
└── README.md       # Dokumentasi proyek
