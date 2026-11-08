#include <iostream>
#include <ncurses.h>

using namespace std;

void loading() {
    clear();

    // LOADING
    attron(COLOR_PAIR(2));
    mvprintw(10, 20, "Loading...");
    mvprintw(11, 20, "-----------------");
    mvprintw(13, 20, "------------------");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(12, 20, "|               |");
    attroff(COLOR_PAIR(1));

    for (int f = 1; f < 16; f++) {
        attron(COLOR_PAIR(3));
        mvprintw(12, 20 + f, ">");
        attroff(COLOR_PAIR(3));

        refresh();
        napms(250);
    }
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
    clear();

    int dino_x = 5;
    int dino_y = ground_y - 3;
    int old_dino_y = dino_y;

    int ground_y = max_y - 2;

    loading();

    int pilihan = 0;
    int tombol;

    // MENU UTAMA
    while (true) {
        clear();

        attron(COLOR_PAIR(2));
        mvprintw(5, 25, "=== Selamat datang di Game ===");
        attroff(COLOR_PAIR(2));

        if (pilihan == 0) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 20, "> Mulai Game");
            attroff(COLOR_PAIR(3));
        }
        else {
            attron(COLOR_PAIR(1));
            mvprintw(12, 20, "  Mulai Game");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 1) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 38, "> Keluar");
            attroff(COLOR_PAIR(3));
        }
        else {
            attron(COLOR_PAIR(1));
            mvprintw(12, 38, "  Keluar");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 2) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 52, "> About");
            attroff(COLOR_PAIR(3));
        }
        else {
            attron(COLOR_PAIR(1));
            mvprintw(12, 52, "  About");
            attroff(COLOR_PAIR(1));
        }

        attron(COLOR_PAIR(4));
        mvprintw(15, 20, "Created by:");
        mvprintw(16, 20, "Raihan Belvananda Zuhair * Irsal Muflih * Nur Kholifah * Anisa Setiyawati");
        attroff(COLOR_PAIR(4));

        refresh();

        tombol = getch();

        if (tombol == KEY_LEFT) {
            pilihan--;

            if (pilihan < 0)
                pilihan = 2;
        }

        else if (tombol == KEY_RIGHT) {
            pilihan++;

            if (pilihan > 2)
                pilihan = 0;
        }

        else if (tombol == 10 || tombol == KEY_ENTER) {

            // MULAI GAME
            if (pilihan == 0) {
                loading();
                clear();

                mvprintw(dino_y, dino_x, "  \\0/  ");
                mvprintw(dino_y + 1, dino_x, "   |   ");
                mvprintw(dino_y + 2, dino_x, "  / \\  ");

                for (int i = 0; i < max_x; i++) {
                mvaddch(ground_y, i, '-');
                }

                refresh();
                getch();
            }

            // KELUAR
            else if (pilihan == 1) {
                break;
            }

            // ABOUT
             else if (pilihan == 2) {
                clear();
                attron(COLOR_PAIR(2));
                mvprintw(5, 20, "Game ini dibuat untuk memenuhi tugas mata kuliah Dasar Pemrograman & Algoritma.");
                attroff(COLOR_PAIR(2));

                attron(COLOR_PAIR(4));
                mvprintw(6, 20, "Dibuat oleh kelompok kami yang beranggotakan:");

                mvprintw(8, 20, "Raihan Belvananda Zuhair : NPM (2657052002)");
                mvprintw(9, 20, "Irsal Muflih             : NPM (2617052056)");
                mvprintw(10, 20, "Nur Kholifah             : NPM (2657052001)");
                mvprintw(11, 20, "Anisa Setiyawati         : NPM (2617052037)");

                mvprintw(13, 20, "Tekan tombol apa saja untuk kembali.");
                attroff(COLOR_PAIR(4));

                refresh();
                getch();
            }
        }
    }

    endwin();

    return 0;
}
