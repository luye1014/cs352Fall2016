#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myToc(char * str){
    int spcCount = 0;
    int ptrIndex = 0;

    int n = strlen(str);

    for(int i = 0; i < n; i++){
        if(i != 0 && str[i] == ' ' && str[i-1] != ' '){
            spcCount++;
        }
    }

    char **ptr = calloc(spcCount+2, sizeof(char*));
    //ptr[spcCount+1] = '\0';//0 initialized by calloc 
    char temp = ' ';//can simplify the code

    for(int j = 0; j < n; j++){
        if(str[j] == ' '){
            temp = str[j];
            str[j] = '\0';
        } else if(str[j] != '\0' && temp == ' '){//can omit `str[j] != ' ' &&`
            ptr[ptrIndex++] = &str[j];
            temp = str[j];
        }
    }

    int k = 0;
    while(ptr[k] != NULL){//better use NULL
        printf("%s \n", ptr[k++]);
    }
    free(ptr);
}

int main(){
    char test1[] = "a b c";
    myToc(test1);
    char test2[] = "hello world";
    myToc(test2);
    return 0;
}