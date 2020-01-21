#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;  //it is a bollean variavle to detect that snake is not hit the wall or tail

const int width =20,height=20;    //it is dimension of play area

int headx,heady;             //coordinate of head of snake
int fruitx,fruity,score;          //cordinate of next fruits and score
int tailx[1000],taily[10000],ntail;     //array to store coordinate of all tails
int dir,predir;                         //

//intial setup function
void setup(){
    gameover=false;
    dir=0;
    headx=width/2;
    heady=height/2;
    fruitx=rand()%width;
    fruity=rand()%height;
    score=0;
}


//after every time draw function is called and it print the snake and next fruit
void draw(){
    system("cls");
    for(int i=0;i<width+2;i++){
        cout<<"-";
    }
    cout<<endl;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0){
                cout<<"|";
            }

            if(i==heady && j==headx){
                cout<<"O";
            }
            else if(i==fruity && j==fruitx){
                cout<<"f";
            }
            else{
                bool printtail=false;
                for(int k=0;k<ntail;k++){
                    if(tailx[k]==j && taily[k]==i){
                        cout<<"o";
                        printtail=true;
                    }
                }
                if(!printtail)
                cout<<" ";
            }

            if(j==width-1){
                cout<<"|";
            }
        }
        cout<<endl;
    }

    for(int i=0;i<width+2;i++){
        cout<<"-";
    }
    cout<<endl;

    cout<<"score= "<<score<<endl;
}

//take the input
//in which direction you want to move the snake
void input(){
    if(_kbhit()){
        switch(_getch()){
        case 'a':
            dir=1;
            break;
        case 'd':
            dir=3;
            break;
        case 'w':
            dir=2;
            break;
        case 's':
            dir=4;
            break;
        case 'x':
            gameover=true;
            break;
        }
    }
}

//change the coordinate of head and tail
void logic(){
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=headx;
    taily[0]=heady;
    for(int i=1;i<ntail;i++){
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    switch(dir){
    case 1:
        headx--;
        break;
    case 3:
        headx++;
        break;
    case 2:
        heady--;
        break;
    case 4:
        heady++;
        break;
    default:
        break;
    }
    if(headx>width || headx<0 || heady>height || heady<0){
        gameover=true;
    }
    for(int i=0;i<ntail;i++){
        if(tailx[i]==headx && taily[i]==heady){
            gameover=true;
        }
    }

    if(headx==fruitx && heady==fruity){
        score++;
        fruitx=rand()%width;
        fruity=rand()%height;
        ntail++;
    }
}

//just sleep function so that game will be bit slow
void sleep(){
    for(int i=0;i<10000000;i++){
        //for(int j=0;j<100000000;j++){
        //}
    }
}
int main(){
    setup();
    while(!gameover){
        draw();
        input();
        logic();
        sleep();
    }

    cout<<"Game over"<<endl;
    cout<<"Final Score= "<<score<<endl;

    while(1){
        _getch();
    }
    return 0;
}
