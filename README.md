# 프로젝트 주제 : 콘솔창으로 하는 행맨 게임 (Using C)
# 주제 선정 이유
: 이 프로젝트는 제가 프로그래밍 공부를 시작 한 후 '지금까지 배운 것을 활용하여 무언가를 내 힘으로 개발해 봐야겠다.' 라는 생각으로 처음 시작하게 된 토이 프로젝트인만큼, 제가 지금까지 배운 것들을 최대한 활용한 기존 지식+추가로 필요한 내용을 공부하면서 개발에 대한 감을 잡기 위해 접하기 쉬우면서 비교적 구현하는데에 많은 배경지식이 필요하지 않은 영어 단어 맞추기인 행맨 게임을 주제로 잡았습니다. <br/> 이 프로젝트는 복잡하고 뛰어난 기능을 가지거나 어플/웹으로 시각화되어 구현된 것도 아닌 단순한 기능의 콘솔 게임이지만, 이 프로젝트를 개발하면서 제가 지금까지 배운 지식을 복습하고, 제가 넣고 싶은 기능을 구현하는 데에 알맞게 활용하고, 개발 중 발생한 에러를 해결하는 디버깅 과정 등에서 이전엔 알지 못했던 다양한 지식과 경험을 얻을 수 있었습니다.<br/> 그래서 저는 이런 작은 경험들을 토대로 더욱 공부하고 실력을 쌓아 사용자에게 필요한 창의적인 서비스를 제공하거나 사용자가 겪는 현실적인 불편함을 해소시킬 수 있는 더욱 전문적인 프로그램을 개발하고 싶습니다.

# 프로젝트 구성 파일 설명
1. main.c : main 함수가 존재하는 파일, 로그인 기능 / 게임 기능으로 크게 두 부분으로 나누었다.
2. Hangman.h : 필요한 헤더파일, 매크로, 구조체, 단어별 데이터 등 변수를 따로 선언해놓은 헤더파일
3. Signup.h : 로그인/회원가입 시 필요한 함수들을 정의한 헤더파일
4. GameFunctions: 게임 기능 구현에 필요한 함수들을 정의한 헤더파일
5. hnguser.txt: 회원 유저의 id,pwd가 저장된 텍스트 파일
6. hngrecord.txt: 유저의 게임 플레이 기록 (id, 정답을 맞춘 단어 개수)가 저장된 텍스트 파일

# 프로젝트 핵심 기능, 게임 규칙 설명
1. 로그인 및 회원가입 프로그램
: 본 프로젝트에는 회원 별 id, 비밀번호를 관리하는 로그인 및 회원가입 기능이 구현하였다. 해당 기능에 필요한 함수들은 Signup.h 파일에 정의했고 로그인 및 회원가입 기능은 main.c 파일 첫번째 부분에 구현해 놓았다. 간단히 처음 게임 시작 시 유저는 새로 회원가입을 하거나/기존 저장된 정보를 사용하여 로그인을 할 수 있다.<br>
새로 회원가입을 할 경우, NewUser()를 호출하여 영소문자+숫자로 구성된 id(15자리이내), 5자리 이내 숫자로 구성된 비밀번호를 사용자로부터 입력받아 user.txt파일에 한 행씩 공백을 두고 저장한다. 이때 이미 존재하는 id인지 검사 후 중복된 id로는 회원가입을 할 수 없도록 했다.<br>
로그인 시, 기존에 저장되어있던 user.txt 파일 내용을 읽어서 먼저 id가 존재하는지 검사하고, 존재하지 않는다면 존재하지 않는다는 메시지와 함께 다시 회원가입을 하게 하거나 게임을 종료하게 하고/ id가 존재한다면 해당 id의 비밀번호를 물어 일치할 경우 로그인 성공, 아닐 경우 계속해서 비밀번호를 물어보게 한다. 이때 id와 pwd를 한번에 편하게 다루기 위해 사용자의 로그인 정보를 저장하는 두 가지 변수를 멤버로 갖는 LOGIN 구조체를 선언하고 사용했다. 

2. 게임 부분
: 행맨 게임은 사용자로부터 매 턴마다 알파벳을 하나 입력받고, 그 알파벳이 정답 문자열에 존재하면 기회를 날리지 않고, 존재하지 않으면 기회를 -1번 날리게 한다. 따라서 게임의 기회가 처음부터 정해져 있는 것이 아니라 사용자가 입력하는 알파벳에 따라 달라지게 구현해야한다. 만약 기회를 일정한 정수로 정해놓고 for문을 돌리면 실제 남은 기회가 다하기도 전에 게임이 종료되는 것으로 잘못 구현될 것이다. 
따라서 만약 남은 기회가 4번일 때 사용자가 정답 문자열에 없는 알파벳을 입력하면 기회가 한번 줄어 3번이 되지만, 존재하는 알파벳을 입력했을 경우 여전히 4번의 기회를 사용할 수 있도록 구현해야 한다.<br>
따라서 이 기능을 구현할 때에는 최초로 (영어 단어의 길이+5) 번의 기회가 주어지고, 반복의 횟수가 정해진 for문이 아닌 while문을 사용하여 매 턴마다 chance에 flag변수 (사용자가 입력한 알파벳이 문자열에 존재하면 0, 존재하지 않으면 -1을 반환하는 정수 변수) 값을 더하면서 chance가 0이 될 때까지 반복한다.<br>
로그인을 완료한 사용자는 바로 게임을 시작하거나, 저장된 랭킹을 보거나, 게임을 종료할 수 있다. 게임을 시작할 경우 카운트와 함께 바로 위의 규칙대로 게임이 진행되고 해당 사용자의 게임 기록 (id,정답유무)대로 이벤트를 발생시키고 기록 정보를 hngrecord.txt 파일에 저장한다. 이때 파일에 유저의 게임 전적이 없다면 새 행에 추가하고 있다면 정답 맞춘 횟수를 갱신한다. 이 부분은 파일 입출력과 수정에 관한 문제로 아직 구현중이다.<br> 
랭킹은 hngrecord.txt 파일에 저장된 유저 별 전적을 토대로 출력된다. 먼저 파일의 id와 각 사용자의 정답 횟수를 읽어와서 따로 구조체에 저장한 뒤, 전체 단어 30개 중 맞춘 단어가 많은 순대로 내림차순 정렬하여 등수를 산출하여 출력한다. 이 부분도 추후 구현 예정이다. 사용자가 종료를 원할 경우 게임은 종료되며 한번 빌드 할 때마다 로그인한 한 계정의 플레이 기록만 다루는 것을 가정한다. 빌드를 여러 번해도 한 번 플레이한 유저의 정보가 남아있어야 하기 때문에 대부분 주요 기능을 c 파일 입출력 기능을 활용하여 로그인 정보나 게임 기록을 기록 저장하였다. 

    



# 개발 중 발생한 에러 디버깅 / 프로그램 개선 과정

1. 로그인/회원가입 시 id나 passwd를 사용자로부터 입력받아 파일에 저장하거나 대조할 때, 사용자의 실수로 '한글'이 입력될 경우 발생한 에러
   : 본래 게임의 id 및 비밀번호는 영문자와 숫자로 구성된다. 그러나 테스트 중 다음과 같은 에러가 발생할 수 있음을 알게 되었다.

   1) 사용자가 실수로 '한글'을 입력했을 경우 -> 콘솔창에서 회원 가입까지는 정상 작동하는 것처럼 보이나 인코딩 문제로 파일에 자소 분리 현상이 일어나 로그인 시 사용하는 SearchId, CheckPwd 함수에서 에러가 발생했다.
   2) enter키를 누르기 전에 '한글'을 입력했다가 지우고 다시 입력했을 경우 -> 로그인 시) 썼다 지운 한글이 사라지지 않고 입력 버퍼에 남아 있어 로그인 시 에러가 발생했다. 회원가입 시) 엔터를 입력하기 전에 지운 내용이 사라지지 않고 그대로 남아 파일에 저장되어 로그인 시 에러가 발생했다. 한글이 파일에 저장되었기 때문에 이후 user.txt 파일이 '인코딩 에러' 메시지와 함께 열리지 않았다. 
      비슷한 에러들을 모두 구글링 해 본 결과 delete 키를 글자 수 보다 더 많이 누르면 정상적으로 작동한다고 했고 실제 테스트로 사실임을 확인했다. 하지만 원인과 해결 방법까지는 정확히 알 수 없었다.

=> mac 운영체제에서 한글을 인코딩 하는 방법에 있어서 문제가 있는 것으로 생각되며 1번 상황의 경우 로그인 시 '사용자를 찾을 수 없음'이라는 오류 메시지와 함께 다시 회원가입 단계로 돌아가 처음부터 영어로 새로 등록하도록 했고, 2번 에러 상황의 경우 리눅스 환경에서 실행 시 제대로 작동함을 확인하였다. mac에서도 정상적으로 실행시킬 수 있는 방법을 추후에 더 찾아봐야겠다.

2. 로그인 시 id를 검색 및 passwd 대조하는 과정에서 발생한 에러
   : Check함수를 사용하여 passwd 대조 시, 다음과 같은 에러가 발생할 수 있음을 확인했다.
    ex) <파일에 저장된 내용(id pwd)> "user2 2222"
        input_pwd에 "2222"가 입력될 경우,<br>
        올바른 결과: 로그인이 정상적으로 수행됨 / 잘못된 결과: passwd가 일치하지 않아 CheckPwd 함수에서 -1반환

    =>  기존에 사용한 함수는 두 문자열을 한 문자씩 모두 비교하여 모두 같으면 0을 반환하는 strcmp 함수를 사용했다. 해당 함수의 첫번째 인자는 파일에 저장된 passwd이고 두번째 인자는 사용자로부터 입력받은 input_pwd이다. strlen 함수로 두 문자열의 길이를 확인해본 결과, 두 문자열의 길이가 상이하며 첫번째 인자의 뒤에 붙은 개행문자로 인해 위와 같은 에러가 발생했음을 알게 되었다. 첫번째 인자는 fgets()로 전체 행을 입력받아 strtok() 함수를 사용하여 두번째 토큰인 passwd를 분리한 결과로 얻어진 것이다. fgets()는 입력받은 문자열 맨 뒤에 개행문자를 붙이기 때문에 이 개행문자를 널 문자로 대체하는 작업을 추가하여 에러를 해결했다.  

        (추가한 코드) buffer[strlen(buffer)-1]='\0'; 
        
 3. goto문법 수정
    : 기존 로그인/회원가입 프로그램을 구현할 때, 단순히 (회원가입->로그인 / 로그인 시도->id를 찾을 수 없음->새로 회원가입) 매커니즘을 직관적으로 보여주면서 편하다는 이유로 goto 문법을 사용했다. 그런데 goto문법은 c언어의 절차적 특성을 무시하면서 자칫하면 코드의 가독성을 떨어뜨릴 수 있다는 것을 알게되어 회원가입 프로세스를 main에 넣고 goto를 사용하는 대신 NewUser() 함수를 따로 만들어서 호출하고, 새로운 while문을 추가하고 그 아래에 switch문의 temp값을 변경시켜 매커니즘을 구현하는 방법으로 수정하였다.
    
 4. 파일 입출력시 내용 수정하기
    : 플레이어의 게임 기록을 저장하고 갱신하기 위해, 유저 별 전적을 파일에 따로 저장하고 필요할 때마다 가져오는 작업의 기능이 필요했다. 따라서,<br>
 1) 사용자가 게임을 플레이 할 때마다 hngrecrod.txt 파일에 "userid 정답을 맞춘 횟수" 내용을 각 행에 저장한다.
 2) 유저가 플레이를 마치면, 그 유저의 id가 해당 파일에 기록되어 있는지 (전적이 있는지) 확인한 후 없다면 새 행에 추가하고, 있다면 그 행에서 정답을 맞춘 횟수 부분을 업데이트한다.
  

 


