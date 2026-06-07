#include <stdio.h>
#include <string.h>
#include <math.h>

/*SIMULADOR DE ULA - VERSÃO 1.0
1. Adição, comparação(>, <, =) e subtração (com resultado positivo)
2. Entradas ou resultados menores que zero resultam em erro
3. Numero caractere numero, separados por espaço
4. Arquitetura de 32 bits
5. Leitura somente de números inteiros.
*/

int main(){

    while(1){
        int numero1, numero2, n1[32]={0}, n2[32]={0}, bit=0, resultado[32]={0};
        double result_num=0;
        char c;
        scanf("%d %c %d", &numero1, &c, &numero2);
        if(numero1<0 || numero2<0){
            printf("Ocorreu um erro.\n"); break;
        }

        while(numero1!=0){//conversão decimal>binario
            n1[bit]=numero1%2;
            numero1=numero1/2;
            bit++;
        }
        bit=0;
        while(numero2!=0){
            n2[bit]=numero2%2;
            numero2=numero2/2;
            bit++;
        }
        
        for(int i=0; i<16; i++){//inversão das strings n1 e n2
            int a = n1[i];
            n1[i] = n1[31-i];
            n1[31-i] = a;

            int b = n2[i];
            n2[i] = n2[31-i];
            n2[31-i] = b;
        }

        if(c=='+'){//ADIÇÃO
            int carry = 0;
            for(int i=31; i>=0; i--){
                int a = n1[i], b = n2[i], r[2];

                if(a&&b){r[0]=1; r[1]=0;}
                else if(!a&&!b){r[0]=0; r[1]=0;}
                else {r[0]=0; r[1]=1;}

                if(carry && r[1]){r[0]=1; r[1]=0;}
                else if(carry && !r[1])r[1]=1;

                carry = r[0];
                resultado[i]=r[1];
                //printf("%d, %d = carry:%d; bit:%d\n", a, b, r[0], r[1]);
            }
            if(carry){
                printf("Ocorreu um erro.\n"); return 0;
            }
        }
        else if(c=='-'){//SUBTRAÇÃO
            for(int i=31; i>=0; i--){
                int a = n1[i], b = n2[i];
                if(a-b>=0)resultado[i]=a-b;
                else{
                    int continuar=0;
                    for(int j=i-1; j>=0; j--){
                        if(n1[j]==1){
                            continuar=1;
                            n1[j]=0; resultado[i]=1;
                            break;
                        }
                        else n1[j]=1;
                    }
                    if(!continuar){
                        printf("Ocorreu um erro\n"); return 0;
                    }
                }
            }
        }
        else{//COMPARAÇÕES
            int verdade=0; 

            if(c=='>'){
                for(int i=0; i<32; i++){
                    if(n1[i]==n2[i])continue;
                    else if(n1[i]>n2[i]){
                        verdade=1; break;
                    }
                    else break;
                    
                }
            }
            else if(c=='<'){
                for(int i=0; i<32; i++){
                    if(n1[i]==n2[i])continue;
                    else if(n1[i]<n2[i]){
                        verdade=1; break;
                    }
                    else break;
                }
            }
            else if(c=='='){
                verdade=1;
                for(int i=0; i<32; i++){
                    if(n1[i]!=n2[i]){
                        verdade=0; break;
                    }
                }
            }
            if(verdade)printf("Verdadeiro.\n");
            else printf("Falso.\n");
            continue;
        }

        for(int i=31; i>=0; i--){
            result_num += resultado[i]*pow(2, 31-i);
        }
        printf("%.0f\n", result_num);
    }

    return 0;
}