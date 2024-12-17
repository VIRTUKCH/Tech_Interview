# Tagging 기능 추가하기

## 들어가기 전에
이번 장에서는 다른 블로그 플랫폼에서 사용되는 기능들로 블로그 애플리케이션을 확장한다. 이런 기능을 만들면서 새로운 컴포넌트와 기능에 대해 배워 보자.

## 1. 태깅 기능 추가하기
블로그의 매우 일반적인 기능으로, 보통 게시물은 태그(tag)를 사용해서 분류한다. 태그를 사용하면 간단한 키워드를 사용해 컨텐츠를 비계층적 방식으로 분류할 수 있다.

서드파티 태깅 애플리케이션을 프로젝트에 통합해서 태깅 시스템을 만들어 보자.

### 서드파티 애플리케이션이란?
서드파티 애플리케이션(Third-party application)은 특정 플랫폼, 프레임워크 또는 소프트웨어의 기능을 확장하거나 보완하기 위해 외부에서 개발된 소프트웨어이다.

예를 들면, Maven Repository 에 있는 의존성들을 서드파티 애플리케이션으로 볼 수 있다.

## 2. pip install django-taggit
django-taggit 은 주로 Tag 모델과 관리자를 제공해 모든 모델에 태그를 쉽게 추가할 수 있게 해주는 재사용 가능한 애플리케이션이다.

```bash
pip install django-taggit==3.0.0
```

위 명령어를 입력해 django-taggit 을 설치해 보자.

이후, mysite 프로젝트의 settings.py 파일을 열고 INSTALLED_APPS 설정에 taggit 을 추가하자.

[{root_directory}/settings.py]
```python
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",
    "blog.apps.BlogConfig",
    'taggit',
]
```

## 3. Model 에 tags 속성 추가
이제 models.py 파일을 열고 TaggableManager 관리자를 Post 모델에 추가하자.

[{root_directory}/models.py]
```python
from taggit.managers import TaggableManager
class Post(models.Model):  # Inheritance
    # 다른 부분은 모두 생략했다...    
    tags = TaggableManager()
    # 다른 부분은 모두 생략했다...
```

이후 마이그레이션을 만들고 적용하자.

마이그레이션 만들기
```bash
python manage.py makemigrations blog
```

마이그레이션 적용하기
```bash
python manage.py migrate
```
