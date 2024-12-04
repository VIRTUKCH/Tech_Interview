# venv (Virtual Environment)

## 1. 파이썬 가상 환경이란?
파이썬으로 애플리케이션을 작성할 때, 특정 버전의 모듈을 시스템 전체에 적용되도록 설치할 수 있다. 그러나, 여러 프로젝트를 만들면 이전 버전이 필요한 다른 애플리케이션에서 문제가 발생할 수도 있다.

이 문제를 해결하기 위해 가상 환경을 사용할 수 있다. 가상 환경을 설치하면 격리된 위치에 파이썬 모듈을 설치할 수 있다.

## 2. 모듈과 패키지의 차이
- 모듈 :  하나의 파이썬 파일로, 함수, 클래스, 변수를 포함할 수 있다.
- 패키지 : 여러 개의 모듈을 포함할 수 있는 디렉토리. 해당 디렉토리 내에 __init__.py 파일이 필요하다.

## 3. 파이썬 런처를 사용하여 격리된 환경을 만드는 명령어
MacOS, Linux 를 사용하는 경우
```zsh
python -m venv my_env
```

WSL 을 사용하는 경우에는 python3 로 명령어를 입력해야 한다. 일반적으로 Linux 와 같은 Unix 계열의 운영체제에서는 기본적으로 python2 가 설치되어 있고, python 으로 명령어를 시작하면 python2 로 인식하기 때문이란다.

나의 경우에는 아래와 같은 오류가 떴다.
```
$ python -m venv my_env
Command 'python' not found, did you mean:
  command 'python3' from deb python3
  command 'python' from deb python-is-python3
```

앞으로도 이러한 것들이 귀찮을까 봐 아래와 같은 패키지를 설치하여 python 명령어가 python3 를 가리키도록 설정했다.
```bash
sudo apt install python-is-python3
```

Windows OS 를 사용하는 경우
```terminal
py -m venv my_env
```

두 명령어는 my_env/ 라는 새 디렉터리에 파이썬 환경을 만드는 명령어이다. 가상 환경이 활성화되어 있는 동안 설치하는 모든 라이브러리는 my_env/lib/python3.10/site-packages 디렉터리로 이동한다.

## 4. 파이썬 런처란?
**py**는 파이썬 런처로, Windows 에서 파이썬 3.3 에서 도입되었다. 컴퓨터에 설치된 파이썬 버전을 감지해서 자동으로 최신 버전에 연결해준다. Windows 를 사용하는 경우에는 python 명령어로 대체하는 것이 좋다.

파이썬 런처를 사용하면 파이썬 파일을 쉽게 실행할 수 있다. 예를 들어, 아래와 같이 명령어를 입력하면 script.py 파일이 실행된다.
```terminal
py script.py
```

## 5. 가상 환경 활성화
MacOS 를 사용하는 경우
```zsh
source my_env/bin/activate
```

Windows OS 를 사용하는 경우
```terminal
./my_env/Scripts/activate
```

쉘 프롬프트를 쓰면 아래와 같이 괄호로 묶인 가상 환경의 이름이 표시된다.
```
(my_env)zenx@pc:~ zenx$
```