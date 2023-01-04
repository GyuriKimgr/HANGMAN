//
//  hang_words.c
// 단어, 난이도, 한글 의미 저장


char *engword[30]={ //단어, 품사 (형10 명10 동10)
    "quantity","evolution","agreement","donation","tendency",
    "unique","entity","decision","tablet","reservation",
    "speak","realize","determine","recognize","require",
    "include","explain", "practice","identify", "investion",
    "nevertheless","inspiration","bilingual","automatically","translation",
    "comfortable","representation","intelligible","survivability","drawback"
};

char *krmeaning[30]={ //의미
    "n.양, 수량","n.진화","n.동의","n.기부","n.경향",
    "n.독특함","n.실제","n.결정","n.태블릿","n.예약",
    "v.말하다","v.실현하다","v.결정하다","v.인식하다","v.요구하다",
    "v.포함하다","v.설명하다","n.연습","v.식별하다","n.투자",
    "adv.그럼에도 불구하고","n.영감","adj.이중 언어를 사용하는","adv.자동적으로","n.번역",
    "adj.편안한","n.묘사, 대표자, 항의","adj.지적인","n.생존 가능성","n.결점"};

int level[30]={ //난이도 1-5 중간 3
    3,3,2,2,3,
    2,3,3,2,3,
    1,3,3,3,3,
    3,3,3,3,4,
    4,4,4,4,4,
    4,5,5,5,5
};



