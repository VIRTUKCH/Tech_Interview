# View
지금까지 ORM 사용 방법에 대해 알아 보았다. 이제는 blog 애플리케이션의 View 를 만들어 볼 것이다.

## 1. View
장고 View 는 웹 요청을 수신하고 웹 응답을 반환하는 파이썬 함수일 뿐이다. 원하는 응답을 반환하는 모든 로직은 View 에 들어간다. (Spring 의 @Controller 와 유사한 듯하다.)

기본적으로 MTV 패턴을 이용해서 Template 를 사용하는 방법을 먼저 익히는 듯하다. 이후에는 RESTful API 를 설계하여 React 와 같은 별도의 서버를 구축하여 FE 를 분리하는 방법 또한 익힐 계획이다.

먼저 애플리케이션 View 를 생성하고 View 에 맞는 URL 패턴을 정의한다. 끝으로 View 에서 생성된 데이터를 렌더링하는 HTML 템플릿을 생성한다. 각 View 는 템플릿을 렌더링하고 변수를 전달하고 렌더링된 출력과 함께 HTTP 응답을 반환한다.

## 2. 목록 및 상세 View 생성하기
게시물의 목록을 보여 주는 View 를 만들어 보겠다. blog 애플리케이션에서 views.py 파일을 편집한다.

```python
from django.shortcuts import render

from .models import Post

def post_list(request):
    posts = Post.published.all() # 커스텀 관리자
    return render(request,
                  'blog/post/list.html',
                  {'posts': posts})
```

post_list 뷰는 request 객체를 유일한 매개 변수로 사용한다. 그리고 이 매개 변수는 모든 View 에 필요하다.

이 뷰는 앞서 생성한 published 관리자를 사용해서 PUBLISHED 상태의 모든 게시물을 조회한다.

마지막으로 장고에서 제공되는 숏컷(shortcut) 함수 render()를 사용해서 주어진 템플릿으로 게시물 목록을 렌더링할 수 있다.

## 3. Shortcut Function
숏컷 함수(Shortcut Function)는 Django 에서 자주 사용하는 기능을 간편하게 사용할 수 있도록 미리 정의된 함수이다. 자주 사용되는 작업을 단순화하고, 코드의 가독성을 높이며, 개발자의 작업을 수월하게 해 준다.

예를 들면 render(), get_object_or_404(), redirect(), HttpResponse() 와 같은 메서드가 있다. Django 에서 자주 사용되는 함수를 숏컷이라는 이름으로 제공해 주기 때문에, 개발자가 더 빠르고 효율적으로 웹 애플리케이션을 개발할 수 있다.

## 4. render() 함수
render() 함수를 사용해서 주어진 템플릿으로 게시물 목록을 렌더링할 수 있다.

> 렌더링 : UI 를 구성하고 업데이트하는 모든 과정 (광범위한 개념임)

render() 함수는 request 객체, 템플릿 경로 및 컨텍스트 변수를 사용해서 주어진 템플릿을 렌더링하는데, 렌더링된 텍스트(일반적으로 HTML 코드)와 함께 HttpResponse 객체를 반환한다.

render() 함수는 요청에 관련된 정보를 템플릿에 전달할 때 사용된다. 지정된 템플릿에 설정된 모든 변수는 템플릿 콘텍스트 프로세서에 의해 접근 가능하다.

템플릿 콘텍스트 프로세서는 변수를 설정하는 callable 이다.

> callable : Python 에서 callable 은 호출 가능한 클래스 인스턴스, 함수, 메서드 등의 객체이다.

## 5. Http404 숏컷 함수
```python
from django.shortcuts import render
from django.http import Http404

from .models import Post

def post_list(request):
    posts = Post.published.all() # 커스텀 관리자
    return render(request,
                  'blog/post/list.html',
                  {'posts': posts})

def post_detail(request, id):
    try:
        post = Post.published.get(id=id)
    except Post.DoesNotExist:
        raise Http404("No Post found.")
    
    return render(request,
                  'blog/post/detail.html',
                  {'post': post})
```

게시물 상세를 조회하는 View 를 추가했다. 이 View 는 게시물의 id 를 인자로 사용한다. View 에서 우리는 기본 objects 관리자에서 get() 메서드를 호출해서 주어진 id 를 가진 Post 객체를 조회하려 한다.

결과가 없어 DoesNotExist 예외가 발생하면 HTTP 404 오류를 반환하기 위해 Http404 예외를 발생시킨다.

마지막으로 render() 숏컷 함수로 템플릿을 사용해 검색된 게시물을 렌더링한다.

## 6. 72 페이지부터 시작하기