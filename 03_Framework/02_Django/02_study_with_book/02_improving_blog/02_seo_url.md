# SEO(검색 엔진 최적화)에 부합하는 게시물 URL 만들기

## 1. SEO 란?
SEO(검색 엔진 최적화)는 웹사이트나 웹 페이지가 검색 엔진의 결과 페이지에서 더 높은 순위를 차지하도록 최적화하는 과정이다.

목표는 자연 검색 결과를 통해 유기적으로 더 많은 트래픽을 유도하는 것이다. SEO 는 여러 요소에 의해 영향을 받으며, 그 요소는 다음과 같다.

### SEO 에 영향을 주는 요소
- 키워드 최적화
- 메타 태그
- 콘텐츠 품질
- 모바일 최젃화
- 백링크

이번 글에서 배울 내용을 간단하게 요약하자면, RESTful 하게 블로그의 한 글을 나타내는 FE URL 을 하나 만든다면 '/blog/1' 정도가 될 것이다. 하지만, SEO 최적화를 위해 '/blog/2023/1/who-was-django-reinhardt/' 와 비슷하게 만들 수 있다.

앞서 만들어 둔 publish 날짜와 slug 값을 모두 포함하여 SEO 친화적인 URL 을 만드는 것이다.

## 2. models.py 파일 수정
```python
class Post(models.Model):
    slug = models.SlugField(max_length=250, # -> VARCHAR : 소문자 + 하이픈(-)을 사용하는 게 컨벤션. URL 등에 적격
                            unique_for_date='publish') # unique_for_date 를 사용하면  slug 필드가 게시 필드에 지정된 날짜의 중복을 허용하지 않음.
```
주석에 나와 있는 것처럼, unique_for_date 를 사용하면 slug 필드가 게시 필드에 지정된 날짜의 중복을 허용하지 않게 된다.

이제 슬러그가 게시 날짜를 기준으로 고유하다(하나이거나, 없거나)는 것을 보장할 수 있기 때문에, publish 와 slug 필드로 단일 게시글을 조회할 수 있다.

## 3. 마이그레이션
모델을 변경한 이후에는 마이그레이션을 생성해야 한다. unique_for_date 는 데이터베이스 수준에서 적용되는 것이 아니라 Django 수준에서 생성되는 것이기 때문에, 데이터베이스 마이그레이션이 필요하지 않다.

그러나 Django 는 마이그레이션을 사용해서 모든 모델 변경 사항을 추적하기 때문에, 마이그레이션을 생성해야 한다.

### migrations 파일은 계속 생기는 걸까?
```bash
python manage.py makemigrations blog
```
위 명령어를 입력하면 {어플리케이션 디렉터리}/migrations 디렉터리 하위에 모델을 어떻게 변경했는지에 대한 설명을 포함하는 파일이 생긴다.

나의 경우에는 해당 명령어를 치고 아래와 같은 메시지를 출력할 수 있었다.
```bash
(my_env) ~/01_kch/01_development_projects/07_django_practice/Django-practice/mysite (main)$ python manage.py makemigrations blog
Migrations for 'blog':
  blog/migrations/0002_alter_post_slug.py
    - Alter field slug on post
```

이후 마이그레이션을 적용하기 위해 다음과 같은 명령어를 입력했다.
```bash
python manage.py migrate
```

이렇게 하면 장고는 모든 마이그레이션이 적용되고 모델과 동기화된 것으로 간주한다. unique_for_date 가 데이터베이스 수준에서 적용이 강제되지 않기 때문에 데이터베이스에서 수행되는 작업은 없다.