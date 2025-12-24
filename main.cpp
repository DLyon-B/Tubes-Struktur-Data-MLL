#include <iostream>
#include "list.h"
using namespace std;

int main() {
    ListPlaylist LP;
    ListLagu LL;
    ListRelasi LR;

    createListPlaylist(LP);
    createListLagu(LL);
    createListRelasi(LR);

    int pilihMenu, pilihSub;
    string idP, idL;

menu_utama:
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Data\n";
        cout << "2. Hapus Data\n";
        cout << "3. Tampilkan Data\n";
        cout << "4. Relasi\n";
        cout << "5. Perhitungan\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihMenu;

        switch (pilihMenu) {
        case 1:
menu_tambah:
            cout << "\n=== MENU TAMBAH DATA ===\n";
            cout << "1. Tambah Playlist\n";
            cout << "2. Tambah Lagu\n";
            cout << "0. Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihSub;

            switch (pilihSub) {
                case 1:
                    cout << "Input: IDPlaylist NamaPlaylist Genre\n";
                    tambahPlaylist(LP);
                    goto menu_tambah;

                case 2:
                    cout << "Input: IDLagu JudulLagu Artis DurasiDetik\n";
                    tambahLagu(LL);
                    goto menu_tambah;

                case 0:
                    goto menu_utama;
            }
            goto menu_tambah;

        case 2:
menu_hapus:
            cout << "\n=== MENU HAPUS DATA ===\n";
            cout << "1. Hapus Playlist\n";
            cout << "2. Hapus Lagu\n";
            cout << "3. Hapus Relasi\n";
            cout << "0. Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihSub;

            switch (pilihSub) {
                case 1:
                    hapusPlaylist(LP, LR);
                    goto menu_hapus;

                case 2:
                    hapusLagu(LL, LR);
                    goto menu_hapus;

                case 3:
                    hapusRelasi(LR);
                    goto menu_hapus;

                case 0:
                    goto menu_utama;
            }
            goto menu_hapus;

        case 3:
menu_tampil:
            cout << "\n=== MENU TAMPILKAN DATA ===\n";
            cout << "1. Tampilkan Semua Playlist\n";
            cout << "2. Tampilkan Semua Lagu\n";
            cout << "3. Tampilkan Lagu dari Playlist\n";
            cout << "4. Tampilkan Playlist dari Lagu\n";
            cout << "5. Tampilkan Semua Playlist + Lagunya\n";
            cout << "6. Tampilkan Semua Lagu + Playlistnya\n";
            cout << "0. Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihSub;

            switch (pilihSub) {
                case 1:
                    showAllPlaylist(LP);
                    goto menu_tampil;

                case 2:
                    showAllLagu(LL);
                    goto menu_tampil;

                case 3:
                    cout << "Masukkan ID Playlist: ";
                    cin >> idP;
                    if (findPlaylist(LP, idP) != nullptr)
                        showLaguDariPlaylist(findPlaylist(LP, idP), LR);
                    else
                        cout << "Playlist tidak ditemukan.\n";
                    goto menu_tampil;

                case 4:
                    cout << "Masukkan ID Lagu: ";
                    cin >> idL;
                    if (findLagu(LL, idL) != nullptr)
                        showPlaylistDariLagu(findLagu(LL, idL), LR);
                    else
                        cout << "Lagu tidak ditemukan.\n";
                    goto menu_tampil;

                case 5:
                    showAllParentWithChild(LP, LR);
                    goto menu_tampil;

                case 6:
                    showAllChildWithParent(LL, LR);
                    goto menu_tampil;

                case 0:
                    goto menu_utama;
            }
            goto menu_tampil;

        case 4:
menu_relasi:
            cout << "\n=== MENU RELASI ===\n";
            cout << "1. Hubungkan Playlist - Lagu\n";
            cout << "2. Cek Relasi Playlist dan Lagu\n";
            cout << "3. Edit Relasi\n";
            cout << "0. Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihSub;

            switch (pilihSub) {
                case 1:
                    cout << "Input: IDPlaylist IDLagu TanggalTambah Catatan\n";
                    hubungkanPlaylistLagu(LR, LP, LL);
                    goto menu_relasi;

                case 2:
                    cout << "Masukkan ID Playlist: ";
                    cin >> idP;
                    cout << "Masukkan ID Lagu: ";
                    cin >> idL;
                    if (findPlaylist(LP, idP) != nullptr && findLagu(LL, idL) != nullptr) {
                        if (isRelated(findPlaylist(LP, idP), findLagu(LL, idL), LR))
                            cout << "Berelasi\n";
                        else
                            cout << "Tidak berelasi\n";
                    } else {
                        cout << "ID tidak ditemukan.\n";
                    }
                    goto menu_relasi;

                case 3:
                    cout << "Input: IDPlaylistLama IDLaguLama\n";
                    editRelasi(LR, LP, LL);
                    goto menu_relasi;

                case 0:
                    goto menu_utama;
            }
            goto menu_relasi;

        case 5:
menu_count:
            cout << "\n=== MENU PERHITUNGAN ===\n";
            cout << "1. Hitung Lagu dalam Playlist\n";
            cout << "2. Hitung Playlist dari Lagu\n";
            cout << "3. Hitung Lagu tanpa Playlist\n";
            cout << "4. Hitung Playlist tanpa Lagu\n";
            cout << "0. Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilihSub;

            switch (pilihSub) {
                case 1:
                    cout << "Masukkan ID Playlist: ";
                    cin >> idP;
                    if (findPlaylist(LP, idP) != nullptr)
                        countLaguDalamPlaylist(findPlaylist(LP, idP), LR);
                    else
                        cout << "Playlist tidak ditemukan.\n";
                    goto menu_count;

                case 2:
                    cout << "Masukkan ID Lagu: ";
                    cin >> idL;
                    if (findLagu(LL, idL) != nullptr)
                        countPlaylistDariLagu(findLagu(LL, idL), LR);
                    else
                        cout << "Lagu tidak ditemukan.\n";
                    goto menu_count;

                case 3:
                    cout << "Jumlah lagu tanpa playlist: " << countChildNoParent(LL, LR) << endl;
                    goto menu_count;

                case 4:
                    cout << "Jumlah playlist tanpa lagu: " << countParentNoChild(LP, LR) << endl;
                    goto menu_count;

                case 0:
                    goto menu_utama;
            }
            goto menu_count;


        case 0:
            cout << "Program selesai.\n";
            goto akhir_program;

        default:
            cout << "Pilihan tidak valid.\n";
            goto menu_utama;
        }

    } while (pilihMenu != 0);
akhir_program:
    return 0;
}
