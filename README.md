# Game
# Stickman Obstacle Runner — C++ Ncurses Game

Proyek ini adalah permainan berbasis teks (*Text-based User Interface* / TUI) yang dikembangkan menggunakan bahasa pemrograman C++ dan pustaka <ncurses.h>. Proyek ini dibuat untuk memenuhi tugas proyek akhir mata kuliah Dasar Pemrograman & Algoritma dengan mengimplementasikan seluruh materi perkuliahan dari Pertemuan pertama hingga Pertemuan terakhir secara terstruktur.

 Deskripsi Permainan
Stickman Obstacle Runner adalah permainan berjenis Endless Side-Scrolling Runner. Pemain mengendalikan karakter berbentuk stickman di sisi kiri layar yang harus melompati deretan rintangan (<----<) yang bergerak secara konstan dari arah kanan ke kiri. 

Setiap rintangan yang berhasil dilewati akan menambah Skor pemain. Seiring bertambahnya skor, tingkat kesulitan permainan akan meningkat melalui penambahan kecepatan gerak rintangan (Speed). Permainan berakhir (Game Over) apabila koordinat tubuh stickman bertabrakan dengan rintangan, lalu skor pemain akan disimpan ke dalam berkas teks untuk diurutkan pada papan peringkat (Leaderboard).

 Visualisasi Elemen Permainan
HUD Status (Sudut Kiri Atas):
  text
  Skor: 0 | Speed: 2
Karakter Pemain (Stickman):
Plaintext
\0/
 |
/ \

Objek Rintangan:
Plaintext
<----<
<----<
<----<

Sistem & Fitur Utama
Animasi Loading & Transisi Teks: Menampilkan progress bar yang bergerak secara bertahap sebelum masuk ke menu utama dan saat memulai permainan.
Menu Utama Interaktif (TUI): Navigasi horizontal menggunakan tombol panah kiri/kanan dengan perubahan warna indikator (highlighting) pada menu aktif (Mulai Game, Keluar, dan About).
Mekanisme Lompat & Pergerakan Rintangan Berbasis Array: Lima objek rintangan di layar diatur posisinya menggunakan struktur data Array dan digerakkan secara simultan setiap frame.
Deteksi Tabrakan (Collision Detection): Pengecekan kondisi koordinat (Y, X) antara posisi kaki/tubuh stickman dan posisi rintangan terdekat.
Penyimpanan Riwayat Skor (File Text): Menyimpan nama pemain dan perolehan skor akhir secara permanen ke dalam file eksternal (highscore.txt / skor.txt) agar data tidak hilang saat program ditutup.
Papan Peringkat & Pencarian Pemain (Sorting & Searching): Mengurutkan daftar skor tertinggi dari yang terbesar ke terkecil (Sorting) serta menyediakan fitur pencarian nama pemain (Searching) pada data riwayat skor.
Implementasi Materi Perkuliahan dalam Kode Program
Seluruh arsitektur kode dalam game ini dibangun ketat berdasarkan silabus materi perkuliahan tanpa menggunakan pustaka eksternal di luar materi yang diajarkan:
Modul Pertemuan
Materi Perkuliahan
Implementasi pada Sistem Game
Pertemuan 2
Pengenalan C++ & Operasi Berkas GNU/Linux
Struktur dasar program (#include <iostream>, using namespace std;, int main()) serta kompilasi dan eksekusi program melalui terminal Linux menggunakan perintah g++.
Pertemuan 3
Struktur Penulisan, Flowchart, & Percabangan
Penggunaan percabangan if, else if, dan else untuk logika pemilihan menu, batas pergerakan kursor menu, pengecekan tombol input keyboard, mekanisme lompat, serta deteksi tabrakan (collision detection) antara stickman dan rintangan.
Pertemuan 4
Perulangan / Looping
Penggunaan while (true) sebagai Main Menu Loop dan Game Loop agar permainan terus berjalan secara real-time, serta perulangan for untuk merender animasi loading bar dan memperbarui posisi seluruh rintangan di layar.
Pertemuan 6
Array
Penyimpanan kumpulan posisi koordinat horizontal (X) dari 5 objek rintangan (<----<) yang muncul berjejer di layar, serta penyimpanan daftar nama dan skor pemain di memori sebelum diurutkan.
Pertemuan 7
Searching & Sorting
Sorting (seperti Bubble Sort / Selection Sort) digunakan untuk mengurutkan data skor pemain dari tertinggi ke terendah pada menu High Score. Searching (seperti Sequential/Linear Search) digunakan untuk mencari riwayat skor berdasarkan nama pemain.
Pertemuan 8
Function
Pemecahan program menjadi fungsi-fungsi modular seperti void loading(), fungsi tampilan karakter stickman, fungsi logika pergerakan game, dan fungsi pengelolaan skor agar kode di dalam int main() tetap bersih dan terstruktur.
Pertemuan 10
File Text
Pemanfaatan pustaka <fstream> (ifstream dan ofstream) untuk membaca dan menulis data skor pemain ke dalam berkas teks .txt secara permanen.
Pertemuan 11
Ncurses
Penggunaan pustaka <ncurses.h> (initscr, cbreak, noecho, keypad, mvprintw, getch, clear, refresh, endwin) dan manajemen skema warna (start_color, init_pair, attron, attroff, bkgd).
Pertemuan 12
Text Animation
Penerapan animasi berbasis teks melalui siklus clear – update koordinat – draw – refresh yang dikombinasikan dengan fungsi penunda waktu napms() untuk menghasilkan efek gerakan loading bar, lompatan stickman, dan laju rintangan yang mulus.

Kontrol Permainan
Tombol
Fungsi di Menu Utama
Fungsi di Dalam Game
Panah Kiri (KEY_LEFT)
Menggeser kursor menu ke kiri
-
Panah Kanan (KEY_RIGHT)
Menggeser kursor menu ke kanan
-
Enter (10 / KEY_ENTER)
Memilih menu yang aktif
-
Spasi / Panah Atas
-
Melompati rintangan (<----<)
Sembarang Tombol
Kembali dari halaman About
Kembali ke Menu Utama saat Game Over

Alur Kerja Program (Ringkasan Flowchart)
Mulai (Start)  Inisialisasi layar ncurses dan konfigurasi pasangan warna (init_pair).
Jalankan fungsi animasi loading().
Tampilkan Menu Utama di dalam perulangan while (true):
Jika pilih "Mulai Game" (pilihan == 0):
Jalankan animasi loading().
Inisialisasi variabel Skor = 0, Speed = 2, posisi awal stickman, dan Array koordinat rintangan.
Masuk ke Game Loop: Gambar HUD, stickman, dan rintangan  Baca input lompat  Geser koordinat array rintangan ke kiri sesuai nilai Speed  Cek tabrakan.
Jika tertabrak (Game Over): Simpan skor ke File Text, urutkan skor dengan Sorting, lalu kembali ke Menu Utama.
Jika pilih "Keluar" (pilihan == 1): Hentikan perulangan (break), panggil endwin(), dan selesai (End).
Jika pilih "About" (pilihan == 2): Tampilkan informasi tugas mata kuliah serta daftar nama & NPM anggota kelompok.
Cara Kompilasi dan Menjalankan Program (GNU/Linux)
Buka terminal Linux (atau workspace CoCalc / WSL) pada direktori tempat berkas kode sumber disimpan, lalu jalankan perintah berikut:
Kompilasi kode C++ dengan flag -lncurses:
Bash
g++ main.cpp -o game -lncurses


Jalankan berkas hasil kompilasi:
Bash
./game


Tim Pengembang (Kelompok)
Proyek ini disusun untuk memenuhi tugas mata kuliah Dasar Pemrograman & Algoritma oleh:
Raihan Belvananda Zuhair — NPM: 2657052002
Irsal Muflih — NPM: 2617052056
Nur Kholifah — NPM: 2657052001
Anisa Setiyawati — NPM: 2617052037


