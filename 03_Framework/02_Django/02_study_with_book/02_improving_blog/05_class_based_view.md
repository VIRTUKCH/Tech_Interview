# 클래스 기반 뷰

## 1. View
지금까지는 함수 기반 View 를 사용했다. 이번 단원에서 다뤄볼 것은 클래스 기반 뷰이다.

클래스 기반 뷰는 함수 대신 파이썬 객체로 뷰를 구현하는 방법이다. 뷰는 웹 요청을 받고 응답을 반환하는 함수이므로 뷰를 클래스 메서드로 정의할 수도 있다.

클래스 기반 View 는 HTTP 메서드와 관련한 코드를 조건부 분기 대신 별도의 메서드로 구성할 수 있고, 다중 상속을 사용해 재사용 가능한 뷰 클래스(믹스인) 을 생성할 수 있다는 장점이 있다.

## 2. 게시글 목록에 클래스 기반 View 사용하기
[이전 게시글 목록 View]
```python
from django.shortcuts import render, get_object_or_404
from .models import Post
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger

def post_list(request):
    post_list = Post.published.all() # 커스텀 관리자
    # 페이지 당 세 개의 게시물로 페이지를 매김.
    paginator = Paginator(post_list, 3)
    page_number = request.GET.get('page', 1)

    try:
        posts = paginator.page(page_number)
    
    except PageNotAnInteger: # page_number 가 정수가 아니라면
        posts = paginator.page(1) # 첫 페이지를 반환하자.
    
    except EmptyPage: # 페이지의 번호가 벗어나면
        posts = paginator.page(paginator.num_pages) # 마지막 페이지를 반환하자.

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

[클래스 기반 게시글 목록 View(후)]
```python
from django.shortcuts import render, get_object_or_404
from .models import Post
from django.views.generic import ListView

class PostListView(ListView):
    '''
    Alternative post list view
    '''
    queryset = Post.published.all()
    context_object_name = 'posts'
    paginate_by = 3
    template_name = 'blog/post/list.html'

def post_detail(request, year, month, day, post):
    post = get_object_or_404(Post,
                            status=Post.Status.PUBLISHED,
                            slug=post,
                            publish__year=year,
                            publish__month=month,
                            publish__day=day)
    
    return render(request,
                  'blog/post/detail.html',
                  {'post': post})
```

urls.py 파일 또한 바꿔줬다.

[urls.py]
```python
from django.urls import path
from . import views

app_name = 'blog'
urlpatterns = [
    # post View
    # path('', views.post_list, name='post_list'),
    path('', views.PostListView.as_view(), name='post_list'),
    path('<int:year>/<int:month>/<int:day>/<slug:post>/',
            views.post_detail,
            name='post_detail'),
]
```

클래스 기반의 ListView(클래스로 Pagination 을 구현하는 경우) 는 page_obj 라고 하는 변수에 요청된 페이지를 전달한다. list.html 파일을 수정하여 page_obj 로 페이지가 전달되도록 수정했다.

[이전 list.html]
```html
{% extends "blog/base.html" %}

{% block title %}My Blog{% endblock %}

{% block content %}
  <h1>My Blog</h1>
  {% for post in posts %}
    <h2>
      <a href="{{ post.get_absolute_url }}">
        {{ post.title }}
      </a>
    </h2>
    <p class="date">
      Published {{ post.publish }} by {{ post.author }}
    </p>
    {{ post.body|truncatewords:30|linebreaks }}
  {% endfor %}
  {% include "pagination.html" with page=posts %}
{% endblock %}
```

[이후 list.html]
```html
{% extends "blog/base.html" %}

{% block title %}My Blog{% endblock %}

{% block content %}
  <h1>My Blog</h1>
  {% for post in posts %}
    <h2>
      <a href="{{ post.get_absolute_url }}">
        {{ post.title }}
      </a>
    </h2>
    <p class="date">
      Published {{ post.publish }} by {{ post.author }}
    </p>
    {{ post.body|truncatewords:30|linebreaks }}
  {% endfor %}
  {% include "pagination.html" with page=page_obj %}
{% endblock %}
```