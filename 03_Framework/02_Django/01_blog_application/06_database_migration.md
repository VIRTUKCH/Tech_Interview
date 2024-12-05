# Database Migration

장고 애플리케이션에는 대용량 데이터를 위한 데이터베이스가 필요하다. settings.py 파일에는 프로젝트를 위한 데이터베이스 구성이 DATABASES 설정에 포함되어 있다.

기본 구성은 SQLite3 데이터베이스이다. SQLite 는 파이썬 3과 함께 번들로 제공되며, 장고로 개발할 때 함께 사용할 수 있는 경량 데이터베이스이다.

프로덕션 환경에 애플리케이션을 배포하고자 한다면 PostgreSQL, MySQL, Oracle 과 같이 많은 기능을 제공하는 DBMS 를 사용하는 것이 옳겠다.

## 1. 명령어
```bash
cd {project_directory}
python manage.py migrate
```
정확히 이해하지는 못했지만, 데이터베이스를 이용해서 테이블, 필드, 인덱스, 제약 조건을 생성하고 관리할 수 있는 기능을 추가해주는 명령어라고 한다.

진짜 솔직히 뭐하는 건지 이해 아직 못 했다.