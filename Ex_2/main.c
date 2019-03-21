#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(void)
{
    	int h = 0;
    	Node *n = InsereAVL(NULL, 30, &h);
    	n = InsereAVL(n, 15, &h);
    
    	//PreOrdem(n);
    
    	n = InsereAVL(n, 58, &h);
    	n = InsereAVL(n, 40, &h);
    	n = InsereAVL(n, 2, &h);
    	n = InsereAVL(n, 5, &h);
    	n = InsereAVL(n, 48, &h);
        
    	printf("\n\n%d \n", NodeMaxValue(n, 7));



    return 0;
}