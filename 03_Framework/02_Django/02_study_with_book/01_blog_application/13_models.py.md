# models.py

## 1. ORM (Object-Relation Mapping)
ORM 은 객체 지향 프로그래밍 언어에서 데이터베이스의 데이터를 객체로 매핑하여 사용할 수 있게 해주는 기술이다. ORM 을 사용하면 SQL 쿼리를 직접 작성하지 않고도 데이터베이스와 상호작용할 수 있다.

ORM 의 핵심은 데이터베이스의 한 row 에 해당하는 것과 객체를 매핑한다는 것이다. 이를 사용해서 CRUD 작업을 쉽게 수행할 수 있고, 쿼리에 의존적인 개발을 하지 않아도 된다.

ORM 또한 하나의 인터페이스를 사용하는 것이기 때문에 직접적으로 Driver 를 사용하는 것보다 더 느릴 수밖에 없다. 하지만, 쿼리에 의존적인 개발을 피하여 개발 속도를 더 빠르게 하고 유지 보수를 유지하게 하는 데에 큰 의미가 있다.

동시에 ORM 은 데이터베이스 이식성을 높여주며, 여러 데이터베이스 시스템 간의 전환을 쉽게 해주며, ORM 프레임워크는 객체 지향적 접근 방식을 통해 비즈니스 로직과 데이터베이스 접근 로직을 분리할 수 있게 도와준다.

## 2. models.py 란?
models.py 는 Django 애플리케이션 내에서 데이터베이스 모델을 정의하는 파일이다. 이 파일에서 각 모델 (데이터베이스의 테이블과 Mapping) 을 클래스로 정의한다.

Django 는 이 클래스를 기반으로 데이터베이스 테이블을 생성하고, CRUD 작업을 수행할 수 있는 메서드를 자동으로 제공한다.

## 3. 실제 파이썬 코드
```python
from django.db import models
from django.utils import timezone

# Create your models here.

class Post(models.Model): # Inheritance
    title = models.CharField(max_length=250) # -> VARCHAR : 일반적으로 사용. 띄어쓰기 가능함.
    slug = models.SlugField(max_length=250) # -> VARCHAR : 소문자 + 하이픈(-)을 사용하는 게 컨벤션. URL 등에 적격
    body = models.TextField() # TEXT
    publish = models.DateTimeField(default=timezone.now)
    created = models.DateTimeField(auto_now_add=True) # 객체를 생성할 때 날짜가 자동으로 저장된다.
    updated = models.DateTimeField(auto_now=True) # 객체를 저장할 때 날짜가 자동으로 저장된다.

    class Meta: # 모델 내부에 Meta 클래스를 추가하여, 모델에 대한 메타데이터를 정의함.
        ordering = ['-publish'] # 출시일 역순으로 정렬
        indexes = [
            models.Index(fields=['-publish']), # 인덱스를 출시일 역순으로
        ]

    def __str__(self):
        return self.title
```