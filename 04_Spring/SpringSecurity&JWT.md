# Spring Security & JWT

## 1. Spring Security 란?


: Spring Security 는 Spring Framework 의 보안 인증 및 권한 부여 기능을 제공하는 모듈입니다.

이를 통해 애플리케이션의 보안을 강화하고, 사용자 인증(로그인)과 권한 관리(리소스 접근 제어)를 쉽게 구현할 수 있습니다.


## 2. Spring Security 의 주요 기능


### 2-1 인증 (Authentication)


: 사용자의 신원을 확인합니다.


### 2-2 권한 부여 (Authorization)


: 사용자가 특정 리소스에 접근할 수 있는지 결정합니다.


### 2-3 CSRF 보호


: 교차 사이트 요청 위조 공격을 방지합니다.


### 2-4 세션 관리


: 사용자 세션을 관리하고, 세션 고정 공격을 방지합니다.


### 2-5 그 외


: Spring Security는 다양한 인증 방법(예: 폼 로그인, OAuth2, JWT 등)을 지원하며, 커스터마이징이 용이합니다.