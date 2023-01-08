//
//  test.c
//  HANGMAN
//
//  Created by SUNJAE on 2023/01/08.
//


#include "Hangman.h"
int main(void){
    char buffer[20],*p=NULL;
    FILE *cnt=NULL; //cnt값을 저장할 파일포인터
    FILE* f=fopen(RCFNAME,"r+");
    int findpos=0;
    while (fgets(buffer,20,f)!=NULL) {
        if (strstr(buffer,"user1")!=NULL) { //id 검색 (strstr: 문자열 안에 특정 문자열이 포함되어있는지 확인)
            p=strtok(buffer, " ");
            p=strtok(NULL," "); //buffer안에서 맞춘개수의 시작 위치가 p에 저장됨 (문자열 포인터임)->파일 포인터로 변환
            fseek(f,-2,SEEK_CUR);
            fwrite("",4,1,f);
            break;
        }
        fclose(f);
        break;
    }
    return 0;
}
    
