# Middleware

## 1. 미들웨어(Middleware) 란?
미들웨어(Middleware) 란 소프트웨어 아키텍처에서 클라이언트와 서버 간의 통신을 중재하는 컴포넌트를 의미한다.

주로 웹 애플리케이션에서 요청과 응답을 처리하는 과정에서 사용되며, 여러 기능을 추가하거나 수정하는 등의 역할을 수행한다.

예를 들어, 인증, 로깅, CORS 처리, 데이터 변환, 요청 및 응답 수정 등을 포함할 수 있다.

## 2. WAS(Web Application Server) 가 있어도 Middleware 가 있어야 하는 이유가 뭘까?
WAS 는 웹 애플리케이션을 실행하고 관리하는 서버로, 클라이언트의 요청을 받아 비즈니스 로직을 처리하고 반환하는 역할을 수행한다.

그러나 WAS 만으로는 다음과 같은 기능을 제공하기 어려운 경우가 많다.
- 기능의 세분화 : 특정 기능을 독립적으로 처리하여 애플리케이션의 구조를 명확하게 분리하여 관리할 수 있다.
- 재사용성 : 여러 애플리케이션에서 미들웨어의 기능을 재사용할 수 있다. 예를 들어, 인증 미들워에는 여러 애플리케이션에서 공통적으로 사용할 수 있다.
- 유연성 : 미들웨어를 통해 요청 처리의 흐름을 조정하거나 특정 로직을 추가할 수 있어, 애플리케이션의 유연성을 높일 수 있다.
- 특화된 기능 제공 : 메시지 큐 처리, 데이터베이승 연결 관리, API 게이트웨이 기능 등 다양하고 특화된 기능을 제공할 수 있다.

## 3. NGINX 는 Middleware 인가?
NGINX 는 일반적으로 정적인 html 파일을 전달하는 웹 서버로 분류된다. 그러나, 리버스 프록시, 로드 밸런서, HTTP 캐시 등 다양한 역할을 수행할 수 있는 다기능 서버이다.

또한, NGINX 는 클라이언트와 실제 백엔드 서버 간의 중재 역할을 수행하기 때문에 특정 관점에서 미들웨어로 간주될 수 있다.

- 리버스 프록시 : 클라이언트의 요청을 받아 실제 서버로 전달하고, 서버의 응답을 클라이언트에게 전달한다.
- 로드 밸런싱 : 여러 서버에 요청을 분산하여 서버의 부하를 줄이고, 고가용성을 제공한다.
- CORS 처리 : NGINX 를 사용하여 CORS 관련 설정을 추가할 수 있다.

결론적으로, NGINX 는 웹 서버이자 리버스 프록시 역할을 하는 소프트웨어로, 미들웨어의 기능을 일부 포함하지만 일반적으로 웹 서버로 더 잘 알려져 있다.

## 4. 미들웨어의 구체적인 구현체
### 1. 웹 애플리케이션 미들웨어
웹 애플리케이션 미들웨어란, 
#### 4-1-1. Django Middleward
[예시]
- django.middleware.common.CommonMiddleware
- django.middleware.csrf.CsrfViewMiddleware
- django.middleware.security.SecurityMiddleware

#### 4-1-2. Spring Middleware
- OncePerRequestFilter
- CorsFilter

### 2. 인증 및 권한 부여 미들웨어
#### 4-2-1. Django Authentication Middleware
Django의 기본 인증 미들웨어로, 사용자 인증 정보를 관리하고 세션을 처리한다.
django.contrib.auth.middleware.AuthenticationMiddleware를 사용하여 인증된 사용자 정보를 요청 객체에 추가한다.

#### 4-2-2. Spring Security
Java Spring 애플리케이션에서 인증 및 권한 부여를 관리하는 강력한 프레임워크이다.
WebSecurityConfigurerAdapter를 통해 보안 설정을 간편하게 구성할 수 있다.

### 3. 로깅 및 모니터링 미들웨어
#### 4-3-1. Django Logging Middleware
Django의 로깅 기능을 활용하여 요청과 응답을 로깅할 수 있다.
django.utils.log 모듈을 사용하여 커스텀 로깅 미들웨어를 구현할 수 있다.

#### 4-3-2. Log4j
Spring에서는 Log4j와 같은 로깅 라이브러리를 사용하여 애플리케이션의 로그를 관리한다.
Spring Boot에서는 기본적으로 Logback을 사용한다.

### 4. 데이터베이스 연결 미들웨어
#### 4-4-1. Django ORM
Django는 자체 ORM(Object Relational Mapping)을 사용하여 데이터베이스와의 상호작용을 관리한다.
Django ORM을 통해 데이터베이스 연결, 쿼리 작성, 데이터 조작을 쉽게 할 수 있다.

#### 4-4-2. Hibernate
Spring 애플리케이션에서는 Hibernate를 사용하여 데이터베이스와의 상호작용을 관리한다.
Hibernate는 강력한 ORM 프레임워크로, 복잡한 쿼리와 관계형 데이터베이스 작업을 지원한다.

### 5. API 미들웨어
#### 4-5-1. Django REST Framework (DRF)
Django에서 RESTful API를 구축하기 위해 사용하는 프레임워크로, 다양한 미들웨어와 기능을 제공하여 API 요청을 처리한다.
rest_framework.authentication 모듈을 통해 인증 미들웨어를 사용할 수 있다.

#### 4-5-2. Spring MVC
Spring에서는 RESTful API를 구축하기 위해 Spring MVC를 사용한다.
@RestController와 같은 어노테이션을 통해 요청을 처리하고, @RequestMapping으로 엔드포인트를 설정할 수 있다.

### 6. 메시지 큐 미들웨어
#### 4-6-1. Celery
Django와 함께 사용할 수 있는 비동기 작업 큐로, 백그라운드에서 작업을 처리하는 데 사용된다.
Celery는 RabbitMQ 또는 Redis와 같은 메시지 브로커와 함께 사용할 수 있다.
Django 또한 Kafka 에 메시지를 전송할 수 있다.

#### 4-6-2. RabbitMQ / Kafka
Spring에서는 RabbitMQ 또는 Apache Kafka와 같은 메시지 브로커를 사용하여 비동기 작업을 처리할 수 있다.
Spring Cloud Stream을 통해 메시지 기반의 아키텍처를 쉽게 구축할 수 있다.

### 7. 캐시 미들웨어
#### 4-7-1. Django Chching Framework
Django는 내장된 캐싱 프레임워크를 제공하여 데이터 캐싱 및 성능 향상을 지원한다.
다양한 캐시 백엔드를 사용할 수 있으며, django.core.cache 모듈을 통해 캐시를 관리할 수 있다.

#### 4-7-2. Spring Cache
Spring에서도 캐싱을 지원하며, @Cacheable, @CachePut, @CacheEvict와 같은 어노테이션을 사용하여 메서드 레벨에서 캐싱을 쉽게 설정할 수 있다.

### 8. CORS 미들웨어
#### 4-8-1. Django CORS Headers
Django에서 CORS를 처리하기 위한 서드파티 패키지로, django-cors-headers를 사용하여 CORS 설정을 쉽게 관리할 수 있다.
설정 후, 특정 출처에 대한 요청을 허용할 수 있다.

#### 4-8-2. Spring CORS Configuration
Spring에서는 @CrossOrigin 어노테이션을 사용하거나, WebMvcConfigurer를 구현하여 CORS 설정을 전역적으로 구성할 수 있다.