#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <dirent.h>
// #include"pregame.h" 
#include "2.h"
#define MAP_WIDTH 150
#define MAP_HEIGHT 40
#define MAX_ROOMS 10
#define ROOM_MIN_SIZE 7
#define ROOM_MAX_SIZE 50
// typedef struct {
//     char filename[1024];
//     int score;
// } FileInfo;
typedef struct {
    int x, y;
} d;
typedef struct{
    int x;
    int y;
    int points;
}golden;
typedef struct {
    int x, y, width, height;
    int door_count;
    int doors[4][2];
    int encryped_door_condition;
    int is_there_encryped_door;
    d trap;
    int is_trap_visited;
    d pillar;
} Room;
typedef struct{
    int collects;
    int damage;
}weapon;
typedef struct {
    int x;
    int y;
    char username[50];
    char password[50];
    int score;
    int games_played;
    int experience;
    int health;
    int golds;
    weapon gun[5];
    int whicch_weapom_is_being_used;
    int spell[3];
    int which_spell_is_being_used;
}player;
typedef struct{
    char type;
    int damage;
    int move;
    int life;
    int x;
    int y;
    int range;
}Monster;
Room rooms[6];
Monster monsters[6];
player user;
int seconds=120,inital_health=80;
int a;
int b=0;
int temps_gold;
int temps_health;
int temps_score;
int temps_gun_collected[4];
int gorosnegi=30;
int finish;
int man;
int visited[MAP_HEIGHT][MAP_WIDTH];
// int playing_music;
// int m=1;
char map[MAP_HEIGHT][MAP_WIDTH];
char map2[MAP_HEIGHT][MAP_WIDTH];
char map3[MAP_HEIGHT][MAP_WIDTH];
void check(Room* rooms,player * user,int floor);
void hiding_map(char map[][150]);
void display_map(Room*rooms);
void display_map2(Room rooms);
void making_pillar(Room * romms);
void connect_doors(int door1_x,int  door2_x,int door1_y,int door2_y);
void stairs(Room *rooms);
void encryped_door(Room* rooms);
void ancient_key(Room *rooms);
int encrypting();
int next_floor();
void show_message(const char * massage);
void gold(Room *rooms,player* user,int a);
void guns(Room* rooms,player* user,int* a);
int picking();
void gun_menu(player* user);
void putting_monsters(Room* rooms,Monster* monsters,int floor);
void monsters_move(player* p,Monster* monsters);
void snake_move(player * p,Monster* monsters);
void show_message2(const char* message,int a);
void health(int p);
void food(Room* rooms);
void putting_spells(Room* rooms);
void spell_menu(player* p);
void play_music(const char *filename);
void show_message3(const char * a,int f);
void saving_map( char * username);
int timing(player *p,time_t t) {
    mvprintw(4,140,"%ld",time(NULL)-t);
    return (time(NULL)-t);
    
}

void initialize_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = ' ';
        }
    }
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map2[y][x] = ' ';
        }
    }
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map3[y][x] = ' ';
        }
    }
}
void creat_room(Room* rooms,int floor){
    srand(time(NULL));
    rooms[0].height=rand()%8+7;
    rooms[0].width=rand()%12+7;
    rooms[0].x=rand()%7 +6;
    rooms[0].y=rand()%5 +5;
    for(int i=rooms[0].y;i<rooms[0].y+rooms[0].height;i++){
        for(int j=rooms[0].x;j<rooms[0].x+rooms[0].width;j++){
            map[rooms[0].y][j]='_';
            map[rooms[0].y+rooms[0].height-1][j]='_';
            if(i!=rooms[0].y && i!=rooms[0].y+rooms[0].height-1){
                map[i][j]='.';
            }
            map[i][rooms[0].x]='|';
            map[i][rooms[0].x+rooms[0].width-1]='|';
        }
    }
    int q=0,w=0,e=0,r=0,t=0;
    rooms[0].doors[0][0]=rooms[0].x+1+(rand()%(rooms[0].width-2));
    rooms[0].doors[0][1]=rooms[0].y+rooms[0].height-1;
    map[rooms[0].y+rooms[0].height-1][(rooms[0].doors[0][0])]='+';
    q=1;
    rooms[0].doors[1][1]=rooms[0].y+rand()%rooms[0].height;
    rooms[0].doors[1][0]=rooms[0].x+rooms[0].width-1;
    map[ rooms[0].doors[1][1]][rooms[0].doors[1][0]]='+';
    rooms[1].height=rand()%8+4;
    rooms[1].width=rand()%12+7;
    rooms[1].x=rand()%7 +13;
    rooms[1].y=rand()%5 +25;
    for(int i=rooms[1].y;i<rooms[1].y+rooms[1].height;i++){
        for(int j=rooms[1].x;j<rooms[1].x+rooms[1].width;j++){
            map[rooms[1].y][j]='_';
            map[rooms[1].y+rooms[1].height-1][j]='_';
            if(i!=rooms[1].y && i!=rooms[1].y+rooms[1].height-1){
                map[i][j]='.';
            }
            map[i][rooms[1].x]='|';
            map[i][rooms[1].x+rooms[1].width-1]='|';
        }
    }
    rooms[1].doors[0][0]=rooms[1].x+rand()%rooms[1].width;
    rooms[1].doors[0][1]=rooms[1].y;
    map[rooms[1].y][(rooms[1].doors[0][0])]='+';
    int z=rand()%2;
    rooms[1].doors[1][1]=rooms[1].y+rand()%rooms[1].height;
    rooms[1].doors[1][0]=rooms[1].x+rooms[1].width-1;
    map[ rooms[1].doors[1][1]][rooms[1].doors[1][0]]='+';

    rooms[2].height=rand()%8+7;
    rooms[2].width=rand()%12+7;
    rooms[2].x=rand()%7 +55;
    rooms[2].y=rand()%5 +1;
    for(int i=rooms[2].y;i<rooms[2].y+rooms[2].height;i++){
        for(int j=rooms[2].x;j<rooms[2].x+rooms[2].width;j++){
            map[rooms[2].y][j]='_';
            map[rooms[2].y+rooms[2].height-1][j]='_';
            if(i!=rooms[2].y && i!=rooms[2].y+rooms[2].height-1){
                map[i][j]='.';
            }
            map[i][rooms[2].x]='|';
            map[i][rooms[2].x+rooms[2].width-1]='|';
        }
    }
    rooms[2].doors[0][0]=rooms[2].x+rand()%rooms[2].width;
    rooms[2].doors[0][1]=rooms[2].y+rooms[2].height-1;
    map[rooms[2].y+rooms[2].height-1][(rooms[2].doors[0][0])]='+';
    int y=rand()%2;
    rooms[2].doors[1][1]=rooms[2].y+rand()%rooms[2].height;
    rooms[2].doors[1][0]=rooms[2].x+rooms[2].width-1;
    map[ rooms[2].doors[1][1]][rooms[2].doors[1][0]]='+';
    rooms[2].doors[2][1]=rooms[2].y+rand()%rooms[2].height;
    rooms[2].doors[2][0]=rooms[2].x;
    map[ rooms[2].doors[2][1]][rooms[2].doors[2][0]]='+';

    rooms[3].height=rand()%8+7;
    rooms[3].width=rand()%12+7;
    rooms[3].x=rand()%7 +45;
    rooms[3].y=rand()%5 +20;
    for(int i=rooms[3].y;i<rooms[3].y+rooms[3].height;i++){
        for(int j=rooms[3].x;j<rooms[3].x+rooms[3].width;j++){
            map[rooms[3].y][j]='_';
            map[rooms[3].y+rooms[3].height-1][j]='_';
            if(i!=rooms[3].y && i!=rooms[3].y+rooms[3].height-1){
                map[i][j]='.';
            }
            map[i][rooms[3].x]='|';
            map[i][rooms[3].x+rooms[3].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[3].doors[0][0]=rooms[3].x+rand()%rooms[3].width;
    rooms[3].doors[0][1]=rooms[3].y;//+rooms[3].height-1;
    map[rooms[3].y][(rooms[3].doors[0][0])]='+';
    int m=rand()%2;
    // if(!e || m){
        // r=1;
        //mvprintw(0,0,"%d",q);
        rooms[3].doors[1][1]=rooms[3].y+rand()%rooms[3].height;
        rooms[3].doors[1][0]=rooms[3].x+rooms[3].width-1;
        map[ rooms[3].doors[1][1]][rooms[3].doors[1][0]]='+';
    // }
    // int u=rand()%3;
    // if(u==0){
        
        rooms[3].doors[2][1]=rooms[3].y+rand()%rooms[3].height;
        rooms[3].doors[2][0]=rooms[3].x;
        map[ rooms[3].doors[2][1]][rooms[3].doors[2][0]]='+';
    // }
    
    rooms[4].height=rand()%8+7;
    rooms[4].width=rand()%12+7;
    rooms[4].x=rand()%7 +110;
    rooms[4].y=rand()%5 +1;
    for(int i=rooms[4].y;i<rooms[4].y+rooms[4].height;i++){
        for(int j=rooms[4].x;j<rooms[4].x+rooms[4].width;j++){
            map[rooms[4].y][j]='_';
            map[rooms[4].y+rooms[4].height-1][j]='_';
            if(i!=rooms[4].y && i!=rooms[4].y+rooms[4].height-1){
                map[i][j]='.';
            }
            map[i][rooms[4].x]='|';
            map[i][rooms[4].x+rooms[4].width-1]='|';
        }
    }
    // int q=0,w=0,e=0,r=0,t=0;
    rooms[4].doors[0][0]=rooms[4].x+rand()%rooms[4].width;
    rooms[4].doors[0][1]=rooms[4].y+rooms[4].height-1;
    map[rooms[4].y+rooms[4].height-1][(rooms[4].doors[0][0])]='+';
    // int x=rand()%2;
    // if(x){
    //     t=1;
        //mvprintw(0,0,"%d",q);
        rooms[4].doors[1][1]=rooms[4].y+rand()%rooms[4].height;
        rooms[4].doors[1][0]=rooms[4].x;
        map[ rooms[4].doors[1][1]][rooms[4].doors[1][0]]='+';
    // }
    rooms[5].height=rand()%8+7;
    rooms[5].width=rand()%12+7;
    rooms[5].x=rand()%7 +130;
    rooms[5].y=rand()%4 +22;
    for(int i=rooms[5].y;i<rooms[5].y+rooms[5].height;i++){
        for(int j=rooms[5].x;j<rooms[5].x+rooms[5].width;j++){
            map[rooms[5].y][j]='_';
            map[rooms[5].y+rooms[5].height-1][j]='_';
            if(i!=rooms[5].y && i!=rooms[5].y+rooms[5].height-1){
                map[i][j]='.';
            }
            map[i][rooms[5].x]='|';
            map[i][rooms[5].x+rooms[5].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[5].doors[0][0]=rooms[5].x+rand()%rooms[5].width;
    rooms[5].doors[0][1]=rooms[5].y;//+rooms[5].height-1;
    map[rooms[5].y][(rooms[5].doors[0][0])]='+';
    // int l=rand()%2;
    // if(!t || l){
        //mvprintw(0,0,"%d",q);
        rooms[5].doors[1][1]=rooms[5].y+rand()%rooms[5].height;
        rooms[5].doors[1][0]=rooms[5].x;
        map[ rooms[5].doors[1][1]][rooms[5].doors[1][0]]='+';
    // }
    if(floor==4){
        int x=rand()%(rooms[5].width-2)+rooms[5].x+1;
        int y=rand()%(rooms[5].height-2)+rooms[5].y+1;
        map[y][x]='?';
        map2[y][x]='?';
    }
    connect_doors(rooms[0].doors[0][0],rooms[1].doors[0][0],rooms[0].doors[0][1],rooms[1].doors[0][1]);
    //int io=rand()%2;
    //if(io){
        connect_doors(rooms[0].doors[1][0],rooms[2].doors[2][0],rooms[0].doors[1][1],rooms[2].doors[2][1]);
        connect_doors(rooms[1].doors[1][0],rooms[3].doors[2][0],rooms[1].doors[1][1],rooms[3].doors[2][1]);
    //}
    //else{
       // connect_doors(rooms[0].doors[1][0],rooms[3].doors[2][0],rooms[0].doors[1][1],rooms[3].doors[2][1]);
        //connect_doors(rooms[1].doors[1][0],rooms[2].doors[2][0],rooms[1].doors[1][1],rooms[2].doors[2][1]);
    //}
    connect_doors(rooms[2].doors[1][0],rooms[4].doors[1][0],rooms[2].doors[1][1],rooms[4].doors[1][1]);
    connect_doors(rooms[2].doors[0][0],rooms[3].doors[0][0],rooms[2].doors[0][1],rooms[3].doors[0][1]);
    connect_doors(rooms[3].doors[1][0],rooms[5].doors[1][0],rooms[3].doors[1][1],rooms[5].doors[1][1]);
    connect_doors(rooms[4].doors[0][0],rooms[5].doors[0][0],rooms[4].doors[0][1],rooms[5].doors[0][1]);
    if(floor==1 && !b){
        show_message("you have entered the first floor!");
    }
    else if(floor==2 && !b){
        show_message("you have entered the second floor!");
    }
    else if(floor==3 && !b){
        show_message("you have entered the third floor!");
    }
    else if(floor==4 && !b){
        show_message("you have entered the last floor!");
    }

}
void creat_room2(Room* rooms){
    rooms[6].height=rand()%10+7;
    rooms[6].width=rand()%15+7;
    rooms[6].x=rand()%7 +9;
    rooms[6].y=rand()%5 +1;
    for(int i=rooms[6].y;i<rooms[6].y+rooms[6].height;i++){
        for(int j=rooms[6].x;j<rooms[6].x+rooms[6].width;j++){
            map[rooms[6].y][j]='_';
            map[rooms[6].y+rooms[6].height-1][j]='_';
            if(i!=rooms[6].y && i!=rooms[6].y+rooms[6].height-1){
                map[i][j]='.';
            }
            map[i][rooms[6].x]='|';
            map[i][rooms[6].x+rooms[6].width-1]='|';
        }
    }
    int q=0,w=0,e=0,r=0,t=0;
    rooms[6].doors[0][0]=rooms[6].x+1+(rand()%(rooms[6].width-2));
    rooms[6].doors[0][1]=rooms[6].y+rooms[6].height-1;
    map[rooms[6].y+rooms[6].height-1][(rooms[6].doors[0][0])]='+';
    // int h=rand()%2;
    // if(h){
        q=1;
        //mvprintw(0,0,"%d",q);
        rooms[6].doors[1][1]=rooms[6].y+rand()%rooms[6].height;
        rooms[6].doors[1][0]=rooms[6].x+rooms[6].width-1;
        map[ rooms[6].doors[1][1]][rooms[6].doors[1][0]]='+';
    // }
    rooms[7].height=rand()%10+4;
    rooms[7].width=rand()%15+7;
    rooms[7].x=rand()%7 +9;
    rooms[7].y=rand()%5 +22;
    for(int i=rooms[7].y;i<rooms[7].y+rooms[7].height;i++){
        for(int j=rooms[7].x;j<rooms[7].x+rooms[7].width;j++){
            map[rooms[7].y][j]='_';
            map[rooms[7].y+rooms[7].height-1][j]='_';
            if(i!=rooms[7].y && i!=rooms[7].y+rooms[7].height-1){
                map[i][j]='.';
            }
            map[i][rooms[7].x]='|';
            map[i][rooms[7].x+rooms[7].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[7].doors[0][0]=rooms[7].x+rand()%rooms[7].width;
    rooms[7].doors[0][1]=rooms[7].y;
    map[rooms[7].y][(rooms[7].doors[0][0])]='+';
    int z=rand()%2;
    // if(!q || z){
        // w=1;
        //mvprintw(0,0,"%d",q);
        rooms[7].doors[1][1]=rooms[7].y+rand()%rooms[7].height;
        rooms[7].doors[1][0]=rooms[7].x+rooms[7].width-1;
        map[ rooms[7].doors[1][1]][rooms[7].doors[1][0]]='+';
    // }
    rooms[8].height=rand()%10+7;
    rooms[8].width=rand()%15+7;
    rooms[8].x=rand()%7 +50;
    rooms[8].y=rand()%5 +1;
    for(int i=rooms[8].y;i<rooms[8].y+rooms[8].height;i++){
        for(int j=rooms[8].x;j<rooms[8].x+rooms[8].width;j++){
            map[rooms[8].y][j]='_';
            map[rooms[8].y+rooms[8].height-1][j]='_';
            if(i!=rooms[8].y && i!=rooms[8].y+rooms[8].height-1){
                map[i][j]='.';
            }
            map[i][rooms[8].x]='|';
            map[i][rooms[8].x+rooms[8].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[8].doors[0][0]=rooms[8].x+rand()%rooms[8].width;
    rooms[8].doors[0][1]=rooms[8].y+rooms[8].height-1;
    map[rooms[8].y+rooms[8].height-1][(rooms[8].doors[0][0])]='+';
    int y=rand()%2;
    // if(y){
    //     e=1;
        //mvprintw(0,0,"%d",q);
        rooms[8].doors[1][1]=rooms[8].y+rand()%rooms[8].height;
        rooms[8].doors[1][0]=rooms[8].x+rooms[8].width-1;
        map[ rooms[8].doors[1][1]][rooms[8].doors[1][0]]='+';
        rooms[8].doors[2][1]=rooms[8].y+rand()%rooms[8].height;
        rooms[8].doors[2][0]=rooms[8].x;
        map[ rooms[8].doors[2][1]][rooms[8].doors[2][0]]='+';
    // }
    rooms[9].height=rand()%10+7;
    rooms[9].width=rand()%15+7;
    rooms[9].x=rand()%7 +50;
    rooms[9].y=rand()%5 +20;
    for(int i=rooms[9].y;i<rooms[9].y+rooms[9].height;i++){
        for(int j=rooms[9].x;j<rooms[9].x+rooms[9].width;j++){
            map[rooms[9].y][j]='_';
            map[rooms[9].y+rooms[9].height-1][j]='_';
            if(i!=rooms[9].y && i!=rooms[9].y+rooms[9].height-1){
                map[i][j]='.';
            }
            map[i][rooms[9].x]='|';
            map[i][rooms[9].x+rooms[9].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[9].doors[0][0]=rooms[9].x+rand()%rooms[9].width;
    rooms[9].doors[0][1]=rooms[9].y+rooms[9].height-1;
    map[rooms[9].y][(rooms[9].doors[0][0])]='+';
    int m=rand()%2;
    // if(!e || m){
        // r=1;
        //mvprintw(0,0,"%d",q);
        rooms[9].doors[1][1]=rooms[9].y+rand()%rooms[9].height;
        rooms[9].doors[1][0]=rooms[9].x+rooms[9].width-1;
        map[ rooms[9].doors[1][1]][rooms[9].doors[1][0]]='+';
    // }
    // int u=rand()%3;
    // if(u==0){
        
        rooms[9].doors[2][1]=rooms[9].y+rand()%rooms[9].height;
        rooms[9].doors[2][0]=rooms[9].x;
        map[ rooms[9].doors[2][1]][rooms[9].doors[2][0]]='+';
    // }
    
    rooms[4].height=rand()%10+7;
    rooms[4].width=rand()%15+7;
    rooms[4].x=rand()%7 +100;
    rooms[4].y=rand()%5 +1;
    for(int i=rooms[4].y;i<rooms[4].y+rooms[4].height;i++){
        for(int j=rooms[4].x;j<rooms[4].x+rooms[4].width;j++){
            map[rooms[4].y][j]='_';
            map[rooms[4].y+rooms[4].height-1][j]='_';
            if(i!=rooms[4].y && i!=rooms[4].y+rooms[4].height-1){
                map[i][j]='.';
            }
            map[i][rooms[4].x]='|';
            map[i][rooms[4].x+rooms[4].width-1]='|';
        }
    }
    // int q=0,w=0,e=0,r=0,t=0;
    rooms[4].doors[0][0]=rooms[4].x+rand()%rooms[4].width;
    rooms[4].doors[0][1]=rooms[4].y+rooms[4].height-1;
    map[rooms[4].y+rooms[4].height-1][(rooms[4].doors[0][0])]='+';
    // int x=rand()%2;
    // if(x){
    //     t=1;
        //mvprintw(0,0,"%d",q);
        rooms[4].doors[1][1]=rooms[4].y+rand()%rooms[4].height;
        rooms[4].doors[1][0]=rooms[4].x;
        map[ rooms[4].doors[1][1]][rooms[4].doors[1][0]]='+';
    // }
    rooms[5].height=rand()%10+7;
    rooms[5].width=rand()%15+7;
    rooms[5].x=rand()%7 +100;
    rooms[5].y=rand()%5 +22;
    for(int i=rooms[5].y;i<rooms[5].y+rooms[5].height;i++){
        for(int j=rooms[5].x;j<rooms[5].x+rooms[5].width;j++){
            map[rooms[5].y][j]='_';
            map[rooms[5].y+rooms[5].height-1][j]='_';
            if(i!=rooms[5].y && i!=rooms[5].y+rooms[5].height-1){
                map[i][j]='.';
            }
            map[i][rooms[5].x]='|';
            map[i][rooms[5].x+rooms[5].width-1]='|';
        }
    }
    //int q=0,w=0,e=0,r=0,t=0;
    rooms[5].doors[0][0]=rooms[5].x+rand()%rooms[5].width;
    rooms[5].doors[0][1]=rooms[5].y+rooms[5].height-1;
    map[rooms[5].y][(rooms[5].doors[0][0])]='+';
    // int l=rand()%2;
    // if(!t || l){
        //mvprintw(0,0,"%d",q);
        rooms[5].doors[1][1]=rooms[5].y+rand()%rooms[5].height;
        rooms[5].doors[1][0]=rooms[5].x;
        map[ rooms[5].doors[1][1]][rooms[5].doors[1][0]]='+';
    // }
    connect_doors(rooms[6].doors[0][0],rooms[7].doors[0][0],rooms[6].doors[0][1],rooms[7].doors[0][1]);
    //int io=rand()%2;
    //if(io){
        connect_doors(rooms[6].doors[1][0],rooms[8].doors[2][0],rooms[6].doors[1][1],rooms[8].doors[2][1]);
        connect_doors(rooms[7].doors[1][0],rooms[9].doors[2][0],rooms[7].doors[1][1],rooms[9].doors[2][1]);
    //}
    //else{
       // connect_doors(rooms[6].doors[1][0],rooms[9].doors[2][0],rooms[6].doors[1][1],rooms[9].doors[2][1]);
        //connect_doors(rooms[7].doors[1][0],rooms[8].doors[2][0],rooms[7].doors[1][1],rooms[8].doors[2][1]);
    //}
    connect_doors(rooms[8].doors[1][0],rooms[4].doors[1][0],rooms[8].doors[1][1],rooms[4].doors[1][1]);
    connect_doors(rooms[8].doors[0][0],rooms[9].doors[0][0],rooms[8].doors[0][1],rooms[9].doors[0][1]);
    connect_doors(rooms[9].doors[1][0],rooms[5].doors[1][0],rooms[3].doors[1][1],rooms[5].doors[1][1]);
    connect_doors(rooms[4].doors[0][0],rooms[5].doors[0][0],rooms[4].doors[0][1],rooms[5].doors[0][1]);

}
void connect_doors(int door1_x,int  door2_x,int door1_y,int door2_y){
    refresh();
    d temps ;
    temps.x=door1_x;
    temps.y=door1_y;
    d pre ;
    pre.x= door1_x;
    pre.y=door1_y;
    int max_steps = 1000; 
    while (max_steps--) {
        //map[2][2]='o';
        if (temps.x == door2_x && temps.y == door2_y-1) //{
            // map[]
            break;

        if (temps.x > door2_x &&(map[temps.y][temps.x - 1] == ' ' ) ) {
            pre.x = temps.x;
            temps.x--;
        } else if (temps.x < door2_x && (map[temps.y][temps.x + 1] == ' ' ) ){
            pre .x= temps.x;
            temps.x++;
        } else if (temps.y > door2_y && (map[temps.y - 1][temps.x] == ' ' )) {
            pre.y = temps.y;
            temps.y--;
        } else if (temps.y < door2_y &&(map[temps.y + 1][temps.x] == ' ')) {
            pre.y = temps.y;
            temps.y++;
        } else {
            temps .y= pre.y;
            temps.x=pre.x; 
            continue;
        }

        if (temps.x >= 0 && temps.x < MAP_WIDTH && temps.y >= 0 && temps.y < MAP_HEIGHT) {
            map[temps.y][temps.x] = '#';
        }
    }
}
void maps(){
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map2[y][x] = map[y][x];
        }
    }
}
void trap(Room* rooms,player* user, int a){
    user->health=a;
    srand(time(NULL));
    // getch();
    for(int i=0;i<6;i++){
        rooms[i].trap.y=rooms[i].y+1+(rand()%(rooms[i].height-2));
        rooms[i].trap.x=rooms[i].x+1 +(rand()%(rooms[i].width-2));
        if(map[rooms[i].trap.y][rooms[i].trap.x]=='&')
            i--;
        else {
            // map[rooms[i].trap.y][rooms[i].trap.x]='^';
            // map2[rooms[i].trap.y][rooms[i].trap.x]='^';
            rooms[i].is_trap_visited=0;
        }    
    }
}
void move_player(player* p,int floor){
    p->whicch_weapom_is_being_used=0;
    map2[rooms[0].y+1][rooms[0].x+1]='$';
    p->y=rooms[0].y+1;
    p->x=rooms[0].x+1;
    int pause=0;
    time_t start=time(NULL);
    while(1){//time(NULL)-start<seconds){
    if(playing_music){
        if(!donot){
            play_music(musicer);
            playing_music=0;
        }    
    } 
    if(donot){
        donot=0;
        Mix_HaltMusic();
    }   
        for(int dfg=0;dfg<MAP_HEIGHT;dfg++){
            for(int uyt=0;uyt<MAP_WIDTH;uyt++){
                if(map2[dfg][uyt]=='$')
                    visited[dfg][uyt]=1;
            }
        }
        // show_message2("score: ",p->score);
        // check(rooms,&user);
        // hiding_map(map2);
        temps_gold=p->golds;
        temps_health=p->health;
        temps_score=p->score;
        health(temps_health);
        for(int i=1;i<5;i++){
            temps_gun_collected[i-1]=p->gun[i].collects;
        }
        check(rooms,&user,floor);
        if(b){
            clear();
            show_message("Oops you lost the game! press any key to exit");
            return;
        }
        if(finish){
            return;
        }    
        display_map(rooms);
        display_map2(rooms[0]);
        if(floor==4){
            start_color();
            init_pair(23,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(23));
            for(int i=rooms[5].y;i<rooms[5].y+rooms[5].height;i++){
                for(int j=rooms[5].x;j<rooms[5].x+rooms[5].width;j++){
                    if(map2[i][j]=='.' || map2[i][j]=='|' || map2[i][j]=='_' || map2[i][j]=='O')
                        mvaddch(i,j,map2[i][j]);
                }
            }
            attroff(COLOR_PAIR(23));
        }   
        if(next_floor())
            break;
        char a=getch();
        if(a=='8'){
            if(map[p->y-1][p->x]!='_' && map[p->y-1][p->x]!='|' && map[p->y-1][p->x]!=' ' && map[p->y-1][p->x]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[--p->y][p->x]='$';
                
            }    
        }
        else if(a=='2'){
            if(map[p->y+1][p->x]!='_' && map[p->y+1][p->x]!='|' && map[p->y+1][p->x]!=' ' && map[p->y+1][p->x]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[++p->y][p->x]='$';
                
            }    
        }
        else if(a=='6'){
            if(map[p->y][p->x+1]!='_' && map[p->y][p->x+1]!='|' && map[p->y][p->x+1]!=' ' && map[p->y][p->x+1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[p->y][++p->x]='$';
                
            }    
        }
        else if(a=='4'){
            if(map[p->y][p->x-1]!='_' && map[p->y][p->x-1]!='|' && map[p->y][p->x-1]!=' ' && map[p->y][p->x-1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[p->y][--p->x]='$';
               
            }    
        }
        else if(a=='9'){
            if(map[p->y-1][p->x+1]!='_' && map[p->y-1][p->x+1]!='|' && map[p->y-1][p->x+1]!=' ' && map[p->y-1][p->x+1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[--p->y][++p->x]='$';
                
            }    
        }
        else if(a=='7'){
            if(map[p->y-1][p->x-1]!='_' && map[p->y-1][p->x-1]!='|' && map[p->y-1][p->x-1]!=' ' && map[p->y-1][p->x-1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[--p->y][--p->x]='$';
                
            }    
        }
        else if(a=='1'){
            if(map[p->y+1][p->x-1]!='_' && map[p->y+1][p->x-1]!='|' && map[p->y+1][p->x-1]!=' ' && map[p->y+1][p->x-1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[++p->y][--p->x]='$';
                
            }    
        }
        else if(a=='3'){
            if(map[p->y+1][p->x+1]!='_' && map[p->y+1][p->x+1]!='|' && map[p->y+1][p->x+1]!=' ' && map[p->y+1][p->x+1]!='O'){
                map2[p->y][p->x]=map[p->y][p->x];
                map2[++p->y][++p->x]='$';
                
            }    
        }
        // else if(a==27 && !pause){
        //     show_message("Pause");
        //     char f=getch();
        //     clear();
        //     mvprintw(LINES/2-3,COLS/2-15,"Quit(esc)");
        //     mvprintw(LINES/2-2,COLS/2-15,"Resume(r)");
        //     if(f==27)
        //         return;
        //     else
        //         pause=0;
        // }
        else if(a==27){
            show_message("press (esc) once more to exit");
            int r=getch();
            if(r==27){
                saving_map(username);
                b=1;
            }    
        }
        else if(a=='h' || a=='H'){
            time_t temps=start;
            pregame();
            start=temps;
            clear();
        }
        else if((a=='f' || a=='F') ){
            a=getch();
            if(a=='8'){
                while(map[p->y-1][p->x]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][p->x]='$';
                    refresh();
                }
            }
            else if(a=='2'){
                while(map[p->y+1][p->x]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][p->x]='$';
                    refresh();
                }
            }
            else  if(a=='6'){
                while(map[p->y][p->x+1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[p->y][++p->x]='$';
                    refresh();
                }
            }
            else  if(a=='4'){
                while(map[p->y][p->x-1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[p->y][--p->x]='$';
                    refresh();
                }
            }
            else  if(a=='9'){
                while(map[p->y-1][p->x+1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][++p->x]='$';
                    refresh();
                }
            }
            else  if(a=='7'){
                while(map[p->y-1][p->x-1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][--p->x]='$';
                    refresh();
                }
            }
            else  if(a=='3'){
                while(map[p->y+1][p->x+1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][++p->x]='$';
                    refresh();
                }
            }
            else  if(a=='1'){
                while(map[p->y+1][p->x-1]=='.'){
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][--p->x]='$';
                    refresh();
                }
            }
        }
        else if(a=='m' || a=='M'){
            clear();
            man++;
            if(man%2){
                for(int qwqw=0;qwqw<MAP_HEIGHT;qwqw++){
                    for(int mew=0;mew<MAP_WIDTH;mew++){
                        mvprintw(qwqw,mew,"%c",map2[qwqw][mew]);
                    }
                }
            }
        }
        else if(a=='s' || a=='S'){
            int i;
            for(i=0;i<6;i++){
                if(p->y>=rooms[i].y && p->y<rooms[i].y+rooms[i].height && p->x>=rooms[i].x && p->x<rooms[i].x+rooms[i].width)
                    break;
            }
            switch (i){
                case 0:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 1:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
                case 2:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    display_map2(rooms[4]);
                    refresh();
                    sleep(10);
                    break;    
                case 3:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    display_map2(rooms[5]);
                    refresh();
                    sleep(10);
                    break;    
                case 4:
                    clear();
                    display_map2(rooms[5]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 5:
                    clear();
                    display_map2(rooms[4]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
            }
        }
        else if(a=='i' || a=='I'){
            gun_menu(&user);
        }
        else if(a=='w' || a=='W'){
            p->whicch_weapom_is_being_used=0;
            show_message("Now you have no weapon in hand!");
        }
        else if(a=='p' || a=='P'){
            spell_menu(p);
        }
    }
}
void check(Room * rooms,player* user , int floor){
    int c=0;
    if(user->health<=0)
        b=1;
    for(int i=0;i<MAP_HEIGHT ;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(map[i][j]=='&' && map2[i][j]=='$'){
                int y;
                for(y=0;y<6;y++){
                    if(i<rooms[y].y+rooms[y].height && i>=rooms[y].y && j<rooms[y].x+rooms[y].width && j>=rooms[y].x){
                        break;
                    }
                }
                if(!rooms[y].encryped_door_condition){
                    a=encrypting(); 
                    clear();
                    init_pair(134,COLOR_MAGENTA,COLOR_BLACK);
                    attron(COLOR_PAIR(134));
                    mvprintw(LINES/2-3,COLS/2-15,"the password is: %d",a);
                    refresh();
                    attroff(COLOR_PAIR(134));
                    napms(1000);
                    clear();  
                    break;
                }    
            }
            else if(map2[i][j]=='$' && map[i][j]=='*'){
                user->score+=5;
                int h=rand()%4+1;
                user->golds+=h;
                map[i][j]='.';
                int height = 3, width = 50;
                int start_y = 0, start_x = 3; 
                start_color();
                init_pair(11,COLOR_YELLOW,COLOR_BLACK);
                WINDOW *msg_win = newwin(height, width, start_y, start_x);
                box(msg_win, 0, 0); 
                wattron(msg_win, COLOR_PAIR(11));
                mvwprintw(msg_win, 1, 4, "That's it! you got %d more golds. Total:%d",h,user->golds);
                wattroff(msg_win, COLOR_PAIR(11));
                wrefresh(msg_win);  
                napms(2000); 
                werase(msg_win);
                wrefresh(msg_win);
                delwin(msg_win); 
                refresh();
            }
            else if(map2[i][j]=='$' && map[i][j]=='!'){
                int h=rand()%5+5;
                user->golds+=h;
                map[i][j]='.';
                int height = 3, width = 50;
                int start_y = 0, start_x = 3; 
                start_color();
                init_pair(11,COLOR_YELLOW,COLOR_BLACK);
                WINDOW *msg_win = newwin(height, width, start_y, start_x);
                box(msg_win, 0, 0); 
                wattron(msg_win, COLOR_PAIR(11));
                mvwprintw(msg_win, 1, 4, "That's it! you got %d more golds. Total:%d",h,user->golds);
                wattroff(msg_win, COLOR_PAIR(11));
                wrefresh(msg_win);  
                napms(2000); 
                werase(msg_win);
                wrefresh(msg_win);
                delwin(msg_win); 
                refresh();
            }
            else if(map2[i][j]=='$' && map[i][j]=='X'){
                if(picking()){
                    user->gun[1].collects+=10;
                    map[i][j]='.';
                    show_message("you got 10 more Daggers!");
                }
                
            }
            else if(map2[i][j]=='$' && map[i][j]=='M'){
                if(picking()){
                    user->gun[2].collects+=8;
                    map[i][j]='.';
                    show_message("you got 8 more Magic Wands!");
                }
                
            }
            else if(map2[i][j]=='$' && map[i][j]=='N'){
                if(picking()){
                    user->gun[3].collects+=20;
                    map[i][j]='.';
                    show_message("you got 20 more Normal Arrows");
                }
                
            }
            else if(map2[i][j]=='$' && map[i][j]=='/'){
                if(picking()){
                    user->gun[4].collects=1;
                    map[i][j]='.';
                    show_message("Now you have sword!");
                }
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='D') || (map2[i][j]=='$' && map[i-1][j]=='D' )|| (map2[i][j]=='$' && map[i][j+1]=='D' )|| (map2[i][j]=='$' && map[i][j-1]=='D') || (map2[i][j]=='$' && map[i-1][j-1]=='D') || (map2[i][j]=='$' && map[i+1][j-1]=='D') || (map2[i][j]=='$' && map[i+1][j+1]=='D') || (map2[i][j]=='$' && map[i-1][j+1]=='D')){
                user->health-=monsters[0].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[0]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='F') || (map2[i][j]=='$' && map[i-1][j]=='F' )|| (map2[i][j]=='$' && map[i][j+1]=='F' )|| (map2[i][j]=='$' && map[i][j-1]=='F') || (map2[i][j]=='$' && map[i-1][j-1]=='F') || (map2[i][j]=='$' && map[i+1][j-1]=='F') || (map2[i][j]=='$' && map[i+1][j+1]=='F') || (map2[i][j]=='$' && map[i-1][j+1]=='F')){
                user->health-=monsters[1].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[1]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='G') || (map2[i][j]=='$' && map[i-1][j]=='G' )|| (map2[i][j]=='$' && map[i][j+1]=='G' )|| (map2[i][j]=='$' && map[i][j-1]=='G') || (map2[i][j]=='$' && map[i-1][j-1]=='G') || (map2[i][j]=='$' && map[i+1][j-1]=='G') || (map2[i][j]=='$' && map[i+1][j+1]=='G') || (map2[i][j]=='$' && map[i-1][j+1]=='G')){
                user->health-=monsters[2].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[2]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='U') || (map2[i][j]=='$' && map[i-1][j]=='U' )|| (map2[i][j]=='$' && map[i][j+1]=='U' )|| (map2[i][j]=='$' && map[i][j-1]=='U') || (map2[i][j]=='$' && map[i-1][j-1]=='U') || (map2[i][j]=='$' && map[i+1][j-1]=='U') || (map2[i][j]=='$' && map[i+1][j+1]=='U') || (map2[i][j]=='$' && map[i-1][j+1]=='U')){
                user->health-=monsters[4].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[4]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='S') || (map2[i][j]=='$' && map[i-1][j]=='S' )|| (map2[i][j]=='$' && map[i][j+1]=='S' )|| (map2[i][j]=='$' && map[i][j-1]=='S') || (map2[i][j]=='$' && map[i-1][j-1]=='S') || (map2[i][j]=='$' && map[i+1][j-1]=='S') || (map2[i][j]=='$' && map[i+1][j+1]=='S') || (map2[i][j]=='$' && map[i-1][j+1]=='S')){
                user->health-=monsters[3].damage;
                show_message2("the snake hit you! health: ",user->health);
                snake_move(user,monsters);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='d') || (map2[i][j]=='$' && map[i-1][j]=='d' )|| (map2[i][j]=='$' && map[i][j+1]=='d' )|| (map2[i][j]=='$' && map[i][j-1]=='d') || (map2[i][j]=='$' && map[i-1][j-1]=='d') || (map2[i][j]=='$' && map[i+1][j-1]=='d') || (map2[i][j]=='$' && map[i+1][j+1]=='d') || (map2[i][j]=='$' && map[i-1][j+1]=='d')){
                user->health-=monsters[5].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[5]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='f') || (map2[i][j]=='$' && map[i-1][j]=='f' )|| (map2[i][j]=='$' && map[i][j+1]=='f' )|| (map2[i][j]=='$' && map[i][j-1]=='f') || (map2[i][j]=='$' && map[i-1][j-1]=='f') || (map2[i][j]=='$' && map[i+1][j-1]=='f') || (map2[i][j]=='$' && map[i+1][j+1]=='f') || (map2[i][j]=='$' && map[i-1][j+1]=='f')){
                user->health-=monsters[6].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[6]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='g') || (map2[i][j]=='$' && map[i-1][j]=='g' )|| (map2[i][j]=='$' && map[i][j+1]=='g' )|| (map2[i][j]=='$' && map[i][j-1]=='g') || (map2[i][j]=='$' && map[i-1][j-1]=='g') || (map2[i][j]=='$' && map[i+1][j-1]=='g') || (map2[i][j]=='$' && map[i+1][j+1]=='g') || (map2[i][j]=='$' && map[i-1][j+1]=='g')){
                user->health-=monsters[7].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[7]);
            }
            else if((map2[i][j]=='$' && map[i+1][j]=='u') || (map2[i][j]=='$' && map[i-1][j]=='u' )|| (map2[i][j]=='$' && map[i][j+1]=='u' )|| (map2[i][j]=='$' && map[i][j-1]=='u') || (map2[i][j]=='$' && map[i-1][j-1]=='u') || (map2[i][j]=='$' && map[i+1][j-1]=='u') || (map2[i][j]=='$' && map[i+1][j+1]=='u') || (map2[i][j]=='$' && map[i-1][j+1]=='u')){
                user->health-=monsters[9].damage;
                show_message2("the Monster hit you! health: ",user->health);
                monsters_move(user,&monsters[9]);
            }
            else if(map2[i][j]=='$' && (map[i][j]=='W' || map[i][j]=='Q' || map[i][j]=='T' || map[i][j]=='Y' )){
                if(user->health<inital_health)
                    user->health+=2;
                gorosnegi-=2;
                show_message3("sir:",gorosnegi);
                if(!gorosnegi){
                    user->health=inital_health;
                    gorosnegi=30;
                }
                show_message2("you ate some food!  health: ",user->health);
                map[i][j]='.';
            }
            else if(map2[i][j]=='$' && ((i==rooms[5].doors[0][1] && j==rooms[5].doors[0][0] )||(i==rooms[5].doors[1][1] && j==rooms[5].doors[1][0]))  && floor==4){
                // show_message2("congratulations you could finish the game   score: ",user->score);
                play_music("track2.mp3");
            }
            else if(map2[i][j]=='$' && map[i][j]=='?'){
                finish=1;
                clear();
                show_message2("congratulations you could finish the game   score: ",user->score);
            }
            else if(map2[i][j]=='$' && map[i][j]=='H'){
                if(picking()){
                    show_message("you got one more health spell in your bag!");
                    user->spell[0]++;
                    map[i][j]='.';
                }    
            }
            else if(map2[i][j]=='$' && map[i][j]=='%'){
                if(picking()){
                    show_message("you got one speed health spell in your bag!");
                    user->spell[1]++;
                    map[i][j]='.';
                }    
            }
            else if(map2[i][j]=='$' && map[i][j]=='='){
                if(picking()){
                    show_message("you got one more damage spell in your bag!");
                    user->spell[2]++;
                    map[i][j]='.';
                }    
            }
            else if(map2[i][j]=='$'){
                for(int k=0;k<6;k++){
                    if(i==rooms[k].trap.y && j==rooms[k].trap.x && !rooms[k].is_trap_visited){
                        user->health-=5;
                        rooms[k].is_trap_visited=1;
                        map[rooms[k].trap.y][rooms[k].trap.x]='^';
                        // map2[rooms[k].trap.y][rooms[k].trap.x]='^';
                        int height = 3, width = 50;
                        int start_y = 0, start_x = 3; 
                        start_color();
                        init_pair(11,COLOR_YELLOW,COLOR_BLACK);
                        WINDOW *msg_win = newwin(height, width, start_y, start_x);
                        box(msg_win, 0, 0); 
                        wattron(msg_win, COLOR_PAIR(11));
                        mvwprintw(msg_win, 1, 4, "Oops!! you went on a trap. health: %d",user->health);
                        wattroff(msg_win, COLOR_PAIR(11));
                        wrefresh(msg_win);  
                        napms(2000); 
                        werase(msg_win);
                        wrefresh(msg_win);
                        delwin(msg_win); 
                        refresh();
                        break;
                    }
                }
            }
        }
    }
    int which_room;
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(map[i][j]=='@' && map2[i][j]=='$'){
                for(int y=0;y<6;y++){
                    if(i<rooms[y].y+rooms[y].height && i>=rooms[y].y && j<rooms[y].x+rooms[y].width && j>=rooms[y].x){
                        which_room=y;
                        break;
                    }
                }
                if(!rooms[which_room].encryped_door_condition){
                    for (int h = 0; h < 3; h++) {
                        int d;
                        char r[50];
                        clear();
                        curs_set(TRUE);
                        echo(); 
                        init_pair(135,COLOR_MAGENTA,COLOR_BLACK);
                        attron(COLOR_PAIR(135));
                        mvprintw(LINES / 2 - 3, COLS / 2 - 15, "Enter the password: ");
                        refresh();
                        attroff(COLOR_PAIR(135));
                        scanw("%d",&d);
                        noecho(); 
                        refresh(); 
                        clear();
                        if(d==a){
                            rooms[which_room].encryped_door_condition=1;
                            break;
                        }
                        if (d != a && h == 0) {
                            clear();
                            start_color();
                            init_pair(6, COLOR_YELLOW, COLOR_BLACK);
                            attron(COLOR_PAIR(6));
                            mvprintw(LINES / 2 - 3, COLS / 2 - 25, "The password you have entered is wrong! You have 2 more chances!");
                            attroff(COLOR_PAIR(6));
                            refresh();
                            napms(2000);
                        } 
                        else if (d != a && h == 1) {
                            clear();
                            start_color();
                            init_pair(7, COLOR_RED, COLOR_BLACK);
                            attron(COLOR_PAIR(7));
                            mvprintw(LINES / 2 - 3, COLS / 2 - 25, "The password you have entered is wrong! You have 1 more chance!");
                            attroff(COLOR_PAIR(7));
                            refresh();
                            napms(2000);
                        }
                    }
                }    
            }
        }
    }
}
void display_map(Room * rooms) {
    for(int y=0;y<MAP_HEIGHT;y++){
        for(int x=0;x<MAP_WIDTH;x++){
            if(map2[y][x]=='#' && (visited[y-1][x] || visited[y+1][x] || visited[y][x-1] || visited[y][x+1])){
                mvaddch(y,x,map[y][x]);
            }
            else if(map2[y][x]=='$'){
                switch (color){
                    case 0:
                        start_color();
                        init_pair(234,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(234));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(234));
                        break;
                    case 1:
                        start_color();
                        init_pair(235,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(235));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(235));
                        break;
                    case 2:
                        start_color();
                        init_pair(236,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(236));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(236));
                        break;
                }
            }
            else if((map2[y][x]=='D' || map2[y][x]=='d')&& (visited[monsters[0].y-1][monsters[0].x] || visited[monsters[0].y+1][monsters[0].x]||visited[monsters[0].y-1][monsters[0].x-1]||visited[monsters[0].y-1][monsters[0].x+1]||visited[monsters[0].y+1][monsters[0].x-1]||visited[monsters[0].y+1][monsters[0].x+1]||visited[monsters[0].y][monsters[0].x-1]||visited[monsters[0].y][monsters[0].x+1])){
                        start_color();
                        init_pair(17,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(17));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(17));
                    }
                    else if((map2[y][x]=='F' || map2[y][x]=='f') && (visited[y-1][x] || visited[y+1][x]||visited[y-1][x-1]||visited[y-1][x+1]||visited[y+1][x-1]||visited[y+1][x+1]||visited[y][x-1]||visited[y][x+1])){
                        start_color();
                        init_pair(16,COLOR_CYAN,COLOR_BLACK);
                        attron(COLOR_PAIR(16));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(16));
                    }
                    else if((map2[y][x]=='G' || map2[y][x]=='g') && (visited[y-1][x] || visited[y+1][x]||visited[y-1][x-1]||visited[y-1][x+1]||visited[y+1][x-1]||visited[y+1][x+1]||visited[y][x-1]||visited[y][x+1])){
                        start_color();
                        init_pair(18,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(18));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(18));
                    }
                    else if((map2[y][x]=='S' || map2[y][x]=='s') && (visited[y-1][x] || visited[y+1][x]||visited[y-1][x-1]||visited[y-1][x+1]||visited[y+1][x-1]||visited[y+1][x+1]||visited[y][x-1]||visited[y][x+1])){
                        start_color();
                        init_pair(19,COLOR_YELLOW,COLOR_BLACK);
                        attron(COLOR_PAIR(19));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(19));
                    }
                    else if((map2[y][x]=='U' || map2[y][x]=='u') && (visited[y-1][x] || visited[y+1][x]||visited[y-1][x-1]||visited[y-1][x+1]||visited[y+1][x-1]||visited[y+1][x+1]||visited[y][x-1]||visited[y][x+1])){
                        start_color();
                        init_pair(20,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(20));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(20));
                    }
        }
    }

    for(int  y=rooms[0].y;y<rooms[0].y+rooms[0].height;y++){
        for(int x=rooms[0].x;x<rooms[0].x+rooms[0].width;x++){
            if(map2[y][x]=='@'){
                int i;
                for(i=0;i<6;i++){
                    if(y>=rooms[i].y && y<rooms[i].y+rooms[i].height && x>=rooms[i].x && x<rooms[i].x+rooms[i].width){
                        break;
                    }
                }
                if(!rooms[i].encryped_door_condition){
                    start_color();
                    init_pair(4,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(4));
                    mvaddch(y,x,map2[y][x]);
                    attroff(COLOR_PAIR(4));
                }
                else {
                    start_color();
                    init_pair(8,COLOR_GREEN,COLOR_BLACK);
                    attron(COLOR_PAIR(8));
                    mvaddch(y,x,map2[y][x]);
                    attroff(COLOR_PAIR(8));
                }    
            }
            else if(map2[y][x]=='&'){
                start_color();
                init_pair(5,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(5));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(5));
            }
            else if(map2[y][x]=='K'){
                start_color();
                init_pair(9,COLOR_YELLOW,COLOR_BLACK);
                attron(COLOR_PAIR(9));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(9));
            }
            else if(map2[y][x]=='^'){
                start_color();
                init_pair(11,COLOR_CYAN,COLOR_BLACK);
                attron(COLOR_PAIR(11));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(11));
            }
            else if(map2[y][x]=='*'){
                start_color();
                init_pair(9,COLOR_YELLOW,COLOR_BLACK);
                attron(COLOR_PAIR(9));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(9));
            }
            else if(map2[y][x]=='!'){
                start_color();
                init_pair(12,COLOR_RED,COLOR_BLACK);
                attron(COLOR_PAIR(12));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(12));
            }
            else if(map2[y][x]=='/'){
                start_color();
                init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
                attron(COLOR_PAIR(13));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(13));
            }
            else if(map2[y][x]=='X'){
                start_color();
                init_pair(14,COLOR_GREEN,COLOR_BLACK);
                attron(COLOR_PAIR(14));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(14));
            }
            else if(map2[y][x]=='M'){
                start_color();
                init_pair(15,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(15));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(15));
            }
            else if(map2[y][x]=='N'){
                start_color();
                init_pair(16,COLOR_CYAN,COLOR_BLACK);
                attron(COLOR_PAIR(16));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(16));
            }
            else if(map2[y][x]=='D' || map2[y][x]=='d'){
                start_color();
                init_pair(17,COLOR_GREEN,COLOR_BLACK);
                attron(COLOR_PAIR(17));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(17));
            }
            else if(map2[y][x]=='F' || map2[y][x]=='f'){
                start_color();
                init_pair(16,COLOR_CYAN,COLOR_BLACK);
                attron(COLOR_PAIR(16));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(16));
            }
            else if(map2[y][x]=='G' || map2[y][x]=='g'){
                start_color();
                init_pair(18,COLOR_BLUE,COLOR_BLACK);
                attron(COLOR_PAIR(18));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(18));
            }
            else if(map2[y][x]=='S' || map2[y][x]=='s'){
                start_color();
                init_pair(19,COLOR_YELLOW,COLOR_BLACK);
                attron(COLOR_PAIR(19));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(19));
            }
            else if(map2[y][x]=='U' || map2[y][x]=='u'){
                start_color();
                init_pair(20,COLOR_RED,COLOR_BLACK);
                attron(COLOR_PAIR(20));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(20));
            }
            else if(map2[y][x]=='W' || map2[y][x]=='Q' || map2[y][x]=='T' || map2[y][x]=='Y' ){
                start_color();
                init_pair(232,COLOR_MAGENTA,COLOR_BLACK);
                attron(COLOR_PAIR(232));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(232));
            }
            // else if(map2[y][x]=='#' && (visited[y-1][x] || visited[y+1][x] || visited[y][x-1] || visited[y][x+1])){
            //     mvaddch(y,x,map2[y][x]);
            // }
            else if(map2[y][x]=='H' || map2[y][x]=='%' || map2[y][x]=='='){
                start_color();
                init_pair(233,COLOR_GREEN,COLOR_BLACK);
                attron(COLOR_PAIR(233));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(233));
            }
            else if(map2[y][x]=='$'){
                switch (color){
                    case 0:
                        start_color();
                        init_pair(234,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(234));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(234));
                        break;
                    case 1:
                        start_color();
                        init_pair(235,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(235));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(235));
                        break;
                    case 2:
                        start_color();
                        init_pair(236,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(236));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(236));
                        break;
                }
            }
            else if(map2[y][x]=='.' || map2[y][x]=='_' || map2[y][x]=='|' || map2[y][x]=='O'){
                start_color();
                init_pair(142,COLOR_MAGENTA,COLOR_BLACK);
                attron(COLOR_PAIR(142));
                mvaddch(y,x,map2[y][x]);
                attroff(COLOR_PAIR(142));
            }
            else 
                mvaddch(y,x,map2[y][x]);
        }
    }
    for(int i=1;i<6;i++){
        if(visited[rooms[i].doors[0][1]-1][rooms[i].doors[0][0]] || visited[rooms[i].doors[0][1]+1][rooms[i].doors[0][0]] || visited[rooms[i].doors[0][1]][rooms[i].doors[0][0]+1] || visited[rooms[i].doors[0][1]][rooms[i].doors[0][0]-1] || visited[rooms[i].doors[1][1]-1][rooms[i].doors[1][0]] || visited[rooms[i].doors[1][1]+1][rooms[i].doors[1][0]] || visited[rooms[i].doors[1][1]][rooms[i].doors[1][0]-1] || visited[rooms[i].doors[1][1]][rooms[i].doors[1][0]+1] || visited[rooms[i].doors[2][1]][rooms[i].doors[2][0]]){
    
            for (int y = rooms[i].y; y < rooms[i].y+rooms[i].height; y++) {
                for (int x = rooms[i].x; x < rooms[i].x+rooms[i].width; x++) {
                    if(map2[y][x]=='@'){
                        int i;
                        for(i=0;i<6;i++){
                            if(y>=rooms[i].y && y<rooms[i].y+rooms[i].height && x>=rooms[i].x && x<rooms[i].x+rooms[i].width){
                                break;
                            }
                        }
                        if(!rooms[i].encryped_door_condition){
                            start_color();
                            init_pair(4,COLOR_RED,COLOR_BLACK);
                            attron(COLOR_PAIR(4));
                            mvaddch(y,x,map2[y][x]);
                            attroff(COLOR_PAIR(4));
                        }
                        else {
                            start_color();
                            init_pair(8,COLOR_GREEN,COLOR_BLACK);
                            attron(COLOR_PAIR(8));
                            mvaddch(y,x,map2[y][x]);
                            attroff(COLOR_PAIR(8));
                        }    
                    }
                    else if(map2[y][x]=='&'){
                        start_color();
                        init_pair(5,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(5));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(5));
                    }
                    else if(map2[y][x]=='K'){
                        start_color();
                        init_pair(9,COLOR_YELLOW,COLOR_BLACK);
                        attron(COLOR_PAIR(9));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(9));
                    }
                    else if(map2[y][x]=='^'){
                        start_color();
                        init_pair(11,COLOR_CYAN,COLOR_BLACK);
                        attron(COLOR_PAIR(11));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(11));
                    }
                    else if(map2[y][x]=='*'){
                        start_color();
                        init_pair(9,COLOR_YELLOW,COLOR_BLACK);
                        attron(COLOR_PAIR(9));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(9));
                    }
                    else if(map2[y][x]=='!'){
                        start_color();
                        init_pair(12,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(12));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(12));
                    }
                    else if(map2[y][x]=='/'){
                        start_color();
                        init_pair(13,COLOR_MAGENTA,COLOR_BLACK);
                        attron(COLOR_PAIR(13));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(13));
                    }
                    else if(map2[y][x]=='X'){
                        start_color();
                        init_pair(14,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(14));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(14));
                    }
                    else if(map2[y][x]=='M'){
                        start_color();
                        init_pair(15,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(15));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(15));
                    }
                    else if(map2[y][x]=='N'){
                        start_color();
                        init_pair(16,COLOR_CYAN,COLOR_BLACK);
                        attron(COLOR_PAIR(16));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(16));
                    }
                    else if(map2[y][x]=='D' || map2[y][x]=='d'){
                        start_color();
                        init_pair(17,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(17));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(17));
                    }
                    else if(map2[y][x]=='F' || map2[y][x]=='f'){
                        start_color();
                        init_pair(16,COLOR_CYAN,COLOR_BLACK);
                        attron(COLOR_PAIR(16));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(16));
                    }
                    else if(map2[y][x]=='G' || map2[y][x]=='g'){
                        start_color();
                        init_pair(18,COLOR_BLUE,COLOR_BLACK);
                        attron(COLOR_PAIR(18));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(18));
                    }
                    else if(map2[y][x]=='S' || map2[y][x]=='s'){
                        start_color();
                        init_pair(19,COLOR_YELLOW,COLOR_BLACK);
                        attron(COLOR_PAIR(19));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(19));
                    }
                    else if(map2[y][x]=='U' || map2[y][x]=='u'){
                        start_color();
                        init_pair(20,COLOR_RED,COLOR_BLACK);
                        attron(COLOR_PAIR(20));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(20));
                    }
                    else if(map2[y][x]=='W'){
                        start_color();
                        init_pair(232,COLOR_MAGENTA,COLOR_BLACK);
                        attron(COLOR_PAIR(232));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(232));
                    }
                    // else if(map2[y][x]=='#' && (visited[y-1][x] || visited[y+1][x] || visited[y][x-1] || visited[y][x+1])){
                    //     mvaddch(y,x,map2[y][x]);
                    // }
                    else if(map2[y][x]=='H' || map2[y][x]=='%' || map2[y][x]=='='){
                        start_color();
                        init_pair(233,COLOR_GREEN,COLOR_BLACK);
                        attron(COLOR_PAIR(233));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(233));
                    }
                    else if(map2[y][x]=='$'){
                        switch (color){
                            case 0:
                                start_color();
                                init_pair(234,COLOR_RED,COLOR_BLACK);
                                attron(COLOR_PAIR(234));
                                mvaddch(y,x,map2[y][x]);
                                attroff(COLOR_PAIR(234));
                                break;
                            case 1:
                                start_color();
                                init_pair(235,COLOR_GREEN,COLOR_BLACK);
                                attron(COLOR_PAIR(235));
                                mvaddch(y,x,map2[y][x]);
                                attroff(COLOR_PAIR(235));
                                break;
                            case 2:
                                start_color();
                                init_pair(236,COLOR_BLUE,COLOR_BLACK);
                                attron(COLOR_PAIR(236));
                                mvaddch(y,x,map2[y][x]);
                                attroff(COLOR_PAIR(236));
                                break;
                        }
                    }
                    else if(map2[y][x]=='.' || map2[y][x]=='_' || map2[y][x]=='|' || map2[y][x]=='O'){
                        start_color();
                        init_pair(142,COLOR_MAGENTA,COLOR_BLACK);
                        attron(COLOR_PAIR(142));
                        mvaddch(y,x,map2[y][x]);
                        attroff(COLOR_PAIR(142));
                    }
                    else 
                        mvaddch(y,x,map2[y][x]);
                }
            }
        }    
    }    
}
void display_map2(Room rooms){
    start_color();
    init_pair(18,COLOR_CYAN,COLOR_BLACK);
    attron(COLOR_PAIR(18));
    for(int i=rooms.y;i<rooms.y+rooms.height;i++){
        for(int j=rooms.x;j<rooms.x+rooms.width;j++){
            if(map2[i][j]=='.' || map2[i][j]=='|' || map2[i][j]=='_' || map2[i][j]=='O')
                mvaddch(i,j,map2[i][j]);
        }
    }
    attroff(COLOR_PAIR(18));
}
void hiding_map(char map[][150]){
    display_map2(rooms[0]);
    // mvprintw(2,2,"<%d> <%d>",user.y,user.x);
    // mvprintw(3,3,"%d %d",rooms[0].doors[0][0],rooms[0].doors[0][1]); 
    if(user.y>rooms[0].doors[0][1] && user.y<=rooms[1].doors[0][1]){
        int x=rooms[0].doors[0][0] > rooms[1].doors[0][0] ? rooms[0].doors[0][0] : rooms[1].doors[0][0];
        int y= rooms[0].doors[0][0] < rooms[1].doors[0][0] ? rooms[0].doors[0][0]  : rooms[1].doors[0][0];
        mvprintw(2,2,"%d %d",rooms[0].doors[0][0],y);
        if(user.x>=y && user.x<=x){
            int c=0;
            for(int i=user.y-1;i<user.y+2;i++){
                for(int j=user.x-1;j<user.x+2;j++){
                    mvprintw(i,j,"%c",map2[i][j]);
                    if(map[i][j]=='+' && i!=user.y-1){
                        c=1;
                        break; 
                    }     
                }
                if(c)
                    break;
            }
        }    
    }    
    if(user.y>=rooms[1].doors[0][1]  && user.x<rooms[1].x+rooms[1].width ){
        // mvprintw(4,4,"gs");
        display_map2(rooms[1]);
    }
    if(user.x>rooms[1].doors[1][0] && user.x<=rooms[3].doors[2][0] ){
        int x=rooms[1].doors[1][1]>=rooms[3].doors[2][1] ? rooms[1].doors[1][1]:rooms[3].doors[2][1]; 
        int y=rooms[1].doors[1][1]<=rooms[3].doors[2][1] ? rooms[1].doors[1][1]:rooms[3].doors[2][1];
        int c=0;
        if(user.y>=y && user.y<=x){
            mvprintw(2,2,"help");
            for(int i=user.y-1;i<user.y+2;i++){
                for(int j=user.x-1;j<user.x+2;j++){
                    mvaddch(i,j,map2[i][j]);
                    if(map[i][j]=='+' && i!=user.x){
                        c=1;
                        break; 
                    }     
                }
                if(c)
                    break;
            }
        }    
    }    
    if(user.x>=rooms[3].doors[2][0] && user.x<=rooms[3].x+rooms[3].width-1 && user.y>=rooms[3].y){
        // mvprintw(4,4,"gs");
        display_map2(rooms[3]);
    }
    
}
void making_pillar(Room * rooms){
    srand(time(NULL));
    for(int i=0;i<6;i++){
        rooms[i].pillar.x=rand()%(rooms[i].width-2) + rooms[i].x+1;
        rooms[i].pillar.y=rand()%(rooms[i].height-2)+ rooms[i].y+1;
        if((rooms[i].pillar.x==rooms[i].trap.x  &&  rooms[i].pillar.y==rooms[i].trap.y) || map[rooms[i].pillar.y][rooms[i].pillar.x]=='&')
            i--;
        else{  
            map[rooms[i].pillar.y][rooms[i].pillar.x]='O'; 
            map2[rooms[i].pillar.y][rooms[i].pillar.x]='O'; 
        }    
    }
}
void stairs(Room *rooms){
    srand(time(NULL));
    int a=1;
    while(a){
        int i=rand()%5+1;
        int st_x=rand()%(rooms[i].width-2)+rooms[i].x+1;
        int st_y=rand()%(rooms[i].height-2)+rooms[i].y+1;
        if(map2[st_y][st_x]=='O' || map2[st_y][st_x]=='^' || map2[st_y][st_x]=='@' || map2[st_y][st_x]=='&')
            a=1;
        else {
            map[st_y][st_x]='<';
            map2[st_y][st_x]='<';
            a=0;
        }    
    }
}
void encryped_door(Room *rooms){
    int a=1;
    srand(time(NULL));
    int i1=rand()%3;
    switch(i1){
        case 1:
            map[rooms[0].doors[0][1]][rooms[0].doors[0][0]]='@';
            map2[rooms[0].doors[0][1]][rooms[0].doors[0][0]]='@';
            rooms[0].is_there_encryped_door=1;
            break;
        case 2:
            map[rooms[0].doors[1][1]][rooms[0].doors[1][0]]='@';
            map2[rooms[0].doors[1][1]][rooms[0].doors[1][0]]='@';
            rooms[0].is_there_encryped_door=1;
            break;
    }
    int i2=rand()%3;
    switch(i2){
        // case 1:
        //     map[rooms[1].doors[0][1]][rooms[1].doors[0][0]]='@';
        //     map2[rooms[1].doors[0][1]][rooms[1].doors[0][0]]='@';
        //     rooms[1].is_there_encryped_door=1;
        //     break;
        case 2:
            map[rooms[1].doors[1][1]][rooms[1].doors[1][0]]='@';
            map2[rooms[1].doors[1][1]][rooms[1].doors[1][0]]='@';
            rooms[1].is_there_encryped_door=1;
            break;
    }
    int i5=rand()%3;
    switch(i5){
        case 1:
            map[rooms[4].doors[0][1]][rooms[4].doors[0][0]]='@';
            map2[rooms[4].doors[0][1]][rooms[4].doors[0][0]]='@';
            rooms[4].is_there_encryped_door=1;
            break;
        case 2:
            map[rooms[4].doors[1][1]][rooms[4].doors[1][0]]='@';
            map2[rooms[4].doors[1][1]][rooms[4].doors[1][0]]='@';
            rooms[4].is_there_encryped_door=1;
            break;
    }
    int i6=rand()%3;
    switch(i6){
        case 1:
            map[rooms[5].doors[0][1]][rooms[5].doors[0][0]]='@';
            map2[rooms[5].doors[0][1]][rooms[5].doors[0][0]]='@';
            rooms[5].is_there_encryped_door=1;
            break;
        case 2:
            map[rooms[5].doors[1][1]][rooms[5].doors[1][0]]='@';
            map2[rooms[5].doors[1][1]][rooms[5].doors[1][0]]='@';
            rooms[5].is_there_encryped_door=1;
            break;
    }
    int i3=rand()%4;
    switch(i3){
        case 1:
            map[rooms[2].doors[0][1]][rooms[2].doors[0][0]]='@';
            map2[rooms[2].doors[0][1]][rooms[2].doors[0][0]]='@';
            rooms[2].is_there_encryped_door=1;
            break;
        case 2:
            map[rooms[2].doors[1][1]][rooms[2].doors[1][0]]='@';
            map2[rooms[2].doors[1][1]][rooms[2].doors[1][0]]='@';
            rooms[2].is_there_encryped_door=1;
            break;
        // case 3:
        //     map[rooms[2].doors[2][1]][rooms[2].doors[2][0]]='@';
        //     map2[rooms[2].doors[2][1]][rooms[2].doors[2][0]]='@';
        //     rooms[2].is_there_encryped_door=1;
        //     break;
    }
   int i4=rand()%4;
    switch(i4){
        case 1:
            map[rooms[3].doors[0][1]][rooms[3].doors[0][0]]='@';
            map2[rooms[3].doors[0][1]][rooms[3].doors[0][0]]='@';
            rooms[3].is_there_encryped_door=1;
            break;
        case 2:
            map[rooms[3].doors[1][1]][rooms[3].doors[1][0]]='@';
            map2[rooms[3].doors[1][1]][rooms[3].doors[1][0]]='@';
            rooms[3].is_there_encryped_door=1;
            break;
        case 3:
            map[rooms[3].doors[2][1]][rooms[3].doors[2][0]]='@';
            map2[rooms[3].doors[2][1]][rooms[3].doors[2][0]]='@';
            rooms[3].is_there_encryped_door=1;
            break;
    }
    if(map[rooms[0].doors[0][1]][rooms[0].doors[0][0]]=='@' || map[rooms[0].doors[1][1]][rooms[0].doors[1][0]]=='@'){
        int j1=rand()%3+1;
        switch(j1){
            case 1:
                map[rooms[0].y+1][rooms[0].x+rooms[0].width-2]='&';
                map2[rooms[0].y+1][rooms[0].x+rooms[0].width-2]='&';
                break;
            case 2:
                map[rooms[0].y+rooms[0].height-2][rooms[0].x+rooms[0].width-2]='&';
                map2[rooms[0].y+rooms[0].height-2][rooms[0].x+rooms[0].width-2]='&';
                break;     
            case 3:
                map[rooms[0].y+rooms[0].height-2][rooms[0].x+1]='&';
                map2[rooms[0].y+rooms[0].height-2][rooms[0].x+1]='&';
                break;    
        }
    }
    if(map[rooms[1].doors[0][1]][rooms[1].doors[0][0]]=='@' || map[rooms[1].doors[1][1]][rooms[1].doors[1][0]]=='@'){
        int j2=rand()%4+1;
        switch(j2){
            case 1:
                map[rooms[1].y+1][rooms[1].x+rooms[1].width-2]='&';
                map2[rooms[1].y+1][rooms[1].x+rooms[1].width-2]='&';
                break;
            case 2:
                map[rooms[1].y+rooms[1].height-2][rooms[1].x+rooms[1].width-2]='&';
                map2[rooms[1].y+rooms[1].height-2][rooms[1].x+rooms[1].width-2]='&';
                break;     
            case 3:
                map[rooms[1].y+rooms[1].height-2][rooms[1].x+1]='&';
                map2[rooms[1].y+rooms[1].height-2][rooms[1].x+1]='&';
                break; 
            case 4:
                map[rooms[1].y+1][rooms[1].x+1]='&';
                map2[rooms[1].y+1][rooms[1].x+1]='&';
                break;       
        }
    }
    if(map[rooms[4].doors[0][1]][rooms[4].doors[0][0]]=='@' || map[rooms[4].doors[1][1]][rooms[4].doors[1][0]]=='@'){
        int j5=rand()%4+1;
        switch(j5){
            case 1:
                map[rooms[4].y+1][rooms[4].x+rooms[4].width-2]='&';
                map2[rooms[4].y+1][rooms[4].x+rooms[4].width-2]='&';
                break;
            case 2:
                map[rooms[4].y+rooms[4].height-2][rooms[4].x+rooms[4].width-2]='&';
                map2[rooms[4].y+rooms[4].height-2][rooms[4].x+rooms[4].width-2]='&';
                break;     
            case 3:
                map[rooms[4].y+rooms[4].height-2][rooms[4].x+1]='&';
                map2[rooms[4].y+rooms[4].height-2][rooms[4].x+1]='&';
                break; 
            case 4:
                map[rooms[4].y+1][rooms[4].x+1]='&';
                map2[rooms[4].y+1][rooms[4].x+1]='&';
                break;       
        }
    }if(map[rooms[5].doors[0][1]][rooms[5].doors[0][0]]=='@' || map[rooms[5].doors[1][1]][rooms[5].doors[1][0]]=='@'){
        int j6=rand()%4+1;
        switch(j6){
            case 1:
                map[rooms[5].y+1][rooms[5].x+rooms[5].width-2]='&';
                map2[rooms[5].y+1][rooms[5].x+rooms[5].width-2]='&';
                break;
            case 2:
                map[rooms[5].y+rooms[5].height-2][rooms[5].x+rooms[5].width-2]='&';
                map2[rooms[5].y+rooms[5].height-2][rooms[5].x+rooms[5].width-2]='&';
                break;     
            case 3:
                map[rooms[5].y+rooms[5].height-2][rooms[5].x+1]='&';
                map2[rooms[5].y+rooms[5].height-2][rooms[5].x+1]='&';
                break; 
            case 4:
                map[rooms[5].y+1][rooms[5].x+1]='&';
                map2[rooms[5].y+1][rooms[5].x+1]='&';
                break;       
        }
    }
    if(map[rooms[2].doors[0][1]][rooms[2].doors[0][0]]=='@' || map[rooms[2].doors[1][1]][rooms[2].doors[1][0]]=='@' || map[rooms[2].doors[2][1]][rooms[2].doors[2][0]]=='@'){
        int j3=rand()%4+1;
        switch(j3){
            case 1:
                map[rooms[2].y+1][rooms[2].x+rooms[2].width-2]='&';
                map2[rooms[2].y+1][rooms[2].x+rooms[2].width-2]='&';
                break;
            case 2:
                map[rooms[2].y+rooms[2].height-2][rooms[2].x+rooms[2].width-2]='&';
                map2[rooms[2].y+rooms[2].height-2][rooms[2].x+rooms[2].width-2]='&';
                break;     
            case 3:
                map[rooms[2].y+rooms[2].height-2][rooms[2].x+1]='&';
                map2[rooms[2].y+rooms[2].height-2][rooms[2].x+1]='&';
                break; 
            case 4:
                map[rooms[2].y+1][rooms[2].x+1]='&';
                map2[rooms[2].y+1][rooms[2].x+1]='&';
                break;       
        }
    }
    if(map[rooms[3].doors[0][1]][rooms[3].doors[0][0]]=='@' || map[rooms[3].doors[1][1]][rooms[3].doors[1][0]]=='@' || map[rooms[3].doors[2][1]][rooms[3].doors[2][0]]=='@'){
        int j4=rand()%4+1;
        switch(j4){
            case 1:
                map[rooms[3].y+1][rooms[3].x+rooms[3].width-2]='&';
                map2[rooms[3].y+1][rooms[3].x+rooms[3].width-2]='&';
                break;
            case 2:
                map[rooms[3].y+rooms[3].height-2][rooms[3].x+rooms[3].width-2]='&';
                map2[rooms[3].y+rooms[3].height-2][rooms[3].x+rooms[3].width-2]='&';
                break;     
            case 3:
                map[rooms[3].y+rooms[3].height-2][rooms[3].x+1]='&';
                map2[rooms[3].y+rooms[3].height-2][rooms[3].x+1]='&';
                break; 
            case 4:
                map[rooms[3].y+1][rooms[3].x+1]='&';
                map2[rooms[3].y+1][rooms[3].x+1]='&';
                break;       
        }
    }
    for(int u=0;u<6;u++){
        rooms[u].encryped_door_condition=0;
    }
    if(map[rooms[1].doors[0][1]][rooms[1].doors[0][0]]=='@'  &&  map[rooms[2].doors[2][1]][rooms[2].doors[2][0]]=='@'){
       map[rooms[1].doors[0][1]][rooms[1].doors[0][0]]=='+'; 
       rooms[1].is_there_encryped_door=0;
    }
    if(map[rooms[2].doors[2][1]][rooms[2].doors[2][0]]=='@'  &&  map[rooms[3].doors[2][1]][rooms[3].doors[2][0]]=='@'){
       map[rooms[3].doors[2][1]][rooms[3].doors[2][0]]=='+'; 
       rooms[3].is_there_encryped_door=0;
    }
}
int encrypting(){
    srand(time(NULL));
    int a=(rand()%9 +1)*1000 + (rand()%10)*100 + (rand()%10)*10 + rand()%10;
    return a;
}
void ancient_key(Room* rooms){
    srand(time(NULL));
    for(int i=0;i<6;i++){
        if(rooms[i].is_there_encryped_door){
            int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
            int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
            if(map[y][x]=='O' || map[y][x]=='&' || (x==rooms[i].trap.x && y==rooms[i].trap.y) || map[y][x]=='<' )
                i--;
            else{
                map[y][x]='K';
                map2[y][x]='K';
            }
        }
    }
}
int next_floor(){
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(map[i][j]=='<' && map2[i][j]=='$'){
                char a=getch();
                if(a=='>'){
                    return 1;
                }
            }
        }
    }
    return 0;
}
void show_message(const char *message) {
    int height = 3, width = 60;
    int start_y = 0, start_x = 3; 
    start_color();
    init_pair(11,COLOR_YELLOW,COLOR_BLACK);
    WINDOW *msg_win = newwin(height, width, start_y, start_x);
    box(msg_win, 0, 0); 
    wattron(msg_win, COLOR_PAIR(11));
    mvwprintw(msg_win, 1, (width - strlen(message)) / 2, "%s", message);
    wattroff(msg_win, COLOR_PAIR(11));
    wrefresh(msg_win);  
    napms(2000); 
    werase(msg_win);
    wrefresh(msg_win);
    delwin(msg_win); 
}
void show_message2(const char* message,int a){
    int height = 3, width = 60;
    int start_y = 0, start_x = 3; 
    start_color();
    init_pair(11,COLOR_YELLOW,COLOR_BLACK);
    WINDOW *msg_win = newwin(height, width, start_y, start_x);
    box(msg_win, 0, 0); 
    wattron(msg_win, COLOR_PAIR(11));
    mvwprintw(msg_win, 1, (width - strlen(message)) / 2, "%s%d", message,a);
    wattroff(msg_win, COLOR_PAIR(11));
    wrefresh(msg_win);  
    napms(1000); 
    werase(msg_win);
    wrefresh(msg_win);
    delwin(msg_win); 
}
void show_message3(const char* message,int a){
    int height = 5, width = 5;
    int start_y = 0, start_x = COLS-5; 
    start_color();
    init_pair(11,COLOR_YELLOW,COLOR_BLACK);
    WINDOW *msg_win = newwin(height, width, start_y, start_x);
    box(msg_win, 0, 0); 
    wattron(msg_win, COLOR_PAIR(11));
    mvwprintw(msg_win, 1, (width - strlen(message)) / 2, "%s%d", message,a);
    wattroff(msg_win, COLOR_PAIR(11));
    wrefresh(msg_win);  
    napms(1000); 
    werase(msg_win);
    wrefresh(msg_win);
    delwin(msg_win); 
}
void gold(Room * rooms,player*user,int a){

    user->golds=a;
    srand(time(NULL));
    for(int i=0;i<6;i++){
        int k=rand()%2;
        switch(k){
            case 0:
                break;
            case 1:
                int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                if(map[y][x]=='&' || map[y][x]=='<' || map[y][x]=='O' || (y==rooms[i].trap.y && x==rooms[i].trap.x))
                    i--;
                else{
                    map[y][x]='*';
                    map2[y][x]='*';
                }
                break;
        }
    }
    for(int i=0;i<6;i++){
        int k=rand()%2;
        switch(k){
            case 0:
                break;
            case 1:
                int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                if(map[y][x]=='&' || map[y][x]=='<' || map[y][x]=='O' || (y==rooms[i].trap.y && x==rooms[i].trap.x))
                    i--;
                else{
                    map[y][x]='*';
                    map2[y][x]='*';
                }
                break;
        }
    }
    for(int i=0;i<6;i++){
        int k=rand()%2;
        switch(k){
            case 0:
                break;
            case 1:
                int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                if(map[y][x]=='&' || map[y][x]=='<' || map[y][x]=='O' || (y==rooms[i].trap.y && x==rooms[i].trap.x))
                    i--;
                else{
                    map[y][x]='*';
                    map2[y][x]='*';
                }
                break;
        }
    }
    int i=rand()%2 +1;
    switch(i){
        case 1:
            int h=rand()%6;
            while(1){
                int x=rand()%(rooms[h].width-2)+rooms[h].x+1;
                int y=rand()%(rooms[h].height-2)+rooms[h].y+1;
                if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[i].trap.y || x!=rooms[i].trap.x)&& map[y][x]!='*'){
                    map[y][x]='!';
                    map2[y][x]='!';
                    break;
                }
                    
            }
            break;
        case 2:
            for(int j=0;j<2;j++){
                int h=rand()%6;
                while(1){
                    int x=rand()%(rooms[h].width-2)+rooms[h].x+1;
                    int y=rand()%(rooms[h].height-2)+rooms[h].y+1;
                    if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[i].trap.y || x!=rooms[i].trap.x)&& map[y][x]!='*'){
                        map[y][x]='!';
                        map2[y][x]='!';
                        break;
                    }
                }
            }
            break;
    }
}
void guns(Room* rooms,player* user,int* a){
    srand(time(NULL));
    for(int i=1;i<5;i++){
        user->gun[i].collects=a[i-1];
    }
    user->gun[0].damage=5;
    user->gun[1].damage=12;
    user->gun[2].damage=15;
    user->gun[3].damage=5;
    user->gun[4].damage=10;
    user->gun[0].collects=0;
    user->gun[1].collects=0;
    user->gun[2].collects=0;
    user->gun[3].collects=0;
    user->gun[4].collects=0;
    int h1=rand()%6;
    while(1){
        int x=rand()%(rooms[h1].width-2)+rooms[h1].x+1;
        int y=rand()%(rooms[h1].height-2)+rooms[h1].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h1].trap.y || x!=rooms[h1].trap.x)&& map[y][x]!='*' && map[y][x]!='!' ){
            map[y][x]='X';
            map2[y][x]='X';
            break;
        }
    }
    int h2;
    while(1){
        h2=rand()%6;
        if(h2!=h1)
            break;
    }
    while(1){
        int x=rand()%(rooms[h2].width-2)+rooms[h2].x+1;
        int y=rand()%(rooms[h2].height-2)+rooms[h2].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h2].trap.y || x!=rooms[h2].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x'){
            map[y][x]='M';
            map2[y][x]='M';
            break;
        }
    }
    int h3;
    while(1){
        h3=rand()%6;
        if(h3!=h1 && h3!=h2)
            break;
    }
    while(1){
        int x=rand()%(rooms[h3].width-2)+rooms[h3].x+1;
        int y=rand()%(rooms[h3].height-2)+rooms[h3].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h3].trap.y || x!=rooms[h3].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M'){
            map[y][x]='N';
            map2[y][x]='N';
            break;
        }
    }
    int h4;
    while(1){
        h4=rand()%6;
        if(h4!=h1 && h4!=h2 && h4!=h3)
            break;
    }
    while(1){
        int x=rand()%(rooms[h4].width-2)+rooms[h4].x+1;
        int y=rand()%(rooms[h4].height-2)+rooms[h4].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h4].trap.y || x!=rooms[h4].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N'){
            map[y][x]='/';
            map2[y][x]='/';
            break;
        }
    }
}
int picking(){
    // clear();
    // mvprintw(LINES/2-3,COLS/2-15,"if you want to pick it press enter");
    // napms(2000);
    show_message("if you want to pick it press enter");
    char a=getch();
    if(a==10)
        return 1;
    return 0;
}
void gun_menu(player* user){
    int vn=0;
    curs_set(0);
    keypad(stdscr, TRUE);
    
    start_color();
    init_pair(102, COLOR_BLUE, COLOR_BLACK);
    init_pair(103, COLOR_BLACK, COLOR_BLUE);
    init_pair(104, COLOR_GREEN, COLOR_BLACK);

    while(1){
        clear(); 
        switch (user->whicch_weapom_is_being_used){
        case 1:
            mvprintw(LINES/2-6,COLS/2-16,"*");
            refresh();
            break;
        case 2:
            mvprintw(LINES/2-2,COLS/2-16,"*");
            break;
        case 3:
            mvprintw(LINES/2-1,COLS/2-16,"*");
            break;
        case 4:
            mvprintw(LINES/2,COLS/2-16,"*");
            break;
        case 5:
            mvprintw(LINES/2-5,COLS/2-16,"*");
            break;
    } 
        attron(COLOR_PAIR(104));
        mvprintw(LINES/2-6, COLS/2-28, "short range:");
        attroff(COLOR_PAIR(104));
        attron(COLOR_PAIR(104));
        mvprintw(LINES/2-2, COLS/2-28, "dose range:");
        attroff(COLOR_PAIR(104));
        attron(COLOR_PAIR(102));
        mvprintw(LINES/2-6, COLS/2-15, "Mace    number:-   damage:%d",user->gun[0].damage);
        mvprintw(LINES/2-5, COLS/2-15, "sword   number:-   damage:%d",user->gun[4].damage);
        mvprintw(LINES/2-2, COLS/2-15, "Dagger  number:%d   damage:%d",user->gun[1].collects,user->gun[1].damage);
        mvprintw(LINES/2-1, COLS/2-15, "Magic Wand  number:%d   damage:%d",user->gun[2].collects,user->gun[2].damage);
        mvprintw(LINES/2, COLS/2-15, "Normal Arrow  number:%d   damage:%d",user->gun[3].collects,user->gun[3].damage);
        attroff(COLOR_PAIR(102));
        attron(COLOR_PAIR(103));
        if(vn == 0) mvprintw(LINES/2-6, COLS/2-15, "Mace    number:-   damage:%d",user->gun[0].damage);
        if(vn == 1) mvprintw(LINES/2-5, COLS/2-15, "sword   number:-   damage:%d",user->gun[4].damage);
        if(vn == 2) mvprintw(LINES/2-2, COLS/2-15, "Dagger  number:%d   damage:%d",user->gun[1].collects,user->gun[1].damage);
        if(vn == 3) mvprintw(LINES/2-1, COLS/2-15,  "Magic Wand  number:%d   damage:%d",user->gun[2].collects,user->gun[2].damage);
        if(vn == 4) mvprintw(LINES/2, COLS/2-15,  "Normal Arrow  number:%d   damage:%d",user->gun[3].collects,user->gun[3].damage);
        attroff(COLOR_PAIR(103));

        refresh();

        int a = getch();
        if(a == KEY_DOWN && vn < 4) vn++;
        else if(a == KEY_UP && vn > 0) vn--;
        else if(a == 10) {
            clear();
            if(!user->whicch_weapom_is_being_used){
                if(vn==0 )
                    user->whicch_weapom_is_being_used= vn + 1;
                else if(vn==1)
                    user->whicch_weapom_is_being_used= 5;
                else if(vn==2 && user->gun[1].collects!=0)
                    user->whicch_weapom_is_being_used= vn;
                else if(vn==3 && user->gun[2].collects!=0)
                    user->whicch_weapom_is_being_used= vn ;
                else if(vn==4 && user->gun[3].collects!=0)
                    user->whicch_weapom_is_being_used= vn ;

                return;
            }
            else{
                clear();
                mvprintw(LINES/2-3,COLS/2-20,"you already have weapon put it down to pick another");
                refresh();
                napms(3000);
                clear();
                return;
            }    
        } 
        else if(a=='i' || a=='I'){
            clear();
            return; 
        }    
    }
}
void putting_monsters(Room * rooms,Monster* monsters,int floor){
    
    monsters[0].damage=7;
    monsters[0].life=5;
    monsters[0].type='D';
    monsters[1].damage=9;
    monsters[1].life=10;
    monsters[1].type='F';
    monsters[1].range=5;
    monsters[2].damage=11;
    monsters[2].life=15;
    monsters[2].type='G';
    monsters[2].range=10;
    monsters[3].damage=13;
    monsters[3].life=20;
    monsters[3].type='S';
    monsters[3].range=5;
    monsters[4].damage=15;
    monsters[4].life=30;
    monsters[4].type='U';
    /////////////////////
    monsters[5].damage=5;
    monsters[5].life=5;
    monsters[5].type='d';
    monsters[6].damage=7;
    monsters[6].life=10;
    monsters[6].type='f';
    monsters[6].range=5;
    monsters[7].damage=9;
    monsters[7].life=15;
    monsters[7].type='g';
    monsters[7].range=10;
    monsters[8].damage=11;
    monsters[8].life=20;
    monsters[8].type='s';
    monsters[8].range=5;
    monsters[9].damage=13;
    monsters[9].life=30;
    monsters[9].type='u';
    int h1=rand()%5+1;
    while(1){
        int x=rand()%(rooms[h1].width-2)+rooms[h1].x+1;
        int y=rand()%(rooms[h1].height-2)+rooms[h1].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h1].trap.y || x!=rooms[h1].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/'){
            map[y][x]='D';
            map2[y][x]='D';
            monsters[0].x=x;
            monsters[0].y=y;
            break;
        }
    }
    int h2;
    while(1){
        h2=rand()%5+1;
        if(h2!=h1)
            break;
    }
    while(1){
        int x=rand()%(rooms[h2].width-2)+rooms[h2].x+1;
        int y=rand()%(rooms[h2].height-2)+rooms[h2].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h2].trap.y || x!=rooms[h2].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/'){
            map[y][x]='F';
            map2[y][x]='F';
            monsters[1].x=x;
            monsters[1].y=y;
            break;
        }
    }
    int h3;
    while(1){
        h3=rand()%5+1;
        if(h3!=h1 && h3!=h2)
            break;
    }
    while(1){
        int x=rand()%(rooms[h3].width-2)+rooms[h3].x+1;
        int y=rand()%(rooms[h3].height-2)+rooms[h3].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h3].trap.y || x!=rooms[h3].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/'){
            map[y][x]='G';
            map2[y][x]='G';
            monsters[2].x=x;
            monsters[2].y=y;
            break;
        }
    }
    int h4;
    while(1){
        h4=rand()%5+1;
        if(h4!=h1 && h4!=h2 && h4!=h3)
            break;
    }
    while(1){
        int x=rand()%(rooms[h4].width-2)+rooms[h4].x+1;
        int y=rand()%(rooms[h4].height-2)+rooms[h4].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h4].trap.y || x!=rooms[h4].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/'){
            map[y][x]='S';
            map2[y][x]='S';
            monsters[3].x=x;
            monsters[3].y=y;
            break;
        }
    }
    int h5;
    while(1){
        h5=rand()%5+1;
        if(h5!=h1 && h5!=h2 && h5!=h3 )
            break;
    }
    while(1){
        int x=rand()%(rooms[h5].width-2)+rooms[h5].x+1;
        int y=rand()%(rooms[h5].height-2)+rooms[h5].y+1;
        if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h5].trap.y || x!=rooms[h5].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/'){
            map[y][x]='U';
            map2[y][x]='U';
            monsters[4].x=x;
            monsters[4].y=y;
            break;
        }
    }
    
    if(floor>=2){
        int h6;
        while(1){
            h6=rand()%5+1;
            if(h6!=h1 && h6!=h2 && h6!=h3 && h6!=h4)
                break;
        }
        while(1){
            int x=rand()%(rooms[h6].width-2)+rooms[h6].x+1;
            int y=rand()%(rooms[h6].height-2)+rooms[h6].y+1;
            if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h6].trap.y || x!=rooms[h6].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/' && map[y][x]!='D' && map[y][x]!='F' && map[y][x]!='U' && map[y][x]!='S' && map[y][x]!='G'){
                map[y][x]='d';
                map2[y][x]='d';
                monsters[5].x=x;
                monsters[5].y=y;
                break;
            }
        }
        int h7;
        while(1){
            h7=rand()%5+1;
            if(h7!=h1 && h7!=h2 && h7!=h3 && h7!=h4)
                break;
        }
        while(1){
            int x=rand()%(rooms[h7].width-2)+rooms[h7].x+1;
            int y=rand()%(rooms[h7].height-2)+rooms[h7].y+1;
            if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h7].trap.y || x!=rooms[h7].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/' && map[y][x]!='D' && map[y][x]!='F' && map[y][x]!='U' && map[y][x]!='S' && map[y][x]!='G' && map[y][x]!='d'){
                map[y][x]='f';
                map2[y][x]='f';
                monsters[6].x=x;
                monsters[6].y=y;
                break;
            }
        }      
    }
    if(floor>=3){
        int h8;
        while(1){
            h8=rand()%5+1;
            if(h8!=h1 && h8!=h2 && h8!=h3 && h8!=h4)
                break;
        }
        while(1){
            int x=rand()%(rooms[h8].width-2)+rooms[h8].x+1;
            int y=rand()%(rooms[h8].height-2)+rooms[h8].y+1;
            if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h8].trap.y || x!=rooms[h8].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/' && map[y][x]!='D' && map[y][x]!='F' && map[y][x]!='U' && map[y][x]!='S' && map[y][x]!='G' && map[y][x]!='d' && map[y][x]!='f'){
                map[y][x]='g';
                map2[y][x]='g';
                monsters[7].x=x;
                monsters[7].y=y;
                break;
            }
        }
        int h9;
        while(1){
            h9=rand()%5+1;
            if(h9!=h1 && h9!=h2 && h9!=h3 && h9!=h4)
                break;
        }
        while(1){
            int x=rand()%(rooms[h9].width-2)+rooms[h9].x+1;
            int y=rand()%(rooms[h9].height-2)+rooms[h9].y+1;
            if(map[y][x]!='&' && map[y][x]!='<' && map[y][x]!='O' && (y!=rooms[h9].trap.y || x!=rooms[h9].trap.x)&& map[y][x]!='*' && map[y][x]!='!' && map[y][x]!='x' && map[y][x]!='M' && map[y][x]!='N' && map[y][x]!='/' && map[y][x]!='D' && map[y][x]!='F' && map[y][x]!='U' && map[y][x]!='S' && map[y][x]!='G' && map[y][x]!='d' && map[y][x]!='f' && map[y][x]!='g'){
                map[y][x]='u';
                map2[y][x]='u';
                monsters[9].x=x;
                monsters[9].y=y;
                break;
            }
        }            
    }
}
void monsters_move(player*p,Monster* monsters){
    int when_to_stop=0;
    for(int qw=0;qw<7;qw++){
        for(int dfg=0;dfg<MAP_HEIGHT;dfg++){
            for(int uyt=0;uyt<MAP_WIDTH;uyt++){
                if(map2[dfg][uyt]=='$')
                    visited[dfg][uyt]=1;
            }
        }
        int se=rand()%4;
        if(se)
            qw--;
        // check(rooms,&user);
        // hiding_map(map2);
        if(monsters->life<=0){
            p->score+=10;
            for(int df1=0;df1<MAP_HEIGHT;df1++){
                for(int gh=0;gh<MAP_WIDTH;gh++){
                    if(map2[df1][gh]==monsters->type){
                        map[monsters->y][monsters->x]='.';
                        map2[df1][gh]=map[df1][gh];
                    }    
                }
            }
            show_message("you killed the Monster!");
            return;
        }
        if(p->health<=0){
            b=1;
        }
        temps_gold=p->golds;
        temps_health=p->health;
        for(int i=1;i<5;i++){
            temps_gun_collected[i-1]=p->gun[i].collects;
        }
        // check(rooms,&user);
        if(b)
            return;
        display_map(rooms);
        if(next_floor())
            break;
        if(qw==6){
            for(int df1=0;df1<MAP_HEIGHT;df1++){
                for(int gh=0;gh<MAP_WIDTH;gh++){
                    if(map2[df1][gh]==monsters->type){
                        map[monsters->y][monsters->x]='.';
                       map2[df1][gh]=map[df1][gh];
                        
                    }    
                }
            }
            return;
        }
        char a=getch();
        if(a=='8'){
            if(map[p->y-1][p->x]!='_' && map[p->y-1][p->x]!='|' && map[p->y-1][p->x]!=' ' && map[p->y-1][p->x]!='O'){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                                map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }    
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[--p->y][p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][p->x]='$';
                }
            }    
        }
        else if(a=='2'){
            if(map[p->y+1][p->x]!='_' && map[p->y+1][p->x]!='|' && map[p->y+1][p->x]!=' ' && map[p->y+1][p->x]!='O' ){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[++p->y][p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][p->x]='$';
                }
            }    
        }
        else if(a=='6'){
            if(map[p->y][p->x+1]!='_' && map[p->y][p->x+1]!='|' && map[p->y][p->x+1]!=' ' && map[p->y][p->x+1]!='O'){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[p->y][++p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[p->y][++p->x]='$';
                }
            }    
        }
        else if(a=='4'){
            if(map[p->y][p->x-1]!='_' && map[p->y][p->x-1]!='|' && map[p->y][p->x-1]!=' ' && map[p->y][p->x-1]!='O' ){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[p->y][--p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[p->y][--p->x]='$';
                }
            }    
        }
        else if(a=='9'){
            if(map[p->y-1][p->x+1]!='_' && map[p->y-1][p->x+1]!='|' && map[p->y-1][p->x+1]!=' ' && map[p->y-1][p->x+1]!='O'){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[--p->y][++p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][++p->x]='$';
                }
            }    
        }
        else if(a=='7'){
            if(map[p->y-1][p->x-1]!='_' && map[p->y-1][p->x-1]!='|' && map[p->y-1][p->x-1]!=' ' && map[p->y-1][p->x-1]!='O'){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[--p->y][--p->x]='$';
                }
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[--p->y][--p->x]='$';
                }
            }    
        }
        else if(a=='1'){
            if(map[p->y+1][p->x-1]!='_' && map[p->y+1][p->x-1]!='|' && map[p->y+1][p->x-1]!=' ' && map[p->y+1][p->x-1]!='O' ){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[++p->y][--p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][--p->x]='$';
                }
            }    
        }
        else if(a=='3'){
            if(map[p->y+1][p->x+1]!='_' && map[p->y+1][p->x+1]!='|' && map[p->y+1][p->x+1]!=' ' && map[p->y+1][p->x+1]!='O' ){
                if(!se && !when_to_stop){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]==monsters->type){
                                map[monsters->y][monsters->x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters->damage;
                    show_message2("the Monster hit you! health: ",p->health);
                    map2[p->y][p->x]=monsters->type;
                    map2[++p->y][++p->x]='$';
                }    
                else{
                    map2[p->y][p->x]=map[p->y][p->x];
                    map2[++p->y][++p->x]='$';
                }
            }    
        }
        else if(a=='s' || a=='S'){
            int i;
            for(i=0;i<6;i++){
                if(p->y>=rooms[i].y && p->y<rooms[i].y+rooms[i].height && p->x>=rooms[i].x && p->x<rooms[i].x+rooms[i].width)
                    break;
            }
            switch (i){
                case 0:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 1:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
                case 2:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    display_map2(rooms[4]);
                    refresh();
                    sleep(10);
                    break;    
                case 3:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    display_map2(rooms[5]);
                    refresh();
                    sleep(10);
                    break;    
                case 4:
                    clear();
                    display_map2(rooms[5]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 5:
                    clear();
                    display_map2(rooms[4]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
            }
        }
        else if(a=='i' || a=='I'){
            gun_menu(&user);
        }
        else if(a=='w' || a=='W'){
            p->whicch_weapom_is_being_used=0;
            show_message("Now you have no weapon in hand!");
        }
        else if(a==32 && p->whicch_weapom_is_being_used){
            qw--;
            int abbas=0;
            int th,jh,th_temps,jh_temps;
            for(th=0;th<MAP_HEIGHT;th++){
                for(jh=0;jh<MAP_WIDTH;jh++){
                    if(map2[th][jh]=='$'){
                        abbas=1;
                        break;
                    }    
                }
                if(abbas)
                    break;
            }
            if(p->whicch_weapom_is_being_used!=1 && p->whicch_weapom_is_being_used!=5 && p->gun[p->whicch_weapom_is_being_used-1].collects>0){
                int range;
                if(p->whicch_weapom_is_being_used==2)
                    range=5;
                else if(p->whicch_weapom_is_being_used==3)
                    range=10;
                else  if(p->whicch_weapom_is_being_used==4) 
                    range=5;
                show_message2("Now you can shoot from range: ",range);
                char addd=getch();
                jh_temps=jh;
                th_temps=th;
                for(int ass=0;ass<range;ass++ ){
                    if(addd=='6'){
                        
                        while (map2[th][jh_temps] != '|' && map2[th][jh_temps] != '_' && map2[th][jh_temps] != 'O' && map2[th][jh_temps] != monsters->type) {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }

                        if(map2[th][ass+jh]==monsters->type){
                            monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. Monsters's lifespan: ",monsters->life);
                            if(p->whicch_weapom_is_being_used==3){
                                show_message("the Monster can't move anymore!");
                                when_to_stop=1;
                            }
                            //     return;
                            break;
                        }
                        else if(ass==range-1){
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message("you couldn't hit the monster!");
                        }    
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='2'){
                        while (map2[th_temps][jh] != '|' && map2[th_temps][jh] != '_' && map2[th_temps][jh] != 'O' && map2[th_temps][jh] != monsters->type) {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        // mvprintw(2,2,"%c",monsters->type);
                        if(map2[th+ass][jh]==monsters->type){
                            monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. Monsters's lifespan: ",monsters->life);
                            if(p->whicch_weapom_is_being_used==3){
                                show_message("the Monster can't move anymore!");
                                when_to_stop=1;
                            }
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1){
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message("you couldn't hit the monster!");
                        }    
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='4'){
                        while (map2[th][jh_temps] != '|' && map2[th][jh_temps] != '_' && map2[th][jh_temps] != 'O' && map2[th][jh_temps] != monsters->type) {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        if(map2[th][jh-ass]==monsters->type){
                            monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. Monsters's lifespan: ",monsters->life);
                            if(p->whicch_weapom_is_being_used==3){
                                show_message("the Monster can't move anymore!");
                                when_to_stop=1;
                            }
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }    
                        else if(ass==range-1){
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message("you couldn't hit the monster!");
                        }    
                        
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='8'){
                        while (map2[th_temps][jh] != '|' && map2[th_temps][jh] != '_' && map2[th_temps][jh] != 'O' && map2[th_temps][jh] != monsters->type) {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        if(map2[th-ass][jh]==monsters->type){
                            monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. Monsters's lifespan: ",monsters->life);
                            if(p->whicch_weapom_is_being_used==3){
                                show_message("the Monster can't move anymore!");
                                when_to_stop=1;
                            }
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1){
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message("you couldn't hit the monster!");
                        }    
                    }
                }
                // monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                // p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                // show_message2("Wooow! you hit the Monster. Monsters's lifespan: ",monsters->life);
            }
            else{
                if(map2[th+1][jh]==monsters->type || map2[th+1][jh+1]==monsters->type ||map2[th+1][jh-1]==monsters->type ||map2[th][jh+1]==monsters->type ||map2[th][jh-1]==monsters->type ||map2[th-1][jh-1]==monsters->type ||map2[th-1][jh+1]==monsters->type || map2[th-1][jh]==monsters->type ){
                    monsters->life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                    p->health-=monsters->damage;
                    show_message2("Wooow! you hit the Monster. Monster's lifespan: ",monsters->life);
                    show_message2("Your health: ",p->health);
                }    
            }
        }
        else    
            qw--;
    }
}
void snake_move(player *p , Monster* monsters){
    // play_music()
    int when_to_stop=0;
    while(1){
        for(int dfg=0;dfg<MAP_HEIGHT;dfg++){
            for(int uyt=0;uyt<MAP_WIDTH;uyt++){
                if(map2[dfg][uyt]=='$')
                    visited[dfg][uyt]=1;
            }
        }
        int h=0;
        int df=rand()%4;
        if(monsters[3].life<=0){
            p->score+=15;
            for(int df1=0;df1<MAP_HEIGHT;df1++){
                for(int gh=0;gh<MAP_WIDTH;gh++){
                    if(map2[df1][gh]=='S'){
                        map[monsters[3].y][monsters[3].x]='.';
                        map2[df1][gh]=map[df1][gh];
                    }    
                }
            }
            show_message("you killed the snake!");
            return;
        }
        temps_gold=p->golds;
        temps_health=p->health;
        for(int i=1;i<5;i++){
            temps_gun_collected[i-1]=p->gun[i].collects;
        }
        if(p->health<=0)
            b=1;
        // check(rooms,&user);
        if(b)
            return;
        display_map(rooms);
        if(next_floor())
            break;
        char a=getch();
        int py,px;
        for(int as=0;as<MAP_HEIGHT;as++){
            for(int ds=0;ds<MAP_WIDTH;ds++){
                if(map2[as][ds]=='$'){
                    py=as;
                    px=ds;
                }    
            }
        }
        if(a=='8'){
            if(map[py-1][px]!='_' && map[py-1][px]!='|' && map[py-1][px]!=' ' && map[py-1][px]!='O'){
                if(!df){
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                                map2[df1][gh]=map[df1][gh];
                            }    
                        }
                    }

                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]=map[py][px];
                    map2[h+py][px]='S';
                    map2[--py][px]='$';
                }
                else{
                    map2[py][px]=map[py][px];
                    map2[--py][px]='$';
                }
                
            }    
        }
        else if(a=='2'){
            if(map[py+1][px]!='_' && map[py+1][px]!='|' && map[py+1][px]!=' ' && map[py+1][px]!='O' ){
                if(!df && !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]=map[py][px];
                    map2[py-h][px]='S';
                    map2[++py][px]='$';
                    
                }    
                else{
                    map2[py][px]=map[py][px];
                    map2[++py][px]='$';
                }
            }        
        }
        else if(a=='6'){
            if(map[py][px+1]!='_' && map[py][px+1]!='|' && map[py][px+1]!=' ' && map[py][px+1]!='O'){
                if(!df&& !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';  
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]=map[py][px];
                    map2[py][px+h]='S';
                    map2[py][++px]='$';
                    
                }    
            
                else{
                    map2[py][px]=map[py][px];
                    map2[py][++px]='$';
                }
            }        
        }
        else if(a=='4'){
            if(map[py][px-1]!='_' && map[py][px-1]!='|' && map[py][px-1]!=' ' && map[py][px-1]!='O' ){
                if(!df && !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]=map[py][px];
                    map2[py][px-h]='S';
                    map2[py][--px]='$';
                
                }    
            
                else{
                    map2[py][px]=map[py][px];
                    map2[py][--px]='$';
                } 
            }       
        }
        else if(a=='9'){
            if(map[py-1][px+1]!='_' && map[py-1][px+1]!='|' && map[py-1][px+1]!=' ' && map[py-1][px+1]!='O'){
                if(!df && !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]=map[py][px];
                    map2[--py][++px]='$';
                    
                }    
            
                else{
                    map2[py][px]='S';
                    map2[--py][++px]='$';
                } 
            }       
        }
        else if(a=='7'){
            if(map[py-1][px-1]!='_' && map[py-1][px-1]!='|' && map[py-1][px-1]!=' ' && map[py-1][px-1]!='O'){
                if(!df && !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]='S';
                    map2[--py][--px]='$';
                    
                } 
            
                else{
                    map2[py][px]=map[py][px];
                    map2[--py][--px]='$';
                }
            }           
        }
        else if(a=='1'){
            if(map[py+1][px-1]!='_' && map[py+1][px-1]!='|' && map[py+1][px-1]!=' ' && map[py+1][px-1]!='O' ){
                if(!df && !when_to_stop){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]='S';
                    map2[++py][--px]='$';
                    
                }
            
                else{
                    map2[py][px]=map[py][px];
                    map2[++py][--px]='$';
                }
            }            
        }
        else if(a=='3'){
            if(map[py+1][px+1]!='_' && map[py+1][px+1]!='|' && map[py+1][px+1]!=' ' && map[py+1][px+1]!='O' ){
                if(!df && !when_to_stop ){
                
                    for(int df1=0;df1<MAP_HEIGHT;df1++){
                        for(int gh=0;gh<MAP_WIDTH;gh++){
                            if(map2[df1][gh]=='S'){
                                map[monsters[3].y][monsters[3].x]='.';
                            map2[df1][gh]=map[df1][gh];
                                
                            }    
                        }
                    }
                    p->health-=monsters[3].damage;
                    show_message2("the snake bit you! health: ",p->health);
                    map2[py][px]='S';
                    map2[++py][++px]='$';
                    
                }
            
                else{
                    map2[py][px]=map[py][px];
                    map2[++py][++px]='$';
                } 
            }           
        }
        else if(a=='s' || a=='S'){
            int i;
            for(i=0;i<6;i++){
                if(py>=rooms[i].y && py<rooms[i].y+rooms[i].height && px>=rooms[i].x && px<rooms[i].x+rooms[i].width)
                    break;
            }
            switch (i){
                case 0:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 1:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
                case 2:
                    clear();
                    display_map2(rooms[0]);
                    display_map2(rooms[3]);
                    display_map2(rooms[4]);
                    refresh();
                    sleep(10);
                    break;    
                case 3:
                    clear();
                    display_map2(rooms[1]);
                    display_map2(rooms[2]);
                    display_map2(rooms[5]);
                    refresh();
                    sleep(10);
                    break;    
                case 4:
                    clear();
                    display_map2(rooms[5]);
                    display_map2(rooms[2]);
                    refresh();
                    sleep(10);
                    break;
                case 5:
                    clear();
                    display_map2(rooms[4]);
                    display_map2(rooms[3]);
                    refresh();
                    sleep(10);
                    break;
            }
        }
        else if(a=='i' || a=='I'){
            gun_menu(&user);
        }
        else if(a=='w' || a=='W'){
            p->whicch_weapom_is_being_used=0;
            show_message("Now you have no weapon in hand!");
        }
        // else if(a==10 && p->whicch_weapom_is_being_used){
        //     if(p->whicch_weapom_is_being_used!=1 && p->whicch_weapom_is_being_used!=5){
        //         monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
        //         p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
        //         show_message2("Wooow! you hit the snake. snake's lifespan: ",monsters[3].life);
        //     }
        //     else{
        //         monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
        //         show_message2("Wooow! you hit the snake. snake's lifespan: ",monsters[3].life);
        //     }
        // }
        else if(a==32 && p->whicch_weapom_is_being_used){
            int abbas=0;
            int th,jh;
            for(th=0;th<MAP_HEIGHT;th++){
                for(jh=0;jh<MAP_WIDTH;jh++){
                    if(map2[th][jh]=='$'){
                        abbas=1;
                        break;
                    }    
                }
                if(abbas)
                    break;
            }
            if(p->whicch_weapom_is_being_used!=1 && p->whicch_weapom_is_being_used!=5 && p->gun[p->whicch_weapom_is_being_used-1].collects>0){
                int range;
                if(p->whicch_weapom_is_being_used==2)
                    range=5;
                else if(p->whicch_weapom_is_being_used==3)
                    range=10;
                else if(p->whicch_weapom_is_being_used==4)   
                    range=5;
                
                show_message2("Now you can shoot from range: ",range);
                char addd=getch();
                int th_temps=th;
                int jh_temps=jh;
                for(int ass=0;ass<range;ass++ ){
                    if(addd=='6'){
                        while (map2[th][jh_temps] != '|' && map2[th][jh_temps] != '_' && map2[th][jh_temps] != 'O' && map2[th][jh_temps] != 'S' ) {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    jh_temps++;
                                    mvaddch(th, jh_temps, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        if(map2[th][ass+jh]==monsters[3].type){
                            monsters[3].life-=(p->gun[p->whicch_weapom_is_being_used-1].damage);//();
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. snake's lifespan: ",monsters[3].life);
                            if(p->whicch_weapom_is_being_used==3){
                                show_message("the snake cannot move any more!");
                                when_to_stop=1;
                            }
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1)
                            show_message("you couldn't hit the monster!");
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='2'){
                        while (map2[th_temps][jh] != '|' && map2[th_temps][jh] != '_' && map2[th_temps][jh] != 'O' && map2[th_temps][jh] != 'S') {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    th_temps++;
                                    mvaddch(th_temps, jh, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        // mvprintw(2,2,"%c",monsters[3].type);
                        if(map2[th+ass][jh]==monsters[3].type){
                            monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. snake's lifespan: ",monsters[3].life);
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1)
                            show_message("you couldn't hit the monster!");
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='4'){
                        while (map2[th][jh_temps] != '|' && map2[th][jh_temps] != '_' && map2[th][jh_temps] != 'O' && map2[th][jh_temps] != 'S') {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    jh_temps--;
                                    mvaddch(th, jh_temps, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        if(map2[th][jh-ass]==monsters[3].type){
                            monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. snake's lifespan: ",monsters[3].life);
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1)
                            show_message("you couldn't hit the monster!");
                        // else{
                        //     show_message("you couldn't hit the monster!");
                        // }
                    }
                    else if(addd=='8'){
                        while (map2[th_temps][jh] != '|' && map2[th_temps][jh] != '_' && map2[th_temps][jh] != 'O' && map2[th_temps][jh] != 'S') {
                            switch (p->whicch_weapom_is_being_used) {
                                case 2:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'X');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;
                                case 3:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'M');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;  
                                case 4:
                                    th_temps--;
                                    mvaddch(th_temps, jh, 'N');
                                    refresh();
                                    napms(500);
                                    clear();
                                    display_map(rooms);
                                    break;       
                            }
                        }
                        if(map2[th-ass][jh]==monsters[3].type){
                            monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                            p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                            show_message2("Wooow! you hit the Monster. snake's lifespan: ",monsters[3].life);
                            // if(p->whicch_weapom_is_being_used==3)
                            //     return;
                            break;
                        }
                        else if(ass==range-1)
                            show_message("you couldn't hit the monster!");
                    }
                }
                // monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                // p->gun[p->whicch_weapom_is_being_used-1].collects-=1;
                // show_message2("Wooow! you hit the Monster. monsters[3]'s lifespan: ",monsters[3].life);
            }
            else{
                if(map2[th+1][jh]==monsters[3].type || map2[th+1][jh+1]==monsters[3].type ||map2[th+1][jh-1]==monsters[3].type ||map2[th][jh+1]==monsters[3].type ||map2[th][jh-1]==monsters[3].type ||map2[th-1][jh-1]==monsters[3].type ||map2[th-1][jh+1]==monsters[3].type || map2[th-1][jh]==monsters[3].type){
                    monsters[3].life-=p->gun[p->whicch_weapom_is_being_used-1].damage;
                    p->health-=monsters[3].damage;
                    show_message2("Wooow! you hit the Monster. snake's lifespan: ",monsters[3].life);
                    show_message2("health: ",p->health);
                }    
            }
        }    
    }
}
void putting_spells(Room * rooms){
    while(1){
        int x=rand()%(rooms[0].width-2)+rooms[0].x+1;
        int y=rand()%(rooms[0].height-2)+rooms[0].y+1;
        if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[0].trap.y || x!=rooms[0].trap.x)){
            map[y][x]='H';
            map2[y][x]='H';
            break;
        }
    }
    while(1){
        int x=rand()%(rooms[0].width-2)+rooms[0].x+1;
        int y=rand()%(rooms[0].height-2)+rooms[0].y+1;
        if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[0].trap.y || x!=rooms[0].trap.x) && map2[y][x]!='+'){
            map[y][x]='%';
            map2[y][x]='%';
            break;
        }
    }
    while(1){
        int x=rand()%(rooms[0].width-2)+rooms[0].x+1;
        int y=rand()%(rooms[0].height-2)+rooms[0].y+1;
        if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[0].trap.y || x!=rooms[0].trap.x) && map2[y][x]!='+' && map2[y][x]!='%'){
            map[y][x]='=';
            map2[y][x]='=';
            break;
        }
    }
    for(int i=1;i<6;i++){
        int y=rand()%3;
        switch (y){
            case 0:
                while(1){
                    int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                    int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                    if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[i].trap.y || x!=rooms[i].trap.x) && map2[y][x]!='+' && map2[y][x]!='%'){
                        map[y][x]='=';
                        map2[y][x]='=';
                        break;
                    }
                }
                break;
            case 1:
                while(1){
                    int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                    int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                    if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[i].trap.y || x!=rooms[i].trap.x) && map2[y][x]!='+' && map2[y][x]!='%'){
                        map[y][x]='H';
                        map2[y][x]='H';
                        break;
                    }
                }
                break;
            case 2:
                while(1){
                    int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                    int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                    if(map2[y][x]!='O' && map2[y][x]!='W' && (y!=rooms[i].trap.y || x!=rooms[i].trap.x) && map2[y][x]!='+' && map2[y][x]!='%'){
                        map[y][x]='%';
                        map2[y][x]='%';
                        break;
                    }
                }
                break;    
        }
    }
}
void health(int a){
    mvprintw(4,140,"your health: %d",a);
}
void food(Room * rooms){
    srand(time(NULL));
    char fooding[]="TYWWQQ";
    for(int i=0;i<6;i++){
        int k=rand()%2;
        switch(k){
            case 0:
                break;
            case 1:
                int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                if(map[y][x]=='&' || map[y][x]=='<' || map[y][x]=='O' || (y==rooms[i].trap.y && x==rooms[i].trap.x))
                    i--;
                else{
                    map[y][x]=fooding[i];
                    map2[y][x]=fooding[i];
                }
                break;
        }
    }
    for(int i=0;i<6;i++){
        int k=rand()%2;
        switch(k){
            case 0:
                break;
            case 1:
                int x=rand()%(rooms[i].width-2)+rooms[i].x+1;
                int y=rand()%(rooms[i].height-2)+rooms[i].y+1;
                if(map[y][x]=='&' || map[y][x]=='<' || map[y][x]=='O' || (y==rooms[i].trap.y && x==rooms[i].trap.x))
                    i--;
                else{
                    map[y][x]=fooding[i];
                    map2[y][x]=fooding[i];
                }
                break;
        }
    }
}
void spell_menu(player* p){
    int vn=0;
    curs_set(0);
    keypad(stdscr, TRUE);
    
    start_color();
    init_pair(102, COLOR_BLUE, COLOR_BLACK);
    init_pair(103, COLOR_BLACK, COLOR_BLUE);
    init_pair(104, COLOR_GREEN, COLOR_BLACK);

    while(1){
        clear();  
        attron(COLOR_PAIR(102));
        mvprintw(LINES/2-6, COLS/2-15, "health spell: %d",p->spell[0]);
        mvprintw(LINES/2-5, COLS/2-15, "speed spell: %d",p->spell[1]);
        mvprintw(LINES/2-4, COLS/2-15, "damage spell: %d",p->spell[2]);
        attroff(COLOR_PAIR(102));
        attron(COLOR_PAIR(103));
        if(vn == 0) mvprintw(LINES/2-6, COLS/2-15, "health spell: %d",p->spell[0]);
        if(vn == 1) mvprintw(LINES/2-5, COLS/2-15, "speed spell: %d",p->spell[1]);
        if(vn == 2) mvprintw(LINES/2-4, COLS/2-15, "damage spell: %d",p->spell[2]);
        attroff(COLOR_PAIR(103));

        refresh();

        int a = getch();
        if(a == KEY_DOWN && vn < 2) vn++;
        else if(a == KEY_UP && vn > 0) vn--;
        else if(a == 10) {
            clear();
            if(vn==0 ){
                if(p->spell[0]!=0){
                    p->spell[0]--;
                    p->which_spell_is_being_used= vn + 1;
                    show_message("Now you are using health spell");
                }
                else
                    show_message("you have no health spell");
            }    
            else if(vn==1){        
                if(p->spell[1]>0){
                    p->spell[1]--;
                    p->which_spell_is_being_used= 2;
                    show_message("Now you are using speed spell");
                    for(int h=0;h<10;h++){
                    temps_gold=p->golds;
                    temps_health=p->health;
                    health(temps_health);
                    for(int i=1;i<5;i++){
                        temps_gun_collected[i-1]=p->gun[i].collects;
                    }
                    check(rooms,&user,1);
                    if(b)
                        return;
                    display_map(rooms);
                    if(next_floor())
                        break;
                    char a=getch();
                    if(a=='8'){
                        if(map[p->y-2][p->x]!='_' && map[p->y-2][p->x]!='|' && map[p->y-2][p->x]!=' ' && map[p->y-2][p->x]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y-=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='2'){
                        if(map[p->y+2][p->x]!='_' && map[p->y+2][p->x]!='|' && map[p->y+2][p->x]!=' ' && map[p->y+2][p->x]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y+=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='6'){
                        if(map[p->y][p->x+2]!='_' && map[p->y][p->x+2]!='|' && map[p->y][p->x+2]!=' ' && map[p->y][p->x+2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->x+=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='4'){
                        if(map[p->y][p->x-2]!='_' && map[p->y][p->x-2]!='|' && map[p->y][p->x-2]!=' ' && map[p->y][p->x-2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->x-=2;
                            map2[p->y][--p->x]='$';
                        
                        }    
                    }
                    else if(a=='9'){
                        if(map[p->y-2][p->x+2]!='_' && map[p->y-2][p->x+2]!='|' && map[p->y-2][p->x+2]!=' ' && map[p->y-2][p->x+2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y-=2;
                            p->x+=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='7'){
                        if(map[p->y-2][p->x-2]!='_' && map[p->y-2][p->x-2]!='|' && map[p->y-2][p->x-2]!=' ' && map[p->y-2][p->x-2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y-=2;
                            p->x-=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='1'){
                        if(map[p->y+2][p->x-2]!='_' && map[p->y+2][p->x-2]!='|' && map[p->y+2][p->x-2]!=' ' && map[p->y+2][p->x-2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y+=2;
                            p->x-=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if(a=='3'){
                        if(map[p->y+2][p->x+2]!='_' && map[p->y+2][p->x+2]!='|' && map[p->y+2][p->x+2]!=' ' && map[p->y+2][p->x+2]!='O'){
                            map2[p->y][p->x]=map[p->y][p->x];
                            p->y+=2;
                            p->x+=2;
                            map2[p->y][p->x]='$';
                            
                        }    
                    }
                    else if((a=='f' || a=='F') ){
                        a=getch();
                        if(a=='8'){
                            while(map[p->y-1][p->x]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][p->x]='$';
                                refresh();
                            }
                        }
                        else if(a=='2'){
                            while(map[p->y+1][p->x]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='6'){
                            while(map[p->y][p->x+1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[p->y][++p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='4'){
                            while(map[p->y][p->x-1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[p->y][--p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='9'){
                            while(map[p->y-1][p->x+1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][++p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='7'){
                            while(map[p->y-1][p->x-1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][--p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='3'){
                            while(map[p->y+1][p->x+1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][++p->x]='$';
                                refresh();
                            }
                        }
                        else  if(a=='1'){
                            while(map[p->y+1][p->x-1]=='.'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][--p->x]='$';
                                refresh();
                            }
                        }
                    }
                    else if(a=='s' || a=='S'){
                        h--;
                        int i;
                        for(i=0;i<6;i++){
                            if(p->y>=rooms[i].y && p->y<rooms[i].y+rooms[i].height && p->x>=rooms[i].x && p->x<rooms[i].x+rooms[i].width)
                                break;
                        }
                        switch (i){
                            case 0:
                                clear();
                                display_map2(rooms[1]);
                                display_map2(rooms[2]);
                                refresh();
                                sleep(10);
                                break;
                            case 1:
                                clear();
                                display_map2(rooms[0]);
                                display_map2(rooms[3]);
                                refresh();
                                sleep(10);
                                break;
                            case 2:
                                clear();
                                display_map2(rooms[0]);
                                display_map2(rooms[3]);
                                display_map2(rooms[4]);
                                refresh();
                                sleep(10);
                                break;    
                            case 3:
                                clear();
                                display_map2(rooms[1]);
                                display_map2(rooms[2]);
                                display_map2(rooms[5]);
                                refresh();
                                sleep(10);
                                break;    
                            case 4:
                                clear();
                                display_map2(rooms[5]);
                                display_map2(rooms[2]);
                                refresh();
                                sleep(10);
                                break;
                            case 5:
                                clear();
                                display_map2(rooms[4]);
                                display_map2(rooms[3]);
                                refresh();
                                sleep(10);
                                break;
                        }
                    }
                    else if(a=='i' || a=='I'){
                        h--;
                        gun_menu(&user);
                    }
                    else if(a=='w' || a=='W'){
                        h--;
                        p->whicch_weapom_is_being_used=0;
                        show_message("Now you have no weapon in hand!");
                    }
                    else if(a=='p' || a=='P'){
                        h--;
                        spell_menu(p);
                    }
                }
                }    
                else
                    show_message("you have no speed spell");    
            }    
            else if(vn==2 ){                
                if(p->spell[2]>0){
                    p->spell[2]--;
                    p->which_spell_is_being_used= 3;
                    show_message("Noe you are using damage spell for 10 seconds");
                    time_t start=time(NULL);
                    while (time(NULL) - start < 10) {
                        p->gun[0].damage=10;
                        p->gun[1].damage=24;
                        p->gun[2].damage=30;
                        p->gun[3].damage=10;
                        p->gun[4].damage=20;
                        // check(rooms,&user);
                        // hiding_map(map2);
                        temps_gold=p->golds;
                        temps_health=p->health;
                        health(temps_health);
                        for(int i=1;i<5;i++){
                            temps_gun_collected[i-1]=p->gun[i].collects;
                        }
                        check(rooms,&user,1);
                        if(b)
                            return;
                        display_map(rooms);
                        if(next_floor())
                            break;
                        char a=getch();
                        if(a=='8'){
                            if(map[p->y-1][p->x]!='_' && map[p->y-1][p->x]!='|' && map[p->y-1][p->x]!=' ' && map[p->y-1][p->x]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][p->x]='$';
                                
                            }    
                        }
                        else if(a=='2'){
                            if(map[p->y+1][p->x]!='_' && map[p->y+1][p->x]!='|' && map[p->y+1][p->x]!=' ' && map[p->y+1][p->x]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][p->x]='$';
                                
                            }    
                        }
                        else if(a=='6'){
                            if(map[p->y][p->x+1]!='_' && map[p->y][p->x+1]!='|' && map[p->y][p->x+1]!=' ' && map[p->y][p->x+1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[p->y][++p->x]='$';
                                
                            }    
                        }
                        else if(a=='4'){
                            if(map[p->y][p->x-1]!='_' && map[p->y][p->x-1]!='|' && map[p->y][p->x-1]!=' ' && map[p->y][p->x-1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[p->y][--p->x]='$';
                            
                            }    
                        }
                        else if(a=='9'){
                            if(map[p->y-1][p->x+1]!='_' && map[p->y-1][p->x+1]!='|' && map[p->y-1][p->x+1]!=' ' && map[p->y-1][p->x+1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][++p->x]='$';
                                
                            }    
                        }
                        else if(a=='7'){
                            if(map[p->y-1][p->x-1]!='_' && map[p->y-1][p->x-1]!='|' && map[p->y-1][p->x-1]!=' ' && map[p->y-1][p->x-1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[--p->y][--p->x]='$';
                                
                            }    
                        }
                        else if(a=='1'){
                            if(map[p->y+1][p->x-1]!='_' && map[p->y+1][p->x-1]!='|' && map[p->y+1][p->x-1]!=' ' && map[p->y+1][p->x-1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][--p->x]='$';
                                
                            }    
                        }
                        else if(a=='3'){
                            if(map[p->y+1][p->x+1]!='_' && map[p->y+1][p->x+1]!='|' && map[p->y+1][p->x+1]!=' ' && map[p->y+1][p->x+1]!='O'){
                                map2[p->y][p->x]=map[p->y][p->x];
                                map2[++p->y][++p->x]='$';
                                
                            }    
                        }
                        else if((a=='f' || a=='F') ){
                            a=getch();
                            if(a=='8'){
                                while(map[p->y-1][p->x]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[--p->y][p->x]='$';
                                    refresh();
                                }
                            }
                            else if(a=='2'){
                                while(map[p->y+1][p->x]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[++p->y][p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='6'){
                                while(map[p->y][p->x+1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[p->y][++p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='4'){
                                while(map[p->y][p->x-1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[p->y][--p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='9'){
                                while(map[p->y-1][p->x+1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[--p->y][++p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='7'){
                                while(map[p->y-1][p->x-1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[--p->y][--p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='3'){
                                while(map[p->y+1][p->x+1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[++p->y][++p->x]='$';
                                    refresh();
                                }
                            }
                            else  if(a=='1'){
                                while(map[p->y+1][p->x-1]=='.'){
                                    map2[p->y][p->x]=map[p->y][p->x];
                                    map2[++p->y][--p->x]='$';
                                    refresh();
                                }
                            }
                        }
                        else if(a=='s' || a=='S'){
                            int i;
                            for(i=0;i<6;i++){
                                if(p->y>=rooms[i].y && p->y<rooms[i].y+rooms[i].height && p->x>=rooms[i].x && p->x<rooms[i].x+rooms[i].width)
                                    break;
                            }
                            switch (i){
                                case 0:
                                    clear();
                                    display_map2(rooms[1]);
                                    display_map2(rooms[2]);
                                    refresh();
                                    sleep(10);
                                    break;
                                case 1:
                                    clear();
                                    display_map2(rooms[0]);
                                    display_map2(rooms[3]);
                                    refresh();
                                    sleep(10);
                                    break;
                                case 2:
                                    clear();
                                    display_map2(rooms[0]);
                                    display_map2(rooms[3]);
                                    display_map2(rooms[4]);
                                    refresh();
                                    sleep(10);
                                    break;    
                                case 3:
                                    clear();
                                    display_map2(rooms[1]);
                                    display_map2(rooms[2]);
                                    display_map2(rooms[5]);
                                    refresh();
                                    sleep(10);
                                    break;    
                                case 4:
                                    clear();
                                    display_map2(rooms[5]);
                                    display_map2(rooms[2]);
                                    refresh();
                                    sleep(10);
                                    break;
                                case 5:
                                    clear();
                                    display_map2(rooms[4]);
                                    display_map2(rooms[3]);
                                    refresh();
                                    sleep(10);
                                    break;
                            }
                        }
                        else if(a=='i' || a=='I'){
                            gun_menu(&user);
                        }
                        else if(a=='w' || a=='W'){
                            p->whicch_weapom_is_being_used=0;
                            show_message("Now you have no weapon in hand!");
                        }
                        else if(a=='p' || a=='P'){
                            spell_menu(p);
                        }
                    }
                    p->gun[0].damage=5;
                    p->gun[1].damage=12;
                    p->gun[2].damage=15;
                    p->gun[3].damage=5;
                    p->gun[4].damage=10;      
                }    
                else 
                    show_message("you have no damage spell");
            }    
            return;
        } 
        else if(a=='p' || a=='P'){
            clear();
            return; 
        }    
    }
}
void updating_file(char *username, char *email, char *password, int gold, int score) {
    FILE *file;
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);

    file = fopen(filepath, "r+");
    if (!file) {
        show_message("Error opening file!\n");
        return;
    }

    char line[1024];
    int stored_gold = 0;
    int past_score = 0;
    int game_played = 0;
    long gold_position = 0;
    long score_position = 0;
    long game_played_position = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Gold: ", 6) == 0) {
            stored_gold = atoi(line + 6);
            stored_gold += gold;
            gold_position = ftell(file) - strlen(line) + 6;
        } else if (strncmp(line, "Game played: ", 13) == 0) {
            game_played = atoi(line + 13);
            game_played += 1;
            game_played_position = ftell(file) - strlen(line) + 13;
        } else if (strncmp(line, "Score: ", 7) == 0) {
            past_score = atoi(line + 7);
            past_score += score;
            score_position = ftell(file) - strlen(line) + 7;
        }
    }

    if (gold_position != 0) {
        fseek(file, gold_position, SEEK_SET);
        fprintf(file, "%d\n", stored_gold);
    }

    if (game_played_position != 0) {
        fseek(file, game_played_position, SEEK_SET);
        fprintf(file, "%d\n", game_played);
    }

    if (score_position != 0) {
        fseek(file, score_position, SEEK_SET);
        fprintf(file, "%d\n", past_score);
    }

    fclose(file);
    show_message2("Golds ", stored_gold);
}
void saving_map(char *username){//,char * map[150]){
    FILE *file;
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "./player_data/%s.txt", username);
    file=fopen(filepath,"w");
    fprintf(file,"\f");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for(int j=0;j<MAP_WIDTH;j++){
            if(visited[i][j])
                fprintf(file, "%c", map2[i][j]); 
        }
        fprintf(file,"\n");     
    }
    fclose(file);
}
void play_music(const char *filename) {
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "Mix_OpenAudio: %s", Mix_GetError());
        exit(1);
    }

    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        fprintf(stderr, "Mix_LoadMUS: %s", Mix_GetError());
        exit(1);
    }

    Mix_PlayMusic(music, -1);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ncurses.h>
int main() {
    srand(time(NULL));
    // setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr,true);
    cbreak();
    
    // noecho();
    // while(1){
        main_page(&m);
        
        // Difficulty(&m);
        // show_message(username);
        if(difficulty==2){
            seconds=100;
            inital_health=70;
        }
        else if(difficulty==3){
            seconds=80;
            inital_health=60;
        }
        if(!m){
            // time_t start=time(NULL);
            // while(timing(&user,start)<10)
            //     timing(&user,start);
            
            // if(!donot)
            //     play_music(musicer);
            noecho();
            curs_set(0);
            clear();
            curs_set(0);
            initialize_map();
            creat_room(rooms,1);
            maps();
            encryped_door(rooms);
            trap(rooms,&user,inital_health);
            making_pillar(rooms);
            stairs(rooms);
            gold(rooms,&user,0);
            putting_spells(rooms);
            food(rooms);
            int adidas[4]={0,0,0,0};
            guns(rooms,&user,adidas);
            putting_monsters(rooms,monsters,1);
            move_player(&user,1);
            clear();
            for(int i=0;i<MAP_HEIGHT;i++){
                for(int j=0;j<MAP_WIDTH;j++)
                    visited[i][j]=0;
            }
            initialize_map();
            creat_room(rooms,2);
            maps();
            start_color();
            encryped_door(rooms);
            trap(rooms,&user,temps_health);
            making_pillar(rooms);
            stairs(rooms);
            start_color();
            gold(rooms,&user,temps_gold);
            guns(rooms,&user,temps_gun_collected);
            putting_spells(rooms);
            putting_monsters(rooms,monsters,2);
            move_player(&user,2);
            clear();
            for(int i=0;i<MAP_HEIGHT;i++){
                for(int j=0;j<MAP_WIDTH;j++)
                    visited[i][j]=0;
            }
            initialize_map();
            creat_room(rooms,3);
            maps();
            encryped_door(rooms);
            trap(rooms,&user,temps_health);
            making_pillar(rooms);
            stairs(rooms);
            start_color();
            gold(rooms,&user,temps_gold);
            guns(rooms,&user,temps_gun_collected);
            putting_spells(rooms);
            putting_monsters(rooms,monsters,3);
            move_player(&user,3);
            clear();
            for(int i=0;i<MAP_HEIGHT;i++){
                for(int j=0;j<MAP_WIDTH;j++)
                    visited[i][j]=0;
            }
            initialize_map();
            creat_room(rooms,4);
            maps();
            encryped_door(rooms);
            trap(rooms,&user,temps_health);
            making_pillar(rooms);
            stairs(rooms);
            start_color();
            gold(rooms,&user,temps_gold);
            guns(rooms,&user,temps_gun_collected);
            putting_spells(rooms);
            putting_monsters(rooms,monsters,4);
            move_player(&user,4);
            if(b)
                play_music("Habib - Marde Tanhaye Shab (128) (mp3cut.net).mp3");
            if(finish)
                updating_file(username,email,password,user.golds,user.score);
            refresh();
            getch();
            endwin();
        }    
    // }    
    return 0;
}
