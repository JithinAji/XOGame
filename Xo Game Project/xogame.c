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


#ifdef GUI     //Define GUI (-DGUI) while compiling to compile the interface.

#include <gtk/gtk.h>
#include <gio/gio.h>
#include "xogame.h"
#define XIMAGE "/usr/share/XOGame/resources/X.png"
#define OIMAGE "/usr/share/XOGame/resources/O.png"
#define EIMAGE "/usr/share/XOGame/resources/empty.png"


void main(int argc,char* argv[]){

    gtk_init(&argc, &argv);
  
    int status;

    GtkWidget       *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "/usr/share/XOGame/xogame.glade", NULL); //Creating builder object from xogame.glade file.

    window = GTK_WIDGET(gtk_builder_get_object(builder, "xogame-window"));
    gtk_builder_connect_signals(builder, NULL);

    window_abt = GTK_WIDGET(gtk_builder_get_object(builder, "about_dialog"));

    label=GTK_LABEL((gtk_builder_get_object(builder, "message_label")));

    reveal=GTK_REVEALER(gtk_builder_get_object(builder, "reveal_credits"));

    combo=GTK_COMBO_BOX(gtk_builder_get_object(builder, "character_combo"));

    
 
    buttons[0]=GTK_BUTTON(gtk_builder_get_object(builder, "A"));            //Getting buttons by their id.
    buttons[1]=GTK_BUTTON(gtk_builder_get_object(builder, "B"));
    buttons[2]=GTK_BUTTON(gtk_builder_get_object(builder, "C"));
    buttons[3]=GTK_BUTTON(gtk_builder_get_object(builder, "D"));
    buttons[4]=GTK_BUTTON(gtk_builder_get_object(builder, "E"));
    buttons[5]=GTK_BUTTON(gtk_builder_get_object(builder, "F"));
    buttons[6]=GTK_BUTTON(gtk_builder_get_object(builder, "G"));
    buttons[7]=GTK_BUTTON(gtk_builder_get_object(builder, "H"));
    buttons[8]=GTK_BUTTON(gtk_builder_get_object(builder, "I"));

    load_images();

    reset=GTK_BUTTON(gtk_builder_get_object(builder, "reset_button"));


    g_object_unref(builder);  

    gtk_widget_show(window);
    gtk_main();

  }

  void btn_clicked(GtkButton *button){

    //setting the clicked button's image.
    gtk_widget_set_sensitive((GtkWidget *)reset, TRUE);
    gtk_widget_set_sensitive((GtkWidget *)combo, FALSE);

    if(count>=5)   //User only allowed 5 clicks.
    return;

    if(xo=='X')
    gtk_button_set_image(button,GTK_WIDGET(ximages[count]));   //Will set 'X' on the clicked button.
    else if(xo=='O')
    gtk_button_set_image(button,GTK_WIDGET(oimages[count]));   //Will set 'O' on the clicked button.
      
    gtk_widget_set_sensitive ((GtkWidget *)button, FALSE);

    count++;

    const char* c=gtk_buildable_get_name(GTK_BUILDABLE(button));  //To find the button's id to find it's position values.eg (1,1) or (2,1) etc.

    struct graphic_use values;  //Defined in engine.h

    struct point userpoint=getValue(c);  //To store position x,y

    values=game_on(userpoint.x,userpoint.y);  

    if(values.you_win)              //Checking if the user wins. See engine.c
    gtk_label_set_text (label,"You Win !");

  else if(values.we_win)            //Checking if the engine wins. See engine.c
    gtk_label_set_text (label,"I Win !");
  
  else if(values.we_both_win)       //Checking if the match is a tie. See engine.c
    gtk_label_set_text (label,"It's a tie !");
  
  else{
  setButtonPic(values.x,values.y);   //Calling the function that sets the image on the position (button) selected by the engine.
  return;}

  setButtonPic(values.x,values.y);
  disable_all();                    //Disable all buttons if anybody wins or the match is tied.
  }

  struct point getValue(const char* x){           //Function to convert button name(char) to respective coordinates (struct point).
    struct point temp;

    //If xo="X" that means user's character is 'X' so, we need to use 'O' here.
    switch(*x){
      case 'A':
      temp.x=0;
      temp.y=0;
      break;
      case 'B':
      temp.x=0;
      temp.y=1;
      break;
      case 'C':
      temp.x=0;
      temp.y=2;
      break;
      case 'D':
      temp.x=1;
      temp.y=0;
      break;
      case 'E':
      temp.x=1;
      temp.y=1;
      break;
      case 'F':
      temp.x=1;
      temp.y=2;
      break;
      case 'G':
      temp.x=2;
      temp.y=0;
      break;
      case 'H':
      temp.x=2;
      temp.y=1;
      break;
      case 'I':
      temp.x=2;
      temp.y=2;
      break;
      default:
      temp.x=-1;
      temp.y=-1;
    }
    return temp;
  }

  void setButtonPic(int x,int y){               //This function sets the image of the button which the engine has selected.

    GtkImage *temp[5];
    int j;

    if(xo=='X')                         //Checking what the engine's character is and swapping the image arrays as needed.
     for(j=0;j<5;j++)
     temp[j]=oimages[j];
    else if(xo=='O')
    for(j=0;j<5;j++)
    temp[j]=ximages[j];

    switch(x){                                   //To put the image of the engine's character on the correct button.

      case 0:
      switch(y){
        case 0:
        gtk_button_set_image(buttons[0],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[0], FALSE);
        break;
        case 1:
        gtk_button_set_image(buttons[1],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[1], FALSE);
         break;
        case 2:
        gtk_button_set_image(buttons[2],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[2], FALSE);
         break;
      }
       break;

      case 1:
      switch(y){
        case 0:
        gtk_button_set_image(buttons[3],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[3], FALSE);
         break;
        case 1:
        gtk_button_set_image(buttons[4],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[4], FALSE);
         break;
        case 2:
        gtk_button_set_image(buttons[5],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[5], FALSE);
         break;
      }
       break;

      case 2:
      switch(y){
        case 0:
        gtk_button_set_image(buttons[6],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[6], FALSE);
         break;
        case 1:
        gtk_button_set_image(buttons[7],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[7], FALSE);
         break;
        case 2:
        gtk_button_set_image(buttons[8],GTK_WIDGET(temp[count]));
        gtk_widget_set_sensitive ((GtkWidget *)buttons[8], FALSE);
         break;
      }
       break;
    }
  }

void change_character(GtkComboBox *box){            //To change the user's character (X or O).

    int i=gtk_combo_box_get_active(box);

    if(i==1){
    xo='O';
    reset_all();
    /**
    count=0;
    struct graphic_use gd;
    gd=game_start();
    setButtonPic(gd.x,gd.y); 
    count++;       **/                     //The Engine makes the first move.
    }
   
    else if(i==0){
    xo='X';
    reset_all();                        //If X is selected, any X put by previously selecting O is to be removed.
    gtk_widget_set_sensitive((GtkWidget *)combo, FALSE);
    }
   
  }

  void disable_all(){                                //The function that disables all the buttons.
    int i;

    for(i=0;i<9;i++)
    gtk_widget_set_sensitive((GtkWidget *)buttons[i], FALSE);
  }

  void load_images(){                               //The function that loads the images for X,O and the empty images into appropriate arrays.See xogame.h
    int i;

    for(i=0;i<5;i++){
      ximages[i]=(GtkImage *)gtk_image_new_from_file(XIMAGE);
      oimages[i]=(GtkImage *)gtk_image_new_from_file(OIMAGE);
    }

    for(i=0;i<9;i++)
    empty_images[i]=(GtkImage *)gtk_image_new_from_file(EIMAGE);    //The empty images that are put on the buttons when reset button is clicked are loaded here.
  }

  void reset_all(){ 
                                       //This function handles removing images of buttons and resetting the board (see engine.h) for a new game
   int i;

   gtk_label_set_text (label,"Here we go again !");
    
    for(i=0;i<9;i++){
    gtk_button_set_image(buttons[i],GTK_WIDGET(empty_images[i]));
    
    gtk_widget_set_sensitive((GtkWidget *)buttons[i], TRUE);}         //Enabling the buttons again for the new game.
     
    gtk_widget_set_sensitive((GtkWidget *)reset, FALSE);              //Disabling the reset button.
    gtk_widget_set_sensitive((GtkWidget *)combo, TRUE);               //Enabling the combobox that allows user to pick 'X' or'O'. 
          
    reset_game();          //resetting the board from the engine.See engine.h
    count=0;     //Resetting the counter that prevents user from clicking more that 5 buttons.
    load_images();  //Reloading images.
    if(xo=='O'){
    struct graphic_use gd;
    gd=game_start();
    setButtonPic(gd.x,gd.y);
    }
  }


void on_gtk_about_activate(){               //This function shows the about dialog.
 
  gtk_widget_show(window_abt);
}

void close_about(GtkButton *btn){          //This function closes the about dialog.If gtk_widget_destroy is used, the window won't be available if 'About' from menu is clicked again.

gtk_widget_hide (window_abt);
}

int revealed=0;  //This variables holds the state of the Credits revealer in about dialog. 0 means Credits are not revealed. 1 means Credits are revealed.

void reveal_credits(GtkButton *credits){               //Function to reveal the GtkRevealer in about dialog based on the value of int revealed.

  if(revealed==0){
  gtk_revealer_set_reveal_child (reveal,TRUE);
  revealed=1;}

  else{
  gtk_revealer_set_reveal_child (reveal,FALSE);
  revealed=0;}
}

#endif

// END OF FILE