/*
Name:P.Veera Abhiram
Roll.no:CS21B2026*/
#include<stdio.h>

void main(){
    FILE *rp;
    FILE *wp;
    char text[50];

   rp=fopen("input.txt","r");
   wp=fopen("output.txt","w");
   while(fgets(text,10,rp)) {
    fputs(text,wp);
   }
    fclose(rp);
    fclose(wp);
}