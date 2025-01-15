# 데이터베이스 명령어 (개인정보 포함, 보안에 유의)

## 1. PostgreSQL Shell 접속
```bash
# PostgreSQL 관리자 계정으로 접속
sudo -u postgres psql

# {USER_NAME}으로 지정된 사용자 계정으로 특정 데이터베이스에 접속
psql -U {USER_NAME} -h localhost -d {DATABASE_NAME}
```

## 2. 사용자 생성
```sql
-- 새로운 사용자 계정을 생성하고 비밀번호를 설정
CREATE USER {USER_NAME} WITH PASSWORD '{PASSWORD}';
```

## 3. 사용자 단일 조회
```sql
-- 특정 사용자의 정보를 roles 테이블에서 조회
SELECT * FROM pg_roles WHERE rolname = '{USER_NAME}';  

-- 현재 사용자 조회
SELECT current_user;
```

## 4. 사용자 리스트 조회
```sql
-- 현재 PostgreSQL에 등록된 모든 사용자와 역할을 조회
\du
```

## 5. 사용자 수정
```sql
-- 기존 사용자의 비밀번호를 새로 설정
ALTER USER {USER_NAME} WITH PASSWORD '{PASSWORD}';
```

## 6. 사용자 삭제
```sql
-- 지정된 사용자 계정을 삭제 (해당 사용자가 소유한 객체가 없을 경우에만 성공)
DROP ROLE {USER_NAME};
```

## 7. 데이터베이스 생성
```sql
-- 지정된 사용자를 소유자로 하여 데이터베이스를 생성
CREATE DATABASE {DATABASE_NAME} OWNER {USER_NAME};
```

## 8. 특정 데이터베이스 접속
```sql
-- 지정된 데이터베이스로 접속
\c {DATABASE_NAME}
```

## 9. 데이터베이스 소유자 확인
```sql
-- 데이터베이스 이름과 해당 소유자를 조회
SELECT datname, pg_catalog.pg_get_userbyid(datdba) AS owner
FROM pg_database;
```

## 10. 데이터베이스 소유권 변경
```sql
-- 데이터베이스의 소유권을 새로운 사용자로 변경
ALTER DATABASE {DATABASE_NAME} OWNER TO {NEW_OWNER};
```

## 11. 데이터베이스 전체 조회
```sql
-- 현재 PostgreSQL 인스턴스에 존재하는 모든 데이터베이스를 조회
\l
```

## 12. 현재 데이터베이스 조회
```sql
-- 현재 연결된 데이터베이스 이름을 반환
SELECT current_database();
```

## 13. 데이터베이스 이름 수정
```sql
-- 데이터베이스의 이름을 변경
ALTER DATABASE {OLD_NAME} RENAME TO {NEW_NAME};
```

## 14. 데이터베이스 삭제
```sql
-- 지정된 데이터베이스를 삭제 (접속 중인 클라이언트가 없어야 함)
DROP DATABASE {DATABASE_NAME};
```

## 15. 접근 권한 관리
```sql
-- 모든 사용자에 대한 데이터베이스 연결 권한 제거
REVOKE CONNECT ON DATABASE {DATABASE_NAME} FROM PUBLIC;

-- 특정 사용자에게 데이터베이스 연결 권한 부여
GRANT CONNECT ON DATABASE {DATABASE_NAME} TO {USER_NAME};
```

## 16. 테이블 관련 명령어
### 테이블 목록 조회
```sql
-- 현재 데이터베이스의 테이블 목록을 조회
\dt
```

### 테이블 상세 정보
```sql
-- 특정 테이블의 구조와 속성을 조회
\d {TABLE_NAME}
```

### 테이블 생성
```sql
-- 테이블 생성
CREATE TABLE {TABLE_NAME} (
    id SERIAL PRIMARY KEY,  -- 자동 증가하는 기본 키
    name VARCHAR(255) NOT NULL,  -- 최대 255자의 문자열 필드, NULL 값 불가
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP  -- 생성 시간을 기본값으로 설정
);
```

### 테이블 삭제
```sql
-- 지정된 테이블을 삭제
DROP TABLE {TABLE_NAME};
```