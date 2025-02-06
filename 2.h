#include<ncurses.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<locale.h>
// #include"pregame.h"
int m=1;
int difficulty;
int color;
char username[1000], password[1000], email[1000];
char musicer[100];
int donot,playing_music;
void draw_border_4();
void Character_Color(int *al){
    clear();
    start_color();
    init_pair(111,COLOR_BLACK,COLOR_CYAN);
    init_pair(110,COLOR_CYAN,COLOR_BLACK);
    attron(COLOR_PAIR(111));
    mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
    attroff(COLOR_PAIR(111));
    attron(COLOR_PAIR(110));
    draw_border_4();
    mvprintw(LINES/2-2,COLS/2-15,"Green");
    mvprintw(LINES/2-1,COLS/2-15,"Blue");
    mvprintw(LINES/2,COLS/2-15,"Exit");
    int vn=0;
    while(1){
        if(vn==0){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Blue");
            mvprintw(LINES/2,COLS/2-15,"Exit");
        }
        else if(vn==1){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2-1,COLS/2-15,"Blue");
            mvprintw(LINES/2,COLS/2-15,"Exit");
        }
        
        
        else if(vn==2){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-1,COLS/2-15,"Blue");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2,COLS/2-15,"Exit");
        }
        else if(vn==3){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Blue");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
        }
        
        int a=getch();
        if(a==KEY_DOWN && vn<3)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10 && vn==0)
            *al=0;
        else if(a==10 && vn==1)
            *al=1;
        else if(a==10 && vn==2)
            *al=2;
        else if(a==10 && vn==3)
            return;
    }
}
void Difficulty(int *a);
void setting();
void main_page();
void pregame();
void enter();
void new_user_menu();
void which_item(char * r);
void main_page();
void scoreboard();
void music();
void profile();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ncurses.h>
typedef struct {
    char filename[256];
    int score;
    int gold;
    int games_played;
    long int experience;
    char emailer[100];
} FileInfo;
FileInfo * files;
void show_messager(const char *message, int y) {
    int height = 3, width = 60;
    int start_y = y, start_x = COLS / 2 - 30; 
    // getch();
    start_color();
    init_pair(209, COLOR_YELLOW, COLOR_BLACK);

    WINDOW *msg_win = newwin(height, width, start_y, start_x);
    wbkgd(msg_win, COLOR_PAIR(209));  
    wattron(msg_win, COLOR_PAIR(209));

    box(msg_win, 0, 0);
    mvwprintw(msg_win, 1, 1 , "%s", message);
    wattroff(msg_win, COLOR_PAIR(209));

    wrefresh(msg_win); 
}
int compare_scores(const void *a, const void *b) {
    return ((FileInfo *)b)->score - ((FileInfo *)a)->score;
}
int get_scores(const char *directory, FileInfo **files) {
    struct dirent *entry;
    DIR *dp = opendir(directory);
    
    if (dp == NULL) {
        perror("Error opening directory");
        return -1;
    }

    int file_count = 0;
    int capacity = 100;
    char filepath[1024];
    FileInfo *temp_files = malloc(capacity * sizeof(FileInfo));
    
    if (!temp_files) {
        perror("Memory allocation failed");
        closedir(dp);
        return -1;
    }

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    while ((entry = readdir(dp))) {
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

        struct stat file_stat;
        if (stat(filepath, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) { // Check if it's a regular file
            FILE *file = fopen(filepath, "r");

            if (!file) {
                perror("Error opening file");
                continue;
            }

            char line[1024];
            int score = 0, gold = 0, games_played = 0;
            long int exper=0;
            char emailing[100];
            while (fgets(line, sizeof(line), file)) {
                if (strncmp(line, "Score: ", 7) == 0) {
                    score = atoi(line + 7);
                } else if (strncmp(line, "Gold: ", 6) == 0) {
                    gold = atoi(line + 6);
                } else if (strncmp(line, "Game played: ", 13) == 0) {
                    games_played = atoi(line + 13);
                }else if (strncmp(line, "Experience: ", 12) == 0) {
                    exper = atoi(line + 12);
                }
                else if (strncmp(line, "Email: ", 7) == 0) {
                    strcpy(emailing,line+7);
                }
            }
            fclose(file);

            // Expand array if needed
            if (file_count >= capacity) {
                capacity *= 2;
                FileInfo *new_files = realloc(temp_files, capacity * sizeof(FileInfo));
                if (!new_files) {
                    perror("Memory reallocation failed");
                    free(temp_files);
                    closedir(dp);
                    return -1;
                }
                temp_files = new_files;
            }

            // Store file information
            strncpy(temp_files[file_count].filename, entry->d_name, sizeof(temp_files[file_count].filename) );
            temp_files[file_count].filename[sizeof(temp_files[file_count].filename) - 1] = '\0';
            temp_files[file_count].score = score;
            temp_files[file_count].gold = gold;
            temp_files[file_count].games_played = games_played;
            temp_files[file_count].experience=(time(NULL)-exper)/(24*3600);
            strcpy(temp_files[file_count].emailer,emailing);
            file_count++;
        }
    }

    closedir(dp);

    *files = temp_files;
    return file_count;
}
void sort_scores(FileInfo *files, int count) {
    qsort(files, count, sizeof(FileInfo), compare_scores);
}
void display_scores_ncurses(FileInfo *files, int count) {
    setlocale(LC_ALL, ""); 
    initscr();            
    noecho();             
    curs_set(0);          
    keypad(stdscr, TRUE); 
    start_color();
    clear();
    cbreak();
    keypad(stdscr, TRUE);
    mvprintw(LINES/2-3,COLS/2-15,"Press any key to see the scoreboard");
    getch();
    init_pair(212, COLOR_RED, COLOR_BLACK);
    init_pair(213, COLOR_CYAN, COLOR_BLACK);
    init_pair(214, COLOR_BLUE, COLOR_BLACK);
    init_pair(209, COLOR_YELLOW, COLOR_BLACK);
    for(int i=0;i<count;i++){
        files[i].filename[strlen(files[i].filename)-4]='\0';
    }
    int height = 1000, width = 80;
    int start_y = 0, start_x = COLS / 2 - 40;

    WINDOW *msg_win = newwin(height, width, start_y, start_x);
    scrollok(msg_win, TRUE);
    wbkgd(msg_win, COLOR_PAIR(209));
    wattron(msg_win,COLOR_PAIR(209));
    mvwprintw(msg_win,1,1,"Username         ||   Score    ||    Gold   ||   Game_played   ||    days");
    for(int u=1;u<79;u++)
        mvwprintw(msg_win,2,u,"=");
    for(int u=3;u<50;u+=2){
        mvwprintw(msg_win,u,18,"||");
        mvwprintw(msg_win,u,32,"||");
        mvwprintw(msg_win,u,46,"||");
        mvwprintw(msg_win,u,64,"||");
    }
    mvprintw(20,5,"press 'q' to exit");
    wattroff(msg_win,COLOR_PAIR(209));
    box(msg_win, 0, 0);
    wrefresh(msg_win);
    int row=4;
    for(int j=0;j<3;j++){
        
        wattron(msg_win,A_BLINK);
        if(j==0)
            wattron(msg_win, COLOR_PAIR(212));
        else if(j==1)
            wattron(msg_win, COLOR_PAIR(214));
        else if(j==2)
            wattron(msg_win, COLOR_PAIR(213));
        mvwprintw(msg_win, row, 1, "%d:        %s           %d           %d            %d            %ld",j+1,files[j].filename , files[j].score,files[j].gold,files[j].games_played,files[j].experience);
        if(strcmp(username,files[j].filename)==0){
            mvwprintw(msg_win,row,3,"->");
        }
        if(j==0){
            // mvprintw(2,2,"🥇");
            mvwprintw(msg_win,row,5,"(ZEOS)");
        }    
        else if(j==1){
            // mvwprintw(msg_win,row,1,"🥈");
            mvwprintw(msg_win,row,5,"(GOAT)");
        }    
        else if(j==2){
            // mvwprintw(msg_win,row,1,"🥉");
            mvwprintw(msg_win,row,5,"(KING)");
        }    
        wattroff(msg_win, COLOR_PAIR(212));
        wattroff(msg_win, COLOR_PAIR(214));
        wattroff(msg_win, COLOR_PAIR(213));
        wattroff(msg_win,A_BLINK);
        row+=2;
    }
    for (int i = 3; i < count; i++) {
        init_pair(123,COLOR_MAGENTA,COLOR_BLACK);
        wattron(msg_win,COLOR_PAIR(209));
        mvwprintw(msg_win, row, 1, "%d:  %s%20d%15d%15d%15ld",i+1,files[i].filename , files[i].score,files[i].gold,files[i].games_played,files[i].experience);
        if(strcmp(username,files[i].filename)==0){
            mvwprintw(msg_win,row,3,"->");
        }
        wattroff(msg_win,COLOR_PAIR(209));
        row+=2;
    }

    wrefresh(msg_win);

    int ch;
    int min=50-row,max=50;
    while ((ch = getch()) != 'q') {
        if (ch == KEY_UP) {
            // if(min>0){
                wscrl(msg_win, -1);
                max--;
                min--;
            // }    
        } else if (ch == KEY_DOWN) {
            if(max<50){
                wscrl(msg_win, 1);
                max++;
                min++;
            }
        }
        wrefresh(msg_win);
    }

    delwin(msg_win);
    endwin();
}
void free_scores(FileInfo *files) {
    free(files);
}
void draw_border_4(){
    for(int i=0;i<LINES;i++){
        mvprintw(i,0,"#");
        mvprintw(i,COLS-1,"#");
    }
    for(int i=0;i<COLS;i++){
        mvprintw(0,i,"#");
        mvprintw(LINES-1,i,"#");
    }
}
void pregame(){
    start_color();
    init_pair(100,COLOR_BLUE,COLOR_BLACK);
    init_pair(101,COLOR_BLACK,COLOR_BLUE);
    attron(COLOR_PAIR(101));
    draw_border_4();
    mvprintw(LINES/2 -3,COLS/2-15,"Start New Game");
    attroff(COLOR_PAIR(101));
    attron(COLOR_PAIR(100));
    mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
    mvprintw(LINES/2-1,COLS/2-15,"Setting");
    mvprintw(LINES/2,COLS/2-15,"Scoreboard");
    mvprintw(LINES/2+1,COLS/2-15,"Exit");
    attroff(COLOR_PAIR(100));
    curs_set(0);
    int vn=0;
    while(1){
        clear();
        if(vn==0){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2 -3,COLS/2-15,"Start New Game");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
            mvprintw(LINES/2-1,COLS/2-15,"Setting");
            mvprintw(LINES/2,COLS/2-15,"Scoreboard");
            mvprintw(LINES/2+1,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(100));
        }
        else if(vn==1){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            draw_border_4();
            mvprintw(LINES/2-3,COLS/2-15,"Start New Game");
            mvprintw(LINES/2-1,COLS/2-15,"Setting");
            mvprintw(LINES/2,COLS/2-15,"Scoreboard");
            mvprintw(LINES/2+1,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(100));
            
        }
        else if(vn==2){
            attron(COLOR_PAIR(101));
            mvprintw(LINES/2-1,COLS/2-15,"Setting");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
            mvprintw(LINES/2-3,COLS/2-15,"Start New Game");
            mvprintw(LINES/2,COLS/2-15,"Scoreboard");
            mvprintw(LINES/2+1,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(100));
            
        }
        else if(vn==3){
             attron(COLOR_PAIR(101));
            mvprintw(LINES/2,COLS/2-15,"Scoreboard");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
            mvprintw(LINES/2-1,COLS/2-15,"Setting");
            mvprintw(LINES/2-3,COLS/2-15,"Start New Game");
            mvprintw(LINES/2+1,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(100));
            
        }
        else if(vn==4){
             attron(COLOR_PAIR(101));
            mvprintw(LINES/2+1,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(101));
            attron(COLOR_PAIR(100));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Continue Privious Game");
            mvprintw(LINES/2-1,COLS/2-15,"Setting");
            mvprintw(LINES/2,COLS/2-15,"Scoreboard");
            mvprintw(LINES/2-3,COLS/2-15,"Start New Game");
            attroff(COLOR_PAIR(100));
            
        }
        int a=getch();
        if(a==KEY_DOWN && vn<4)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10){
            if(vn==0){
                m=0;
                return;
            }
            // else if(vn==1)
            //     Character_Color();
            // else if(vn==2)
            //     Music();
            if(vn==2)
                setting();
            else if(vn==3)
                scoreboard();
            else if(vn==4)
                return;
        }   
    }    
}
void profile(){
    const char * directory="player_data";
    int count=get_scores(directory,&files);
    init_pair(32,COLOR_RED,COLOR_BLACK);
    int i;
    for(int j=0;j<count;j++){
        files[j].filename[strlen(files[j].filename)-4]='\0';
    }
    for(i=0;i<count;i++){
        if(strcmp(username,files[i].filename)==0){
            break;
        }           // break;
    }
    // 
    clear();
    attron(COLOR_PAIR(32));
    draw_border_4();
    // mvprintw(2,2,"%d",i);
    mvprintw(LINES/2-4,COLS/2-15,"username: %s",username);
    mvprintw(LINES/2-3,COLS/2-15,"password: %s",password);
    mvprintw(LINES/2-2,COLS/2-15,"Email: %s",files[i].emailer);
    mvprintw(LINES/2-1,COLS/2-15,"Gold: %d",files[i].gold);
    mvprintw(LINES/2,COLS/2-15,"Score: %d",files[i].score);
    mvprintw(LINES/2+1,COLS/2-15,"Game_played: %d",files[i].games_played);
    mvprintw(LINES/2+2,COLS/2-15,"experience: %ld (days)",files[i].experience);
    refresh();
    if(getch()=='q')
        return;
}
void setting(){
    int vn=0;
    start_color();
    init_pair(102,COLOR_YELLOW,COLOR_BLACK);
    init_pair(103,COLOR_BLACK,COLOR_YELLOW);
    attron(COLOR_PAIR(103));
    mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
    attroff(COLOR_PAIR(103));
    attron(COLOR_PAIR(102));
    mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
    mvprintw(LINES/2-3,COLS/2-18,"Music");
    mvprintw(LINES/2-2,COLS/2-18,"Exit");
    mvprintw(LINES/2-1,COLS/2-18,"Profile");
    attroff(COLOR_PAIR(102));
    refresh();
    while(1){
        
        clear();
        if(vn==0){
            attron(COLOR_PAIR(103));
            mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
            attroff(COLOR_PAIR(103));
            attron(COLOR_PAIR(102));
            draw_border_4();
            mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
            mvprintw(LINES/2-3,COLS/2-18,"Music");
            mvprintw(LINES/2-2,COLS/2-18,"Exit");
            mvprintw(LINES/2-1,COLS/2-18,"Profile");
            attroff(COLOR_PAIR(102));
            
        }
        else if(vn==1){
            attron(COLOR_PAIR(103));
            mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
            attroff(COLOR_PAIR(103));
            attron(COLOR_PAIR(102));
            draw_border_4();
            mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
            mvprintw(LINES/2-3,COLS/2-18,"Music");
            mvprintw(LINES/2-2,COLS/2-18,"Exit");
            mvprintw(LINES/2-1,COLS/2-18,"Profile");
            attroff(COLOR_PAIR(102));
        }
        else if(vn==2){
            attron(COLOR_PAIR(103));
            mvprintw(LINES/2-3,COLS/2-18,"Music");
            attroff(COLOR_PAIR(103));
            attron(COLOR_PAIR(102));
            draw_border_4();
            mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
            mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
            mvprintw(LINES/2-2,COLS/2-18,"Exit");
            mvprintw(LINES/2-1,COLS/2-18,"Profile");
            attroff(COLOR_PAIR(102));
        }
        else if(vn==3){
            attron(COLOR_PAIR(103));
            mvprintw(LINES/2-2,COLS/2-18,"Exit");
            attroff(COLOR_PAIR(103));
            attron(COLOR_PAIR(102));
            draw_border_4();
            mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
            mvprintw(LINES/2-3,COLS/2-18,"Music");
            mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
            mvprintw(LINES/2-1,COLS/2-18,"Profile");
            attroff(COLOR_PAIR(102));
        }
        else if(vn==4){
            attron(COLOR_PAIR(103));
            mvprintw(LINES/2-1,COLS/2-18,"Profile");
            attroff(COLOR_PAIR(103));
            attron(COLOR_PAIR(102));
            draw_border_4();
            mvprintw(LINES/2-5,COLS/2-18,"Difficulty");
            mvprintw(LINES/2-3,COLS/2-18,"Music");
            mvprintw(LINES/2-4,COLS/2-18,"Color Of Main Character");
            mvprintw(LINES/2-2,COLS/2-18,"Exit");
            attroff(COLOR_PAIR(102));
        }
        int a=getch();
        if(a==KEY_DOWN && vn<4)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10){
            if(vn==0)
               Difficulty(&difficulty);
            else if(vn==1)
                 Character_Color(&color);
            else if(vn==2)
                music();
            else if(vn==3)
                return;
            else if(vn==4)  
                profile();

        }   
        
       
    }
}
void Difficulty(int *m){
    start_color();
    init_pair(109,COLOR_BLACK,COLOR_RED);
    init_pair(108,COLOR_RED,COLOR_BLACK);
    attron(COLOR_PAIR(109));
    mvprintw(LINES/2-3,COLS/2-15,"easy");
    attroff(COLOR_PAIR(109));
    attron(COLOR_PAIR(108));
    mvprintw(LINES/2-2,COLS/2-15,"average");
    mvprintw(LINES/2-1,COLS/2-15,"hard");
    mvprintw(LINES/2,COLS/2-15,"Exit");
    attroff(COLOR_PAIR(108));
    int vn=0;
    while(1){
        clear();
        if(vn==0){
        attron(COLOR_PAIR(109));
        mvprintw(LINES/2-3,COLS/2-15,"easy");
        attroff(COLOR_PAIR(109));
        attron(COLOR_PAIR(108));
        draw_border_4();
        mvprintw(LINES/2-2,COLS/2-15,"average");
        mvprintw(LINES/2-1,COLS/2-15,"hard");
        mvprintw(LINES/2,COLS/2-15,"Exit");
        attron(COLOR_PAIR(108));        
        }
        if(vn==1){
            attron(COLOR_PAIR(109));
            mvprintw(LINES/2-2,COLS/2-15,"average");
            attroff(COLOR_PAIR(109));
            attron(COLOR_PAIR(108));
            draw_border_4();
            mvprintw(LINES/2-3,COLS/2-15,"easy");
            mvprintw(LINES/2-1,COLS/2-15,"hard");
            mvprintw(LINES/2,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(108));
        }
        else if(vn==2){
            attron(COLOR_PAIR(109));
            mvprintw(LINES/2-1,COLS/2-15,"hard");
            attroff(COLOR_PAIR(109));
            attron(COLOR_PAIR(108));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"average");
            mvprintw(LINES/2-3,COLS/2-15,"easy");
            mvprintw(LINES/2,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(108));    
        }
        else if(vn==3){
            attron(COLOR_PAIR(109));
            mvprintw(LINES/2,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(109));
            attron(COLOR_PAIR(108));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"average");
            mvprintw(LINES/2-3,COLS/2-15,"easy");
            mvprintw(LINES/2-1,COLS/2-15,"hard");
            attroff(COLOR_PAIR(108));    
        }
        int a=getch();
        if(a==KEY_DOWN && vn<3)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10 ){
            if(vn==3)
                return;
            else {
                *m=(vn+1);
            }        
        }    
    }
}
void scoreboard(){
    const char * directory="player_data";
    int count=get_scores(directory,&files);
            // if(count>0){
    sort_scores(files,count);
    display_scores_ncurses(files,count);
    free_scores(files);
}
void draw_border() {
    for (int i = 0; i < LINES; i++) {
        mvprintw(i, 0, "*");
        mvprintw(i, COLS - 1, "*");
    }
    for (int i = 0; i < COLS; i++) {
        mvprintw(0, i, "*");
        mvprintw(LINES - 1, i, "*");
    }
}
void draw_border_2() {
    for (int i = 0; i < LINES; i++) {
        mvprintw(i, 0, "!");
        mvprintw(i, COLS - 1, "!");
    }
    for (int i = 0; i < COLS; i++) {
        mvprintw(0, i, "!");
        mvprintw(LINES - 1, i, "!");
    }
}
void draw_border_3(){
     for (int i = 0; i < LINES; i++) {
        mvprintw(i, 0, "0");
        mvprintw(i, COLS - 1, "0");
    }
    for (int i = 0; i < COLS; i++) {
        mvprintw(0, i, "0");
        mvprintw(LINES - 1, i, "0");
    }
}
int check_password(const char *username, const char *entered_password) {
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);
    FILE *file = fopen(filepath, "r");
    char line[1024];
    char stored_password[1000];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Password: ", 10) == 0) {
            strcpy(stored_password, line + 10); 
            stored_password[strcspn(stored_password, "\n")] = '\0';
            break;
        }
    }
    fclose(file);
    if (strcmp(stored_password, entered_password) == 0) {
        return 1; 
    }
    return 0; 
}
int check_username(char * username){
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);
    FILE* file=fopen(filepath,"r");
    if(file){
        return 1;
        fclose(file);
    }    
    return 0;
}
void save_info(char *username, char *password, char *email) {
    FILE *file;
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);
    file = fopen(filepath, "w");
    fprintf(file, "Username: %s\n", username);
    fprintf(file, "Password: %s\n", password);
    fprintf(file, "Email: %s\n", email);
    fprintf(file,"Gold: %d\n",0);
    fprintf(file,"Game played: %d\n",0);
    fprintf(file,"Score: %d\n",0);
    fprintf(file,"Experience: %ld\n",time(NULL));
    fclose(file);
}
void forgot_password(char * username){
    clear();
    echo();
    char temps[100];
    mvprintw(LINES/2-3,COLS/2-15,"Enter you Email address: ");
    getstr(temps);
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);
    FILE *file = fopen(filepath, "r");
    char line[1024];
    char stored_email[1000];
    char stored_password[100];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Email: ", 7) == 0) {
            strcpy(stored_email, line + 7);
            stored_email[strcspn(stored_email, "\n")] = '\0';  // Remove newline
        }
        if (strncmp(line, "Password: ", 10) == 0) {
            strcpy(stored_password, line + 10);
            stored_password[strcspn(stored_password, "\n")] = '\0';  // Remove newline
        }
    }
    if(strcmp(stored_email,temps)!=0) {
        clear();
        fclose(file);
        mvprintw(LINES/2-3,COLS/2-15,"your email is wrong");
        napms(2000);
        return;
    }
    fclose(file);
    clear();
    init_pair(210,COLOR_RED,COLOR_BLACK);
    attron (COLOR_PAIR(210));
    mvprintw(LINES/2-3,COLS/2-18,"<%s>",stored_password);
    attroff (COLOR_PAIR(210));
    mvprintw(LINES/2-3,COLS/2-8,"is your password(press 'q' to exit)");
    if(getch()=='q')
        return;
}
void enter() {
    // char username[1000], password[1000];
    start_color();
    init_pair(106, COLOR_GREEN, COLOR_BLACK);
    init_pair(107, COLOR_BLACK, COLOR_GREEN);
    init_pair(108, COLOR_RED, COLOR_BLACK); 
    int step=0;
    while (1) {
        clear();
        if(step==0){
            draw_border();
            attron(COLOR_PAIR(106));
            mvprintw(LINES / 2 - 4, COLS / 2 - 16, "Username: ");
            attroff(COLOR_PAIR(106));
            refresh();
            getstr(username);
            if(username[0]==27)
                return;
            if (!check_username(username)) {
                clear();
                attron(COLOR_PAIR(108));
                draw_border_2();
                mvprintw(LINES / 2, COLS / 2 - 25, "There is no username as this!");
                attroff(COLOR_PAIR(108));
                refresh();
                napms(4000);
                continue; 
            }
            step ++;
        }  

        else if(step==1){
            draw_border_2();
            attron(COLOR_PAIR(107));
            mvprintw(LINES / 2 - 3, COLS / 2 - 16, "Password: ");
            attroff(COLOR_PAIR(107));
            mvprintw(LINES/2-1,COLS/2-16,"forgot password(press @)");
            noecho();
            getstr(password);
            echo();
            if(password[0]==27){
                step--;
                continue;
            } 
            else if(password[0]=='@'){
                forgot_password(username);
                continue;
            }   
            if (!check_password(username, password)) {
                clear();
                attron(COLOR_PAIR(108));
                draw_border_2();
                mvprintw(LINES / 2, COLS / 2 - 25, "The entered password is wrong!");
                attroff(COLOR_PAIR(108));
                refresh();
                napms(2000);
                continue;    
            }
            pregame();
            if(!m)
                return;
        }    
        
    }
}
void generating_random_password() {
    srand(time(NULL));
    
    char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char digits[] = "0123456789";
    char temps[11];  
    
    int l = 0, u = 0, d = 0;  

    for (int i = 0; i < 10; i++) {
        int h = rand() % 3;  
        int g = rand() % 26; 
        int digi = rand() % 10; 

        if (h == 0) {  
            temps[i] = lowercase[g];
            l = 1;
        } else if (h == 1) {  
            temps[i] = uppercase[g];
            u = 1;
        } else {  
            temps[i] = digits[digi];
            d = 1;
        }

        if (i == 9 && (!l || !u || !d)) {
            i--;  
        }
    }

    temps[10] = '\0';  
    strcpy(password, temps);

    clear();
    init_pair(209,COLOR_RED,COLOR_BLACK);
    attron(COLOR_PAIR(209));
    mvprintw(LINES / 2 - 3, COLS / 2 - 18, "%s", temps);
    attroff(COLOR_PAIR(209));
    mvprintw(LINES/2-3,COLS/2-8," is your password (press 'q' to exit)");
    refresh();

    if (getch() == 'q') {
        clear();
        return;
    }
}

void new_user_menu() {
    int step = 0; 
    draw_border();
    start_color();
    init_pair(102, COLOR_BLUE, COLOR_BLACK);
    init_pair(103, COLOR_BLACK, COLOR_RED);
    init_pair(104, COLOR_GREEN, COLOR_BLACK);
    init_pair(105, COLOR_BLACK, COLOR_YELLOW);

    while (1) {
        clear();
        refresh();
        draw_border();
        if (step == 0) {
            attron(COLOR_PAIR(102));
            mvprintw(LINES / 2 - 15, COLS / 2 - 40, "Enter your username (Press ESC to back to previous page): ");
            attroff(COLOR_PAIR(102));
            attron(COLOR_PAIR(104));
            getstr(username);
            attroff(COLOR_PAIR(104));

            if ( username[0] == 27) { 
                return; 
            }

            if (check_username(username)) {
                clear();
                attron(COLOR_PAIR(103));
                mvprintw(LINES / 2, COLS / 2 - 18, "Your username has been used!");
                mvprintw(LINES / 2 + 1, COLS / 2 - 21, "Choose another username for yourself");
                attroff(COLOR_PAIR(103));
                refresh();
                napms(3000);
                continue;
            }
            step++;
        }

        else if (step == 1) { 
            attron(COLOR_PAIR(102));
            mvprintw(LINES / 2 - 5, COLS / 2 - 23, "Enter your password (Press ESC to go back): ");
            mvprintw(LINES / 2 - 4, COLS / 2 - 23, "Generating random password(press @)");
            attroff(COLOR_PAIR(102));
            attron(COLOR_PAIR(104));
            getstr(password);
            attroff(COLOR_PAIR(104));
            if(password[0]=='@'){
                // clear();
                // mvprintw(2,2,"salam");
                // refresh();
                // napms(2000);
                generating_random_password();
                step++;
                continue;
            }
            else if ( password[0] == 27) {
                step--; 
                continue;
            }

            int has_upper = 0, has_lower = 0, has_digit = 0;
            for (int i = 0; i < strlen(password); i++) {
                if (password[i] >= 'A' && password[i] <= 'Z')
                     has_upper = 1;
                else if (password[i] >= 'a' && password[i] <= 'z') 
                    has_lower = 1;
                else if (password[i] >= '0' && password[i] <= '9') 
                    has_digit = 1;
            }

            if (!has_upper || !has_lower || !has_digit || strlen(password) < 7) {
                clear();
                attron(COLOR_PAIR(103));
                mvprintw(LINES / 2 - 1, COLS / 2 - 12, "Invalid password!");
                mvprintw(LINES / 2, COLS / 2 - 40, "Password must include uppercase, lowercase, and a number, with at least 7 characters.");
                attroff(COLOR_PAIR(103));
                refresh();
                napms(3000);
                step--;
                continue;
            }
            step++; 
        }

        else if (step == 2) { 
            attron(COLOR_PAIR(102));
            mvprintw(LINES / 2 + 5, COLS / 2 - 6, "Enter your email address (Press ESC to go back): ");
            attroff(COLOR_PAIR(102));
            attron(COLOR_PAIR(104));
            getstr(email);
            attroff(COLOR_PAIR(104));

            if ( email[0] == 27) { 
                step--;
                continue;
            }

            int at_index = -1, dot_index = -1;
            for (int i = 0; i < strlen(email); i++) {
                if (email[i] == '@') 
                    at_index = i;
                else if (email[i] == '.') 
                    dot_index = i;
            }

            if (at_index == -1 || dot_index == -1 || dot_index <= at_index || dot_index == at_index + 1 || at_index == 0 || dot_index == strlen(email) - 1) {
                clear();
                attron(COLOR_PAIR(103));
                mvprintw(LINES / 2, COLS / 2 - 22, "Please enter a correct email address!");
                attroff(COLOR_PAIR(103));
                refresh();
                napms(3000);
                step-=2;
                continue;
            }
            break;
        }
    }

    save_info(username, password, email);
    curs_set(0);
    clear();
    attron(COLOR_PAIR(104));
    mvprintw(LINES/2-4,COLS/2-15,"You successfully signed up in!");
    attroff(COLOR_PAIR(104));
    refresh();
    napms(3000);
}
void which_item(char *r){
    if(strcmp(r,"Sign Up")==0)
        new_user_menu();
    else if(strcmp(r,"Log In")==0)
        enter();
    if(strcmp(r,"guest")==0)
        pregame();

}
void main_page(){
    curs_set(0);
    if(!m)
        return;
    start_color();
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    //noecho();
    char gozine[4][100]={{"Sign Up"},{"Log In"},{"Exit"},{"guest"}};
    int n_items = 4;
    int choice = 0;
    int ch;
    while (1) {
        clear();
        attron(COLOR_PAIR(104));
        draw_border_3();
        attroff(COLOR_PAIR(104));
        attron(COLOR_PAIR(1));
        attron(A_BOLD);
        mvprintw(LINES/2-4,COLS/2-13,"Welcome To My Game!");
        attroff(COLOR_PAIR(1));
        attroff(A_BOLD);
        refresh();
        for (int i = 0; i < n_items; i++) {
            init_pair(2,COLOR_MAGENTA,COLOR_BLACK);
            attron(COLOR_PAIR(2));
            if (i == choice) 
                attron(A_REVERSE);
            mvprintw(LINES/2+i, COLS/2-10, "%s", gozine[i]);
            if (i == choice) 
                attroff(A_REVERSE);
            attroff(COLOR_PAIR(2));
        }
        ch = getch();
        if (ch == KEY_UP && choice > 0) choice--;
        else if (ch == KEY_DOWN && choice < n_items - 1) choice++;
        else if (ch == 10) {
            if (choice == 2) {
                break;
            } else {
                clear();
                which_item(gozine[choice]);
                if(!m)
                    return;
            }
        }
    }
    curs_set(0);
}
void music(){
    int vn=0;
    curs_set(0);
    keypad(stdscr, TRUE);
    
    start_color();
    init_pair(102, COLOR_RED, COLOR_BLACK);
    init_pair(103, COLOR_BLACK, COLOR_RED);
    init_pair(104, COLOR_GREEN, COLOR_BLACK);

    while(1){
        clear();  
        attron(COLOR_PAIR(102));
        draw_border_4();
        attron(A_BOLD);
        mvprintw(LINES/2-6, COLS/2-15, "Arbab_e_vafa");
        mvprintw(LINES/2-5, COLS/2-15, "Mama");
        mvprintw(LINES/2-4, COLS/2-15, "Pink Soldiers");
        mvprintw(LINES/2-3, COLS/2-15, "No music");
        attroff(COLOR_PAIR(102));
        attron(COLOR_PAIR(103));
        if(vn == 0) mvprintw(LINES/2-6, COLS/2-15, "Arbab_e_vafa");
        if(vn == 1) mvprintw(LINES/2-5, COLS/2-15, "Mama");
        if(vn == 2) mvprintw(LINES/2-4, COLS/2-15, "Pink Soldiers");
        if(vn == 3) mvprintw(LINES/2-3, COLS/2-15, "No music");
        attroff(COLOR_PAIR(103));
        attroff(A_BOLD);

        refresh();

        int a = getch();
        if(a == KEY_DOWN && vn < 3) vn++;
        else if(a == KEY_UP && vn > 0) vn--;
        else if(a == 10) {
            switch(vn){
                case 0:
                    strcpy(musicer,"02 Arbabe Vafa.mp3");
                    playing_music=1;
                    donot=0;
                    return;
                    break;
                case 1:
                    strcpy(musicer,"queen_bohemian-rhapsody.mp3");
                    playing_music=1;
                    donot=0;
                    return;
                    break;
                case 2:
                    strcpy(musicer,"squid_game_04 - Pink Soldiers.mp3");
                    playing_music=1;
                    donot=0;
                    return;
                    break;
                case 3:
                    donot=1;
                    return;
                    break;
            }
        }
    }    
}
// int main(){
//     initscr();
//     keypad(stdscr,true);
//     cbreak();
//     main_page();
//     //new_user_menu();
//     //enter();
//     refresh();
//     endwin();
//     return 0;
// }
