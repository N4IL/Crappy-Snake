#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <chrono>
#include <thread>

#define width 100
#define height 25

char ch='d'; int ch1=4; /* direction key and value */
int snakeX[20], snakeY[20]; /* snake position values X/Y */
int i=0,j=0,l=0,k=0; /* looping variables */
int apple[2]={rand()%99+1,rand()%24+1}; /* apple position X/Y values */
int points=0,eaten=0,length=1,random=0; /* game values */

void appleEaten(){ /* Checks if apple is eaten, generates new apple, and increases length */
    if (snakeX[0]==apple[0]&&snakeY[0]==apple[1]){
        points+=100;
        for(random=0;random==0;){
            apple[0]={rand()%99+1};
            apple[1]={rand()%24+1};
            for(i=0;i<length;i++){
                if(apple[0]==snakeX[i]||apple[1]==snakeY[i]){break;random=0;}
                else {random=1;}
            }
        }
        length+=1;
    }
}

void snakeEaten(){ /* Checks if the snake is eating itself */
    for(l=1,k=0;l<length;l++){
        if(snakeX[l]==snakeX[0]&&snakeY[l]==snakeY[0]) k=1;
    }
}

void direction(){ /* Assigns corresponding integer direction to ch1 */
    if (ch=='w') ch1=1;
    if (ch=='a') ch1=2;
    if (ch=='s') ch1=3;
    if (ch=='d') ch1=4;
}

void movement(){ /* Shifts all snake values right one & moves head */
    for(i=length;i>0;i--){
        snakeX[i]=snakeX[i-1];
        snakeY[i]=snakeY[i-1];
    }
    switch (ch1){
        case 1:snakeY[0]-=1;break;
        case 2:snakeX[0]-=1;break;
        case 3:snakeY[0]+=1;break;
        case 4:snakeX[0]+=1;break;
    }
}

void newBoard(){ /* Generates new board */
    printf("############################################# Score: %d ",points);
    if(points==0) printf("##############################################\n");
    if(0<points&&points<=900) printf("############################################\n");
    if(900<points&&points<=9900) printf("###########################################\n");
    for(i=1;i<height;i++){
        printf("#");
        for(j=0;j<width-1;j++){
            k=0;
            if(i==snakeY[0] && j==snakeX[0]){
                switch (ch1){
                    case 1:printf("^");k=1;break;
                    case 2:printf("<");k=1;break;
                    case 3:printf("v");k=1;break;
                    case 4:printf(">");k=1;break;
                }
            }
            else if(i==height-1) {printf("#");k=1;}
            else if(i==apple[1] && j==apple[0]){ printf("@"); k=1;}
            else if(k==0){
                for(l=1;l<length;l++){
                    if(snakeX[l]==j && snakeY[l]==i){ 
                        printf("0");
                        k=1;
                    }
                }
            }  
            if(k==0) printf(" ");
        }
        printf("#\n");
    }
}

int main(){
    snakeX[0]={10}; snakeY[0]={10}; 
    while(snakeX[0]!=0&&snakeX[0]!=100&&snakeY[0]!=0&&snakeY[0]!=25){
        system("cls\n");
        if(kbhit()) {ch=getch();}
        direction();
        movement();
        appleEaten();
        newBoard();
        snakeEaten();
        if(k==1)break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    printf("Your Snake is Dead!");
    for(;;){std::this_thread::sleep_for(std::chrono::minutes(1));}
}

