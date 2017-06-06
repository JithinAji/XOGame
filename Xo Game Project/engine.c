/**Copyright (C) 2017 Jithin Aji

This file is part of XO Game.

XO Game is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

XO Game is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XO Game.  If not, see <http://www.gnu.org/licenses/>. **/
/*This file is to be run to play the game.
*/

#include <stdio.h>
#include <stdlib.h>
#include "draw_board.h"
#include "engine.h"

char user_char='x',engine_char='o';
char board[3][3]={{'.','.','.'},{'.','.','.'},{'.','.','.'}};
//char board[3][3]={"...","...","..."};//initializes an empty board
int position_pick=0,i,j;

#ifdef CLI
//this main function is used for command line play
void main() {

  char ch;
  int n,mode;
  char win;
  struct graphic_use gd;

  printf("\n\n***********\n");
  printf("* WELCOME *\n");
  printf("***********");
  printf("\n\n\nThis is a minimal xo game written purely in c with no gui.\n\n\nAuthor name:Jithin\nMail:jithin396@gmail.com\n");
  printf("The position values are as follows\n\n\n");
  show_pos(board);
  printf("\n");

  mode=set_mode();//ask single or multiplayer modes
	
  if(mode==1){	
	  printf("\nEnter your character('x' or 'o'):");
	  scanf("%c",&ch);
	  init(ch);
	  draw(board);
	  if (user_char=='x') {
		goto user;
	  }
	  else{
		goto engine;
	  }
	  user:n=ask_user(user_char);
	  draw(board);
	  win=if_win(board,user_char,engine_char);
	  if (win=='y') {
		printf("You Win!!!\nThank you and play again :-)\n\n");
		exit(0);
	  }
	  if_end();
	  goto engine;
	  engine:printf("Thinking\n");
	  position_pick=play(user_char,engine_char,board);
	  //printf("%d\n",position_pick);
	  j=position_pick%10;
	  position_pick/=10;
	  i=position_pick%10;
	  board[i][j]=engine_char;
	  draw(board);
	  win=if_win(board,user_char,engine_char);
	  if (win=='y') {
		printf("You Loose!!!\nBetter luck next time :-(\n\n");
		exit(0);
	  }
	  if_end();
	  goto user;
	}
	else{
		win='n';
		user_char='x';
		engine_char='o';
		cont:i=ask_user(user_char);
		draw(board);
		win=if_win(board,user_char,engine_char);
		if(win=='y'){
			printf("x wins the game");
			exit(0);
		}
		if_end();
		i=ask_user(engine_char);
		draw(board);
		win=if_win(board,user_char,engine_char );
		if(win=='y'){
			printf("y wins the game");
			exit(0);
		}
		draw(board);
		goto cont;	
	}
}
#endif


void init(char ch) {
	char x;
    if (ch=='x') {
	  user_char='x';
      engine_char='o';
    }
    else if (ch=='o') {
	  user_char='o';
      engine_char='x';
    }
    else {
      scanf("%c",&x);
      init(x);
    }
}

int ask_user(char user_char){//use getline function
  int x,y,success=0;
  while(success==0){
    fflush(stdin);
    printf("\n\nEnter the position(3 3 to display available positions):\n");
    scanf("%d %d",&x,&y);
    if(x>=0 && x<3){
      if(y>=0 && y<3){
        if(board[x][y]=='.')
        {
          board[x][y]=user_char;
          return 0;
        }
      }
    }
    if (x==3 && y==3) {
      show_pos(board);
    }
    else{
    printf("Invalid Choice\n");
  }
  }
}

void if_end() {
  int i,j;
  int success=0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (board[i][j]=='.') {
        success+=1;
        break;
      }
    }
  }
  if (success==0) {
    printf("\nGame Drawn.Atleast you ain't a looser :-|\n\n");
    exit(0);
  }
}

int draw(char c[3][3]) {
  int i=0,j,pos=0;
  for ( i = 0; i < 5; i++) {
    if (i%2==0) {
      for ( j = 0; j < 3; j++) {
        printf(" %c ",c[pos][j]);
        if (j!=2) {
          printf("|");
        }
      }
      printf("\n");
      pos++;
    }
    else{
      printf("---+---+---\n");
    }
  }
  return 1;
}

void show_pos(char c[3][3]) {
  int i,j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (c[i][j]=='.') {
        printf("%d %d",i,j );
      }
      else{
        printf("   ");
      }
      if (j!=2) {
        printf("|");
      }
    }
    printf("\n");

    if (i!=2) {
    printf("---+---+---");
    printf("\n");
    }
  }
}

int  play(char user_char,char engine_char,char board[3][3]) {

  int pos_value[3][3]={0,0,0,0,0,0,0,0,0};
  int value;
  char win;
  int i,j,x;
  int incase=-1;
  int r_values,ch_values;
  srand(time(NULL));
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (board[i][j]=='.') {
        board[i][j]=engine_char;
        win=if_win(board,user_char,engine_char);
        if (win=='y') {
          board[i][j]='.';
          value=i*10+j;
          return value;
        }
        board[i][j]='.';
      }
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (board[i][j]=='.') {
        board[i][j]=user_char;
        win=if_win(board,user_char,engine_char);
        if (win=='y') {
          board[i][j]='.';
          value=i*10+j;
          return value;
        }
        board[i][j]='.';
      }
    }
  }
  again:
  for (i=0;i<3;i++){
    for (j = 0; j < 3; j++) {
      if (board[i][j]=='.') {
        if (incase==1) {
          return i*10+j;
        }
        value=0;
        for (x=0;x<3;x++) {
          if (x!=i) {
            if (board[x][j]==user_char) {
              value+=-9;
            }
            else if (board[x][j]==engine_char) {
              value+=10;
            }
            else{
              /* do nothing */
            }
          }
          if (abs(value)>15) {
            return i*10+j;
          }
          }
        for (x=0;x<3;x++) {
          if (x!=j) {
            if (board[i][x]==user_char) {
              value+=-9;
            }
            else if (board[i][x]==engine_char) {
              value+=10;
            }
            else{
              /* do nothing */
            }
            if (abs(value)>15) {
              return i*10+j;
            }
          }
        }
        if (i==j) {
          for (x=0;x<3;x++) {
            if (x!=i) {
              if (board[x][x]==user_char) {
                value+=-9;
              }
              else if (board[x][x]==engine_char) {
                value+=10;
              }
              else{}
              if (board[x][2-x]==user_char) {
                value+=-9;
              }
              else if (board[x][2-x]==engine_char) {
                value+=10;
              }
              else{}
              /*if (abs(value)>15) {
                return i*10+j;
              }*/
            }
          }
        }
        pos_value[i][j]=value;
            }
          }
        }
        value=pos_value[0][0];
        r_values=00;
        for (i = 0; i < 3; i++) {
          for (j = 0; j < 3; j++) {
            //printf("%d\n",pos_value[i][j] );
            if (pos_value[i][j]==value){
              //pull randomly
              if(rand()%100>80){
              r_values=i*10+j;}
            }
            if (pos_value[i][j]>value) {
              value=pos_value[i][j];
              r_values=i*10+j;
            }
          }
        }
        //printf("r_values= %d\n",r_values );
        ch_values=r_values;
        j=ch_values%10;
        ch_values/=10;
        i=ch_values;
        if(board[i][j]=='.'){
        return r_values;
      }
      else{
        incase=1;
        goto again;}
    }

char if_win(char board[3][3],char user_char,char engine_char){//completed
  int i,j;
  char r_value='n';
  int count_u=0;
  int count_w=0;
  for(j=0;j<3;j++){
    count_w=count_u=0;
    for (i = 0; i < 3; i++) {
      if(board[j][i]!='.'){
        if (board[j][i]==user_char) {
          count_u+=1;
       }
        else{
          count_w+=1;
        }
      }
      else{break;}
      if (count_u==3) {
        r_value='y';
      }
      else if (count_w==3) {
        r_value='y';
      }
    }
  }
  for(j=0;j<3;j++){
    count_w=count_u=0;
    for (i = 0; i < 3; i++) {
      if(board[i][j]!='.'){
        if (board[i][j]==user_char) {
          count_u+=1;
       }
        else{
          count_w+=1;
        }
      }
      else{break;}
      if (count_u==3) {
        r_value='y';
      }
      else if (count_w==3) {
        r_value='y';
      }
    }
  }
  count_u=count_w=0;
  for (i = 0; i < 3; i++) {
    if (board[i][i]==user_char) {
      count_u++;
    }
    else if (board[i][i]==engine_char) {
      count_w++;
    }
  }
  if (count_u==3) {
    r_value='y';
  }
  else if(count_w==3){
    r_value='y';
  }
  count_u=count_w=0;
  for (i = 0; i < 3; i++) {
    if (board[i][2-i]==user_char) {
      count_u++;
    }
    else if (board[i][2-i]==engine_char) {
      count_w++;
    }
  }
  if (count_u==3) {
    r_value='y';
  }
  else if(count_w==3){
    r_value='y';
  }
  return r_value;
}


struct graphic_use game_on(int x,int y){
  struct graphic_use decide;
  decide.we_both_win=false;
	decide.we_win=false;
	decide.you_win=false;
	decide.x=decide.y=-1;
	int r_num=0;
/**
	if(if_end_graphic()){
	decide.we_both_win=true;
	}**/
if(board[x][y]=='.'){
		board[x][y]=user_char;
	}
	else{
		return decide;
	}
  if(if_win(board,user_char,engine_char)=='y'){
		decide.you_win=true;
		return decide;
	}
/**	if(if_win(board,user_char,engine_char)=='y'){
		decide.you_win=true;
		return decide;
	}**/
   if(if_end_graphic()){ 
	decide.we_both_win=true;
  return decide;
	}
  	else{
		r_num=play(user_char,engine_char,board);
    //changed
		decide.y=r_num%10;
		r_num=r_num/10;
		decide.x=r_num;
    board[decide.x][decide.y]=engine_char;
	}
	if(if_win(board,engine_char,user_char)=='y'){
		decide.we_win=true;
	}	
   if(if_end_graphic()){  //to here //DUPLICATE
	decide.we_both_win=true;
	}


  return decide;
}

int set_mode(){
	int x;
	label:printf("Enter 1 for single player and 2 for multiplayer:\n");
	scanf("%d",&x);
	if(x==1 || x==2){
		return x;
	}
	else
		goto label;
}

bool if_end_graphic(){
	int i,j;
	bool r_value=false;
	  int success=0;
	  for (i = 0; i < 3; i++) {
	    for (j = 0; j < 3; j++) {
	      if (board[i][j]=='.') {
		success+=1;
		break;
	      }
	    }
	  }
	  if (success==0) {
	    r_value=true;
	  }
	return r_value;
}

void reset_game(){
 int i,j;
 for(i=0;i<3;i++){
   for(j=0;j<3;j++){
     board[i][j]='.';
   }
 }
}

struct graphic_use game_start(){
  struct graphic_use gd;
  srand(time(NULL));
  gd.x=(rand()%3);
  gd.y=(rand()%3);
  gd.you_win=gd.we_win=gd.we_both_win=false;
  if(board[gd.x][gd.y]=='.')
  board[gd.x][gd.y]=engine_char;
  return gd;
}
