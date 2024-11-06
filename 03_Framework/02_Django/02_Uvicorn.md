# Uvicorn

## 1. Uvicorn 이란?
Uvicorn 은 Python 으로 작성된 ASGI(Asynchronous Server Gateway Interface) 서버로, 비동기 웹 프레임워크와 애플리케이션을 실행하기 위해 설계되었다. FastAPI와 같은 비동기 웹 프레임워크와 함께 사용되며, 높은 성능과 효율성을 자랑합니다.

## 2. Uvicorn 의 특징
- 비동기 지원
- ASGI 호환성
- 성능

## 3. 사용법
```bash
uvicorn main:app --reload
```
main 은 Python 파일의 이름이고, app 은 FastAPI 인스턴스의 이름이다.