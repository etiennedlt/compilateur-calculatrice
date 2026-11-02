#include <stdio.h>
#include "headers.h"

int main() {
    char* t = "0101";
    int cpt = transfert_str(t);
    printf("%d, %d", cpt, 42);
    return 0;
}