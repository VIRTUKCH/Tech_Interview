# Form Data

## 1. Form Data 란?
Form Data 는 웹 애플리케이션에서 사용자가 입력한 데이터를 서버로 전송하는 방법 중 하나이다. 일반적으로 HTML 폼을 통해 수집된 데이터가 포함되며, 사용자가 웹 페이지에서 정보를 입력하고 제출할 때 생성된다.

당연하게도 Form Data 또한 CSS 의 꾸밈을 받을 수 있고, 다양한 형식으로 전송될 수 있으며, 주로 GET 또는 POST 방식으로 처리된다.

만약 Form Data 를 사용하지 않고 싶다면, AJAX(Asynchronous JavaScript and XML)를 사용하면, 웹 페이지를 새로 고치지 않고도 서버에 데이터를 비동기적으로 전송할 수 있다. JavaScript 의 fetch API 나 XMLHttpRequest 객체를 사용하여 데이터를 전송할 수 있다.

이번 장에서 할 것은 이메일로 어떤 게시물을 보내는 것이다. 이론적으로 발신자의 이메일, 수신자의 이메일, 내용만 있다면 이메일을 보낼 수 있다. 이번 파일에서는 Form Data 로 준비하는 과정에 대해 알아 본다.

## 2. Form Data 의 사용 이유
- 사용자로부터 정보를 수집하는 표준화된 방법
- 필수 입력 필드, 이메일 형식 검사 등 클라이언트 측에서 기본적인 유효성 검사를 지원.
- 웹 프레임워크에서 쉽게 처리할 수 있는 구조.

* 주의 : HTTPS(SSL/TLS) 를 사용하지 않으면 보안에 취약할 수 있음. CSRF 토큰 또한 주의할 것.

## 3. forms.py 파일 생성
```python
from django import forms

class EmailPostForm(forms.Form):
    name = forms.CharField(max_length=25)
    email = forms.EmailField()
    to = forms.EmailField()
    comments = forms.CharField(required=False,
                               widget=forms.Textarea)
```

사용자에게 입력 받을 정보를 Mapping 하기 위한 클래스이다. 각 필드 유형에는 필드가 HTML 와 Mapping 되는 기본 타입과 같은 것들이 있다. text, email, textarea 등 다양하다.

아래는 코드 예시이다.

```html
<form method="POST" action="">
    {% csrf_token %}
    
    <label for="id_name">이름:</label>
    <input type="text" id="id_name" name="name" maxlength="25" required>
    
    <label for="id_email">이메일:</label>
    <input type="email" id="id_email" name="email" required>
    
    <label for="id_to">수신자 이메일:</label>
    <input type="email" id="id_to" name="to" required>
    
    <label for="id_comments">댓글:</label>
    <textarea id="id_comments" name="comments"></textarea>
    
    <button type="submit">보내기</button>
</form>
```

## 4. View 에서 Form 처리
어떤 입력을 받아야 하는지에 대한 Form 을 .py 형식으로 만들었다. 이제는 폼의 인스턴스를 생성하고 전송된 폼의 값을 처리하는 로직, 뷰가 필요하다.

blog 애플리케이션의 views.py 파일을 열어서 코드를 추가했다.
```python
from django.shortcuts import render, get_object_or_404
from django.views.generic import ListView
from .models import Post
from .forms import EmailPostForm

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
    
    # 2. 근데 만약 POST 라면 == 폼이 제출되었다면
    if request.method == 'POST':

        # 2-1. form 이라는 변수에 해당 입력 값들을 할당.
        form = EmailPostForm(request.POST)

        # 2-2. form 이라는 변수에 할당된 값들이 유효한가?
        if form.is_valid():
            cd = form.cleaned_data # 폼 데이터가 유효하지 않다면, 유효한 필드만 포함하게 만듦.
    
    # 3. POST 가 아니라면 == 제출하기 전이다.
    else:
        form = EmailPostForm() # 템플릿에 비어 있는 폼을 표시하는 데 사용된다.
    
    return render(request, 'blog/templates/post/share.html', {'post': post,
                                                              'form': form})

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

post_share() 메서드를 새로 만들었다. View 는 Spring Boot 로 따지면 @Controller + @Service 정도라고 생각하면 될 듯하다.