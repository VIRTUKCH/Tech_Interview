# FastAPI

## 1. FastAPI 란?
FastAPI는 Python으로 작성된 현대적인 웹 프레임워크로, RESTful API를 신속하고 쉽게 개발할 수 있도록 설계되었다.

FastAPI는 타입 힌트를 활용하여 코드의 가독성과 유지보수성을 높이고, 자동으로 API 문서를 생성하는 기능을 제공한다.

비동기 프로그래밍을 지원하며, 성능이 뛰어나고, Django나 Flask와 같은 다른 웹 프레임워크와 함께 사용할 수 있다.

## 2. FastAPI 란 기본 라이브러리인가? 아니면 프레임워크인가?
FastAPI는 프레임워크이다. 내부적으로 Python 의 네트워크 관련 패키지를 사용한다. FastAPI 는 주로 Starlette 라는 비동기 웹 프레임워크를 기반으로 만들어졌다. Starlette 는 비동기 HTTP 서버를 구축하기 위한 다양한 기능을 제공하며, FastAPI 는 이를 활용하여 API 를 쉽게 만들 수 있도록 돕는다.

## 3. Uvicorn 이란?
Uvicorn 은 Python 으로 작성된 ASGI(Asynchronous Server Gateway Interface) 서버로, 비동기 웹 프레임워크와 애플리케이션을 실행하기 위해 설계되었다. FastAPI와 같은 비동기 웹 프레임워크와 함께 사용되며, 높은 성능과 효율성을 자랑합니다.