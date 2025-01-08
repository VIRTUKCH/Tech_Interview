# settings.py == application.properties

## 1. settings.py 파일이 하는 일
settings.py 파일은 Django 프로젝트의 설정을 정의하는 주요 파일이다. 이 파일은 Django 애플리케이션의 동작 방식과 관련된 다양한 설정을 포함하고 있으며, 데이터베이스 연결, 미들웨어, 템플릿, 정적 파일, 보안 설정 등 많은 중요한 구성 요소들을 설정할 수 있다.

Spring 에서 application.properties 와 같은 역할을 수행하는 파일이라고 할 수 있다. 주요 역할은 다음과 같다.
- 프로젝트의 전역 설정을 정의
- 애플리케이션의 동작 환경을 구성
- 개발 및 배포 환경에 따른 설정을 관리

## 2. 구성 요소 분석
settings.py 파일은 다음과 같은 주요 구성 요소로 이루어져 있다.

### 2-1. DEBUG
디버그 모드 여부를 설정하는 Boolean 값이다. 우리가 일반적으로 IDE 에서 설정하는 디버깅과는 약간 다른 기능을 한다.

DEBUG 모드가 활성화되면 Django 는 더 많은 오류 메시지와 디버깅 정보를 표시한다. 개발 중에는 유용하지만, 배포 시에는 보안 상의 이유로 비활성화하는 것이 좋다.
```python
DEBUG = True
```

### 2-2. DATABASES
데이터베이스 연결 정보를 설정합니다. 데이터베이스의 엔진, 이름, 사용자, 비밀번호 등을 포함한다.
``` python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': BASE_DIR / "db.sqlite3",
    }
}
```

### 2-3. INSTALLED_APPS
프로젝트에서 사용할 애플리케이션 목록이다. Spring 에서 의존성을 관리하는 build.gradle, pom.xml 과 비슷한 역할을 수행한다. 하지만 약간은 다른 것이, Spring 의 build.gradle 이나 pom.xml 이 의존성을 관리하는 방식과 Django 의 INSTALLED_APPS 가 애플리케이션을 등록하는 방식은 약간 다르다.

INSTALLED_APPS 는 Django 에서 사용할 앱을 나열하여, 장고가 해당 앱의 모델, 뷰, 템플릿 등을 인식하도록 하는 역할을 한다. 또한, Django의 기본 제공 앱과 사용자 정의 앱 모두 포함할 수 있습니다.
```python
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'myapp',  # 사용자 정의 앱
]
```

### 2-4. MIDDLEWARE
요청과 응답 처리 과정에서 사용할 미들웨어를 설정한다. 미들웨어는 요청을 처리하기 전후에 추가적인 작업을 수행할 수 있다.

> **미들웨어**는 Django의 요청 처리 과정에서 특정 작업을 수행하는 함수 또는 클래스이다. 예를 들어, 요청의 인증, 세션 관리, CSRF 보호, 로그 기록 등의 작업을 수행할 수 있다.

미들웨어의 설정 순서는 요청과 응답 처리에 영향을 미치기 때문에, 올바른 순서로 미들웨어를 설정하는 것이 중요하다.

```python
MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]
```

### 2-5. TEMPLATES
템플릿 엔진 설정을 정의합니다. 템플릿 디렉토리와 컨텍스트 프로세서를 설정할 수 있다. 순수하게 백엔드 포인트(API)만 제공하는 경우에는 정의하지 않아도 되겠다.

> **템플릿 엔진**이란, HTML 문서와 데이터를 결합하여 동적인 웹 페이지를 생성하는 데에 사용되는 엔진이다. 템플릿 엔진을 사용하면 서버 사이드 렌더링 방식이 채택된다.

```python
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [BASE_DIR / "templates"], # html 파일이 위치할 디렉터리
        'APP_DIRS': True, # 각 설치된 앱의 템플릿 디렉터리도 자동으로 인식된다.
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]
```

### 2-6. STATIC_URL
정적 파일의 URL 경로를 설정한다. CSS, JavaScript, 이미지 파일 등을 관리한다.
```python
STATIC_URL = '/static/'
```

## 3. 커스터마이징 예시
settings.py 파일은 프로젝트의 요구에 맞게 커스터마이징할 수 있다. 아래는 몇 가지 커스터마이징 예시이다.

### 3-1. 데이터베이스 설정 변경
SQLite 대신 PostgreSQL을 사용하고 싶다면, DATABASES 설정을 다음과 같이 변경할 수 있다.

```python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': 'mydatabase',
        'USER': 'myuser',
        'PASSWORD': 'mypassword',
        'HOST': 'localhost',
        'PORT': '5432',
    }
}
```

### 3-2. 미들웨어 추가
CORS를 허용하기 위해 django-cors-headers 미들웨어를 추가할 수 있다.

```python
MIDDLEWARE = [
    # 기존 미들웨어...
    'corsheaders.middleware.CorsMiddleware',
    # ...
]
```
> 미들웨어는 Spring 의 Fiter, Interceptor, AOP 와 유사한 개념으로 볼 수 있다.

### 3-3. 커스텀 템플릿 디렉토리 설정
템플릿 디렉토리를 추가하여 사용자 정의 템플릿을 사용할 수 있다.

```python
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [BASE_DIR / "my_custom_templates"],
        'APP_DIRS': True,
        # ...
    },
]
```
템플릿 디렉터리를 사용하면 여러 페이지에서 헤더, 푸터처럼 공통적인 레이아웃을 정의할 수 있다.

### 3-4. 보안 설정 강화
CSRF 및 세션 보안을 강화하기 위해 다음과 같은 설정을 추가할 수 있습니다.

```python
# CSRF 보호를 위해 쿠키를 안전하게 설정
CSRF_COOKIE_SECURE = True  # HTTPS에서만 쿠키 전송
CSRF_COOKIE_HTTPONLY = True  # JavaScript에서 쿠키 접근 방지
CSRF_USE_SESSIONS = False  # CSRF 토큰을 세션에 저장하지 않음

# 세션 쿠키 보안 강화
SESSION_COOKIE_SECURE = True  # HTTPS에서만 세션 쿠키 전송
SESSION_COOKIE_HTTPONLY = True  # JavaScript에서 세션 쿠키 접근 방지
```

이와 같은 커스터마이징을 통해 프로젝트의 요구사항에 맞게 settings.py 파일을 조정할 수 있다.