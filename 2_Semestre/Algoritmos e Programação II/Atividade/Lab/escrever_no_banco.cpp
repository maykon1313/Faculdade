#include <stdio.h>

struct ClientData {
    int AcctNum;
    char LastName[15];
    char FirstName[10];
    float balance;
};


int main() {
    struct ClientData client;
    FILE *f;
    
    f = fopen("credit.dat", "rb+");
    
    printf("Digite o número da conta (1 a 100, -1 para sair): ");
    scanf("%d", &client.AcctNum);
    
    while (client.AcctNum != -1) {
        printf("Enter lastname, firstname e balance: ");
        scanf("%s %s %f", client.LastName, client.FirstName, &client.balance);
        
        fseek(f, (client.AcctNum - 1) * sizeof(struct ClientData), SEEK_SET);
        fwrite(&client, sizeof(struct ClientData), 1, f);
        
        printf("Digite o número da conta (1 a 100, -1 para sair): ");
        scanf("%d", &client.AcctNum);
    }
    
    fclose(f);
    return 0;
}