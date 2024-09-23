# External Database Connection
남는 컴퓨터로 DB 를 만들어서 팀원들이 접속할 수 있도록 만들다 쓴 기록..

## 1. 전체 계정 조회하기

```mysql
# mysql 스키마를 사용하면 계정과 관련된 정보를 조회할 수 있다.
use mysql;

# 사용할 수 있는 모든 계정 조회
SELECT host, user FROM mysql.user;
```

---

## 2. root 계정 사용하기

터미널에서 root 계정을 사용하기 위해서는 다음과 같이 명령어를 입력하면 된다.

```shell
mysql -u root -p
```

-p 옵션은 비밀번호를 별도로 입력하겠다는 의미이다. 명령어에 직접 입력하지 않기 때문에 보안이 강화된다.

```shell
mysql -u root -p password
```

위와 같이 입력하면 'password' 라는 문자열을 비밀번호로 입력하는 것과 같다.

Mysql Workbench 를 사용하면 그냥 로비로 나가서 계정을 선택하면 된다.

---

## 3. User 만들기

일단 외부에서 접속할 수 있는 User 를 만들어 주어야 한다.

root 계정에 접속했으니, 이어서 User 를 만드는 명령어를 입력하면 된다.

```mysql
-- 사용자 생성 (없다면)
CREATE USER '{User이름}'@'%' IDENTIFIED BY '{User비밀번호}';
```

@ 뒤에 오는 %는 모든 IP 로부터의 접근을 허용하겠다는 의미이다.

다른 계정을 사용하기 위해서는 Mysql Workbench 에서 로비로 나간 뒤에 다른 계정을 선택해야 하니 알아 두자.

---

## 4. 권한 부여하기
```mysql
-- 권한 부여
GRANT ALL PRIVILEGES ON *.* TO '{User이름}'@'%' WITH GRANT OPTION;
```

---

## 5. 