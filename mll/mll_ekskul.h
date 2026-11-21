#ifndef MLL_EKSKUL_H
#define MLL_EKSKUL_H

#include <iostream>
#include <string>
using namespace std;

// isi data ekskul (bagian child)
struct InfotypeEkskul {
    string kodeEkskul;
    string namaEkskul;
    string jamKegiatan; // contoh: "Selasa 15:30"
    int kuota;
    int jumlahPeserta; // update pas relasi masuk/keluar
};

typedef struct ElmEkskul *adrEkskul;

// node child ekskul
struct ElmEkskul {
    InfotypeEkskul info;
    adrEkskul next;
};

// list ekskul
struct ListEkskul {
    adrEkskul first;
};

typedef struct ElmRelasi *adrRelasi;

// node relasi: nyambungin siswa ke node ekskul
struct ElmRelasi {
    adrEkskul ekskul;
    adrRelasi next;
};

// isi data siswa (bagian parent)
struct InfotypeSiswa {
    string nisn;
    string nama;
    string kelas;
};

typedef struct ElmSiswa *adrSiswa;

// node parent siswa + list relasinya sendiri (MLL-01)
struct ElmSiswa {
    InfotypeSiswa info;
    adrRelasi firstRelasi; // awal list ekskul yang diambil siswa ini
    adrSiswa next;
};

// list siswa
struct ListSiswa {
    adrSiswa first;
};

// siswa (parent) -> insert last
void createListSiswa(ListSiswa &LS); // I.S. bebas; F.S. list siswa kosong
adrSiswa alokasiSiswa(InfotypeSiswa data); // I.S. data ada; F.S. node siswa baru jadi
void insertLastSiswa(ListSiswa &LS, adrSiswa P); // I.S. LS & P ada; F.S. P masuk di akhir LS
adrSiswa findSiswa(ListSiswa LS, string nisn); // I.S. LS & nisn ada; F.S. balikin alamat siswa atau NULL
void deleteSiswa(ListSiswa &LS, string nisn, adrSiswa &P); // I.S. LS & nisn ada; F.S. relasi & node siswa kehapus

// kskul (child) -> insert first
void createListEkskul(ListEkskul &LE); // I.S. bebas; F.S. list ekskul kosong
adrEkskul alokasiEkskul(InfotypeEkskul data); // I.S. data ada; F.S. node ekskul baru jadi
void insertFirstEkskul(ListEkskul &LE, adrEkskul C); // I.S. LE & C ada; F.S. C masuk di awal LE
adrEkskul findEkskul(ListEkskul LE, string kodeEkskul); // I.S. LE & kode ada; F.S. balikin alamat ekskul atau NULL
void deleteEkskul(ListSiswa &LS, ListEkskul &LE, string kodeEkskul, adrEkskul &C); // I.S. LS, LE & kode ada; F.S. relasi di semua siswa & node ekskul kehapus

// relasi -> insert last
adrRelasi alokasiRelasi(adrEkskul C); // I.S. C ada; F.S. node relasi baru jadi
void insertLastRelasi(adrSiswa P, adrRelasi R); // I.S. P & R ada; F.S. R masuk di akhir relasi milik P
adrRelasi findRelasi(adrSiswa P, string kodeEkskul); // I.S. P & kode ada; F.S. balikin alamat relasi atau NULL
void deleteRelasi(adrSiswa P, string kodeEkskul); // I.S. P & kode ada; F.S. relasi ekskul tsb kehapus

// print
void showAllSiswa(ListSiswa LS); // I.S. LS ada; F.S. print semua siswa
void showAllEkskul(ListEkskul LE); // I.S. LE ada; F.S. print semua ekskul
void showEkskulSiswa(adrSiswa P); // I.S. P ada; F.S. print ekskul yang diambil siswa P

#endif
