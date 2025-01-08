# 각 파일 별 하는 일

## 프로젝트 이름을 딴 디렉터리 (프로젝트 수준 설정)

- **`settings.py`**:
  - 프로젝트 전역 설정 파일.
  - **Java Spring 비교**: `application.properties`나 `application.yml`에 해당.
  - **내용**: 데이터베이스 연결, 설치된 앱(`INSTALLED_APPS`), 정적 파일 경로 설정 등.

- **`urls.py`**:
  - 전역 URL 라우팅 설정.
  - **Java Spring 비교**: `@RequestMapping` 또는 React의 Router와 유사.
  - 애플리케이션별 `urls.py` 파일과 연결.

- **`asgi.py` & `wsgi.py`**:
  - Django가 ASGI/WSGI 서버와 통신하도록 설정.
  - **Java Spring 비교**: 내장 톰캣 서버 설정과 유사.

- **`__pycache__/`**:
  - Python 컴파일된 파일 저장소. 사용자가 직접 편집하지 않음.

## 애플리케이션 디렉터리 내 파일

- **`migrations/`**:
  - 데이터베이스 스키마 변경 기록 및 마이그레이션 파일 저장.
  - **Java Spring 비교**: JPA의 `schema.sql` 또는 Flyway 마이그레이션 스크립트.

- **`static/`**:
  - CSS, JS, 이미지 등 정적 파일 저장소.
  - **React 비교**: `public` 디렉터리와 유사.

- **`templates/`**:
  - Django 템플릿 파일(.html) 저장소.
  - **Java Spring 비교**: Thymeleaf 파일 저장 위치.

- **`admin.py`**:
  - Django의 기본 Admin 페이지 설정 및 커스터마이징.
  - 데이터 관리 인터페이스 제공.

- **`apps.py`**:
  - 애플리케이션의 이름 및 설정 관리.
  - **Java Spring 비교**: `@Configuration` 또는 설정 클래스와 유사.

- **`models.py`**:
  - 데이터베이스 테이블 정의.
  - **Java Spring 비교**: `@Entity` 클래스에 해당.

- **`tests.py`**:
  - 유닛 테스트 작성.
  - **Java Spring 비교**: JUnit 또는 Spring Test.

- **`urls.py`**:
  - 이 애플리케이션의 URL 라우팅 정의.
  - **React 비교**: Router와 유사.

- **`views.py`**:
  - 비즈니스 로직 처리 및 HTTP 요청에 응답.
  - **Java Spring 비교**: `@Controller`와 `@Service` 역할.