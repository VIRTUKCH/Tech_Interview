# 댓글 기능 구현하기

## 1. 기획
현재 블로그 애플리케이션을 만들고 있다. 사용자들이 게시물에 댓글을 달 수 있게 만들려고 하는데, 댓글 시스템을 만들기 위해서는 다음과 같은 요소들이 필요하다.

[댓글 기능을 구현하기 위해 필요한 요소들 (Spring 에서의 역할)]
- 모델 (@Entity 역할)
- 데이터를 검증할 수 있는 폼 (@ModelAttribute)
- 댓글을 저장하는 뷰 (@Controller + @Service)
- 새로운 댓글 추가를 위한 템플릿 (.html)

위에 있는 것들을 모두 수정하면, 사용자가 html 페이지를 받고 form 을 통해 댓글을 작성하고, 로직을 거쳐 데이터베이스에 저장되고, 다른 사람들이 댓글을 조회할 수 있는 기능을 추가할 수 있다.

## 2. 댓글 모델 만들기
[models.py]
```python
class Comment(models.Model):
    # Post 와 다대일 관계를 맺는다.
    post = models.ForeignKey(Post,
                             on_delete=models.CASCADE,
                             related_name='comments')
    name = models.CharField(max_length=80)
    email = models.EmailField()
    body = models.TextField()
    created = models.DateTimeField(auto_now_add=True)
    updated = models.DateTimeField(auto_now=True)
    active = models.BooleanField(default=True)

    class Meta:
        ordering = ['created']
        indexes = [
            models.Index(fields=['created']),
        ]

    def __str__(self):
        return f'Comment by {self.name} on {self.post}'
```

[마이그레이션 생성]
```bash
python manage.py makemigrations blog
```

[마이그레이션 적용]
```bash
python manage.py migrate
```

## 3. 관리 사이트에 댓글 추가
Django 는 데이터베이스의 값에 접근할 수 있는 쉽고 간단한 UI 를 제공한다.

[admin.py]
```python
@admin.register(Comment)
class CommentAdmin(admin.ModelAdmin):
    list_display = ['name', 'email', 'post', 'created', 'active'] # Admin 리스트 페이지에 표시할 필드
    list_filter = ['active', 'created', 'updated'] # 필터 사이드바에 표시할 필드
    search_fields = ['name', 'email', 'body'] # Admin 검색 박스에서 검색할 필드
```

안 써도 되지만, 관리 사이트를 사용해서 인스턴스를 관리할 수 있는 기능을 제공하니 알아 두자.

## 4. 모델에서 Form 만들기
여기서 말하는 Form 이란 템플릿 엔진, HTML 에서 사용하는 '<'form'>' 태그를 말한다.

사용자가 블로그 게시물에 댓글을 달 수 있도록 폼을 작성해야 한다. 장고에는 폼을 만드는 데 사용할 수 있는 두 가지 기본 클래스인 Form 과 ModelForm 이 있다.

이전의 Post Model(@Entity) 를 만들 때에는 사용자가 이메일로 게시물을 공유할 수 있게 할 때 Form 클래스를 사용했다. 이번에는 기존 Comment 모델을 활용하고 동적으로 폼을 만들기 위해 ModelForm 을 사용해 보겠다.

[forms.py]
```python
from django import forms
from .models import Comment

class EmailPostForm(forms.Form):
    name = forms.CharField(max_length=25)
    email = forms.EmailField()
    to = forms.EmailField()
    comments = forms.CharField(required=False,
                               widget=forms.Textarea)

class CommentForm(forms.ModelForm):
    class Meta:
        model = Comment
        fields = ['name', 'email', 'body']
```

모델에서 폼을 만들려면 폼의 Meta 클래스에서 폼을 빌드할 모델을 지정하기만 하면 된다. ModelForm 을 사용하면 장고가 모델을 검사하고 해당 폼을 동적으로 만든다.

모델의 각 필드 유형에는 기본 폼 빌드 유형이 존재한다. 폼 유효성 검사 를 위해 모델 필드의 속성을 고려한다. 기본적으로 장고는 모델에 포함된 각 필드에 대한 폼 필드를 만든다.

그러나 템플릿 엔진을 사용할 수 없는 상황에서는 ModelForm 의 필요성이 줄어든다. 그럼에도 코드의 일관성을 유지하고, 백엔드 로직을 명확히 하는 데 도움이 될 수 있겠다.

## 5. View 에서 ModelForms 처리하기
[views.py]
```python
@require_POST # 이 뷰에는 POST 요청만을 허용하게 함. @PostMapping 같은 느낌
def post_comment(request, post_id): # post_id 는, 어떤 글에 속하는지 알기 위함. request 는 걍 붙는 거임.
    post = get_object_or_404(Post, id=post_id, status=Post.Status.PUBLISHED)
    comment = None

    # 댓글이 달림
    form = CommentForm(data=request.POST)
    if form.is_valid():
        comment = form.save(commit=False) # 데이터베이스에 저장하지 않고 Comment 객체 만들기
        comment.post = post # Post 가 할당이 되면
        comment.save() # 그 다음에 save()
    return render(request, 'blog/post/comment.html',
                            {
                                'post': post,
                                'form': form,
                                'comment': comment
                            })
```
댓글을 추가할 수 있는 페이지는 글에 대한 상세 정보를 조회할 수 있는 페이지이기 때문에, 게시물 상세를 조회하는 View 에서 댓글을 다는 메서드를 정의해야 한다.