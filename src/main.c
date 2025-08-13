#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int port = 8080;
    if (argc > 1) port = atoi(argv[1]);
    return 0;
}