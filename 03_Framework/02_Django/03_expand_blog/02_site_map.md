# Site Map

## 1. Site Map 이란?
Site Map(사이트 맵) 이란 웹사이트의 구조를 시각적으로 표현한 것이다. 웹 사이트의 모든 페이지와 그 페이지 간의 관계를 보여주며, 사용자와 검색 엔진 모두에게 유용하다.

사이트 맵은 HTML 사이트 맵과 XML 사이트 맵이 있다. HTML 페이지는 사용자가 웹사이트의 모든 페이지를 쉽게 찾을 수 있도록 링크를 제공하는 페이지이며, 보통 웹사이트의 하단에 위치한다.

XML 사이트 맵은 검색 엔진에 제출하기 위한 형식으로, 웹사이트의 모든 URL 과 메타데이터(업데이트 날짜, 중요도 등)를 포함한다. 주로 SEO(검색 엔진 최적화)를 목적으로 사용한다.

## 2. INSTALLED_APPS 설정에 추가
[settings.py]
```python
SITE_ID = 1

INSTALLED_APPS = [
    # ...
    'django.contrib.sites',
    'django.contrib.sitemaps',
]
```

## 3. 마이그레이션
```bash
python manage.py migrate
```

서드파티를 추가하는데 마이그레이션이 필요할까 싶겠지만, sites 애플리케이션을 추가하면 Site 라는 모델이 DB 에 추가된다고 한다.

## 4. sitemap 파일 만들기

[sitemaps.py]
```python
from django.contrib.sitemaps import Sitemap
from .models import Post

class PostSitemap(Sitemap):
    changefreq = 'weekly'
    priority = 0.9
    
    def items(self):
        return Post.published.all()
    
    def lastmod(self, obj):
        return obj.updated
```
sitempas 모듈의 Sitemap 클래스를 상속해서 커스텀 사이트맵을 정의했다.

## 5. urls.py 파일 편집
[urls.py]
```python
from django.contrib import admin
from django.urls import path, include
from django.contrib.sitemaps.views import sitemap
from blog.sitemaps import PostSitemap

sitemaps = {
    "posts": PostSitemap,
}

urlpatterns = [
    path("admin/", admin.site.urls),
    path("blog/", include("blog.urls", namespace="blog")),

    # 새로 추가
    path(
        "sitemap.xml",
        sitemap,
        {"sitemaps": sitemaps},
        name="django.contrib.sitemaps.views.sitemap",
    ),
]
```

이후 서버를 실행한다.
```bash
# server run
python manage.py runserver
```

http://localhost:8000/sitemap.xml 을 열면 모든 게시물을 포함한 XML 출력이 표시된다.

[사이트맵 XML]
![사이트맵 XML](../../../99_img/sitemap_xml.png)