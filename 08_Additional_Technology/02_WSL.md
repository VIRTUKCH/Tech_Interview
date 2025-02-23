# WSL

## WSL 이란?
WSL(Windows Subsystem for Linux)은 Microsoft에서 제공하는 기능으로, Windows 운영체제 내에서 Linux 환경을 네이티브하게 실행할 수 있도록 지원한다. 이 기능은 Windows와 Linux 사이의 경계를 허물어, 개발자들이 Linux 전용 도구와 애플리케이션을 Windows 환경에서 사용할 수 있게 한다.

## Linux 환경을 굳이 갖추어야 하는 이유는 무엇일까?
많은 개발자들이 Mac OS를 선호하는 이유 중 하나는, Mac OS가 Unix 기반으로 설계되어 터미널 사용과 bash 쉘 환경이 우수하기 때문이다. Linux 또한 Unix 계열로서, 서버 관리, 자동화 스크립트 작성 및 다양한 개발 도구 사용에 적합하다. 특히, Windows 환경에서 Linux 기반 서버나 클라우드 환경과의 호환성을 유지하기 위해 Linux 환경이 요구된다.

## Windows 환경에서는 그런 것들이 안 될까?
Windows는 기본적으로 PowerShell이나 CMD와 같은 쉘을 제공하지만, 이들 쉘은 Linux의 bash와 같은 오픈소스 환경 및 다양한 자동화 도구 지원 측면에서 차이가 있다. Windows의 기본 쉘은 Windows 환경에 최적화되어 있으므로, Linux 환경에서 제공하는 풍부한 개발 도구와 서버 운영 관련 기능을 그대로 활용하기 어렵다. 이로 인해 Linux 환경이 필요한 상황에서는 WSL이 유용하다.

## 왜 서버 컴퓨터는 거의 다 Linux 환경일까? (Windows 환경의 서버는 어떤 것이 안 좋을까)

## Shell 의 종류
- **Bash (Bourne Again SHell):** 가장 널리 사용되는 Shell로 다양한 스크립트와 명령어를 지원한다.
- **Zsh (Z Shell):** Bash보다 확장성이 뛰어나며, 사용자 정의가 용이하여 많은 개발자들이 선호한다.
- **Fish (Friendly Interactive Shell):** 직관적인 인터페이스와 강력한 자동완성 기능을 제공하여 초보자에게도 적합하다.

## WSL 만이 가지는 장점 및 특징
### VM 보다 리소스가 덜 소비된다.
기존에 가상 머신(VM)을 사용하여 Linux 환경을 구동하던 방식과 달리, WSL은 가벼운 호환 계층을 제공하여 자원 사용량을 줄인다. 특히 WSL 2는 실제 Linux 커널을 포함하여, 기존 버전보다 더 높은 성능과 호환성을 제공한다.

### 그 외 장점