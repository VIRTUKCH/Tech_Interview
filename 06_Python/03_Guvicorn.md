# Guvicorn

## 1. Guvicorn 이란?
Guvicorn 은 FastAPI 와 같은 ASGI(Asynchronous Server Gateway Interface) 애플리케이션을 실행하기 위한 비동기 서버인 Uvicorn 의 변형이다. Guvicorn 은 Uvicorn 의 기능을 기반으로 하면서, Guvicorn 의 여러 기능을 통합하여 고유한 성능과 기능을 제공한다.

## 2. Guvicorn 은 Uvicorn 과 같이 사용되는가?
그럴 수 있다. Guvicorn 은 Uvicorn 의 기능을 확장하는 형태로 설계되었기 때문에, Uvicorn 의 장점을 그대로 활용하면서 추가적인 기능을 제공한다. 따라서, FastAPI 와 같은 비동기 애플리케이션을 배포할 때 Guvicorn 을 사용하여 Uvicorn 의 성능을 극대화할 수 있다.

## 3. Guvicorn 이 있다면 Uvicorn 은 왜 사용하는가?
간단한 배포, 리소스 효율이 중요시되는 환경에서는 Uvicorn 이 더 선호될 수 있다. Guvicorn 은 더 복잡한 요구 사항을 충족하기 위한 확장된 솔루션으로 사용된다.