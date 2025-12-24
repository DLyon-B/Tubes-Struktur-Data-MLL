#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <string>
using namespace std;

//Struct Lagu
struct Lagu {
    string idLagu;
    string judul;
    string artis;
    int durasiDetik;
};

typedef Lagu infotypeC;

struct elmtLagu {
    infotypeC info;
    elmtLagu *next;
};

typedef elmtLagu* adrLagu;

struct ListLagu {
    adrLagu first;
};

// Struct Playlist
struct Playlist {
    string idPlaylist;
    string namaPlaylist;
    string genre;
    int jumlahLagu;
};

typedef Playlist infotypeP;

struct elmtPlaylist {
    infotypeP info;
    elmtPlaylist *next;
};

typedef elmtPlaylist* adrPlaylist;

struct ListPlaylist {
    adrPlaylist first;
};

//Struct Relasi
struct DataRelasi {
    string tanggalTambah;
    string catatan;
};

typedef DataRelasi infotypeR;

struct elmtRelasi {
    infotypeR info;
    adrPlaylist parent;
    adrLagu child;
    elmtRelasi *next;
};

typedef elmtRelasi* adrRelasi;

struct ListRelasi {
    adrRelasi first;
};

//Primitive
void createListLagu(ListLagu &L);
adrLagu newLagu(infotypeC x);
void insertLastLagu(ListLagu &L, adrLagu P);
adrLagu findLagu(ListLagu L, string idLagu);
void deleteLagu(ListLagu &L, adrLagu &P);

void createListPlaylist(ListPlaylist &L);
adrPlaylist newPlaylist(infotypeP x);
void insertLastPlaylist(ListPlaylist &L, adrPlaylist P);
adrPlaylist findPlaylist(ListPlaylist L, string idPlaylist);
void deletePlaylist(ListPlaylist &L, adrPlaylist &P);

void createListRelasi(ListRelasi &L);
adrRelasi newRelasi(infotypeR x);
void insertRelasi(ListRelasi &L, adrRelasi R);
void deleteRelasi(ListRelasi &L, adrRelasi &R);

/*Controller*/
void tambahPlaylist(ListPlaylist &LP);
void tambahLagu(ListLagu &LL);
void hubungkanPlaylistLagu(ListRelasi &LR, ListPlaylist LP, ListLagu LL);

void hapusPlaylist(ListPlaylist &LP, ListRelasi &LR);
void hapusLagu(ListLagu &LL, ListRelasi &LR);
void hapusRelasi(ListRelasi &LR);

void showAllPlaylist(ListPlaylist LP);
void showAllLagu(ListLagu LL);
void showLaguDariPlaylist(adrPlaylist P, ListRelasi LR);
void showPlaylistDariLagu(adrLagu C, ListRelasi LR);

void countLaguDalamPlaylist(adrPlaylist P, ListRelasi LR);
void countPlaylistDariLagu(adrLagu C, ListRelasi LR);

bool isRelated(adrPlaylist P, adrLagu C, ListRelasi LR);

void showAllParentWithChild(ListPlaylist LP, ListRelasi LR);
void showAllChildWithParent(ListLagu LL, ListRelasi LR);

int countChildNoParent(ListLagu LL, ListRelasi LR);
int countParentNoChild(ListPlaylist LP, ListRelasi LR);

void editRelasi(ListRelasi &LR, ListPlaylist LP, ListLagu LL);
#endif // MLL_H_INCLUDED
