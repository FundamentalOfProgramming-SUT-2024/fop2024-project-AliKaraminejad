#include<ncurses.h>
#include<stdio.h>
// void menu(){
//     start_color();
//     init_pair(100,COLOR_BLUE,COLOR_BLACK);
//     init_pair(101,COLOR_BLACK,COLOR_BLUE);
//     attron(COLOR_PAIR(100));
//     mvprintw(LINES/2 -1,COLS/2-7,"Start New Game");
//     attroff(COLOR_PAIR(100));
//     attron(COLOR_PAIR(101));
//     mvprintw(LINES/2-2,COLS/2-7,"Continue Privious Game");
//     attroff(COLOR_PAIR(101));
//     curs_set(0);
//     int cnt=0;
//     while(1){
//         int a=getch();
//         clear();
//         if(a == KEY_DOWN && cnt==0){
//             printf("yes\n");
//             break;
//             attron(COLOR_PAIR(101));
//             mvprintw(LINES/2 -1,COLS/2-7,"Start New Game");
//             attroff(COLOR_PAIR(101));
//             attron(COLOR_PAIR(100));
//             mvprintw(LINES/2-2,COLS/2-7,"Continue Privious Game");
//             attroff(COLOR_PAIR(100));
//             cnt++;
//         }
//         else if(a == KEY_UP && cnt==0){
//             attron(COLOR_PAIR(100));
//             mvprintw(LINES/2 -1,COLS/2-7,"Start New Game");
//             attroff(COLOR_PAIR(100));
//             attron(COLOR_PAIR(101));
//             mvprintw(LINES/2-2,COLS/2-7,"Continue Privious Game");
//             attroff(COLOR_PAIR(101));
//             cnt--;
//         }
//         else if(a==10)
//             break;
//     }
// }
// int main(){
//     initscr();
//     menu();
//     refresh();
//     endwin();
//     return 0;
// }
#include <ncurses.h>
#include <stdio.h>

void menu() {
    start_color();
    init_pair(100, COLOR_BLUE, COLOR_BLACK);
    init_pair(101, COLOR_BLACK, COLOR_BLUE);
    
    int cnt = 0;
    while(1) {
        clear();  // Clear the screen at the start of each loop iteration
        if (cnt == 0) {
            attron(COLOR_PAIR(100));
            mvprintw(LINES / 2 - 1, COLS / 2 - 7, "Start New Game");
            attroff(COLOR_PAIR(100));
            attron(COLOR_PAIR(101));
            mvprintw(LINES / 2 - 2, COLS / 2 - 7, "Continue Previous Game");
            attroff(COLOR_PAIR(101));
        } else {
            attron(COLOR_PAIR(101));
            mvprintw(LINES / 2 - 1, COLS / 2 - 7, "Start New Game");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            mvprintw(LINES / 2 - 2, COLS / 2 - 7, "Continue Previous Game");
            attroff(COLOR_PAIR(100));
        }

        refresh();  // Refresh the screen to apply changes
        curs_set(0); // Hide the cursor

        int a = getch(); // Wait for user input
        
        if (a == KEY_DOWN) {
            if (cnt < 1) cnt++;  // Move down to "Continue Previous Game"
        }
        else if (a == KEY_UP) {
            if (cnt > 0) cnt--;  // Move up to "Start New Game"
        }
        else if (a == 10) {  // Enter key to break (select option)
            if (cnt == 0) {
                // Start New Game logic
                break;
            } else if (cnt == 1) {
                // Continue Previous Game logic
                break;
            }
        }
    }
}

int main() {
    initscr();  // Initialize ncurses
    //keypad(stdscr, TRUE);  // Enable special keys like KEY_DOWN and KEY_UP
    //noecho();  // Disable automatic echoing of input
    cbreak();  // Disable line buffering
    menu();  // Display the menu
    endwin();  // End ncurses mode and clean up
    return 0;
}

