//
//  Fuctions.h
//  HANGMAN
//
//  Created by SUNJAE on 2023/01/02.
//

#ifndef Fuctions_h
#define Fuctions_h

#include "Hangman.h"

extern Words data[];
extern char *engword[];
extern int level[];
extern char *krmeaning[];

// 로그인 및 회원가입 프로그램 함수
void NewUser(int usercnt,LOGIN User[]){
    FILE *f=fopen(LGFNAME, "a+");
   
    usercnt++;
    printf("ID를 입력하세요(영어,숫자 포함 15자리 이내): "); scanf("%s",User[usercnt].id);
    printf("PASSWORD를 입력하세요(숫자 5자리 이내): "); scanf("%s",User[usercnt].pwd);
    
    fprintf(f,"%s %s\n", User[usercnt].id, User[usercnt].pwd); //파일에 구조체 내용 쓰기
    fclose(f);
    printf("\n회원가입 완료! 로그인 후 게임을 시작해보세요.\n");
}




int GetTotalLine(FILE *f){ // 파일의 행의 개수를 구하는 함수. 파일 열기 에러 처리 완료
    if (f!=NULL){
        int line=0; char c;
        while((c=fgetc(f))!=EOF)
            if(c=='\n') line++;
        fclose(f);
        return line;
    }
    return -1; //파일 열기 실패
}

int GetletterinOneline(int line){ //파일 내 특정 행의 공백 포함 글자 수를 구하는 함수. 파일 열기 에러 처리 완료
    FILE *f=fopen(LGFNAME, "r");
    if (f!=NULL){
        int count1=0; char buffer[23];
        
        while(fgets(buffer,23,f)!=NULL){
            count1++;
            if (count1==line) break;
        }
        fclose(f);
        return (int) strlen(buffer);
    }
    return -1; //파일 열기 실패
}


int ExistsId(char *input){ // 입력받은 id가 user파일에 존재하는지 검사하는 함수 (없다면 -1반환)
    FILE *f=fopen(LGFNAME, "r");
    char buffer[25]; char *buffer2;
    int i=1;
    int letters=GetletterinOneline(i);
   
    if (f!=NULL){
        while (fgets(buffer,letters+2, f)!=NULL) {
            buffer2=strtok(buffer," ");
            if (strcmp(buffer2,input)==0) return i;
            else{
                ++i;
                letters=GetletterinOneline(i);
            }
        }}
    fclose(f);
    
    return -1;
    
}


 


int CheckPwd(char *input,int line){ // 입력이 user파일에서 특정 id와 매칭되는 패스워드와 일치하는지 검사하는 함수 (일치하지 않는다면 -1반환)
    FILE *f=fopen(LGFNAME, "r");
    char *buffer=malloc(25);
    int i=1;
    int letters=GetletterinOneline(i);
    
    while(fgets(buffer,letters+2,f)!=NULL){
        letters=GetletterinOneline(i);
        if (i==line) break;
        i++;
    } //line번째 행에 도달할때까지 각 행을 buffer에 저장함.
    buffer[strlen(buffer)-1]='\0'; //개행문자 제거

    char *pwd=strtok(buffer," "); //strtok: 문자열 분리 함수," "를 기준으로 (id/pwd)를 구분함
    buffer=pwd;
    pwd=strtok(NULL," "); //pwd 문자열이 마지막 토큰이 되고 해당 문자열의 주소를 리턴함
    if(strcmp(pwd,input)==0){
        printf("< %s >님, 반가워요!!\n (loading. .)\n\n",buffer); //login success
        free(buffer);
        sleep(1);
        return line;  //로그인 한 회원의 정보가 저장된 line 리턴
    }
      
    return -1; //불일치
}





// 게임 구현에 사용된 함수

void SavingWordData(void){
    for (int i=0;i<30;i++){
        data[i].word=engword[i];
        data[i].level=level[i];
        data[i].meaning=krmeaning[i];
   }
   return;
}

Words GeneratingProblem(Words ans){ //정답 구조체 데이터 생성 후 반환. 랜덤하게 생성
    int i=rand()%30;
    ans.word=data[i].word;
    ans.level=data[i].level;
    ans.meaning=data[i].meaning;
    
    return ans;
}

char *Init(char currentstat[], int len){ //정답 입력 상태를 초기화 시키는 함수
    for(int i=0;i<len;i++){
        currentstat[i]='_'; //중간에 공백으로 한칸 띄울 수 있으면 좋겠음 ->출력문에서 해결?
    }
    return currentstat;
}

int SearchAndPrint(char currentstat[],char answer[], char alph){ //사용자가 입력한 문자가 정답에 있는지 검사하고 결과를 출력하는 함수
    int flag=0;
    for (int i=0;i<strlen(answer);i++)
        if (answer[i]==alph){
            currentstat[i]=alph; flag=1; //존재
        }
    printf("결과: %s\n",currentstat);
    if (flag==1) flag=0;
     
    else{
        
        flag=-1;
    }
    return flag;
   
}

void PrintHANGMAN(int rmchance, int flag){ //결과에 따라 행맨 상태를 출력해주는 함수
    printf("남은 기회: %d번. ",rmchance);
    if (flag==-1) printf("행맨이 그려지고 있어요\n");
    printf("\n");
    return;
}

int CheckingAnswer(char *input, char answer[]){ //정답인지 확인하는 함수
    if (strcmp(input, answer)==0) return 0;
    return -1;
}


int isThereRecord(char *userid){ // user가 play한 기록이 있는지 검사하는 함수 (없다면 -1반환)
    FILE *f=fopen(RKFNAME, "r");
    if (f!=NULL){
        char buffer[25]; char *buffer2;
        int i=1;
        int letters=GetletterinOneline(i);
        
        while (fgets(buffer,letters+2, f)!=NULL) {
            buffer2=strtok(buffer," ");
            if (strcmp(buffer2,userid)==0) return i; //기록이 있는 행 번호 리턴
            else{
                ++i;
                letters=GetletterinOneline(i);
            }
        }}
    fclose(f);
    return -1; //기록이 없음
    
}




void WritePlayingRecord(RECORD rcd[], int rcdcnt){
    FILE *f=fopen(RKFNAME,"a+");
    if(f!=NULL){
        fprintf(f,"   %s   %d개 %d초\n",rcd[rcdcnt].id,rcd[rcdcnt].score,rcd[rcdcnt].totalsecond);
        fclose(f);
    }
    else{
        printf("파일 열기 실패\n");
        return;
    }
    
}

void ShowRankfile(void){
    FILE *rkf=fopen(RKFNAME, "r");
    if (rkf!=NULL){
        int i=1;
        int letters=GetletterinOneline(i);
        char *buffer=malloc(40);
        while(fgets(buffer,letters+2,rkf)!=NULL){
            letters=GetletterinOneline(i);
            printf("%s",buffer);
            i++;
        } //line번째 행에 도달할때까지 각 행을 buffer에 저장함.
        fclose(rkf);
    }
    else {
        printf("파일 열기 실패\n");
        return;}
    return;
}



#endif /* Fuctions_h */
