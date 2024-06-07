/*
Name:P.Veera Abhiram
Roll.no:CS21B2026*/
#include<stdio.h>  
     
void main(){  
FILE *fp;  
char text[50];  
    
    
fp=fopen("output.txt","a");
fputs("Appended line",fp);
    
fclose(fp);  

}  