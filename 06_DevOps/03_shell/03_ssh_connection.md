# Windows 원격 컴퓨터 (Server 컴퓨터) 설정
Winodws 컴퓨터를 서버 컴퓨터로 등록하는 과정이다.

## 1. OpenSSH 설정 (서버 컴퓨터에서)
Windows 10 이상의 버전에서는 OpenSSH 클라이언트와 서버가 기본적으로 포함되어 있다.
설정에서 "앱 및 기능" > "선택적 기능"에서 OpenSSH 서버를 설치한다.
(OpenSSH 클라이언트와는 다르다)

## 2. SSH 서버 활성화 (서버 컴퓨터에서)
서비스 관리 도구에서 "OpenSSH SSH Server" 서비스를 시작하고,
자동으로 시작되도록 설정한다.

- Windows 키 + R을 눌러 실행 창을 연다.
- services.msc를 입력하고 Enter 키를 눌러서 서비스 관리 도구를 연다.
- 서비스 목록에서 OpenSSH SSH Server를 찾는다.
- 이름은 "OpenSSH SSH Server" 또는 "sshd"로 표시될 수 있다.
- OpenSSH SSH Server를 오른쪽 클릭하고, 시작을 선택한다.
- (서비스가 이미 실행 중이라면 이 단계를 건너뛰어도 된다.)
- OpenSSH SSH Server를 다시 오른쪽 클릭하고, 속성을 선택한다.
- 시작 유형 드롭다운 메뉴에서 자동을 선택한다.
- 확인 버튼을 클릭하여 변경 사항을 저장한다.

## 3. 방화벽 설정 (서버 컴퓨터에서)
Windows 방화벽에서 SSH 포트(기본적으로 22번 포트)가 열려 있는지 확인한다.

[방화벽에서 SSH 포트 확인하는 방법]
- 제어판 -> 시스템 및 보안 -> Windows Defender 방화벽 클릭
- 왼쪽 메뉴에서 "고급 설정" 클릭
- "인바운드 규칙" 선택 -> 새 규칙... 클릭
- "포트" 선택 후 "다음" 클릭
- "TCP" 선택 -> 특정 로컬 포트에 22 입력 -> 다음 클릭
- "연결 허용" 선택 후 -> "다음"을 클릭
- 도메인, 개인, 공용 네트워크 중에서 적용할 네트워크 유형을 선택하고 "다음"을 클릭
- (셋 다 선택하면 외부 아이피도 접근이 가능하다.)
- 규칙에 대한 이름을 입력하고 "마침"을 클릭

## 4. SSH 키 생성 (클라이언트 컴퓨터에서)
```bash
ssh-keygen -t rsa -b 4096
```

## 5. 클라이언트 컴퓨터의 공개 키를 서버 컴퓨터에 등록 (서버 컴퓨터에서)
- 공개 키를 SSH 서버의 ~/.ssh/authorized_keys 파일에 등록.

## 6. 연결 시도 (클라이언트 컴퓨터에서)
```zsh
ssh {username}@{외부아이피} -p {포트번호}
```

### 혹은

```zsh
ssh {username}@{내부아이피}
```
내부 아이피를 통해 접속하려면 같은 네트워크(와이파이 등)에 연결 되어있어야 한다.

### 예시

```zsh
ssh Admin@125.132.216.190 -p 22
```
이후 패스워드를 입력하면 된다.

## 7. 기타 도움이 되는 명령어
### 7-1. Windows PowerShell 에서 username 알아내기
```powershell
$env:USERNAME
```

### 7-2. Windows PowerShell 에서 외부 아이피 알아내기
```powershell
Invoke-RestMethod -Uri "http://ifconfig.me"
```

### 7-3. Windows PowerShell 에서 내부 아이피 알아내기
```powershell
Get-NetIPAddress | Where-Object { $_.AddressFamily -eq "IPv4" }
```