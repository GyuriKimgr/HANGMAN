//
//  GameFuctions.h
//  HANGMAN
//
//  Created by SUNJAE on 2023/01/02.
//

#ifndef GameFuctions_h
#define GameFuctions_h

#include "Hangman.h"
#include "Signup.h"

extern WORDS data[];
extern char *engword[];
extern char *krmeaning[];

// 게임 구현에 사용된 함수

void SavingWordData(void){
    for (int i=0;i<30;i++){
        data[i].word=engword[i];
        data[i].meaning=krmeaning[i];
   }
   return;
}

WORDS GeneratingProblem(WORDS ans){ //정답 구조체 데이터 생성 후 반환. 랜덤하게 생성
    srand((int)time(NULL));
    int i=rand()%30;
    ans.word=data[i].word;
    ans.meaning=data[i].meaning;
    
    return ans;
}

char *Init(char currentstat[], int len){ //정답 입력 상태를 초기화 시키는 함수
    for(int i=0;i<len;i++){
        currentstat[i]='_';
    }
    return currentstat;
}

int SearchAndPrint(char currentstat[],char answer[], char alph){ //사용자가 입력한 문자가 정답에 있는지 검사하고 결과를 출력하는 함수 (존재하면 0, 존재하지 않으면 -1반환)
    int flag=-1;
    for (int i=0;i<strlen(answer);i++)
        if (answer[i]==alph){
            currentstat[i]=alph;
            flag=0; //존재
        }
    printf("결과: %s\n",currentstat);
    return flag;
    
}

void PrintHANGMAN(int rmchance, int flag){ //결과에 따라 행맨 상태를 출력해주는 함수
    printf("남은 기회: < %d >번. ",rmchance);
    if (flag==-1) printf("행맨이 그려지고 있어요. .\n");
   // printf("\n");
    return;
}

int CheckingAnswer(char *input, char answer[]){ //정답인지 확인하는 함수
    if (strcmp(input, answer)==0) return 0;
    return -1;
}

void PrintingResult(int n, WORDS ans){
    if (n==-1) printf("틀렸습니다. 정답: %s %s\n",ans.word, ans.meaning);
    
    else if (n==0){
        for (int i=0;i<4;i++) printf("*- + - * - +");
        printf("\n");
        for (int i=0;i<4;i++) printf("*- + - * - +");
        printf("\n");
        printf("                !!!!정답입니다!!!!                 \n");
        printf("         정답: %s %s\n",ans.word, ans.meaning);
        for (int i=0;i<4;i++) printf("*- + - * - +");
        printf("\n");
        for (int i=0;i<4;i++) printf("*- + - * - +");
    }
    return;
}



void UpdatingRecord(char *userid,int flag){ // user가 play한 기록이 있는지(기록 파일에 ID가 있는지 검사하고 있으면 새로 갱신, 없으면 추가하는 함수) , 정답이면 flag=1, 오답이면 0
    FILE *f=fopen(RCFNAME,"a+");
    if(ExistsId(userid)!=-1){
        //이미 전적이 존재하는 경우 -> 파일을 부분적으로 수정하여 기록 갱신
        return;
    }
    
    fprintf(f,"%s %d\n",userid,flag); //전적 없는 경우새 행에 추가
    fclose(f);
    return;
}

int compare (const void* a, const void* b) //qsort 비교함수 (내림차순)
{
    if (((RECORD*)a)->correctanswer < ((RECORD*)b)->correctanswer)
        return 1;
    else if (((RECORD*)a)->correctanswer > ((RECORD*)b)->correctanswer)
        return -1;
    else
        return 0;
}










#endif /* GameFuctions_h */
