# Shell
Shell 은 컴퓨터 운영 체제와 사용자 간의 인터페이스 역할을 하는 프로그램이다. 사용자는 Shell 을 통해 명령어를 입력하여 운영 체제의 기능을 제어하고, 다양한 작업을 수행할 수 있다. Shell 은 주로 두 가지 형태로 존재한다.

## 1. 두 가지 형태의 Shell

### 1-1. 명령 줄 인터페이스 (CLI)
- 사용자가 텍스트 기반의 명령어를 입력하여 시스템과 상호작용하는 방식이다. 예를 들면, Linux 의 Bash Shell, Windows 의 Command Prompt, PowerShell 등이 있다.
- 사용자는 파일 관리, 프로그램 실행, 시스템 설정 등을 명령어를 통해 수행할 수 있다.

### 1-2. 그래픽 사용자 인터페이스 (GUI)
- 사용자가 마우스와 같은 입력 장치를 사용하여 시스템과 상호작용하는 방식이다. GUI 는 Shell 의 발전된 형태로 볼 수 있으며, Windows, macOS, Linux 의 다양한 데스크탑 환경이 이에 해당한다.

## 2. Shell 의 주요 기능
- 명령어 실행 : 사용자가 입력한 명령어를 해석하고 실행하낟.
- 스크립트 작성 : 복잡한 작업을 자동화하기 위해 여러 명령어를 조합하여 스크립트를 작성할 수 있다.
- 파일 및 프로세스 관리 : 파일 시스템에 접근하고, 파일을 생성, 삭제, 수정하는 등의 작업을 수행할 수 있다.
- 환경 설정 : 시스템 환경 변수를 설정하고 관리할 수 있다.

## 3. OS 별 Shell 의 종류
Shell 은 여러 종류가 있으며, 각기 다른 기능과 특성을 가지고 있다. Shell 에 대해서 깊이 있게 알아 볼 건 아니니까, 대표적인 OS 들의 대표적인 Shell 에 대해서만 알아보고 간단하게 마무리 하겠다.

## 4. Linux - Bash (Bourne Again SHell)
- Linux 의 기본 Shell 로 널리 사용된다.
- 강력한 스크립트 작성 기능과 명령어 자동 완성 기능을 제공한다.
- 히스토리 기능이 있어 이전 명령어를 쉽게 호출할 수 있다.

## 5. macOS - Zsh (Z Shell)
- macOS Catalina(10.15)부터 기본 Shell 로 설정되었다.
- Bash 와 유사하지만, 더 많은 기능과 사용자 정의 옵션을 제공한다.
- macOS 는 Bash 도 가지고 있다.

## 6. Windows - Command Prompt
- Windows 의 기본 Shell 로, 간단한 명령어를 통해 시스템 관리 및 파일 작업을 수행할 수 있다.
- GUI 환경에서 작업하는 데 적합하지 않은 간단한 텍스트 기반 인터페이스이다.

## 7. Windows - PowerShell
- Windows 의 강력한 Shell 로, 객체 지향 언어인 PowerShell 언어를 사용한다.
- 다양한 관리 작업을 자동화하고, 시스템 관리에 적합하다.
- .NET 프레임워크가 통합되어 있어 다양한 작업을 수행할 수 있다.

## 8. Windows - WSL (Windows Subsystem for Linux)
- Windows 에서 Linux 배포판을 실행할 수 있는 환경을 제공한다.
- Bash, Zsh 등의 Linux Shell 을 사용할 수 있다.
- 개발자들이 Linux 기반 도구와 환경을 Windows 에서 쉽게 사용할 수 있도록 해준다.

## 9. Unix - Bash (Bourne Again Shell)
- 많은 Linux 배포판에서 기본 Shell 로 사용된다
- Bourne Shell 의 후속 버전이다.
- Bash 는 C Shell 의 여러 기능도 포함하고 있다.

## 10. Unix vs Linux
Unix 는 1969년 AT&T 의 벨 연구소에서 상업용으로 개발된 운영체제이다. 자유 오픈소스를 주장하던 리누스 토발즈(Linus tovalds) 는 Linux 를 오픈소스로 배포한다.

Unix 는 대부분 상용 라이센스가 필요하고 비용이 발생하는 데에 비해, Linux 는 GNU GPL(General Public License) 와 같은 오픈 소스 라이센스를 사용하기 때문에 누구나 자유롭게 사용할 수 있으며, 수정 및 배포가 가능하다.

## 11. 왜 Linux 명령어를 확장해서까지 쓰는 걸까?
백엔드 개발자들은 macOS 를 사용하는 경우가 많고, 이유가 기본 Shell 이 Zsh 이며 Bash 와 유사하기 때문이라고 한다.

윈도우 또한 WSL 을 사용해서 Linux 기반 도구를 사용하는 경우를 종종 볼 수 있다. Linux 명령어를 사용하기 위해 확장해서까지 사용하는 이유는 무엇일까? 특히, 백엔드 개발자들이 더 좋아하는 이유는 무엇일까?

### 11-1. 사용자보다는 개발자를 위한 운영체제인 Linux
Linux 는 다양한 개발 도구와 유틸리티를 제공하여 개발자가 효율적으로 작업할 수 있도록 돕는다. 강력한 커맨드라인 도구, 스크립팅 기능, 패키지 관리 시스템 등이 있어 반복 작업을 자동화하고, 개발 작업을 간소화할 수 있다.

Linux 는 오픈 소스 운영체제로, 사용자들이 소스 코드를 수정하고 필요한 기능을 추가할 수 있다. 이는 개발자들이 자신에게 맞는 도구를 만들고, 커뮤니티와 협력하여 문제를 해결할 수 있는 환경을 제공한다.

### 11-2. 서버 개발에는 Windows Shell 보다 Bash 가 낫다?
많은 웹 서버가 클라우드 서비스가 Linux 기반으로 운영되기 때문에, Bash 와 같은 Unix 기반 Shell 을 사용하는 것이 실제 운영 환경과의 일관성을 높이는 데에 도움이 된다.

Bash 는 파이프와 리다이렉션, 스크립트 작성 등을 통해 복잡한 작업을 간단하게 수행할 수 있는 기능을 제공한다. 이러한 기능은 서버 관리, 자동화 및 배포 작업에서 매우 유용하다.

많은 오픈 소스 도구와 라이브러리가 Linux 환경에서 개발되었기 때문에, Bash 를 활용하면 이러한 도구들과의 호환성이 높아진다.