#include <stdio.h>
#include <stdlib.h>

int main() {
        int n;
        printf("Combien de nombres pseudo-aléatoire à générer ? ");
        scanf("%d",&n);

        if(n>0) {
                printf("\n");
                for (int x = n ; x>0 ; x-- ) {
                        int numb = rand() % 100 +1;
                        printf(" > %d\n",numb);
                }
                printf("\n");
        }
        return 0;
}
