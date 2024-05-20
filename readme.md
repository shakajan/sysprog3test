0. mystdio.h 파일에 fwrite, fread, fopen, fclose, feof, fflush, fseek을 구현한다.
1. mystdio.h 파일을 이 디렉터리에 추가한다.
2. 프롬프트에서 `make custom` 입력.
3. 프롬프트에서 `./test_custom` 입력.
4. 결과 감상.

#### 시스템에서 제공하는 헤더파일로 컴파일한 결과를 보고싶으면
다음 과정을 통해 mystdio.h 가 아닌 stdio.h 헤더파일로 테스트 파일을 컴파일한다.
1. 프롬프트에서 `make std` 입력.
2. 프롬프트에서 `./test_std` 입력.
3. 결과 감상.
`./test_std` 결과 assertion fail이 발생한다면 꼭 메일로 연락 주시기 바랍니다..ㅠ

## NOTICE
- 명세되지 않는 부분은 되도록 빼려고 했는데
- 명세랑 다르게 assert를 수행한다고 생각되신다면 알려주시면 감사하겠습니다..
- email: 255theend@gmail.com

## TEST ENVIRONMENT
- replit (UBUNTU 20.04.2 LTS, bash, gcc 11.3.0)
- mac (Sonoma 14.4.1, zsh, clang 15.0.0)
