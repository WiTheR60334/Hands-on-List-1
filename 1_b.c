#include<stdio.h>
#include<unistd.h>

int main(){
    if(link("files/original.txt", "files/hardlink_sys")==-1){
        perror("hardlink");
    } else {
        printf("Hard link created successfully.\n");
    }
    return 0;
}