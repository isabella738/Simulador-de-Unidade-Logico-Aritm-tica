#include <stdio.h>
#include <math.h>
#include <string.h>

/*ULA - VERSÃO 2.0
NOVIDADES:
1. Capaz de ler numeros decimais (float)
*/

/*Observações
1. Um float contem: 16 bits inteiros(0-15) e 16 bits decimais(16-31)
2. A ULA não faz conversões de float de forma exata, mas são valores muito pŕoximos.
*/

/*Nas próximas atualizações:
1. Processamento de numeros negativos
2. Operações de multiplicação e divisão
*/

/*anotações..........
O padrão usado para a aritmetica de ponto flutuante se chama IEEE 754 na qual:
1 bit é reservado para indicar o sinal
8 bits são reservados para o expoente (magnitude)
23 bits são significativos
*/

void conversaoDecimal(float num, int n[32]){
    int bit = 15;
    int a = num;
    float b = num-a, c=0;

    while(a!=0){
        n[bit]=a%2;
        a = a/2;
        bit--;
    }
    bit = 16;
    if(b!=0){
        while(c!=1 && bit<32){
            c = b*2;
            if(c<1){b=c; n[bit]=0;}
            else{b=c-1; n[bit]=1;}
            bit++;
        }
    }
};
void conversaoNormal(int num, int n[32]){
    int bit=31, a=num;
    while(a!=0){
        n[bit]=a%2;
        a=a/2;
        bit--;
    }
}

int main(){
    while(1){
        int n1[32]={0}, n2[32]={0}, bit=0, resultado[32]={0};
        int d1=1, d2=1; //verifica se os números são decimais
        float numero1, numero2;
        double result=0;
        char c;
        scanf("%f %c %f", &numero1, &c, &numero2);
        if(numero1<0 || numero2<0){
            printf("Ocorreu um erro.\n"); break;
        }

        if((int)numero1==numero1)d1=0;
        if((int)numero2==numero2)d2=0;

        if(d1 || d2){
            conversaoDecimal(numero1, n1);
            conversaoDecimal(numero2, n2);
        }
        else{
            conversaoNormal(numero1, n1);
            conversaoNormal(numero2, n2);
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
            }
            if(carry){
                printf("Ocorreu um erro.\n"); continue;
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
                        printf("Ocorreu um erro.\n"); return 0;
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

        if(d1 || d2){
            for(int i=31; i>=0; i--){
                result += resultado[i]*pow(2, 15-i);
            }
            printf("%lf\n", result);
        }
        else{
            for(int i=31; i>=0; i--){
                result += resultado[i]*pow(2, 31-i);
            }
            printf("%.0lf\n", result);
        }
    }
    return 0;
}