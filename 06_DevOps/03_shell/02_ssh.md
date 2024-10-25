# SSH (Secure Shell)
SSH (Secure Shell)는 네트워크를 통해 다른 컴퓨터에 안전하게 접속하고 명령을 실행할 수 있게 해주는 프로토콜이다. 주로 원격 서버에 접속하여 관리 작업을 수행하는 데 사용한다.

이번 파일에서는 Windows 원격 컴퓨터와 macOS 로컬 컴퓨터를 SSH 를 통해 연결하려 한다.

[목차]

## 1. SSH 의 주요 기능
- 보안성 : 클라이언트와 서버 간의 모든 데이터 전송을 암호화하여 중간 공격자로부터 보호한다.
- 원격 관리 : SSH 를 통해 원격 서버에 안전하게 접속하여 명령을 실행할 수 있다.
- 파일 전송 : SCP 명령어를 통해 파일을 안전하게 복사할 수 있다.
- 포트 포워딩 : 원격 서버의 특정 포트를 로컬 머신으로 안전하게 전달하여 내부 네트워크 서비스에 접근할 수 있다.
- 원격 터널링 : SSH 를 사용하여 안전한 네트워크 터널을 생성하여 보안이 필요한 데이터 전송을 가능하게 한다.

## 2. Windows 원격 컴퓨터와 macOS 로컬 컴퓨터를 연결하려면
- Windows 원격 컴퓨터 설정
- macOS 로컬 컴퓨터 설정
- SSH 연결

위 순서대로 작업을 진행하면 된다.

## 3. 공개 키란?
공개 키는 공개 키 암호화 방식에서 사용되는 키 중 하나로,
다른 사용자와 안전하게 공유할 수 있는 키이다.
SSH 에서는 공개 키를 사용하여 원격 서버에 대한 인증을 수행한다.

사용자는 자신의 공개 키를 원격 서버에 추가하여,
해당 서버에 접속할 수 있는 권한을 부여 받는다.
공개 키는 일반적으로 .pub 확장자를 가진 파일로 저장된다.

결론 : 공개 키가 원격 서버에 등록 되어 있으면, 해당 서버로 접속할 수 있는 권한을 부여 받는다.

## 4. 개인 키란?
개인 키는 공개 키와 쌍을 이루는 키로, 소유자만 알고 있어야 하는 비밀 키이다.

SSH 에서는 개인 키를 사용하여 원격 서버에 대한 인증을 수행한다.
개인 키는 절대로 다른 사람과 공유해서는 안 되는 키로,
일반적으로 ~/.ssh/id_rsa 와 같은 경로에 저장된다.

결론 : 개인 키는 서버에 저장될 필요가 없는, 남들과는 공유해서는 안 되는 비밀 키이다.

## 5. 서버는 어떻게 공개 키 암호화 방식을 사용하는가?

1. 클라이언트는 공개 키와 개인 키를 생성. 공개 키와 개인 키는 클라이언트마다 다름.
2. 클라이언트의 공개 키를 서버에 등록.
3. 클라이언트는 공개 키와 개인 키를 가지고 SSH 를 통해 서버에 연결을 시도
4. 서버는 인증 요청을 보냄
5. 클라이언트는 자신의 개인 키를 사용하여 인증 요청에 대한 서명을 생성
6. 서명은 단 하나의 공개 키와 매핑되므로, 서버는 공개 키 리스트를 순회하며 유효성 검증.
7. 유효하면 접속을 허용, 그렇지 않으면 접속을 거부.