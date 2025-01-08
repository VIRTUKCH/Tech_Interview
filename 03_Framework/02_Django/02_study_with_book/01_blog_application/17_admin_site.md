# 관리자 사이트
Post 모델을 데이터베이스와 동기화하는 데에 성공했으므로, 블로그 게시물을 관리하는 간단한 관리 사이트를 만들어 보자.

## 1. Super User 생성하기
먼저, 관리 사이트를 관리할 사용자를 생성해야 한다.
```bash
python manage.py createsuperuser
```
원하는 사용자 이름, 이메일 및 패스워드를 요구할 것이다.

```txt
Username : admin
email : admin@admin.com
password : admin1234
```

테스트 계정이니 그냥 이렇게 만들어 봤다.

이후 개발 서버 시작
```python
python manage.py runserver
```

## 2. URL 접속
```txt
http://127.0.0.1:8000/admin/
```
이후 로그인 진행

## 3. 관리 사이트에 모델 추가

### 3.1 admin.py 파일 수정
```python
from django.contrib import admin
from .models import Post

admin.site.register(Post)
```
이후 브라우저에서 관리 사이트를 다시 로드하면, 모델이 표시될 것이다.

장고 관리 사이트에 모델을 등록하면 모델을 살펴보고 간단히 객체를 조회, 수정, 생성 및 삭제할 수 있는 사용자 친화적인 인터페이스를 얻을 수 있다.