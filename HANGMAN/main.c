//
//  main.c
//  HANGMAN
//
//  Created by SUNJAE on 2023/01/02.
//
/* 핵심 구현 기능
1. 사용자 정보 저장  -> (id, passwd/ 최근 시도 횟수, 최고점, 랭킹 )구조체 배열로 관리
2. id,passwd 입력-> id, passwd 일치해야 게임 시도 가능
3. 저장된 단어 중 랜덤하게 하나 선택 -> 정해진 수 만큼의 기회 주어짐.
4. 게임 시작 -> 5글자라면 _____제시, 단어 품사 제시 행맨 상태 제시
5. 게임 중-> 사용자에게 알파벳 입력 받은 후, "검색 알고리즘" 사용해서 일치하면 출력, 없으면 기회 -1. 행맨 상태 출력
6. 게임 종료-> 다 맞추거나/ 기회 다 쓰면 종료, 정답과 뜻도 함께 제시
7. id, 몇번만에맞췄는지, 글자 난이도 기록
8. 글자 난이도/몇번만에 맞췄는지 클수록 1등
 */

#include "Hangman.h" //구조체 및 단어 데이터를 저장한 변수 정의
#include "Fuctions.h" //함수 정의 헤더 파일

Words data[30]; //단어 정보를 저장할 구조체 배열의 전역변수 선언

int main(void) {
    
    SavingWordData(); //단어별 데이터 저장
    
    srand((int)time(NULL));
    LOGIN User[MAX_USER];
    int temp,endinput=0;
    int num,num2; //로그인에 성공한 사용자의 계정 정보
    FILE *lgf=fopen(LGFNAME, "r");
    int usercnt=GetTotalLine(lgf); //파일의 행 수(저장된 사용자의 수)
    
   //로그인 및 회원가입
    
    printf("====  << HANGMAN GAME >>  ====\nLogin and Play the game!!\n\n");
    printf("1. 로그인 하기\n2. 새로 등록하기\n"); scanf("%d",&temp);
    char *input_id=(char *)malloc(16); char *input_pwd=(char *)malloc(6);
    while(temp!=3){
        switch(temp){
            case 2: //회원가입
                NewUser(usercnt,User);
                usercnt++;
                temp=1;
                break;
                
            case 1: //로그인
                printf("로그인 ID를 입력하세요: "); scanf("%s",input_id);
                num=ExistsId(input_id);
                
                if (num==-1){ //id가 존재하지 않음
                    printf("사용자의 ID를 찾을 수 없음.\n1. 새로 등록하기\n3. 종료하기\n"); scanf("%d",&temp);
                    if (temp==1) NewUser(usercnt,User); //회원가입
                    else {
                        printf("게임을 종료합니다 . . .");
                        return 0;}
                }
                else{  //id가 존재함
                    do {
                        printf("PASSWORD를 입력하세요 (종료하려면 -1입력): "); scanf("%s",input_pwd);
                        if (strcmp(input_pwd,"-1")==0) {
                            endinput=1; break;
                        }
                        num2=CheckPwd(input_pwd,num);
                    } while(num2==-1);
                    free(input_pwd);
                    temp=3; //로그인 성공
                }
                break;
        }
    }
    fclose(lgf);
    
  //게임 기능 부분
    RECORD Record[MAX_USER];
    if(endinput!=1){
        FILE *rkf=fopen(RKFNAME, "r");
        Words answer; //정답 단어에 대한 정보를 저장할 구조체
        char input_chr; //사용자가 입력
        int rcdcnt=GetTotalLine(rkf);
        num2=isThereRecord(input_id); //기록이 있는지 확인
        
        do {
            printf("\n\n1. 게임 시작\n2. 랭킹 보기\n3. 종료하기\n"); scanf("%d",&temp);
            if(temp==1){ //game start!!!
                char currentstat[20]; //사용자가 답을 입력 할 때마다 보여줄 문자열
                answer=GeneratingProblem(answer); //정답 데이터 생성
                int len=(int)strlen(answer.word);
                Init(currentstat,len);
                printf("3초 뒤에 시작합니다.(* 기회는 %d번!)\n",len);
                for (int i=3;i>=1;i--) {
                    printf("%d!\n",i); sleep(1);}
                printf("%s\n",currentstat);
                int flag;
                for(int j=0;j<len;j++){
                    sleep(0.8);
                    printf("\n알파벳 소문자를 하나 입력하세요(정답을 입력하려면 !입력): ");
                    scanf(" %c",&input_chr);
                    if(input_chr!='!'){
                        flag=SearchAndPrint(currentstat,answer.word,input_chr); //flag: 0 or -1
                        PrintHANGMAN(len-j-1,flag); //행맨 상태 출력
                    }
                    else { //정답 입력
                        printf("정답은?: ");
                        scanf("%s",currentstat);
                        int n=CheckingAnswer(currentstat,answer.word);
                        printf("loading..\n\n");
                        sleep(1);
                        if (n==-1) {
                            printf("틀렸습니다. 정답: %s %s\n",answer.word, answer.meaning);
                            break;
                        }
                        else if (n==0) {
                            for (int i=0;i<4;i++) printf("*- + - * - +");
                            printf("\n");
                            for (int i=0;i<4;i++) printf("*- + - * - +");
                            printf("\n");
                            printf("                !!!!정답입니다!!!!                 \n");
                            printf("         정답: %s %s\n",answer.word, answer.meaning);
                            for (int i=0;i<4;i++) printf("*- + - * - +");
                            printf("\n");
                            for (int i=0;i<4;i++) printf("*- + - * - +");
                            break;
                        }
                    }
                }
                
            }
            else if(temp==2){ //랭킹 출력
                printf("==========게임 기록 정보==========\n");
                printf(".  랭킹    id     시간(초)   난이도\n");
                ShowRankfile();
            }
       } while(temp!=3);
        free(input_id);
        fclose(rkf);
    }
    
    
    
    printf("게임을 종료합니다 . . . \n");
    
    
    
    
    
    return 0;
}



