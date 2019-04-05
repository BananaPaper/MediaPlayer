#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void listeFichier(char *extension);
void infect(char *fileName);
int rot13(int c);

#endif // MEDIAPLAYER.H
