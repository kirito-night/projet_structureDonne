#include "Hachage.h"

int fonctionCle(int x, int y)
{
    return y+((x+y)*(x+y+1))/2; 
}