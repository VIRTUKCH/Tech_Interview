# Relation

## 1. RDBMS 에서 관계란?
관계형 데이터베이스 관리 시스템(RDBMS)에서 "관계"는 데이터 간의 연관성을 나타내는 개념이다. 관계형 데이터베이스는 데이터를 테이블 형식으로 저장하며, 각 테이블은 행(row)과 열(column)로 구성된다.

## 2. 관계의 구현
RDBMS 에서 관계는 외래 키(Foreign Key)를 사용하여 구현된다. 외래 키는 한 테이블의 필드가 다른 테이블의 기본 키(Primary Key)를 참조하는 방식으로, 두 테이블 간의 관계를 설정한다.

- 기본 키 : 각 레코드를 고유하게 식별하는 필드.
- 외래 키 : 다른 테이블의 기본 키를 참조하는 필드로, 관계를 정의하는 데 사용된다.

## 3. 관계의 중요성

### 3-1. 데이터 무결성
관계를 통해 데이터의 일관성과 무결성을 유지할 수 있다. 예를 들어, 외래 키 제약 조건을 설정하여 참조 무결성을 보장할 수 있다.

"이 값은 무의미한 숫자가 아니라, 다른 테이블의 PK 와 일치하는 값으로, 외래 키와 일치하는 값을 가진 PK 의 한 row 와 관련이 있다"라는 것을 의미할 수 있다.

## 4. Django 에서 다대일 관계 추가하기
지금까지 게시물 테이블을 정의했다. 게시물은 항상 작성자가 존재한다. 어떤 사용자가 어떤 게시물을 작성했는지를 나타내는 사용자와 게시물 간의 관계를 생성해 보자.

장고는 사용자 계정을 처리하는 인증 프레임워크를 함께 제공한다. 장고 인증 프레임워크는 'django.contrib.auth' 패키지로 제공되며 게시물 간의 관계를 생성한다.

```python
from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User

# Create your models here.

class Post(models.Model): # Inheritance

    # List : choices
    # Key : labels
    # Value : values
    class Status(models.TextChoices):
        DRAFT = 'DF', 'Draft'
        PUBLISHED = 'PB', 'Published'

    title = models.CharField(max_length=250) # -> VARCHAR : 일반적으로 사용. 띄어쓰기 가능함.
    slug = models.SlugField(max_length=250) # -> VARCHAR : 소문자 + 하이픈(-)을 사용하는 게 컨벤션. URL 등에 적격
    # 다대일 관계 정의
    author = models.ForeignKey(User,
                               on_delete=models.CASCADE,    # 삭제 되면 같이 삭제 되게
                               related_name='blog_posts')   # User 에서 Post 로의 역방향 관계 명칭 지정.
    body = models.TextField() # TEXT
    publish = models.DateTimeField(default=timezone.now)
    created = models.DateTimeField(auto_now_add=True) # 객체를 생성할 때 날짜가 자동으로 저장된다.
    updated = models.DateTimeField(auto_now=True) # 객체를 저장할 때 날짜가 자동으로 저장된다.
    status = models.CharField(max_length=2,
                              choices=Status.choices,
                              default=Status.DRAFT)

    class Meta: # 모델 내부에 Meta 클래스를 추가하여, 모델에 대한 메타데이터를 정의함.
        ordering = ['-publish'] # 출시일 역순으로 정렬
        indexes = [
            models.Index(fields=['-publish']), # 인덱스를 출시일 역순으로
        ]

    def __str__(self):
        return self.title
```

author 컬럼을 추가하고, Django 의 인증 프레임워크인 django.contrib.auth.models 모듈에서 User 모듈을 가져왔다.

이후 이러한 Entity 의 변경 사항을 데이터베이스에 반영해야 한다. 프로젝트의 루트 디렉터리의 쉘 프롬프트에서 다음 명령을 실행하면 Entity 의 변경 사항이 데이터베이스에 반영 된다.

```bash
python manage.py makemigrations blog
```

이후 DDL 쿼리를 보고 싶다면 다음과 같이 입력하며 된다.

```bash
python manage.py sqlmigrate blog 0001
```

정확한 출력은 사용 중인 DBMS 에 따라 다르다. 테이블 이름은 애플리케이션의 이름과 모델의 이름을 조합해서 만들어지는데, 모델의 Meta 클래스에서 db_table 속성을 사용해서 데이터베이스 이름을 사용자가 지정할 수도 있다.