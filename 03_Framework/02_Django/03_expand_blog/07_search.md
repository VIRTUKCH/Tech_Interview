# Search (조회)

## 1. INSTALLED_APPS 설정에 PostgreSQL 추가하기
[settings.py]
```python
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    "blog.apps.BlogConfig",
    "taggit",  # 태그 서드파티
    "django.contrib.sites",  # 사이트 맵
    "django.contrib.sitemaps",  # 사이트 맵
    "django.contrib.postgres" # PostgreSQL DB
]
```

이후 "python manage.py shell" 을 터미널에 입력해서 PostgreSQL 을 쓸 수 있다.

```bash
>>> from blog.models import Post
>>> Post.objects.filter(body__search='first')
<QuerySet [<Post: 첫 글>]>
```

이렇게 조회할 수도 있다.

## 2. 여러 필드를 검색하기
[shell]
```bash
>>> from django.contrib.postgres.search import SearchVector
>>> from blog.models import Post
>>> 
>>> Post.objects.annotate(
...     search=SearchVector('title', 'body'),
... ).filter(search='post')
<QuerySet [<Post: Fourth Post>, <Post: Third Post>, <Post: Second Post>, <Post: 첫 글>]>
```

annotate 를 사용해서 두 필드로 SearchVector 를 정의하면 게시물의 title 과 body 모두에 매칭시키는 기능을 제공한다.

## 3. 검색 View 만들기
사용자가 게시물을 검색할 수 있도록 Custom View 를 만들어 보겠다. Spring Framework 와 비교하면 DTO(Data Transfer Object) 를 만들고 Service 로직을 만드는 절차와 비슷하다.

일단 form 을 만들어 보자. Spring 에서 @ModelAttribute 를 통해 HTML 의 form 을 사용자에게 받아오는 절차와 비슷하다. 
[forms.py]
```python
from django import forms
from .models import Comment


class EmailPostForm(forms.Form):
    name = forms.CharField(max_length=25)
    email = forms.EmailField()
    to = forms.EmailField()
    comments = forms.CharField(required=False, widget=forms.Textarea)


class CommentForm(forms.ModelForm):
    class Meta:
        model = Comment
        fields = ["name", "email", "body"]

### 추가한 부분
class SearchForm(forms.Form):
    query = forms.CharField()

```

[views.py]
```python
from django.shortcuts import render, get_object_or_404, redirect
from .models import Post, Comment
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.views.generic import ListView
from django.contrib.postgres.search import SearchVector, SearchQuery, SearchRank
from django.contrib.postgres.search import TrigramSimilarity
from .forms import EmailPostForm, CommentForm, SearchForm
from django.core.mail import send_mail
from django.views.decorators.http import require_POST
from taggit.models import Tag
from django.db.models import Count


def post_list(request, tag_slug=None):
    post_list = Post.published.all()
    tag = None
    if tag_slug:
        tag = get_object_or_404(Tag, slug=tag_slug)
        post_list = post_list.filter(tags__in=[tag])
    # Pagination with 3 posts per page
    paginator = Paginator(post_list, 3)
    page_number = request.GET.get("page", 1)
    try:
        posts = paginator.page(page_number)
    except PageNotAnInteger:
        # If page_number is not an integer deliver the first page
        posts = paginator.page(1)
    except EmptyPage:
        # If page_number is out of range deliver last page of results
        posts = paginator.page(paginator.num_pages)
    return render(request, "blog/post/list.html", {"posts": posts, "tag": tag})


def post_detail(request, year, month, day, post):
    post = get_object_or_404(
        Post,
        status=Post.Status.PUBLISHED,
        slug=post,
        publish__year=year,
        publish__month=month,
        publish__day=day,
    )

    # List of active comments for this post
    comments = post.comments.filter(active=True)
    # Form for users to comment
    form = CommentForm()

    # List of similar posts
    post_tags_ids = post.tags.values_list("id", flat=True)
    similar_posts = Post.published.filter(tags__in=post_tags_ids).exclude(id=post.id)
    similar_posts = similar_posts.annotate(same_tags=Count("tags")).order_by(
        "-same_tags", "-publish"
    )[:4]

    return render(
        request,
        "blog/post/detail.html",
        {
            "post": post,
            "comments": comments,
            "form": form,
            "similar_posts": similar_posts,
        },
    )


class PostListView(ListView):
    """
    Alternative post list view
    """

    queryset = Post.published.all()
    context_object_name = "posts"
    paginate_by = 3
    template_name = "blog/post/list.html"


def post_share(request, post_id):
    # Retrieve post by id
    post = get_object_or_404(Post, id=post_id, status=Post.Status.PUBLISHED)
    sent = False

    if request.method == "POST":
        # Form was submitted
        form = EmailPostForm(request.POST)
        if form.is_valid():
            # Form fields passed validation
            cd = form.cleaned_data
            post_url = request.build_absolute_uri(post.get_absolute_url())
            subject = f"{cd['name']} recommends you read " f"{post.title}"
            message = (
                f"Read {post.title} at {post_url}\n\n"
                f"{cd['name']}'s comments: {cd['comments']}"
            )
            send_mail(subject, message, "your_account@gmail.com", [cd["to"]])
            sent = True

    else:
        form = EmailPostForm()
    return render(
        request, "blog/post/share.html", {"post": post, "form": form, "sent": sent}
    )


@require_POST
def post_comment(request, post_id):
    post = get_object_or_404(Post, id=post_id, status=Post.Status.PUBLISHED)
    comment = None
    # A comment was posted
    form = CommentForm(data=request.POST)
    if form.is_valid():
        # Create a Comment object without saving it to the database
        comment = form.save(commit=False)
        # Assign the post to the comment
        comment.post = post
        # Save the comment to the database
        comment.save()
    return render(
        request,
        "blog/post/comment.html",
        {"post": post, "form": form, "comment": comment},
    )


### 추가한 부분
def post_search(request):
    form = SearchForm()
    query = None
    results = []

    if "query" in request.GET:
        form = SearchForm(request.GET)
        if form.is_valid():
            query = form.cleaned_data["query"]
            results = (
                Post.published.annotate(
                    similarity=TrigramSimilarity("title", query),
                )
                .filter(similarity__gt=0.1)
                .order_by("-similarity")
            )

    return render(
        request,
        "blog/post/search.html",
        {"form": form, "query": query, "results": results},
    )

```
검색을 할 때 고려할 만한 부분인데, POST 대신 GET 방식으로 검색을 구현하면 URL 에 쿼리에 대한 내용이 들어가게 된다. 이 URL 을 사용자들 간에 고려할 때 검색 이후 URL 을 공유하면 같은 화면을 공유할 수 있기 때문에, 가능하면 검색은 GET 방식을 사용하는 것이 좋겠다. (검색에 굳이 감추어야 할 정보는 없을 것)

### Django 내 의존성 이용하여 할 수 있는 것들
- SearchForm 을 인스턴스화 해서 query 를 뽑아 서버에 전달. (Spring 단에서 DTO 로 사용할 수 있겠음)
- SearchVector 를 사용해서 다중 검색 기능 구현 (제목, 내용 어디에 등장하던 간에 검색의 결과로 가져올 수 있도록)
- SearchRank 를 사용하여 관련성에 따른 결과 정렬 (둘 다 등장한다면, 어떤 것을 위로 띄울 것이냐. ex_등장 수)
- SearchVector 사용하여 검색어에 가중치 부여 (우선순위 부여하기, 중요하지 않은 정보 안 뜨게 만들기)
- TrigramSimilarity 이용하여 세 글자 이상 겹치는 검색 결과 조회하기