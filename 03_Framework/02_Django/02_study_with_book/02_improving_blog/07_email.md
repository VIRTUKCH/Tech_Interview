# E-Mail

## 1. 이메일을 보내기 위한 환경
Django 로 이메일을 보내기 위해서는 로컬 SMTP(Simple Mail Transfer Protocol) 서버가 있거나, 이메일 서비스 공급자와 같은 외부 SMTP 서버에 액세스해야 한다.

## 2. SMTP 란?
SMTP(간단 메일 전송 프로토콜)는 이메일을 전송하는 데에 사용되는 프로토콜이다. SMTP 는 클라이언트와 서버 간의 통신을 관리하며, 이메일을 다른 이메일 서버로 전송하는 역할을 수행한다.

[SMTP 의 주요 기능]
- 이메일 전송 : 이메일 클라이언트에서 서버로 이메일을 전송하고, 서버 간에 이메일을 전달한다.
- 인증 및 보안 : SMTP 는 기본적인 인증 메커니즘을 제공하며, SSL/TLS 암호화를 통해 이메일 전송의 보안을 강화할 수 있다.

## 3. Django 에서 설정하는 SMTP 의 구성 (settings.py)
내 책에서는 표준 Gmail 계정과 함께 Google 의 SMTP 서버를 사용한다. settings.py 파일을 열어 아래와 같이 수정해 보자.

```python
# settings.py

# 추가 시, 모든 이메일을 보내는 대신 쉘에 출력한다.
# EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'

EMAIL_HOST = 'smtp.gmail.com'  # SMTP 서버 주소
EMAIL_HOST_USER = 'your_email@gmail.com'  # 발신자 이메일
EMAIL_HOST_PASSWORD = ''  # 발신자 이메일 비밀번호 -> App Password 별도 발급해서 정리함.
EMAIL_PORT = 587  # TLS 포트
EMAIL_USE_TLS = True  # TLS 사용
```

이후 시스템 쉘 프롬프트에서 다음 명령을 실행하여 파이썬 쉘을 열자.
```bash
python manage.py shell
```

이후 shell 을 사용하여 import 한 메서드를 실행시킨다.
```python
from django.core.mail import send_mail

password = '12345'  # 비밀번호 설정
subject = '비밀번호 찾기'
message = '새로 발급 받을 비밀번호는 ' + password + ' 입니다.'
from_email = 'empty'  # 발신자 이메일 (settings.py에 설정한 이메일로 사용)
recipient_list = ['kch4731@naver.com']  # 받는 사람 이메일 리스트

send_mail(
    subject,
    message,
    from_email,
    recipient_list,
    fail_silently=False  # 이메일 전송 실패 시 예외 발생
)
```

나의 경우에는 Django 와 Python 의 버전이 상호 호환되지 않아 에러가 발생했다. python 은 3.11, Django 는 ~=4.1.0 을 사용했더니 문제를 해결할 수 있었다.

## 4. View 에서 이메일 보내기
이제 CLI 를 사용하는 것이 아니라, 실제 View 를 수정하여 브라우저를 통해 메일을 보낼 것이다.

views.py, urls.py 파일을 수정하고 share.html 파일을 추가했다.

[views.py]
```python
from django.shortcuts import render, get_object_or_404
from django.views.generic import ListView
from .models import Post
from .forms import EmailPostForm
from django.core.mail import send_mail

class PostListView(ListView):
    '''
    Alternative post list view
    '''
    queryset = Post.published.all()
    context_object_name = 'posts'
    paginate_by = 3
    template_name = 'blog/post/list.html'

def post_share(request, post_id):
    
    # 1. 일단 게시물을 조회하게 놔 둬.
    post = get_object_or_404(Post, id=post_id, status=Post.Status.PUBLISHED)
    sent = False
    
    # 2. 근데 만약 POST 라면 == 폼이 제출되었다면
    if request.method == 'POST':

        # 2-1. form 이라는 변수에 해당 입력 값들을 할당.
        form = EmailPostForm(request.POST)

        # 2-2. form 이라는 변수에 할당된 값들이 유효한가?
        if form.is_valid():
            cd = form.cleaned_data # 폼 데이터가 유효하지 않다면, 유효한 필드만 포함하게 만듦.
            post_url = request.build_absolute_uri(post.get_absolute_url())
            subject = f"{cd['name']} recommends you read " \
                      f"{post.title}"
            message = f"Read {post.title} at {post_url}\n\n" \
                      f"{cd['name']}\'s comments: {cd['comments']}"
            send_mail(subject, message, 'your_account@gmail.com',
                      [cd['to']])
            sent = True
    
    # 3. POST 가 아니라면 == 제출하기 전이다.
    else:
        form = EmailPostForm() # 템플릿에 비어 있는 폼을 표시하는 데 사용된다.
    
    return render(request, 'blog/templates/post/share.html', {'post': post, 'form': form, 'sent': sent})

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
    path('<int:post_id>/share/',
         views.post_share, name='post_share'),
]
```

[share.html]
```html
{% extends "blog/base.html" %}

{% block title %}Share a post{% endblock %}

{% block content %}
  {% if sent %}
    <h1>E-mail successfully sent</h1>
    <p>
      "{{ post.title }}" was successfully sent to {{ form.cleaned_data.to }}.
    </p>
  {% else %}
    <h1>Share "{{ post.title }}" by e-mail</h1>
    <form method="post" novalidate>
      {{ form.as_p }}
      {% csrf_token %} <!-- Django 는 모든 POST 요청에서 CSRF 토큰을 확인한다 -->
                       <!-- POST 를 통해 제출되는 모든 폼에 csfr_token 태그를 포함해야 한다 -->
      <input type="submit" value="Send e-mail">
    </form>
  {% endif %}
{% endblock %}
```

## 5. Django 의 POST 요청과 CSRF Token
Django 는 CSRF(Cross-Site Request Forgecy) 공격을 방지하기 위해 CSRF 토큰을 사용한다. 이 토큰은 POST 요청을 보내는 폼에 포함되어야 한다. 또한, 템플릿 엔진을 사용하지 않더라도 CSRF 토큰 검사는 수행된다.