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

## 2. 여러 필드를 검색하기 (SearchVector)
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

annotate 를 사용해서 두 필드로 SearchVector 를 정의하면 게시물의 title 과 body 모두에 매칭시키는 기능을 제공한다. 제목과 본문 중 어디에 단어가 등장하던 간에 검색의 결과로 가져오고 싶다면, SearchVector 를 사용해서 두 가지 필드를 같이 넣으면 되겠다.

## 3. 검색 우선순위 차등화 (SearchRank)
블로그에 존재하는 글 중에서 어떤 단어를 제목 혹은 본문에 가지고 있는 글을 모두 조회하는 검색 엔진을 구현했다고 생각해 보자. 이 경우에, 한 단어를 검색 했을 때 여러 개의 블로그 글이 동시에 조회될 수 있다.

예를 들어 'Python' 이라고 검색했을 때, 수많은 검색 결과가 나올 것이고, 보통은 최신 글이 가장 먼저 조회될 수 있도록 상단에 위치할 것이다.

내부적인 구현은
- 'Python' 이라는 단어를 포함하고 있으면 등장하게 만들고
- 등장한 단어들을 날짜 순으로 정렬
하도록 구현되어 있을 것이다.

검색 결과 이후에 해당 검색 결과를 정렬함에 있어서 어떤 기준으로 정렬할 것인지에 대한 내용인데, 예를 들어 단어의 등장 횟수에 따라 순위를 매길 수도 있다. 이런 것들을 구현할 때 SearchRank 를 사용한다고 생각하면 되겠다.

## 4. 쿼리에 가중치 부여 (SearchVector)
검색 결과를 관련성에 따라 정렬할 때 특정 벡터의 가중치를 높일 수 있다. 예를 들어, 내가 검색한 단어가 제목과 일치할 수도 있고, 본문과 일치할 수도 있다. 이 때 제목과 관련한 것을 상단에 노출하고 싶다면, 제목이라는 벡터에 가중치를 추가적으로 올릴 수 있다.

Django 가 기본적으로 제공하는 가중치는 D, C, B, A 이며 각기 숫자 0.1, 0.2, 0.4, 1.0 을 나타낸다. title 검색 벡터(A)에 1.0 의 가중치를 적용하고 body 벡터(B) 에 0.4 의 가중치를 적용한다면, 제목의 일치가 본문의 일치보다 우선하게 할 수 있다.

이 때, 추가적으로 결과를 필터링해서 순위가 0.3 보다 높은 항목만 표시되도록 할 수도 있겠다. (이럴 거면 차라리 검색 기준에 안 넣는 게 더 낫지 않나 싶긴 하다.)

## 5. 일부 일치 검색 결과 (TrigramSimilarity)
트라이그램은 세 개의 연속된 문자 그룹이다. 두 문자열이 공유하는 트라이그램의 수를 세어 두 문자열의 유사성을 측정할 수 있다. 유사성을 측정하면 오타가 포함된 검색어에 대한 결과를 찾는 데에 유용하다.

PostgreSQL 에서 트라이그램을 사용하려면 pg_trgm 이라는 확장을 설치해야 한다. Django 에서 제공하는 기능이 아니라, PostgreSQL 에서 자체적으로 제공하는 기능이며, Django 는 이 기능을 활용할 수 있다.

## 6. 검색과 관련된 소소한 Tip
검색을 할 때 고려할 만한 부분인데, POST 대신 GET 방식으로 검색을 구현하면 URL 에 쿼리에 대한 내용이 들어가게 된다. 이 URL 을 사용자들 간에 고려할 때 검색 이후 URL 을 공유하면 같은 화면을 공유할 수 있기 때문에, 가능하면 검색은 GET 방식을 사용하는 것이 좋겠다. (검색에 굳이 감추어야 할 정보는 없을 것)

## 7. 요약
- SearchForm 을 인스턴스화 해서 query 를 뽑아 서버에 전달. (Spring 단에서 DTO 로 사용할 수 있겠음)
- SearchVector 를 사용해서 다중 검색 기능 구현 (제목, 내용 어디에 등장하던 간에 검색의 결과로 가져올 수 있도록)
- SearchRank 를 사용하여 관련성에 따른 결과 정렬 (둘 다 등장한다면, 어떤 것을 위로 띄울 것이냐. ex_등장 수)
- SearchVector 사용하여 검색어에 가중치 부여 (우선순위 부여하기, 중요하지 않은 정보 안 뜨게 만들기)
- TrigramSimilarity 이용하여 세 글자 이상 겹치는 검색 결과 조회하기