# QuerySet

## 1. QuerySet 이란
QuerySet 은 데이터베이스에서 객체를 검색하기 위한 일련의 데이터베이스 쿼리 모음이다. QuerySet 에 필터를 적용해서 주어진 매개변수를 기반으로 쿼리 결과의 범위를 좁힐 수 있다.

Django ORM 은 QuerySet 을 기반으로 한다.

## 2. 객체 조회 및 생성(CRUD 중 R, C)
일단 쉘 프롬프트에서 다음 명령어를 실행해서 파이썬 쉘을 열자.
```shell
python manage.py shell
```

그리고 다음 코드 줄을 입력하자.
```python
from django.contrib.auth.models import User
from blog.models import Post

# 1. findByUsername
user = User.objects.get(username='admin')

# 2. 저장할 객체 생성
post = Post(title='Another post',
            slug='another-post',
            body='Post body.',
            author=user)

# 3. 저장
post.save() 
```
위 코드는 크게 두 가지로 나눌 수 있다.

1. username 이 'admin' 인 user 를 찾아 객체에 할당
2. post 객체를 생성하여 데이터베이스에 저장

여기서는 조회, 저장 메서드 두 가지가 사용되었다.

### 1. 조회 (Read)
```python
user = User.objects.get(username='admin')
```

get() 메서드를 사용하면 데이터베이스에서 단일 객체를 검색할 수 있다. 위 메서드는 username 이 'admin'인 객체를 조회했다.

결과가 데이터베이스에서 반환되지 않으면 DoesNotExist 예외를 발생시키고, 둘 이상의 결과를 반환하면 MultipleObjectsReturned 예외를 발생시킨다. (단일 객체 검색)

두 예외 모두 쿼리가 수행되는 모델 클래스의 속성이다.

### 2. 저장 (Create)
```python
post = Post(title='Another post', slug='another-post', body='Post body.', author=user)
post.save()
```

다음으로 생성해서 Post 객체를 저장하는 로직이다. 일단은 Python 객체로 생성한 뒤, save() 메서드를 사용해서 DB 에 저장하고 있다.

## 3. QuerySet 주요 특징
QuerySet 은 **쿼리 모음** 이다. 예를 들면, 다음 코드를 QuerySet 이라 할 수 있다.
```python
# QuerySet을 정의하지만 쿼리는 실행되지 않음
queryset = Post.objects.filter(status='published')

# 여러 조건을 체인하여 필터링
queryset = Post.objects.filter(status='published').order_by('-publish')
```
이후 filter(), exclude(), order_by(), values(), distinct() 등의 메서드를 붙일 수 있다.

JDBC 의 ResultSet 과는 다른 개념이고, JPA 가 만드는 CriteriaQuery 또는 JPQL 과 비슷한 개념이라고 생각하면 될 것 같다.

## 4. 데이터베이스 설정
프로젝트의 settings.py 파일의 DATABASES 설정에서 프로젝트의 데이터베이스를 정의할 수 있다. Django 는 한 번에 여러 데이터베이스로 작업할 수 있으며, 데이터베이스 라우터를 프로그래밍해서 커스텀 데이터 라우팅 스키마를 만들 수 있다.

## 5. 객체 수정하기 (Update)
```python
post.title = 'New title'
post.save()
```
같은 save() 메서드의 사용이지만 이번에는 UPDATE SQL 문을 수행했다.

## 6. objects
Post.objects.get() 을 사용해서 단일 객체를 조회했다. 장고 모델은 최소 하나의 관리자가 있으며 기본 관리자는 objects 라고 한다. 모델 관리자를 사용해 QuerySet 객체를 얻는다.

테이블에서 모든 객체를 조회하려면 다음과 같이 기본 관리자에서 all() 메서드를 사용하면 된다.
```python
all_posts = Post.objects.all() # JPA 중 findAll() 과 유사
```

개인적인 생각이지만 objects 는 JPA 에서 Persistence Context 에 접근하는 Entity Manager 의 역할을 수행하지 않나 싶다. 다만, save() 할 때는 Post.objects.save() 가 아니라 post.save() 이니 조금은 신기하다.

### Post.objects 를 생성하지 않았는데 post.save() 를 호출할 수 있는 이유
save() 할 때는 Post.objects.save() 가 아닌 post.save() 로 호출된다. 이는 Django 의 ORM 구조에서 save() 메서드가 인스턴스에 바인딩되어 있기 때문이다.

따라서 각 객체가 자신의 상태를 알고 있고, 이를 데이터베이스에 반영하는 방식으로 작동한다.

## 7. Lazy Loading
장고 QuerySet 은 느린(lazy) 특성을 가지는데, 필요할 때만 실제 쿼리를 실행한다. 이를 통해 메모리 사용을 최적화하고 불필요한 데이터베이스 호출을 줄일 수 있다.

## 8. 여러가지 메서드

### 8-1. filter()
QuerySet 을 필터링하기 위해서는 관리자의 filter() 메서드를 사용할 수 있다. 예를 들어 다음 QuerySet 을 사용하여 2023년에 게시된 모든 게시물을 조회할 수 있다.
```python
Post.objects.filter(publish__year=2023) # 하나의 필터만 사용

Post.objects.filter(publish__year=2023, author__username='admin') # 두 개의 필터를 동시에 사용

Post.objects.filter(publish__year=2023) \
            .filter(author__name='admin') # 체인 방식으로도 필터를 사용할 수 있으며, 동일한 결과를 얻음
```

filter() 메서드에서 지정한 조건은 SQL 쿼리의 WHERE 절로 변환되어 데이터베이스에서 실행된다. 또한, 만약 테이블에 존재하지 않는 컬럼을 필터 조건으로 사용한 경우에는 데이터베이스에서 에러가 발생한다. 유의 깊게 볼  점은, Django 에서 DoesNotExist 예외를 발생시키는 것이 아니라 데이터베이스에서 에러를 발생시킨다는 것이다.

### 8-2. exclude()
관리자의 exclude() 메서드를 사용해서 QuerySet 에서 특정 결과를 제외할 수 있다. 예를 들어 제목이 Why 로 시작하지 않는 2023년에 게시된 모든 게시물은 다음과 같이 조회할 수 있다.
```python
Post.objects.filter(publish__year=2023) \
            .exclude(title__startswith='Why')
```

실제 변환되는 쿼리는 다음과 같다.
```sql
SELECT * FROM blog_post 
WHERE publish_year = 2023 
AND title NOT LIKE 'Why%';
```

### 8-3. order_by()
관리자의 order_by() 메서드를 사용해서 필드 별로 결과를 정렬할 수 있다. 예를 들어 다음과 같이 모든 객체를 title 로 정렬해 조회할 수 있다.
```python
Post.objects.order_by('title') # 오름차순
Post.objects.order_by('-title') # 내림차순
```

### 8-4. 객체 삭제하기
객체를 삭제하기 위해서는 객체 인스턴스에서 delete() 메서드를 사용할 수 있다.
```python
post = Post.objects.get(id=1)
post.delete()
```
객체를 삭제할 때는 외래키 제약 조건에 대해 이해한 뒤에 삭제하도록 하자. on_delete 가 CASCADE 로 되어 있다면 모든 종속관계의 객체들도 삭제될 수 있다.

#### 다섯 가지 외래키 제약 조건

##### 1. CASCADE
- 부모 객체가 삭제될 때, 해당 객체에 종속된 모든 자식 객체도 자동으로 삭제된다.
- 예를 들어, 게시물이 삭제되면 그 게시물에 대한 모든 댓글도 삭제된다.
```python
class Post(models.Model):
    # ...

class Comment(models.Model):
    post = models.ForeignKey(Post, on_delete=models.CASCADE)
```

##### 2. PROTECT
부모 객체가 삭제될 때, 종속된 자식 객체가 존재하면 삭제를 방지한다. 이 경우 ProtectedError 가 발생한다.
```python
class Comment(models.Model):
    post = models.ForeignKey(Post, on_delete=models.PROTECT)
```

##### 3. SET_NULL
부모 객체가 삭제될 때, 자식 객체의 외래 키 필드를 NULL 로 설정한다. 이 경우 외래 키 필드는 null=True 로 설정되어 있어야 한다.
```python
class Comment(models.Model):
    post = models.ForeignKey(Post, on_delete=models.SET_NULL, null=True)
```

##### 4. SET_DEFAULT
부모 객체가 삭제될 때, 자식 객체의 외래 키 필드를 기본 값으로 설정한다. 기본 값을 외래 키 필드에 default 인자를 사용하여 설정해야 한다.

##### 5. DO_NOTHING
부모 객체가 삭제될 때 아무 작업도 수행하지 않는다. 이 경우, 데이터베이스에서 무결성을 수동으로 관리해야 한다.

### 8-5. QuerySet 이 데이터베이스에 접근하여 실제 쿼리를 실행하는 시점 (QuerySet 이 실행되는 시점)
QuerySet 생성은 평가될 때까지 어떠한 데이터베이스 활동도 하지 않는다. QuerySet 은 일반적으로 평가되지 않은 다른 QuerySet 을 반환한다.

원하는 만큼 QuerySet 을 연결할 수 있으며, QuerySet 이 평가될 때까지 데이터베이스에 적용하지 않는다. QuerySet이 평가되면 데이터베이스에 대한 SQL 쿼리로 변환된다.

QuerySet 은 다음과 같은 경우에만 평가된다.
- QuerySet 의 첫 반복 시에 (한 번에 list 를 모두 가져옴)
- Post.objects.all()[:3] 과 같이 나눌 때 (한 번에 세 개의 객체를 가져옴)
- 피클(pickle) 또는 캐시할 때 (이해 못했음)
- QuerySet 에 대해 repr() 또는 len() 을 호출할 때 (개수를 가져옴 COUNT 쿼리)
- 명시적으로 list() 를 호출할 때 (전체 list를 모두 가져옴)
- bool(), or, and, if 와 같은 명령문에서 체크할 때 (제어문을 실행하기 위한 조건을 확인할 때 DB 에 접근)

#### Pickle
Pickle 은 파이썬 객체를 바이트 스트림으로 변환하여 파일에 저장하거나 네트워크를 통해 전송할 수 있게 해주는 모듈이다. 파이썬에서 객체를 직렬화(Serialize)하고 역직렬화(Deserialize)하는 데 사용되는 표준 모듈이라고 한다.

이 과정을 피클링이라고 하며, 반대로 바이트 스트림을 다시 파이썬 객체로 변환하는 과정을 언피클링(unpickling) 이라고 한다.

피클링은 데이터를 파일이나 네트워크로 전송할 때 유용하며, QuerySet 을 평가하여 실제 데이터를 메모리에 로드하게 된다.