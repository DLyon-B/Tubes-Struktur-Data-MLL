#include "list.h"
#include <iostream>
using namespace std;

void createListLagu(ListLagu &L) {
    L.first = nullptr;
}

adrLagu newLagu(infotypeC x) {
    adrLagu P;

    P = new elmtLagu;
    P->info = x;
    P->next = nullptr;
    return P;
}

void insertLastLagu(ListLagu &L, adrLagu P) {
    if (L.first == nullptr) {
        L.first = P;
    } else {
        adrLagu Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrLagu findLagu(ListLagu L, string idLagu) {
    adrLagu P;

    P = L.first;
    while (P != nullptr) {
        if (P->info.idLagu == idLagu) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deleteLagu(ListLagu &L, adrLagu &P) {
   adrLagu Q = L.first;
    adrLagu prev = nullptr;

    while (Q != nullptr) {
        if (Q == P) {
            if (prev == nullptr) {
                L.first = Q->next;
            } else {
                prev->next = Q->next;
            }
            delete Q;
            P = nullptr;
        } else {
            prev = Q;
        }
        Q = Q->next;
    }
}

void createListPlaylist(ListPlaylist &L) {
    L.first = nullptr;
}

adrPlaylist newPlaylist(infotypeP x) {
    adrPlaylist P;

    P = new elmtPlaylist;
    P->info = x;
    P->next = nullptr;
    return P;
}

void insertLastPlaylist(ListPlaylist &L, adrPlaylist P) {
    adrPlaylist Q;

    if (L.first == nullptr) {
        L.first = P;
    } else {
        Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrPlaylist findPlaylist(ListPlaylist L, string idPlaylist) {
    adrPlaylist P;

    P = L.first;
    while (P != nullptr) {
        if (P->info.idPlaylist == idPlaylist) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deletePlaylist(ListPlaylist &L, adrPlaylist &P) {
    adrPlaylist Q = L.first;
    adrPlaylist prev = nullptr;

    while (Q != nullptr) {
        if (Q == P) {
            if (prev == nullptr) {
                L.first = Q->next;
            } else {
                prev->next = Q->next;
            }
            delete Q;
            P = nullptr;
        } else {
            prev = Q;
        }
        Q = Q->next;
    }
}

void createListRelasi(ListRelasi &L) {
    L.first = nullptr;
}

adrRelasi newRelasi(infotypeR x) {
    adrRelasi R;

    R = new elmtRelasi;
    R->info = x;
    R->parent = nullptr;
    R->child = nullptr;
    R->next = nullptr;
    return R;
}

void insertRelasi(ListRelasi &L, adrRelasi R) {
    if (L.first == nullptr) {
        L.first = R;
    } else {
        adrRelasi Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = R;
    }
}

void deleteRelasi(ListRelasi &L, adrRelasi &R) {
    adrRelasi Q = L.first;
    adrRelasi prev = nullptr;

    while (Q != nullptr) {
        if (Q == R) {
            if (prev == nullptr) {
                L.first = Q->next;
            } else {
                prev->next = Q->next;
            }
            delete Q;
            R = nullptr;
        } else {
            prev = Q;
        }
        Q = Q->next;
    }
}

void tambahPlaylist(ListPlaylist &LP) {
    infotypeP x;
    cout << "Masukkan ID Playlist: ";
    cin >> x.idPlaylist;
    cout << "Masukkan Nama Playlist: ";
    cin >> x.namaPlaylist;
    cout << "Masukkan Genre: ";
    cin >> x.genre;
    x.jumlahLagu = 0;
    insertLastPlaylist(LP, newPlaylist(x));
    cout << "Playlist ditambahkan.\n";
}

void tambahLagu(ListLagu &LL) {
    infotypeC x;
    cout << "Masukkan ID Lagu: ";
    cin >> x.idLagu;
    cout << "Masukkan Judul Lagu: ";
    cin >> x.judul;
    cout << "Masukkan Artis: ";
    cin >> x.artis;
    cout << "Masukkan Durasi (detik): ";
    cin >> x.durasiDetik;
    insertLastLagu(LL, newLagu(x));
    cout << "Lagu ditambahkan.\n";
}

void hubungkanPlaylistLagu(ListRelasi &LR, ListPlaylist LP, ListLagu LL) {
    string idP, idL;

    cout << "Masukkan ID Playlist: ";
    cin >> idP;
    cout << "Masukkan ID Lagu: ";
    cin >> idL;

    adrPlaylist P = findPlaylist(LP, idP);
    adrLagu C = findLagu(LL, idL);

    if (P != nullptr && C != nullptr) {

        if (isRelated(P, C, LR)) {
            cout << "Relasi sudah ada, tidak boleh duplikat.\n";
        } else {
            infotypeR infoR;
            cout << "Masukkan Tanggal Tambah: ";
            cin >> infoR.tanggalTambah;
            cout << "Masukkan Catatan: ";
            cin >> infoR.catatan;

            adrRelasi R = newRelasi(infoR);
            R->parent = P;
            R->child = C;
            insertRelasi(LR, R);
            P->info.jumlahLagu++;

            cout << "Relasi berhasil ditambahkan.\n";
        }

    } else {
        cout << "ID Playlist atau ID Lagu tidak ditemukan.\n";
    }
}

void hapusPlaylist(ListPlaylist &LP, ListRelasi &LR) {
    string id;
    cout << "Masukkan ID Playlist yang ingin dihapus: ";
    cin >> id;

    adrPlaylist P = findPlaylist(LP, id);
    bool ditemukan = true;

    if (P == nullptr) {
        cout << "Playlist tidak ditemukan.\n";
        ditemukan = false;
    }
    if (ditemukan) {
        adrRelasi R = LR.first;
        while (R != nullptr) {
            adrRelasi nextR = R->next;
            if (R->parent == P) {
                if (P->info.jumlahLagu > 0){
                    P->info.jumlahLagu--;
                    deleteRelasi(LR, R);
                }
            }
            R = nextR;
        }
        deletePlaylist(LP, P);
        cout << "Playlist dihapus.\n";
    }
}

void hapusLagu(ListLagu &LL, ListRelasi &LR) {
    string id;
    cout << "Masukkan ID Lagu yang ingin dihapus: ";
    cin >> id;

    adrLagu C = findLagu(LL, id);
    bool ditemukan = true;

    if (C == nullptr) {
        cout << "Lagu tidak ditemukan.\n";
        ditemukan = false;
    }
    if (ditemukan) {
        adrRelasi R = LR.first;
        while (R != nullptr) {
            adrRelasi nextR = R->next;
            if (R->child == C) {
                if (R->parent != nullptr && R->parent->info.jumlahLagu > 0){
                    R->parent->info.jumlahLagu--;
                    deleteRelasi(LR, R);
                }
            }
            R = nextR;
        }
        deleteLagu(LL, C);
        cout << "Lagu dihapus.\n";
    }
}

void hapusRelasi(ListRelasi &LR) {
    string idP, idL;
    cout << "Masukkan ID Playlist: ";
    cin >> idP;
    cout << "Masukkan ID Lagu: ";
    cin >> idL;

    adrRelasi R = LR.first;
    while (R != nullptr) {
        adrRelasi nextR = R->next;

        if (R->parent != nullptr && R->child != nullptr &&
            R->parent->info.idPlaylist == idP &&
            R->child->info.idLagu == idL) {

            if (R->parent->info.jumlahLagu > 0)
                R->parent->info.jumlahLagu--;

            deleteRelasi(LR, R);
        }
        R = nextR;
    }

    cout << "Relasi dihapus (jika ditemukan).\n";
}

bool isRelated(adrPlaylist P, adrLagu C, ListRelasi LR) {
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->parent == P && R->child == C) return true;
        R = R->next;
    }
    return false;
}

void showAllPlaylist(ListPlaylist LP) {
    adrPlaylist P = LP.first;
    while (P != nullptr) {
        cout << P->info.idPlaylist << " " << P->info.namaPlaylist << " "
             << P->info.genre << " " << P->info.jumlahLagu << endl;
        P = P->next;
    }
}

void showAllLagu(ListLagu LL) {
    adrLagu C = LL.first;
    while (C != nullptr) {
        cout << C->info.idLagu << " " << C->info.judul << " "
             << C->info.artis << " " << C->info.durasiDetik << endl;
        C = C->next;
    }
}

void showLaguDariPlaylist(adrPlaylist P, ListRelasi LR) {
    cout << "Lagu dalam playlist " << P->info.namaPlaylist << ":\n";
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->parent == P)
            cout << R->child->info.judul << " ("
                 << R->info.tanggalTambah << " " << R->info.catatan << ")\n";
        R = R->next;
    }
}

void showPlaylistDariLagu(adrLagu C, ListRelasi LR) {
    cout << "Playlist yang memuat lagu " << C->info.judul << ":\n";
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->child == C)
            cout << R->parent->info.namaPlaylist << endl;
        R = R->next;
    }
}

void showAllParentWithChild(ListPlaylist LP, ListRelasi LR) {
    adrPlaylist P = LP.first;
    while (P != nullptr) {
        cout << "Playlist: " << P->info.namaPlaylist << endl;
        adrRelasi R = LR.first;
        bool ada = false;
        while (R != nullptr) {
            if (R->parent == P) {
                cout << "- " << R->child->info.judul << endl;
                ada = true;
            }
            R = R->next;
        }
        if (!ada) cout << "- Tidak ada lagu\n";
        P = P->next;
    }
}

void showAllChildWithParent(ListLagu LL, ListRelasi LR) {
    adrLagu C = LL.first;
    while (C != nullptr) {
        cout << "Lagu: " << C->info.judul << endl;
        adrRelasi R = LR.first;
        bool ada = false;
        while (R != nullptr) {
            if (R->child == C) {
                cout << "- " << R->parent->info.namaPlaylist << endl;
                ada = true;
            }
            R = R->next;
        }
        if (!ada) cout << "- Tidak ada playlist\n";
        C = C->next;
    }
}

void countLaguDalamPlaylist(adrPlaylist P, ListRelasi LR) {
    int count = 0;
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->parent == P) count++;
        R = R->next;
    }
    cout << count << endl;
}

void countPlaylistDariLagu(adrLagu C, ListRelasi LR) {
    int count = 0;
    adrRelasi R = LR.first;
    while (R != nullptr) {
        if (R->child == C) count++;
        R = R->next;
    }
    cout << count << endl;
}

int countChildNoParent(ListLagu LL, ListRelasi LR) {
    int count = 0;
    adrLagu C = LL.first;
    while (C != nullptr) {
        bool ada = false;
        adrRelasi R = LR.first;
        while (R != nullptr) {
            if (R->child == C) ada = true;
            R = R->next;
        }
        if (!ada) count++;
        C = C->next;
    }
    return count;
}

int countParentNoChild(ListPlaylist LP, ListRelasi LR) {
    int count = 0;
    adrPlaylist P = LP.first;
    while (P != nullptr) {
        bool ada = false;
        adrRelasi R = LR.first;
        while (R != nullptr) {
            if (R->parent == P) ada = true;
            R = R->next;
        }
        if (!ada) count++;
        P = P->next;
    }
    return count;
}

void editRelasi(ListRelasi &LR, ListPlaylist LP, ListLagu LL) {
    string idP, idL;
    cout << "Masukkan ID Playlist lama: ";
    cin >> idP;
    cout << "Masukkan ID Lagu lama: ";
    cin >> idL;

    adrRelasi R = LR.first;
    adrRelasi target = nullptr;

    while (R != nullptr) {
        if (R->parent->info.idPlaylist == idP && R->child->info.idLagu == idL)
            target = R;
        R = R->next;
    }

    if (target != nullptr) {
        int pilih;
        cout << "1. Ganti Playlist\n2. Ganti Lagu\nPilihan: ";
        cin >> pilih;

        if (pilih == 1) {
            cout << "Masukkan ID Playlist baru: ";
            cin >> idP;
            adrPlaylist P = findPlaylist(LP, idP);
            if (P != nullptr) target->parent = P;
        }
        else if (pilih == 2) {
            cout << "Masukkan ID Lagu baru: ";
            cin >> idL;
            adrLagu C = findLagu(LL, idL);
            if (C != nullptr) target->child = C;
        }
    } else {
        cout << "Relasi tidak ditemukan.\n";
    }
}
