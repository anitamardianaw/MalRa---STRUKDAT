#include <iostream>
#include "mll_ekskul.h"
using namespace std;

void createListSiswa(ListSiswa &LS) {
    LS.first = NULL;
}

adrSiswa alokasiSiswa(InfotypeSiswa data) {
    // bikin node siswa baru, list relasinya masih kosong
    adrSiswa P = new ElmSiswa;
    P->info = data;
    P->firstRelasi = NULL;
    P->next = NULL;
    return P;
}

void insertLastSiswa(ListSiswa &LS, adrSiswa P) {
    // tambah siswa di posisi paling belakang
    if (P != NULL) {
        if (LS.first == NULL) {
            LS.first = P;
        } else {
            adrSiswa Q = LS.first;
            while (Q->next != NULL) {
                Q = Q->next;
            }
            Q->next = P;
        }
    }
}

adrSiswa findSiswa(ListSiswa LS, string nisn) {
    // cari siswa pakai flag ketemu supaya tidak perlu break/return di tengah loop
    adrSiswa P = LS.first;
    adrSiswa hasil = NULL;
    bool ketemu = false;

    while (P != NULL && !ketemu) {
        if (P->info.nisn == nisn) {
            hasil = P;
            ketemu = true;
        } else {
            P = P->next;
        }
    }
    return hasil;
}

void deleteSiswa(ListSiswa &LS, string nisn, adrSiswa &P) {
    // hapus semua relasi siswa dulu, baru lepas node siswanya dari LS
    P = NULL;
    if (LS.first != NULL) {
        adrSiswa curr = LS.first;
        adrSiswa prev = NULL;
        bool ketemu = false;

        while (curr != NULL && !ketemu) {
            if (curr->info.nisn == nisn) {
                ketemu = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        if (ketemu) {
            adrRelasi R = curr->firstRelasi;
            while (R != NULL) {
                adrRelasi hapusR = R;
                if (hapusR->ekskul != NULL && hapusR->ekskul->info.jumlahPeserta > 0) {
                    hapusR->ekskul->info.jumlahPeserta--;
                }
                R = R->next;
                delete hapusR;
            }
            curr->firstRelasi = NULL;

            if (prev == NULL) {
                LS.first = curr->next;
            } else {
                prev->next = curr->next;
            }
            curr->next = NULL;
            P = curr;
        }
    }
}

void createListEkskul(ListEkskul &LE) {
    LE.first = NULL;
}

adrEkskul alokasiEkskul(InfotypeEkskul data) {
    // bikin node ekskul baru dengan jumlahPeserta awal 0
    adrEkskul C = new ElmEkskul;
    C->info = data;
    C->info.jumlahPeserta = 0;
    C->next = NULL;
    return C;
}

void insertFirstEkskul(ListEkskul &LE, adrEkskul C) {
    // tambah ekskul di posisi paling depan
    if (C != NULL) {
        C->next = LE.first;
        LE.first = C;
    }
}

adrEkskul findEkskul(ListEkskul LE, string kodeEkskul) {
    // cari ekskul berdasarkan kodeEkskul
    adrEkskul C = LE.first;
    adrEkskul hasil = NULL;
    bool ketemu = false;

    while (C != NULL && !ketemu) {
        if (C->info.kodeEkskul == kodeEkskul) {
            hasil = C;
            ketemu = true;
        } else {
            C = C->next;
        }
    }
    return hasil;
}

void deleteEkskul(ListSiswa &LS, ListEkskul &LE, string kodeEkskul, adrEkskul &C) {
    // bersihin relasi ke ekskul ini di semua siswa sebelum node ekskul dilepas
    C = NULL;
    if (LE.first != NULL) {
        adrSiswa P = LS.first;
        while (P != NULL) {
            deleteRelasi(P, kodeEkskul);
            P = P->next;
        }

        adrEkskul curr = LE.first;
        adrEkskul prev = NULL;
        bool ketemu = false;

        while (curr != NULL && !ketemu) {
            if (curr->info.kodeEkskul == kodeEkskul) {
                ketemu = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        if (ketemu) {
            if (prev == NULL) {
                LE.first = curr->next;
            } else {
                prev->next = curr->next;
            }
            curr->next = NULL;
            C = curr;
        }
    }
}

adrRelasi alokasiRelasi(adrEkskul C) {
    // bikin node relasi yang menunjuk ke node ekskul C
    adrRelasi R = new ElmRelasi;
    R->ekskul = C;
    R->next = NULL;
    return R;
}

void insertLastRelasi(adrSiswa P, adrRelasi R) {
    // tambah relasi di paling akhir list relasi milik siswa P
    if (P != NULL && R != NULL) {
        if (P->firstRelasi == NULL) {
            P->firstRelasi = R;
        } else {
            adrRelasi Q = P->firstRelasi;
            while (Q->next != NULL) {
                Q = Q->next;
            }
            Q->next = R;
        }
        if (R->ekskul != NULL) {
            R->ekskul->info.jumlahPeserta++;
        }
    }
}

adrRelasi findRelasi(adrSiswa P, string kodeEkskul) {
    // cek apakah siswa P sudah terdaftar pada kodeEkskul
    adrRelasi hasil = NULL;
    if (P != NULL) {
        adrRelasi R = P->firstRelasi;
        bool ketemu = false;

        while (R != NULL && !ketemu) {
            if (R->ekskul != NULL && R->ekskul->info.kodeEkskul == kodeEkskul) {
                hasil = R;
                ketemu = true;
            } else {
                R = R->next;
            }
        }
    }
    return hasil;
}

void deleteRelasi(adrSiswa P, string kodeEkskul) {
    // hapus satu relasi ekskul pada siswa P jika ditemukan
    if (P != NULL && P->firstRelasi != NULL) {
        adrRelasi curr = P->firstRelasi;
        adrRelasi prev = NULL;
        bool ketemu = false;

        while (curr != NULL && !ketemu) {
            if (curr->ekskul != NULL && curr->ekskul->info.kodeEkskul == kodeEkskul) {
                ketemu = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        if (ketemu) {
            if (prev == NULL) {
                P->firstRelasi = curr->next;
            } else {
                prev->next = curr->next;
            }
            if (curr->ekskul != NULL && curr->ekskul->info.jumlahPeserta > 0) {
                curr->ekskul->info.jumlahPeserta--;
            }
            delete curr;
        }
    }
}

void showAllSiswa(ListSiswa LS) {
    if (LS.first == NULL) {
        cout << "Belum ada data siswa." << endl;
    } else {
        adrSiswa P = LS.first;
        int i = 1;
        while (P != NULL) {
            cout << i << ". " << P->info.nisn << " - " << P->info.nama << " (" << P->info.kelas << ")" << endl;
            P = P->next;
            i++;
        }
    }
}

void showAllEkskul(ListEkskul LE) {
    // print semua ekskul beserta kuota & pesertanya
    if (LE.first == NULL) {
        cout << "Belum ada data ekskul." << endl;
    } else {
        adrEkskul C = LE.first;
        int i = 1;
        while (C != NULL) {
            cout << i << ". " << C->info.kodeEkskul << " - " << C->info.namaEkskul
                 << " | " << C->info.jamKegiatan
                 << " | " << C->info.jumlahPeserta << "/" << C->info.kuota << endl;
            C = C->next;
            i++;
        }
    }
}

void showEkskulSiswa(adrSiswa P) {
    // tampilin ekskul apa aja yg diambil siswa P
    if (P == NULL) {
        cout << "Siswanya ga ketemu." << endl;
    } else {
        cout << "Ekskul yang diambil " << P->info.nama << " (" << P->info.nisn << "):" << endl;
        if (P->firstRelasi == NULL) {
            cout << "- Belum ambil ekskul." << endl;
        } else {
            adrRelasi R = P->firstRelasi;
            int i = 1;
            while (R != NULL) {
                cout << i << ". " << R->ekskul->info.kodeEkskul << " - "
                     << R->ekskul->info.namaEkskul << " (" << R->ekskul->info.jamKegiatan << ")" << endl;
                R = R->next;
                i++;
            }
        }
    }
}