# 각 파일 별 하는 일

프로젝트 디렉터리 내
- db.sqlite3 : 데이터베이스 스키마, 데이터가 이 파일에 포함 됨.
- manage.py : server run 할 때 필요한 것들

애플리케이션 디렉터리 내
- >(d)migrations : 데이터베이스 스키마에 대한 내용들
- >(d)static : 정적인 파일. css 같은 것들.
- >(d)templates : Thymeleaf 처럼 동적인 html 파일 넣는 공간.
- admin.py : admin page 쓸 거면 편집.
- apps.py : 애플리케이션 이름 설정. 아직 쓴 적 없음.
- models.py : @Entity 역할
- tests.py : 테스트 코드 모음집
- urls.py : React 의 router 역할
- views.py : @Controller + @Service 역할