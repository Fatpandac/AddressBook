#ifndef TUIFUNC_H
#define TUIFUNC_H

void InitWindows();
int DisplayPersion(PersonList personList);
char *formatTag(char *formatContent,tag tag);
char *formatTitle(char *formatContent,TitleElement titleElement);
void TUIRemovePerson(PersonList *personList,PersonList *outputPerson);
void TUIChangePerson(PersonList *personList,PersonList *outputPerson);
void TUIAddPerson(PersonList *personList,PersonList *outputPerson);
void DoFliter(PersonList personList,char fliterName[5],PersonList *fliterPerson);
char *formatIndex(char *formatContent,TitleElement titleElement,PersonList PersonList);
void FliterPerson(PersonList personList,PersonList *outputPerson,PersonList *fliterPerson,char fliterName[6]);

#endif