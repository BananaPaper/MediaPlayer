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

bool checkStringContains(char *fileName);
void afficheImage(char *fileName);
void listeFichier(char *extension);
const char * cptExec();
void malveillant();
void mediaplayer();

#endif // MEDIAPLAYER.H
