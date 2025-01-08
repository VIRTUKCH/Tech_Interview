# Canoncial URL (표준 URL)

## 1. 표준 URL
표준 URL 은 리소스에 대한 기본 URL 이다. 특정 콘텐츠의 가장 대표적인 페이지 URL 이라고 생각하면 된다. 예를 들면, 네이버의 경우 www.naver.com 이 되겠다.

사이트에서 게시물을 표시하는 서로 다른 페이지가 존재할 수 있지만 게시물의 기본 URL 로 사용하는 URL 은 하나이다. 표준 URL 을 사용하면 페이지의 마스터 사본에 대한 URL 을 지정할 수 있다.

장고의 경우 모델에서 get_absolute_url() 메서드를 구현하여 객체의 표준 URL 을 반환할 수 있다. (오버라이딩 같은 것이 아니다. 사용자가 직접 구현해야 한다.)

## 2. django.urls 의 reverse() 유틸리티 함수
django.urls 의 reverse() 유틸리티 함수는 Django 에서 URL 패턴 이름을 사용하여 해당 URL 을 동적으로 생성하는 기능을 제공한다.

[urls.py 파일]
```python
from django.urls import path
from . import views

app_name = 'blog'
urlpatterns = [
    # post View
    path('', views.post_list, name='post_list'),
    path('<int:id>/', views.post_detail, name='post_detail'),
]
```

urls.py 파일에서 post_detail 이라는 이름의 path 를 추가했었다. 이 상황에서 models.py 파일에서 reverse() 함수를 사용할 수 있다.

```python
from django.urls import reverse

# 예를 들어, post_detail 이라는 URL 패턴이 있고, 해당 게시물의 ID 가 1인 경우
url = reverse('blog:post_detail', args=[1])
# url 은 '/blog/1/' 과 같은 형태가 된다.
```

## 3. models.py 수정
이번 장에서는 어플리케이션의 URL 패턴에 정의된 post_deatil URL 을 사용해서 Post 객체에 대한 URL 을 만들 것이다.

Django 는 URL 이름과 필요한 맥 변수를 사용해서 동적으로 URL 을 작성할 수 있는 다양한 URL 해석(resolver) 기능을 제공한다. 우리는 django.urls 모듈의 reverse() 유틸리티 함수를 사용할 것이다.

다음은 blog 애플리케이션의 models.py 파일을 편집해서 reverse() 추가하고 get_absolute_url() 메서드를 Post 모델에 추가한 코드이다.

```python
from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User
from django.urls import reverse

# 관리자 추가
class PublishedManager(models.Manager):
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
    
    # URL 이름을 이용해서 URL 을 동적으로 만듦.
    def get_absolute_url(self):
        return reverse('blog:post_detail', 
                       args=[self.id])
```

## 4. get_absolute_url() 메서드의 사용 및 장점
models.py 파일에서 get_absolute_url() 메서드를 사용하면서, RESTful 하게 path 에 post 의 id 가 함께 들어가도록 조치했다. 이렇게 하면, URL 이 변경되더라도 모델 내부에서만 수정하면 되므로 유지 관리가 용이해진다.

## 5. HTML 파일의 변경
기존의 list.html 파일에서는 다음과 같은 코드가 있었다.
```html
<a href="{% url 'blog:post_detail' post.id %}">
```

위 코드를 아래와 같이 변경했다.
```html
<a href="{{ post.get_absolute_url }}"
```

이렇게 하드코딩하는 것이 아니라, 만들어 둔 함수에 의존하게 설계하면, 유지보수 및 관리에 용이해진다는 장점이 있다.

여기에 env 파일을 이용해서 IP 나 포트번호 같은 것들을 함께 관리하면 더욱 좋겠다.