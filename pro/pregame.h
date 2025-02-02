#include<ncurses.h>
#include<stdio.h>
#include<string.h>
int a;
void draw_border_4();
char Character_Color(){
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
    mvprintw(LINES/2-1,COLS/2-15,"Cyan");
    mvprintw(LINES/2,COLS/2-15,"White");
    mvprintw(LINES/2+1,COLS/2-15,"Blue");
    mvprintw(LINES/2+2,COLS/2-15,"Exit");
    int vn=0;
    while(1){
        if(vn==0){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            mvprintw(LINES/2,COLS/2-15,"White");
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
        }
        else if(vn==1){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            mvprintw(LINES/2,COLS/2-15,"White");
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
        }
        else if(vn==2){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2,COLS/2-15,"White");
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
        }
        else if(vn==3){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2,COLS/2-15,"White");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
        }
        else if(vn==4){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            mvprintw(LINES/2,COLS/2-15,"White");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
        }
        else if(vn==5){
            attron(COLOR_PAIR(111));
            mvprintw(LINES/2+2,COLS/2-15,"Exit");
            attroff(COLOR_PAIR(111));
            attron(COLOR_PAIR(110));
            draw_border_4();
            mvprintw(LINES/2-2,COLS/2-15,"Green");
            mvprintw(LINES/2-1,COLS/2-15,"Cyan");
            mvprintw(LINES/2,COLS/2-15,"White");
            mvprintw(LINES/2+1,COLS/2-15,"Blue");
            mvprintw(LINES/2-3,COLS/2-15,"Red(default)");
        }
        
        int a=getch();
        if(a==KEY_DOWN && vn<5)
            vn++;
        else if(a==KEY_UP && vn>0)
            vn--;
        else if(a==10 && vn==0)
            return 'r';
        else if(a==10 && vn==1)
            return 'g';
        else if(a==10 && vn==2)
            return 'c';
        else if(a==10 && vn==3)
            return 'w';
        else if(a==10 && vn==4)
            return 'b';
        else if(a==10 && vn==5)
            return 0;
    }
    }
void Difficulty(int *a);
void setting();
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
            // if(vn==0)
            //     Difficulty();
            // else if(vn==1)
            //     Character_Color();
            // else if(vn==2)
            //     Music();
            if(vn==2)
                setting();
            if(vn==3)
                // scoreboard();
            if(vn==4)
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
               Difficulty(&a);
            else if(vn==1)
                 Character_Color();
            // else if(vn==2)
            //     Music();
            else if(vn==3)
                return;
        }   
        
       
    }
}
void Difficulty(int *a){
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
                a=(vn+1);
            }        
        }    
    }
}
void scoreboard(){

}