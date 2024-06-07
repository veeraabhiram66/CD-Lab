/*
Name:P.Veera Abhiram
Roll.no:CS21B2026*/
#include<stdio.h> 

void main(){  
FILE *fp;  
char text[50];  
    
    
fp=fopen("input.txt","r");
while(fgets(text,10,fp))  
printf("%s",text);  
    
fclose(fp);  

}  