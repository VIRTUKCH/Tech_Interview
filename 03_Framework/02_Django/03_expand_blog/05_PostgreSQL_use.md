# PostgreSQL 환경 설정

## 1. Terminal 에서 USER, ROLE 생성
일단 데이터베이스에 사용자부터 만들어야 한다. PostgreSQL 의 터미널 기반 프론트엔드 psql 을 사용한다. 쉘 프롬프트에서 다음 명령을 실행해서 PostgreSQL 터미널로 진입하자.

```bash
sudo -u postgres psql
```

나는 Windows 환경에서 WSL 을 사용하고 있는데, psql 만 치면 WSL 기본 계정으로 로그인을 시도하려고 하길래 postgres 계정으로 로그인하라고 명시해 주었다.

이제 데이터베이스를 생성할 수 있는 사용자를 만들어야 한다. 나는 chkim 이라는 이름으로 USER 을 만들었다.

```bash
CREATE USER {하고싶은_USER_NAME} WITH PASSWORD {하고싶은_비밀번호};
```

위와 같이 따라 쳤으면 아마 아래와 같이 출력될 것이다.

```bash
CREATE ROLE
```

사용자가 정상적으로 생성되었다.

## 2. 데이터베이스 생성
이제 blog 라는 이름의 데이터베이스를 만들고 방금 만든 chkim 사용자에게 소유권을 부여해 보겠다.
```bash
CREATE DATABASE blog OWNER chkim ENCODING 'UTF8';
```

잘 생성 되었으면 아래와 같이 출력된다.

```bash
CREATE DATABASE
```