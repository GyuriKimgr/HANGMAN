//
//  Hangman.h
//  HANGMAN
//
//  Created by SUNJAE on 2023/01/02.
//

#ifndef Hangman_h
#define Hangman_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Sleep()사용
#define MAX_USER 10000 //최대 사용자 수
#define LGFNAME "/Users/sunjae/Desktop/HANGMAN/HANGMAN/hnguser.txt"
#define RKFNAME "/Users/sunjae/Desktop/HANGMAN/HANGMAN/hngrecord.txt"

typedef struct{ //등록된 사용자의 정보를 user.txt 파일에 기록하기 위한 구조체
    char id[16]; //id: 영문자,숫자 포함 최대 15자리
    char pwd[6]; //password 숫자 최대 5자리
}LOGIN;


typedef struct{
    char *word; //단어
    int level; //난이도
    char *meaning; //의미
}Words;

typedef struct{ //user1 기회 난이도 . 가장 마지막 플레이 기준. 랭킹
    char *id;
    int score; //cnt*5
    int totalsecond; // 초
}RECORD;



#endif /* Hangman_h */
