#include<stdio.h>

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    else {
        return b;
    }
}

int main(){
    int a,b,s,d;
    s = 10;
    a=(b*3+(4*a-s))/d;
    while(3+a*b){
        b = b - 1;
        a = a - 1;
    }
    if(s == a*b){
        a = a - 1;
        b = b - a / 2;
    }
    printf("%d\n", s);
    return 0;
}