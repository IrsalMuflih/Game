#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <fstream>

using namespace std;

void loading() {
    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int tengah = max_x / 2;

    attron(COLOR_PAIR(2));
    mvprintw(10, tengah - 5, "Loading....");
    mvprintw(11, tengah - 9, "-----------------");
    mvprintw(13, tengah - 9, "-----------------");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(12, tengah - 9, "|                 |");
    attroff(COLOR_PAIR(1));

    for (int f = 1; f < 18; f++) {
        attron(COLOR_PAIR(3));
        mvprintw(12, tengah - 9 + f, ">");
        attroff(COLOR_PAIR(3));

        refresh();
        napms(100);
    }

    clear();
}

struct player {
    string nama;
    int skor;
};

const int MAX_PLAYER = 5;
int jumlahPemain = 0;
player highScores[MAX_PLAYER];

void loadHighScore() {
    ifstream file("highscore.txt");
    string baris;

    jumlahPemain = 0;

    while (getline(file, baris) && jumlahPemain < MAX_PLAYER) {
        size_t posisi = baris.find('|');

        if (posisi != string::npos) {
            highScores[jumlahPemain].skor =
                stoi(baris.substr(0, posisi));

            highScores[jumlahPemain].nama =
                baris.substr(posisi + 1);

            jumlahPemain++;
        }
    }

    file.close();

    for (int i = 0; i < jumlahPemain - 1; i++) {
        for (int j = 0; j < jumlahPemain - i - 1; j++) {
            if (highScores[j].skor < highScores[j + 1].skor) {
                player sementara = highScores[j];
                highScores[j] = highScores[j + 1];
                highScores[j + 1] = sementara;
            }
        }
    }
}

void simpanHighScore() {
    ofstream file("highscore.txt");

    for (int i = 0; i < jumlahPemain; i++) {
        file << highScores[i].skor << "|"
             << highScores[i].nama << endl;
    }

    file.close();
}

void inputHighScore(int skor) {
    char nama[30];

    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int tengah = max_x / 2;

    attron(COLOR_PAIR(2));
    mvprintw(8, tengah - 13, "=== MASUKKAN NAMA ANDA ===");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(11, tengah - 20, "Nama pemain: ");
    mvprintw(13, tengah - 20, "Skor akhir: %d", skor);
    attroff(COLOR_PAIR(1));

    echo();
    curs_set(1);
    move(11, tengah - 7);
    getnstr(nama, 29);
    noecho();
    curs_set(0);

    string namaPemain = nama;

    if (namaPemain.empty()) {
        namaPemain = "Pemain";
    }

    if (jumlahPemain < MAX_PLAYER) {
        highScores[jumlahPemain].nama = namaPemain;
        highScores[jumlahPemain].skor = skor;
        jumlahPemain++;
    }

    else if (skor > highScores[jumlahPemain - 1].skor) {
        highScores[jumlahPemain - 1].nama = namaPemain;
        highScores[jumlahPemain - 1].skor = skor;
    }

    for (int i = 0; i < jumlahPemain - 1; i++) {
        for (int j = 0; j < jumlahPemain - i - 1; j++) {
            if (highScores[j].skor < highScores[j + 1].skor) {
                player sementara = highScores[j];
                highScores[j] = highScores[j + 1];
                highScores[j + 1] = sementara;
            }
        }
    }

    simpanHighScore();

    clear();

    attron(COLOR_PAIR(3));
    mvprintw(9, tengah - 17, "=== SCORE BERHASIL DISIMPAN! ===");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    mvprintw(12, tengah - 20, "Nama pemain : %s", namaPemain.c_str());
    mvprintw(13, tengah - 20, "Skor akhir  : %d", skor);
    mvprintw(16, tengah - 20, "Silakan lihat High Score di menu utama.");
    mvprintw(18, tengah - 22, "Tekan tombol apa saja untuk kembali ke menu.");
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
}

void tampilkanHighScores() {
    loadHighScore();
    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int tengah = max_x / 2;

    attron(COLOR_PAIR(2));
    mvprintw(5, tengah - 10, "=== HIGH SCORES ===");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(4));
    mvprintw(8, tengah - 30, "RANK");
    mvprintw(8, tengah - 18, "NAMA");
    mvprintw(8, tengah + 5, "SKOR");
    attroff(COLOR_PAIR(4));

    if (jumlahPemain == 0) {
        mvprintw(10, tengah - 15, "Belum ada data High Score.");
    }

    for (int i = 0; i < jumlahPemain; i++) {
        attron(COLOR_PAIR(1));
        mvprintw(10 + i, tengah - 30, "%d", i + 1);
        mvprintw(10 + i, tengah - 18, "%s", highScores[i].nama.c_str());
        mvprintw(10 + i, tengah + 5, "%d", highScores[i].skor);
        attroff(COLOR_PAIR(1));
    }

    attron(COLOR_PAIR(3));
    mvprintw(15, tengah - 18, "Tekan tombol apa saja untuk kembali.");
    attroff(COLOR_PAIR(3));

    refresh();
    getch();
    clear();
}

void animasiMenu(int frame, int max_y, int max_x) {
    int ground_y = max_y - 2;

    // Lantai
    attron(COLOR_PAIR(3));
    for (int i = 0; i < max_x; i++) {
        mvaddch(ground_y + 1, i, '=');
    }
    attroff(COLOR_PAIR(3));

    // Posisi stickman berjalan
    int stickman_x = 2 + (frame % (max_x - 5));

    attron(COLOR_PAIR(1));

    // Hapus posisi stickman sebelumnya
    static int old_stickman_x = -1;

    if (old_stickman_x != -1) {
        mvaddstr(ground_y - 2, old_stickman_x, "   ");
        mvaddstr(ground_y - 1, old_stickman_x, "   ");
        mvaddstr(ground_y, old_stickman_x, "   ");
    }

    // Kepala dan badan
    mvaddstr(ground_y - 2, stickman_x, " O ");
    mvaddstr(ground_y - 1, stickman_x, "/|\\");

    // Animasi kaki berjalan
    if ((frame / 4) % 2 == 0) {
        mvaddstr(ground_y, stickman_x, "/ \\");
    } else {
        mvaddstr(ground_y, stickman_x, "|| ");
    }

    old_stickman_x = stickman_x;

    attroff(COLOR_PAIR(1));

    // Posisi burung terbang
    int bird_x = max_x - 4 - (frame % (max_x - 6));
    int bird_y = max_y - 6;

    attron(COLOR_PAIR(2));

    // Hapus posisi burung sebelumnya
    static int old_bird_x = -1;

    if (old_bird_x != -1) {
        mvaddstr(bird_y, old_bird_x, "   ");
    }

    // Animasi burung
    if ((frame / 5) % 2 == 0) {
        mvaddstr(bird_y, bird_x, "<o>");
    } else {
        mvaddstr(bird_y, bird_x, "(o)");
    }

    old_bird_x = bird_x;

    attroff(COLOR_PAIR(2));
}

int runGame() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int ground_y = max_y - 5;
    if (ground_y < 15) ground_y = 15;

    int stickman_x = 10;
    float stickman_y = ground_y - 1;
    float velocity_y = 0;
    float gravity = 0.4;
    bool is_jumping = false;
    bool is_ducking = false;
    int duck_frame = 0;
    const int duck_duration = 8;

    int obstacle_x = max_x - 10;
    int obstacle_type = 0;
    int score = 0;
    bool game_over = false;
    int frame = 0;

    nodelay(stdscr, TRUE);

    while (!game_over) {
        int ch = getch();
        if (ch == ' ' || ch == 'w' || ch == 'W' || ch == KEY_UP) {
            if (!is_jumping && !is_ducking) {
                velocity_y = -2.2;
                is_jumping = true;
            }
        } else if (ch == 's' || ch == 'S' || ch == KEY_DOWN) {
            if (!is_jumping && !is_ducking) {
                is_ducking = true;
                duck_frame = 0;
            }
        } else if (ch == 'q' || ch == 'Q') {
            nodelay(stdscr, FALSE);
            clear();
            attron(COLOR_PAIR(2));
            return -1;
        } else if (ch != ERR) {
            if (!is_jumping) {
                is_ducking = false;
            }
        }

        if (is_ducking) {
            duck_frame++;

            if (duck_frame >= duck_duration) {
                is_ducking = false;
                duck_frame = 0;
            }
        }

        if (is_jumping) {
            stickman_y += velocity_y;
            velocity_y += gravity;
            if (stickman_y >= ground_y - 1) {
                stickman_y = ground_y - 1;
                is_jumping = false;
                velocity_y = 0;
            }
        }

        obstacle_x--;
        if (obstacle_x < 2) {
            obstacle_x = max_x - 10;
            obstacle_type = (frame / 10) % 2;
            score += 10;
        }

        int current_sy = (int)stickman_y;
        if (obstacle_x >= stickman_x && obstacle_x <= stickman_x + 2) {
            if (obstacle_type == 0 && current_sy >= ground_y - 2) {
                game_over = true;
            } else if (obstacle_type == 1 && !is_ducking) {
                game_over = true;
            }
        }

        erase();

        attron(COLOR_PAIR(3));
        for (int i = 0; i < max_x; i++) {
            mvaddch(ground_y + 1, i, '=');
        }
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(2));
        mvprintw(2, 4, "SCORE: %d", score);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4));
        mvprintw(2, max_x / 2 - 20, "W/SPACE: Lompat | S: Tunduk | Q: Keluar");
        attroff(COLOR_PAIR(4));

        attron(COLOR_PAIR(1));
        if (is_ducking) {
            mvaddstr(ground_y - 1, stickman_x, "<o>");
            mvaddstr(ground_y, stickman_x, "/=\\");
        } else {
            int sy = (int)stickman_y;
            mvaddstr(sy - 1, stickman_x, " O ");
            mvaddstr(sy, stickman_x, "/|\\");

            if ((frame / 4) % 2 == 0) {
                mvaddstr(sy + 1, stickman_x, "/ \\");
            } else {
                mvaddstr(sy + 1, stickman_x, "|| ");
            }
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        if (obstacle_type == 0) {
            mvaddstr(ground_y - 2, obstacle_x, "<---<");
            mvaddstr(ground_y - 1, obstacle_x, "<---<");
            mvaddstr(ground_y, obstacle_x, "<---<");
        } else {
            int bird_y = ground_y - 3;
            if ((frame / 5) % 2 == 0) {
                mvaddstr(bird_y, obstacle_x, "<o>");
            } else {
                mvaddstr(bird_y, obstacle_x, "(o)");
            }
        }
        attroff(COLOR_PAIR(2));

        refresh();
        int current_speed = 45000 - (score / 50) * 500;
        if (current_speed < 30000) {
            current_speed = 30000;
        }

        usleep(current_speed);
        frame++;
    }

    nodelay(stdscr, FALSE);
    clear();

    attron(COLOR_PAIR(2));
    mvprintw(max_y / 2 - 2, max_x / 2 - 5, "GAME OVER!");
    mvprintw(max_y / 2, max_x / 2 - 9, "FINAL SCORE: %d", score);
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(max_y / 2 + 2, max_x / 2 - 20, "Tekan tombol apa saja untuk kembali...");
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    return score;
}

void about(){

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int tengah = max_x / 2;
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(5, tengah - 39, "Game ini dibuat untuk memenuhi tugas proyek akhir Mata Kuliah Dasar Pemrograman & Algoritma.");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(4));
    mvprintw(6, tengah - 25, "Dibuat oleh kelompok kami yang beranggotakan:");

    mvprintw(8, tengah - 22, "Raihan Belvananda Zuhair : NPM (2657052002)");
    mvprintw(9, tengah - 22, "Irsal Muflih             : NPM (2617052056)");
    mvprintw(10, tengah - 22, "Nur Kholifah             : NPM (2657052001)");
    mvprintw(11, tengah - 22, "Anisa Setiyawati         : NPM (2617052037)");

    mvprintw(13, tengah - 18, "Tekan tombol apa saja untuk kembali.");
    mvprintw(14, tengah - 8, "Game Version 1.0");
    attroff(COLOR_PAIR(4));

    refresh();
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
    clear();
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));

    loadHighScore();

    int pilihan = 0;
    int tombol;

    loading();

    nodelay(stdscr, TRUE);

    int frame = 0;

    while (true) {

        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        int tengah = max_x / 2;

        attron(COLOR_PAIR(2));
        mvprintw(5, tengah - 14, "=== STICKMAN RUNNER GAME ===");
        attroff(COLOR_PAIR(2));

        if (pilihan == 0) {
            attron(COLOR_PAIR(3));
            mvprintw(12, tengah - 33, "> Mulai Game");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, tengah - 33, "  Mulai Game");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 1) {
            attron(COLOR_PAIR(3));
            mvprintw(12, tengah - 14, "> High Scores");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, tengah - 14, "  High Scores");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 2) {
            attron(COLOR_PAIR(3));
            mvprintw(12, tengah + 5, "> Keluar");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, tengah + 5, "  Keluar");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 3) {
            attron(COLOR_PAIR(3));
            mvprintw(12, tengah + 18, "> Tentang Game");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, tengah + 18, "  Tentang Game");
            attroff(COLOR_PAIR(1));
        }

        attron(COLOR_PAIR(4));
        mvprintw(15, tengah - 5, "Created by:");
        mvprintw(16, tengah - 35, "Raihan Belvananda Zuhair * Irsal Muflih * Nur Kholifah * Anisa Setiyawati");
        attroff(COLOR_PAIR(4));

        // Animasi stickman dan burung
        animasiMenu(frame, max_y, max_x);

        refresh();

        tombol = getch();

        napms(80);
        frame++;

        if (tombol == KEY_LEFT || tombol == 'a' || tombol == 'A') {
            pilihan--;
            if (pilihan < 0)
                pilihan = 3;
        } else if (tombol == KEY_RIGHT || tombol == 'd' || tombol == 'D') {
            pilihan++;
            if (pilihan > 3)
                pilihan = 0;
        } else if (tombol == 10 || tombol == KEY_ENTER || tombol == ' ') {
            if (pilihan == 0) {
                nodelay(stdscr, FALSE);
                loading();

                int finalScore = runGame();

                if (finalScore >= 0) {
                    inputHighScore(finalScore);
                }
                
                clear();
                nodelay(stdscr, TRUE);
            }
            else if (pilihan == 1) {
                nodelay(stdscr, FALSE);

                tampilkanHighScores();

                nodelay(stdscr, TRUE);
            }
            else if (pilihan == 2) {
                break;
            }
            else if (pilihan == 3) {
                about();
            }
        }
    }

    endwin();
    return 0;
}               