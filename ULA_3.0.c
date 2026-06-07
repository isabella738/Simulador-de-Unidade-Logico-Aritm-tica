#include <stdio.h>
#include <string.h>
#include <math.h>

/*ULA 3.0
1. Processa numeros negativos
2. Subtrações feitas de forma mais fiel
3. Não há suporte para float
*/

void soma_binaria(int n1[], int n2[], int n3[]){
    int carry=0, b;
    for(int i=31; i>=0; i--){
        int c=carry;
        if(!n1[i] && !n2[i] && !carry){b=0; carry=0;}
        else if(n1[i] && !n2[i] && !carry){b=1; carry=0;}
        else if(!n1[i] && n2[i] && !carry){b=1; carry=0;}
        else if(!n1[i] && !n2[i] && carry){b=1; carry=0;}
        else if(n1[i] && n2[i] && !carry){b=0; carry=1;}
        else if(n1[i] && !n2[i] && carry){b=0; carry=1;}
        else if(!n1[i] && n2[i] && carry){b=0; carry=1;}
        else if(n1[i] && n2[i] && carry){b=1; carry=1;}

        n3[i]=b;
        if(i==0 && c!=carry)printf("Ocorreu um erro.\n");
    }
}

void complemento(int n[]){
    int x[32]={0}, um[32]={0}; um[31]=1;
    for(int i=0; i<32; i++){n[i]=!n[i]; x[i]=n[i];}
    soma_binaria(x, um, n);
}

void conversao_int(int n[], int num){
    int i=31, ngt=0;
    if(num<0){ngt=1; num=-num;}
    while(num!=0 && i>=0){
        n[i]=num%2;
        num /= 2; i--;
    }
    if(ngt)complemento(n);
}

int conv_Decimal(int n[]){
    int num=0, ngtv=0;
    if(n[0]==1){ngtv=1; complemento(n);}
    for(int i=31; i>0; i--){
        num+= n[i]*pow(2, 31-i);
    }
    if(ngtv)num=-num;
    return num;
}

int main(){
    while(1){
        int num1, num2, num3, n1[32]={0}, n2[32]={0}, n3[32]={0}, verdade=0;
        char c;
        scanf("%d %c %d", &num1, &c, &num2);

        if(c=='-')num2=-num2;// (A-B) <-> (A+(-B))

        conversao_int(n1, num1); conversao_int(n2, num2);

        if(c=='>'){
            if(n1[0]<n2[0])verdade=1;
            else if(n1[0]>n2[0])verdade=0;
            else for(int i=0; i<32; i++)if(n1[i]>n2[i]){verdade=1; break;}
        }
        else if(c=='<'){
            if(n1[0]>n2[0])verdade=1;
            else if(n1[0]<n2[0])verdade=0;
            else for(int i=0; i<32; i++)if(n1[i]<n2[i]){verdade=1; break;}
        }
        else if(c=='='){
            verdade=1;
            for(int i=0; i<32; i++)if(n1[i]!=n2[i]){verdade=0; break;}
        }
        if(c=='-' || c=='+'){
            soma_binaria(n1, n2, n3);
            num3 = conv_Decimal(n3);
            printf("%d\n", num3);
        }
        else{
            if(verdade)printf("Verdadeiro\n");
            else printf("Falso\n");
        }

        //Verificação
        /*
        printf("\nverif\n");
        for(int i=0; i<32; i++){
            printf("%d", n1[i]);
        }
        printf("\n");
        for(int i=0; i<32; i++){
            printf("%d", n2[i]);
        }
        printf("\n");
        */
    }
    return 0;
}