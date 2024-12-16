# E-Mail

## 1. 이메일을 보내기 위한 환경
Django 로 이메일을 보내기 위해서는 로컬 SMTP(Simple Mail Transfer Protocol) 서버가 있거나, 이메일 서비스 공급자와 같은 외부 SMTP 서버에 액세스해야 한다.

## 2. SMTP 란?
SMTP(간단 메일 전송 프로토콜)는 이메일을 전송하는 데에 사용되는 프로토콜이다. SMTP 는 클라이언트와 서버 간의 통신을 관리하며, 이메일을 다른 이메일 서버로 전송하는 역할을 수행한다.

[SMTP 의 주요 기능]
- 이메일 전송 : 이메일 클라이언트에서 서버로 이메일을 전송하고, 서버 간에 이메일을 전달한다.
- 인증 및 보안 : SMTP 는 기본적인 인증 메커니즘을 제공하며, SSL/TLS 암호화를 통해 이메일 전송의 보안을 강화할 수 있다.

## 3. Django 에서 설정하는 SMTP 의 구성 (settings.py)
내 책에서는 표준 Gmail 계정과 함께 Google 의 SMTP 서버를 사용한다. settings.py 파일을 열어 아래와 같이 수정해 보자.

```python
# settings.py

# 추가 시, 모든 이메일을 보내는 대신 쉘에 출력한다.
# EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'

EMAIL_HOST = 'smtp.gmail.com'  # SMTP 서버 주소
EMAIL_HOST_USER = 'your_email@gmail.com'  # 발신자 이메일
EMAIL_HOST_PASSWORD = ''  # 발신자 이메일 비밀번호 -> App Password 별도 발급해서 정리함.
EMAIL_PORT = 587  # TLS 포트
EMAIL_USE_TLS = True  # TLS 사용
```

이후 시스템 쉘 프롬프트에서 다음 명령을 실행하여 파이썬 쉘을 열자.
```bash
python manage.py shell
```

이후 shell 을 사용하여 import 한 메서드를 실행시킨다.
```python
from django.core.mail import send_mail

password = '12345'  # 비밀번호 설정
subject = '비밀번호 찾기'
message = '새로 발급 받을 비밀번호는 ' + password + ' 입니다.'
from_email = 'empty'  # 발신자 이메일 (settings.py에 설정한 이메일로 사용)
recipient_list = ['kch4731@naver.com']  # 받는 사람 이메일 리스트

send_mail(
    subject,
    message,
    from_email,
    recipient_list,
    fail_silently=False  # 이메일 전송 실패 시 예외 발생
)
```

나의 경우에는 Django 와 Python 의 버전이 상호 호환되지 않아 에러가 발생했다. python 은 3.11, Django 는 ~=4.1.0 을 사용했더니 문제를 해결할 수 있었다.