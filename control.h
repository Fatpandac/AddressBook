#ifndef CONTROL_H
#define CONTROL_H

#ifdef linux
enum keys {K_UP      = 107,
           W_UP      = 119,
           J_DOWN    = 106,
           S_DOWN    = 115,
           QUIT      = 27,
           Q_QUIT    = 81,
           FLITER    = 102,
           CHANGE    = 67,
           REMOVE    = 82,
           ADD       = 65,
           ENTER     = 10,
           BACKSPACE = 127,
           TAB       = 9};
#endif
#ifdef WIN32
enum keys {K_UP      = 107,
           W_UP      = 119,
           J_DOWN    = 106,
           S_DOWN    = 115,
           QUIT      = 27,
           Q_QUIT    = 81,
           FLITER    = 102,
           CHANGE    = 67,
           REMOVE    = 82,
           ADD       = 65,
           ENTER     = 13,
           BACKSPACE = 8,
           TAB       = 9};
#endif

int my_getch();
int my_getche();
int control(PersonList *personList,PersonList *outputPerson,PersonList *fliterPerson,char fliterName[6],char *systemLanguage);

#endif