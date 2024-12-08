#include <stdio.h>
int main(){
    int num, divisor = 3;
    bool n_achou_divisor = true, primo = false;
    
    scanf("%d", &num);
    
    if (num == 2) {
        primo = true;
        
    } else if (num > 2) {
        if (num%2 != 0){
            while ((divisor < num) && (n_achou_divisor)) {
                if (num%divisor == 0) {
                    n_achou_divisor = false;
                } else {
                    divisor += 2;
                }
            }
            
            if (n_achou_divisor){
                primo = true;
            }
            
        }
        
    }
    
    if (primo){
        printf("Número primo.");
    } else {
        printf("Não é primo.");
    }
    
    
    return 0;
}