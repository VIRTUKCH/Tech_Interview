# 요청/응답 주기
우리가 만든 애플리케이션으로 장고의 요청(request)/응답(response) 주기를 살펴보자. 장고가 HTTP 요청을 처리하고 HTTP 응답을 생성하는 과정을 단계 별로 표현해 보았다.

## 1. Browser 의 Request
웹 브라우저는 URL 로 페이지를 요청한다. 웹 서버가 HTTP 요청을 수신해서 Django 에게 전달한다.

## 2. Django 의 URL Pattern 검사
Django 는 URL 패턴의 구성에 정의된 각 URL 패턴을 검사한다. 프레임워크는 주어진 URL 경로에 대해 각 패턴을 나타내는 순서대로 확인하고 요청된 URL 과 매칭하는 첫 번째 패턴에서 검차를 멈춘다.

## 3. Django 가 일치하는 Pattern 의 View 를 가져옴
Django 는 일치하는 URL 패턴의 View 를 가져와 HttpRequest 클래스의 인스턴스와 키워드 또는 위치 인수를 전달하여 실행한다.

View 는 Model 을 사용하여 데이터베이스에서 정보를 조회한다. Django ORM QuerySet 을 사용하면 SQL 로 변환되어 데이터베이스에서 실행된다.

## 4. View 의 render() 함수 사용
View 는 render() 함수를 사용해서 콘텍스트 변수로 Post 를 전달하여 HTML 템플릿을 렌더링한다.

## 5. Django 의 Response
렌더링 내용은 콘텐츠 타입이 기본적으로 text/html 인 View 에 의해 HttpResponse 객체로 반환된다.