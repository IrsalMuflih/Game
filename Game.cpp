#include <iostream>
#include <unistd.h>
#include <ncurses.h>

using namespace std;

void loading() {
    clear();

    attron(COLOR_PAIR(2));
    mvprintw(10, 20, "Loading...");
    mvprintw(11, 20, "-----------------");
    mvprintw(13, 20, "-----------------");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(12, 20, "|                 |");
    attroff(COLOR_PAIR(1));

    for (int f = 1; f < 16; f++) {
        attron(COLOR_PAIR(3));
        mvprintw(12, 20 + f, ">");
        attroff(COLOR_PAIR(3));

        refresh();
        usleep(15000); 
    }
}

void runGame() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int ground_y = max_y - 5;
    if (ground_y < 15) ground_y = 15;

    int stickman_x = 10;
    float stickman_y = ground_y - 2;
    float velocity_y = 0;
    float gravity = 0.4;
    bool is_jumping = false;
    bool is_ducking = false;

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
            if (!is_jumping) {
                is_ducking = true;
            }
        } else if (ch == 'q' || ch == 'Q') {
            break;
        } else {
            if (!is_jumping) {
                is_ducking = false;
            }
        }

        if (is_jumping) {
            stickman_y += velocity_y;
            velocity_y += gravity;
            if (stickman_y >= ground_y - 2) {
                stickman_y = ground_y - 2;
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
            } else if (obstacle_type == 1 && !is_ducking)  {
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
        mvprintw(2, max_x - 40, "W/SPACE: Lompat | S: Tunduk | Q: Keluar");
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
    mvprintw(max_y / 2 - 2, max_x / 2 - 6, "GAME OVER!");
    mvprintw(max_y / 2, max_x / 2 - 9, "FINAL SCORE: %d", score);
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(1));
    mvprintw(max_y / 2 + 2, max_x / 2 - 14, "Tekan tombol apa saja untuk kembali...");
    attroff(COLOR_PAIR(1));
    
    refresh();
    getch();
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
    

    int pilihan = 0;
    int tombol;

    while (true) {
        clear();

        attron(COLOR_PAIR(2));
        mvprintw(5, 25, "=== STICKMAN RUNNER GAME ===");
        attroff(COLOR_PAIR(2));

        if (pilihan == 0) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 20, "> Mulai Game");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, 20, "  Mulai Game");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 1) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 38, "> Keluar");
            attroff(COLOR_PAIR(3));
        } else {
            attron(COLOR_PAIR(1));
            mvprintw(12, 38, "  Keluar");
            attroff(COLOR_PAIR(1));
        }

        if (pilihan == 2) {
            attron(COLOR_PAIR(3));
            mvprintw(12, 52, "> About");
            attroff(COLOR_PAIR(3));
        } else {
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

        if (tombol == KEY_LEFT || tombol == 'a' || tombol == 'A') {
            pilihan--;
            if (pilihan < 0)
                pilihan = 2;
        } else if (tombol == KEY_RIGHT || tombol == 'd' || tombol == 'D') {
            pilihan++;
            if (pilihan > 2)
                pilihan = 0;
        } else if (tombol == 10 || tombol == KEY_ENTER || tombol == ' ') {
            if (pilihan == 0) {
                loading();
                runGame();
            }
            else if (pilihan == 1) {
                break;
            }
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
                nodelay(stdscr, FALSE);
                getch();
            }
        }
    }

    endwin();
    return 0;
}
