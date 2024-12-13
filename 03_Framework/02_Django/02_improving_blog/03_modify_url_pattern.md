# URL 패턴 수정하기

## 1. urls.py 파일 편집
게시물 상세 URL 에 게시 날짜와 슬러그를 사용하도록 URL 패턴을 수정해 보자.

[urls.py]
```python
from django.urls import path
from . import views

app_name = 'blog'
urlpatterns = [
    # post View
    path('', views.post_list, name='post_list'),
    path('<int:year>/<int:month>/<int:day>/<slugLpost>/',
            views.post_detail,
            name='post_detail'),
]
```

패스 컨버터(path converter) int 는 year, month, day 매개 변수에 사용되는 반면 패스 컨버터 slug 는 post 매개 변수에 사용된다.

## 2. View 수정하기
새로운 URL 매개 변수와 일치하도록 post_detail 뷰의 매개 변수를 변경하고 이를 사용해서 해당 Post 객체를 조회하자.

[views.py]
```python
from django.shortcuts import render, get_object_or_404
from django.http import Http404

from .models import Post

def post_list(request):
    posts = Post.published.all() # 커스텀 관리자
    return render(request,
                  'blog/post/list.html',
                  {'posts': posts})

def post_detail(request, year, month, day, post):
    post = get_object_or_404(Post,
                            status=Post.Status.PUBLISHED,
                            slug=post,
                            publish__year=year,
                            publish__month=month,
                            publish__day=day)
    
    # get_object_or_404 메서드가 아닌 get() 메서드를 사용한 할 경우의 예외 처리
    # except Post.DoesNotExist:
    #     raise Http404("No Post found.")
    
    return render(request,
                  'blog/post/detail.html',
                  {'post': post})
```
기존에는 자동 생성된 id 를 가지고 구분했지만, 이제는 게시 일자와 slug 만 가지고도 구분할 수 있기 때문에 해당 정보들만 가지고 path 를 구성했다.

## 3. 표준 URL 수정하기
새로운 URL 매개 변수와 일치하도록 블로그 게시물의 표준 URL 매개변수 또한 수정해야 한다. models.py 파일을 열어 다음과 같이 get_absolute_url() 메서드를 편집하자.
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
    slug = models.SlugField(max_length=250, # -> VARCHAR : 소문자 + 하이픈(-)을 사용하는 게 컨벤션. URL 등에 적격
                            unique_for_date='publish') # unique_for_date 를 사용하면  slug 필드가 게시 필드에 지정된 날짜의 중복을 허용하지 않음.
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
                       args=[self.publish.year,
                             self.publish.month,
                             self.publish.day,
                             self.slug])
```

## 4. URL 을 바꾸기 위해서 수정해 주어야 하는 파일들 총 정리
예를 들어 Post List 에서 단일 Post 조회를 하는 상황이라고 가정하자. 그리고 나는 단일 Post 를 조회하는 URL 을 수정하고 싶은 상황이다.

이런 경우에는 아래 파일을 수정해 주어야 하겠다.

- models.py : get_absolute_url -> path 에 어떤 동적인 인자를 넣을 것인가
- urls.py : urlpatterns -> Vue.js 의 router 같은 느낌.
- 템플릿 파일(HTML) : 어떤 URL 로 이동할 것인가 (ex_ {{post.get_absolute_url}})
- view.py : return render() -> 어떤 HTML 파일을 넣어 둘 것인가.