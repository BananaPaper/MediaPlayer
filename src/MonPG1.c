#include <stdio.h>

int main() {
        int n, i = 3, count, c;
        printf("\n ==============================================\n");
        printf(" === Calcul des x premiers nombres premiers ===\n");
        printf(" ==============================================\n\n");
        printf(" x = ");
        scanf("%d",&n);

        if(n>= 1) {
                printf("\n 2\n");
        }

        for ( count = 2 ; count <= n ; ) {
                for( c = 2 ; c <= i - 1 ; c++ ) {
                        if( i%c ==0 )
                                break;
                }
                if( c==i ) {
                        printf(" %d\n",i);
                        count++;
                }
                i++;
        }
        printf("\n");
        return 0;
}
