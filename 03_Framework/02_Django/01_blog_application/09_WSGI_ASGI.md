# WSGI & ASGI

## 1. WSGI 란?
WSGI (Web Server Gateway Interface) 는 파이썬 웹 애플리케이션과 웹 서버 간의 인터페이스를 정의하는 표준이다. WSGI 는 파이썬 웹 애플리케이션이 다양한 웹 서버와 호환될 수 있도록 설계되었으며, 서로 다른 웹 프레임워크와 서버 간의 호환성을 보장한다.

## 2. ASGI 란?
ASGI (Asynchronous Server Gateway Interface) 는 WSGI 의 비동기 버전으로, 파이썬 웹 애플리케이션과 웹 서버 간의 비동기 인터페이스를 정의하는 표준이다.

ASGI 는 WSGI 의 한계를 극복하고, 비동기 프로그래밍 모델을 지원하여 실시간 기능(ex_웹소켓, 푸시 알림 등)을 구현할 수 있도록 설계되었다.



## 3. WSGI 와 ASGI 의 차이