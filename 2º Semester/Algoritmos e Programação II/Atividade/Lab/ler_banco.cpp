#include <stdio.h>

struct ClientData {
    int AcctNum;
    char LastName[15];
    char FirstName[10];
    float balance;
};


int main () {
    int i, nread;
    struct ClientData client;
    FILE *f;

    f = fopen("credit.dat", "rb");
    if (f == NULL) {
        printf("Arquivo nao pode ser aberto!\n");
        return 1;
    }
    
    printf("%-6s %-16s %-11s %10s \n", "Acct", "Last Name", "First Name", "Balance");
 
    while (!feof(f)) {
        nread = fread(&client, sizeof(struct ClientData), 1, f);
        if (nread <= 0) break;
        if (client.AcctNum != 0) {
        printf("%-6d %-16s %-11s %10.2f \n", client.AcctNum, client.LastName, client.FirstName, client.balance);
        }
    }
    
    fclose(f);
    return 0;
}