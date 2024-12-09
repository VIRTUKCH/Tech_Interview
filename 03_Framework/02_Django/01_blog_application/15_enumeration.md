# Enumeration

## 1. Enum (열거형)
열거형은 미리 정의된 상수 집합을 나타내는 데이터 타입니다. 이를 통해 코드에서 특정 값의 의미를 명확하게 하여 가독성을 높이고, 실수를 줄일 수 있다.

Django 에서는 TextChoices, IntegerChoices, Choices 와 같은 클래스를 사용하여 열거형을 정의할 수 있다. 각 선택지는 고유한 값(value)과 레이블(label)을 가진다.

## 2. 코드 예시
```python
from django.db import models
from django.utils import timezone

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

models.TextChoices 를 상속(subclass)해서 열거형 클래스 Status 를 정의했다.

- 클래스 이름 : Status
- 선택 항목 : DRAFT, PUBLISHED
- 값 : DF, PB
- 레이블 혹은 읽을 수 있는 명칭 : Draft, Published

## 3. Python Shell Prompt 에서 확인하기

```bash
python manage.py shell
from blog.models import Post
```

값-레이블 쌍으로 열거형 항목 얻기
```bash
Post.Status.choices
```

사람이 읽을 수 있는 열거형 항목 명칭 얻기
```bash
Post.Status.labels
```

열거형 항목들의 값 얻기
```bash
Post.Status.values
```

열거형 항목들의 명칭 얻기
```bash
Post.Status.names
```

Post.Status.PUBLISHED 처럼 열거형의 특정 항목에 액세스할 수 있으며 해당 항목의 .label, .name, .value 속성에도 액세스할 수 있다.