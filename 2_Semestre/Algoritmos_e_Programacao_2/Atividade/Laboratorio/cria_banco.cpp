#include <stdio.h>

struct ClientData {
    int AcctNum;
    char LastName[15];
    char FirstName[10];
    float balance;
};


int main() {
    int i;
    struct ClientData client = {0,"","", 0.0};
    FILE *f;
    
    f = fopen("credit.dat", "w");
    
    for (i = 0; i < 100; i++) fwrite(&client, sizeof(struct ClientData), 1, f);
    
    fclose(f);
    return 0;
}