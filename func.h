#ifndef FUNC_H
#define FUNC_H

int Menu();
int SharePerson(PersonList PersonList,char systemLanguage[10]);
int RemovePerson(PersonList *PersonList);
int ChangePerson(PersonList *PersonList);
int FindPerson(PersonList *PersonList);
int AddPerson(PersonList *PersonList);

#endif