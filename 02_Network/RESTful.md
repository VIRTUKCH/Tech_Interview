# RESTful API

## 1. API(Application Programming Interface) 란?

: API(Application Programming Interface)는
서로 다른 소프트웨어 시스템 간의 상호작용을 정의하는 인터페이스이다.
특정 기능이나 데이터에 접근할 수 있는 방법을 제공한다.

* 시스템 : 상호작용하는 구성 요소들의 집합

---

### [개인적으로 궁금한 점]

#### Q. "API 를 Network 통신 기술을 이용한 함수" 라고 설명해도 될까?
#### A. 일부 맞지만, 완전한 설명은 아니다.

### [완전한 설명이 아닌 이유]

#### 네트워크 통신이 없어도 API 라고 할 수 있다.


: API 는 소프트웨어 내에서 상호작용하는 구성 요소 간의 상호작용을 정의하는 인터페이스이다.
그러므로, 반드시 네트워크를 통한 통신이 필요하지 않다.

예를 들어, C 언어의 <stdio.h> 같은 라이브러리 또한 API 라고 할 수 있다.
<stdio.h> 라이브러리는 콘솔 입/출력 및 파일 입/출력을 가능할 수 있도록 만드는데,
콘솔 입/출력은 한 프로그램 내에서 사용자 <-> 프로그램 간, 파일 입/출력은 프로그램 <-> 파일 시스템 간의 상호작용으로 볼 수 있기 때문이다.

결론 : API 는 서로 다른 소프트웨어 구성 요소들 간의 상호작용을 정의하는 인터페이스이다.

---

## 2. RESTful API 란?

[Amazon 이 설명하는 RESTful API](https://aws.amazon.com/ko/what-is/restful-api/)


: RESTful API는 두 컴퓨터 시스템이 인터넷을 통해 정보를 안전하게 교환하기 위해 사용하는 인터페이스이다.
대부분의 비즈니스 애플리케이션은 다양한 태스크를 수행하기 위해 다른 내부 애플리케이션 및 서드 파티 애플리케이션과 통신해야 한다.

예를 들어 월간 급여 명세서를 생성하려면 인보이스 발행을 자동화하고
내부의 근무 시간 기록 애플리케이션과 통신하기 위해 내부 계정 시스템이 데이터를
고객의 뱅킹 시스템과 공유해야 한다.

RESTful API는 안전하고 신뢰할 수 있으며
효율적인 소프트웨어 통신 표준을 따르므로 이러한 정보 교환을 지원합니다.

* 서드 파티 애플리케이션
: 특정 플랫폼이나 시스템을 위해 외부에서 개발된 소프트웨어.
예를 들면 CRM 시스템(고객 관계 관리 시스템)에 통합된 외부 회계 소프트웨어가 서드 파티 애플리케이션에 해당함.

---

## 3. RESTful API 의 주요 특징


### 1. 자원 기반이다.


: 

### 2. HTTP 메서드


: 

### 3. 상태 비저장성


: 

### 4. 표현 형식


: 

### 5. 계층화된 시스템


: 