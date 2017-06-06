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

#include "engine.h"

char xo='X';   //The variable that holds the user's character.
int count=0;   //Counts the no. of times the user clicked the buttons.
GtkImage *ximages[5];  //An array that stores the images for character 'X'
GtkImage *oimages[5];  //An array that stores the images for character 'O'
GtkImage *empty_images[9];  //An array that stores the images for empty image.Used to put on the buttons while resetting.
GtkButton *buttons[9];   //Array that stores the buttons from xogame.glade.
GtkBuilder *builder;
GtkLabel *label;  //The label that says 'You Win' or 'I Win'.
GtkButton *reset;  //The reset button.
GtkWidget *window_abt;  //The about dialog.
GtkRevealer *reveal;  //The Credits revealer in about dialog.
GtkComboBox *combo;  //The combobox for charcter selection by the user.

struct point{   //An easy way to store coordinates.
    int x,y;
};
void main(int argc,char* argv[]);

struct point getValue(const char*);

void setButtonPic(int,int);

void disable_all();

void load_images();

void reset_all();