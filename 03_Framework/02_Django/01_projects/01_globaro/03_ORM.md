# JPA vs Django ORM

## 1. JPA 사용 로직
: 어떤 파일에서, 어떤 코드를, 어떻게 추가하는가

### 1-1. application.properties
DB 와 관련된 내용 작성. username, database, password 등

### 1-2. @Entity
@Entity 애너테이션 붙이고 컬럼 설계

### 1-3. ddl-auto: true
테이블을 직접 만드는 것이 좋으나, JPA 써서 쉽게 만들 수 있음

### 1-4. @Repository
Entity 에 대한 CRUD 접근할 수 있는 최소한의 interface

### 1-5. @Service
Service Logic 에서 JpaRepository 가 가지고 있는 CRUD 메서드를 사용해서 구현.

### 1-6. @RestController
RESTful API 와 URL 을 Mapping

## 2. JPA 사용 로직을 Django 로 옮기면?
: 어떤 파일에서, 어떤 코드를, 어떻게 추가하는가

### 2-1. settings.py 에서 DB 설정
JPA의 application.properties에 해당

[settings.py]
```python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',  # DB 엔진 (PostgreSQL)
        'NAME': 'your_database_name',  # 데이터베이스 이름
        'USER': 'your_username',  # 사용자명
        'PASSWORD': 'your_password',  # 비밀번호
        'HOST': 'localhost',  # 호스트 주소
        'PORT': '5432',  # 포트
    }
}
```

### 2-2. 모델 설계
JPA의 @Entity와 컬럼 설계에 해당

[models.py]
```python
from django.db import models

class MyModel(models.Model):
    name = models.CharField(max_length=100)  # VARCHAR(100)
    description = models.TextField()  # TEXT
    created_at = models.DateTimeField(auto_now_add=True)  # TIMESTAMP
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.name
```

### 2-3. 마이그레이션으로 테이블 생성
JPA 에서 ddl-auto: true 에 해당.

JPA 에서 테이블 자동 생성을 설정하는 것처럼, Django 에서는 마이그레이션을 통해 테이블을 생성함. Django 는 명령어를 명시적으로 실행한다는 차이가 있음.

[1. 마이그레이션 파일 생성]
```bash
python manage.py makemigrations
```

[2. 데이터베이스에 적용]
```bash
python manage.py migrate
```

### 2-4. ORM 의 CRUD 인터페이스에 접근
[views.py 같은 서비스 로직에서 바로 하면 됨]
```python
# Create
my_model = MyModel.objects.create(name="Example", description="Django ORM Example")

# Read
my_model = MyModel.objects.get(id=1)  # 특정 ID 조회
all_models = MyModel.objects.all()  # 전체 조회
filtered_models = MyModel.objects.filter(name__icontains="Example")  # 조건 조회

# Update
my_model.name = "Updated Example"
my_model.save()

# Delete
my_model.delete()
```

Django 는 objects 라는 기본 매니저를 제공하며, 이를 통해 CRUD 작업을 수행한다. JPA 의 JpaRepository 역할을 한다.

### 2-5. 서비스 로직
[views.py]
```python
from django.shortcuts import render, get_object_or_404
from django.http import JsonResponse
from .models import MyModel

def my_view(request):
    if request.method == "GET":
        items = MyModel.objects.all()  # Read all items
        data = [{"id": item.id, "name": item.name} for item in items]
        return JsonResponse(data, safe=False)
```

Django 에서는 서비스 로직을 뷰에서 처리한다. 뷰는 요청을 처리하고 데이터를 반환하는 역할을 수행한다. JPA 의 @Service 에서 레파지토리를 호출하여 로직을 구현하는 것과 유사함.

### 2-6. URL Mapping (@RestController)
[urls.py]
```python
from django.urls import path
from . import views

urlpatterns = [
    path('items/', views.my_view, name='my_view'),
]
```

## 3. 요약

| JPA 개념            | Django 대응          | 설명                                   |
|---------------------|---------------------|---------------------------------------|
| `application.properties` | `settings.py`       | 데이터베이스 연결 정보 설정               |
| `@Entity`, `@Column` | `models.py`         | 모델 클래스를 통해 테이블과 컬럼 정의       |
| `ddl-auto: true`    | `makemigrations`, `migrate` 명령어 | 테이블을 자동으로 생성하고 적용         |
| `@Repository`       | `objects` 매니저    | 모델 매니저를 통해 CRUD 작업 수행         |
| `@Service`          | `views.py`          | 뷰에서 서비스 로직을 구현                 |
| REST 컨트롤러        | `urls.py`           | 요청 경로를 URL과 매핑                   |