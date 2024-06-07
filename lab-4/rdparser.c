/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/

// The grammar is S -> AB | BC, A -> a, B -> b, C -> S | e

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char *ptr;
char input[100];

int S(), A(), B(), C(); 

int S()               //function for checking the terminal S->AB|BC
{
    if(A()){
        if(B()){
            return(1);
        }
        else{
            return(0);
        }
    }
    else if(B()){
        if(C()){
            return(1);
        }
        else{
            return(0);
        }
    }
    else{
        return(0);
    }
}


int A()                       //function for checking the terminal A->a
{
    if(*ptr == 'a'){
        ptr++;
        return(1);
    }
    else{
        return(0);
    }
}


int B()                   //function for checking the terminal B->b
{
    if(*ptr == 'b'){
        ptr++;
        return(1);
    }
    else{
        return(0);
    }
}

int C()                        //function for checking the terminal C->S|e
{
    if(S()){
        return(1);
    }
    else{
        return(1);
    }
}

int main(int argc, char *argv[])           //main function with string as argument
{
    if(argc != 2)
    {
        printf("Invalid number of arguments\n");
        return(0);
    }
    printf("The grammar is: \nS -> AB | BC\nA -> a\nB -> b\nC -> S | e\n");
    printf("The string is: %s\n", argv[1]);
    ptr = argv[1];

    if(S() && *ptr == '\0'){
        printf("String is accepted by the grammar\n");
        return(0);
    }
    else{
        printf("String is not accepted by the grammar\n");
        return(1);
    }

    return(0);
}