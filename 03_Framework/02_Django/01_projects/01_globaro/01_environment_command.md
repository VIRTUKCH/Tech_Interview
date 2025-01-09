# 환경 관련 명령어 모음집
특정 의존성이나 라이브러리에 대해 다루는 것이 아니라, 일반적인 방법론에 대해 이야기를 나눔.

## 1. 격리된 환경 만들기
```bash
python3.11 -m venv {원하는_가상환경의_디렉터리_이름} # 10초 이상 걸린다고 생각하기
```

### [참고] 가상 환경 삭제 후 새로 생성
```bash
# 가상 환경 삭제 후 새로 생성
deactivate  # 현재 가상 환경 비활성화
rm -rf my_env  # 가상 환경 폴더 삭제 (my_env는 가상 환경 이름)
python3.11 -m venv my_env  # 새로운 가상 환경 생성
source my_env/bin/activate  # 새로운 가상 환경 활성화
```

## 2. 가상 환경 실행하기
```bash
source {가상환경_디렉터리_이름}/bin/activate
```

## 3. pip 를 이용하여 Django install
```bash
pip install Django==5.1.4 # 2분 이상 걸린다고 생각하기
```

## 4. 프로젝트 만들기 (프로젝트 != 애플리케이션)
```bash
django-admin startproject {하고_싶은_프로젝트_이름}
```

## 5. 데이터베이스 마이그레이션
```bash
# 마이그레이션 생성
# python manage.py makemigrations {application_name}

## 최초의 경우 모든 데이터베이스 마이그레이션하기 (JPA, ddl-auto : create 느낌)
cd {project_directory}
python manage.py migrate

# 특정 모델의 변경 사항을 감지하여 마이그레이션 파일을 생성.
python manage.py makemigrations {특정 Entity 이름}
```
models.py 의 내용을 보고, 테이블과 일치시키는 명령어이다. 필드, 인덱스, 제약 조건 등을 생성하고 관리할 수 있다.

## 6. 서버 실행
```bash
cd {project_directory}
python manage.py runserver
```

## 7. 애플리케이션 생성하기 (project 의 root directory 에서 진행)
```bash
python manage.py startapp {application_name}
```

## 8. 애플리케이션 활성화하기
장고가 애플리케이션을 추적하고 해당 모델에 대해 데이터베이스 테이블을 생성할 수 있또록 하려면 프로젝트에서 blog 애플리케이션을 활성화해야 한다. settings.py 파일에서 INSTALLED_APPS 리스트를 편집하자.

## 9. Super User 생성하기
관리 사이트를 관리할 사용자를 생성할 수 있다.
```bash
python manage.py createsuperuser # 만들어서 나쁠 거 없다
```
이후 적절히 Username, email, password 를 설정한다.

## 10. env 파일 활용하기
Django 에서 .env 파일에 저장된 값을 가져오기 위해서는 python-decouple 패키지를 사용하는 것이 일반적이다.
```bash
pip install python-decouple
```
google SMTP 서버를 사용하고, app_password 를 저장하기 위해서 .env 파일을 사용했다.

## 11. RESTful API 위한 라이브러리 설치
```bash
pip install django djangorestframework==3.13.1
```

## 12. 인증 및 인가 위한 라이브러리 설치
```bash
pip install djangorestframework-simplejwt
```

## 13. PostgreSQL 연결 (binary 를 깔면 <Python.h> 헤더를 가지고 있지 않아도 됨. 가상 환경에 좋음)
```bash
pip install psycopg2-binary
```

## 14. 데이터베이스 설정을 마쳤다면
```bash
python manage.py migrate
```

## 15. 쿼리나 설정이 좀 안 먹힌다면
```bash
걍 윈도우 키 (시작메뉴) 눌러서 psql 친 다음에 거기 들어가서 치셈
```