# PostgreSQL

## 1. SQLite3의 한계
Django는 기본적으로 SQLite3를 지원한다. 그러나, SQLite3는 쓰기 작업이 단일 쓰레드로 제한되어 여러 사용자가 데이터베이스에 접근할 경우 성능 저하가 발생할 수 있다. 또한, 대규모 데이터베이스를 처리하는 데 한계가 있어 데이터베이스 크기가 커질수록 성능이 저하된다.

서버-클라이언트 구조가 아니고 파일 기반이기 때문에 네트워크 기반의 데이터베이스 공유가 어렵고, 경량화된 데이터베이스이기 때문에 복잡한 트리거와 저장 프로시저 같은 고급 기능이 부족하다. 다만 설치가 쉽고 파일 기반으로 작동하기 때문에 별도의 서버 프로세스 없이 사용할 수 있으며, 가볍고 빠르게 설정할 수 있다는 장점이 있다.

## 2. PostgreSQL이 다른 RDBMS와 다른 점
이러한 한계를 극복하기 위해 Django는 기본적으로 제공되는 SQLite3보다 PostgreSQL을 사용하는 것이 권장된다. PostgreSQL은 기능성과 안정성 면에서 훨씬 뛰어난 성능과 유연성을 제공한다.

Django는 MySQL, Oracle 등 다른 RDBMS도 사용할 수 있지만, PostgreSQL에 대한 언급이 많은 편이다. 특히, PostgreSQL은 Django 3.1부터 비동기 뷰와 ORM을 지원하여 높은 성능의 웹 애플리케이션을 구축할 수 있는 기회를 제공한다. 반면 MySQL은 비동기 기능이 제한적이며, 추가적인 설정이나 라이브러리가 필요하다. Oracle은 비동기 처리가 가능하지만, 설정이 복잡할 수 있다.

이것뿐만 아니라, PostgreSQL은 MySQL에 비해 훨씬 더 확장성이 좋고, 사용자 정의 기능을 많이 제공하며, 고급 데이터 타입(JSONB, 배열, 사용자 정의 타입)을 지원하는 등의 장점이 있다.

## 3. Django의 PostgreSQL을 이용한 기능 제공
- **모델 필드**: PostgreSQL의 JSONB, ArrayField 등 다양한 데이터 타입을 지원하여 복잡한 데이터 구조를 쉽게 관리할 수 있다.
- **고급 쿼리**: PostgreSQL의 고급 쿼리 기능을 활용하여 Django ORM에서 복잡한 쿼리를 쉽게 작성할 수 있다.
- **트랜잭션 관리**: PostgreSQL의 트랜잭션 기능을 통해 데이터의 일관성을 보장할 수 있다.

## 4. PostgreSQL 설치
```text
https://www.postgresql.org/download/
```
16.6 버전으로 설치했다.

아래 네 개도 같이 설치하자.
- PostgreSQL Server : PostgreSQL 의 핵심 데이터베이스 서버이다.
- pgAdmin 4 : PostgreSQL 의 공식 관리 도구이다. MySQL 에서 MySQL Workbench 같은 느낌이다.
- Stack Builder : PostgreSQL 에 추가 기능을 쉽게 설치할 수 있도록 도와주는 도구이다.
- Command Line Tools : 데이터베이스와 상호작용할 수 있는 명령줄 도구 모음이다. (Terminal)

## 5. 파이썬용 psycopg2 PostgreSQL 설치하기
psycopg2 어댑터는 데이터베이스와의 연결을 관리하고 SQL 쿼리를 실행할 수 있는 기능을 제공하는 드라이버이다. Java 의 JDBC 와 유사하다고 생각하면 되겠다.

```bash
pip install psycopg2-binary==2.9.3
```

바이너리 파일이라서 Python 개발 패키지를 별도로 설치해야 아마 작동할 거다. 그래서 이걸 해결해야 하는데 이거는 월요일에...