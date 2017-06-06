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

/*This function decides how the computer will
  play the game.
*/

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


int set_mode();
char if_win(char(*)[3],char,char);
int  play(char,char,char(*)[3]);
struct graphic_use{
	int x,y;
	bool you_win;
	bool we_win;
	bool we_both_win;
};

struct graphic_use game_on(int,int);//returns required values for gui use
void init(char);//function to initialize the user and engine charactar(x and o)
int ask_user(char);//ask user for position
void  if_end();//function to find whether game ends as a draw
bool if_end_graphic();//draw function to be used by gui
void reset_game();//start new game
struct graphic_use game_start();//function to start game as o
