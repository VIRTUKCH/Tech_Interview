# Model Manager

## 1. 모델 관리자 생성하기
모든 모델의 기본 관리자는 objects 관리자이다. 이 관리자는 데이터베이스의 모든 객체를 조회한다. 그러나, 모델에 커스텀 관리자를 정의할 수도 있다.

커스텀 관리자를 사용하는 이유는 다양한데, 복잡한 쿼리를 여러 번 사용하는 경우에도 좋고, 프로젝트 전반에 걸쳐 일관된 방식으로 데이터를 조회하고 처리하여 팀원 간의 협업을 용이하게 할 수 있다.

## 2. 모델에 관리자 커스터마이징하기
방법은 총 두 가지가 있다.

### 2-1. 기존 관리자 모델에 관리자 메서드 추가하기
- Post.objects.my_manager() 과 같은 QuerySet 표기법 사용

### 2-2. 관리자가 반환하는 초기 QuerySet 수정하기
- Post.my_manager.all() 과 같은 QuerySet 표기법 사용

교재에서 두 번째 방식을 채택하기 때문에, 나는 두 번째 방식으로 코드를 수정해 보았다.
```python
from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User

# 관리자 추가
class PublishedManager(models.manager):
    def get_queryset(self):
        return super().get_queryset().filter(status=Post.Status.PUBLISHED)

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
    
    # 기본 관리자
    objects = models.Manager()

    # 커스텀 관리자
    published = PublishedManager()

    class Meta: # 모델 내부에 Meta 클래스를 추가하여, 모델에 대한 메타데이터를 정의함.
        ordering = ['-publish'] # 출시일 역순으로 정렬
        indexes = [
            models.Index(fields=['-publish']), # 인덱스를 출시일 역순으로
        ]

    def __str__(self):
        return self.title
```

모델에 선언된 첫 번째 관리자가 기본 관리자가 된다. Meta 의 속성 default_manager_name 을 사용해서 다른 기본 관리자를 지정할 수 있다.

모델에 정의된 관리자가 없으면 장고는 자동으로 objects 기본 관리자를 생성한다. 모델의 관리자를 선언했지만, objects 관리자도 유지하려면 모델에 명시적으로 추가해야 한다.

이전 코드에서는 기본 관리자의 objects 와 커스텀 관리자 published 를 Post 모델에 추가했다.

관리자에도 메서드를 추가했는데, 관리자의 get_queryset() 메서드는 실행할 QuerySet 을 반환한다. 상태별로 게시물을 필터링하고 PUBLISHED 상태의 게시물만 포함하는 연속된 QuerySet 을 반환하는 커스텀 QuerySet 을 만들기 위해 이 메서드를 재정의했다. (QuerySet 은 체인 방식으로 연속 작동하기 때문에 가능한 로직)