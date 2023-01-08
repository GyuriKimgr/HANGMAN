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
#define RCFNAME "/Users/sunjae/Desktop/HANGMAN/HANGMAN/hngrecord.txt"

typedef struct{ //등록된 사용자의 정보를 user.txt 파일에 기록하기 위한 구조체
    char id[16]; //id: 영문자,숫자 포함 최대 15자리
    char pwd[6]; //password 숫자 최대 5자리
}LOGIN;


typedef struct{
    char *word; //단어
    int level; //난이도
    char *meaning; //의미
}WORDS;

WORDS data[30];

typedef struct{ //랭킹 아이디 답을 맞춘 횟수
    char *id; //아이디
    int correctanswer; //답을 맞춘 횟수/전체단어30개
}RECORD;


char *engword[30]={ //단어
    "quantity","evolution","agreement","donation","tendency",
    "unique","entity","decision","tablet","reservation",
    "speak","realize","determine","recognize","require",
    "include","explain", "practice","identify", "investion",
    "nevertheless","inspiration","bilingual","automatically","translation",
    "comfortable","representation","intelligible","survivability","drawback"
};

char *krmeaning[30]={ //품사와 의미
    "n.양, 수량","n.진화","n.동의","n.기부","n.경향",
    "n.독특함","n.실제","n.결정","n.태블릿","n.예약",
    "v.말하다","v.실현하다","v.결정하다","v.인식하다","v.요구하다",
    "v.포함하다","v.설명하다","n.연습","v.식별하다","n.투자",
    "adv.그럼에도 불구하고","n.영감","adj.이중 언어를 사용하는","adv.자동적으로","n.번역",
    "adj.편안한","n.묘사, 대표자, 항의","adj.지적인","n.생존 가능성","n.결점"};



#endif /* Hangman_h */
