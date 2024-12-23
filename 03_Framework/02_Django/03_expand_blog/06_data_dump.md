# Data Dump

## 1. Data Dump 원리
이번 장에서는 SQLite3 로 데이터베이스를 구동시키던 것을 PostgreSQL 로 전환할 것이다. 그러나 이전의 데이터베이스는 여전히 가져가야 하기 때문에, 기존 데이터를 내보내고, 프로젝트의 데이터베이스를 PostgreSQL 로 전환한 뒤 데이터를 새로운 데이터베이스로 가져와야 한다.

Django 는 데이터를 데이터베이스에서 픽스처(fixtures) 라는 파일로 로드하고 덤프하는 간단한 방법을 제공한다. 장고는 JSON, XML, YAML 형식의 픽스처를 지원한다. 데이터베이스에 포함된 모든 데이터를 픽스처로 만들 것이다.

생각해 보면, fixture 와 Java 의 Byte Code 가 조금 닮아 있지 않나 싶다. 데이터를 하나의 표준화된 형태로 전환하여 다른 구현체를 사용하는 데이터베이스에도 이식할 수 있게 만들면서, 직렬화 하여 네트워크를 통해 해당 파일을 받을 수 있게 만들었다는 점에서 그렇다.

## 2. 데이터 덤프 명령어
데이터를 덤프할 때 애플리케이션(도메인과 유사) 범위를 지정할 수도 있고, JSON - XML - YAML 같은 형식을 지정할 수도 있고, 출력 파일을 지정할 수도 있고, 들여쓰기도 지정할 수 있다.

일단 명령어를 아래와 같이 쳐보자.

```bash
python manage.py dumpdata --indent=2 --output=mysite_data.json
```

이렇게 하면 manage.py 파일이 있는 디렉터리에 'mysite_data.json' 이라는 파일이 하나 생길 거다. 데이터베이스에 저장되어 있는 내용이 보인다. 나는 개인적으로 admin 계정의 비밀번호가 기본적으로 암호화 되어 있다는 점에서 신기했다.

## 3. 프로젝트에서 데이터베이스 전환하기
이제 settings.py 파일을 편집해서 DATABASES 설정을 다음과 같이 수정해 보자.
```python
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.postgresql",
        "NAME": "blog",
        "USER": "{USER_NAME}",
        "PASSWORD": "{PASSWORD}",
        "HOST": "localhost",
        "PORT": "5432",
    }
}
```

이렇게 하고 나서 마이그레이션을 하면 된다.

```bash
python manage.py migrate
```

근데 마이그레이션이기 때문에 models.py 같은 파일을 보고 테이블을 만드는 것이지, 이전에 있던 데이터가 이동하는 것은 아니다.

이제 새로운 데이터베이스에 데이터를 가져 오자.

```bash
python manage.py loaddata mysite_data.json
```