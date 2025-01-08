# Project 생성

## 1. 명령어
가상환경을 만들고 활성화한 후, 아래 명령어를 치면 프로젝트 디렉터리를 만들 수 있다.
```bash
django-admin startproject {project_name}
```
위 명령어는 {project_name} 과 일치하는

## 2. 디렉터리 구성
위와 같은 명령어를 작성하여 프로젝트를 만들면, 프로젝트 디렉터리 내에 디렉터리와 여러 파일들이 생성된다.

## 2-1. manage.py
프로젝트와 상호작용하는 데에 사용되는 커맨드라인 도구이다. 이 파일을 편집할 필요는 없다. 하지만, 사용자가 프로젝트의 특정 설정을 변경할 수 있다.

## 2-2. __init__.py
디렉터리를 파이썬 모듈로 취급하도록 파이썬에 지시하는 빈 파일이다.

### 2-3. asgi.py
ASGI 호환 웹 서버와 함께 ASGI(Asynchronous Server Gateway Interface) 애플리케이션으로 프로젝트를 실행하기 위한 구성(configuration)이다.

ASGI 는 Python 웹 애플리케이션과 웹 서버 간의 비동기 통신을 위한 표준 인터페이스이다. ASGI 는 WSGI(Web Server Gateway Interface) 의 비동기 버전으로, 비동기 프로그래밍을 지원하여 웹 애플리케이션이 더 많은 동시 연결을 처리할 수 있도록 한다.

### 2-4. settings.py
프로젝트 설정 및 구성을 나타내며 초기 기본 설정을 포함한다.

### 2-5. urls.py
URL 패턴이 있는 곳이다. URL 과 View 를 Mapping 한다. Servlet & JSP 구조에서 web.xml 파일과 유사한 기능을 하는 듯하다.

### 2-6. wsgi.py
WSGI 호환 웹 서버와 함께 WSGI(Web Server Gateway Interface) 애플리케이션으로 프로젝트를 실행하기 위한 구성이다.