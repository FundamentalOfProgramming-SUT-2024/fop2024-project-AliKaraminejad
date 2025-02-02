#include<ncurses.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
// #include"pregame.h"
int m=1;
int difficulty;
int color;
char username[1000], password[1000], email[1000];
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
            // else if(vn==3)
                // scoreboard();
            else if(vn==4)
                return;
        }   
    }    
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
            attroff(COLOR_PAIR(102));
        }
        int a=getch();
        if(a==KEY_DOWN && vn<3)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10){
            if(vn==0)
               Difficulty(&difficulty);
            else if(vn==1)
                 Character_Color(&color);
            // else if(vn==2)
            //     Music();
            else if(vn==3)
                return;
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
void scoreboard(){}
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
    fclose(file);
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
            noecho();
            getstr(password);
            echo();
            if(password[0]==27){
                step--;
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
            attroff(COLOR_PAIR(102));
            attron(COLOR_PAIR(104));
            getstr(password);
            attroff(COLOR_PAIR(104));

            if ( password[0] == 27) {
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

}
void main_page(){
    if(!m)
        return;
    start_color();
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    //noecho();
    char gozine[3][100]={{"Sign Up"},{"Log In"},{"Exit"}};
    int n_items = 3;
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
