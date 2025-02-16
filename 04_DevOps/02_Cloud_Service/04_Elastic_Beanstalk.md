# Elastic Beanstalk

## 1. Elastic Beanstalk 란?
Elastic Beanstalk 는 AWS 에서 제공하는 관리형 애플리케이션 배포 서비스이다.

개발자가 애플리케이션 코드를 업로드하면 Elastic Beanstalk 가 자동으로 필요한 인프라를 설정하고, 애플리케이션을 배포하며, 모니터링과 확장을 관리해준다.

이를 통해 개발자는 인프라 관리에서 벗어나 애플리케이션 개발에 집중할 수 있다.

## 2. Elastic Beanstalk 의 기능
다음과 같은 기능을 제공한다.

- 자동화된 배포 : 애플리케이션 코드를 업로드하면 필요한 리소스를 자동으로 설정하고 배포한다.
- 자동 확장 : 트래픽 변화에 따라 인스턴스를 자동으로 추가 또는 제거하여 성능을 최적화한다.
- 모니터링 : AWS Management Console 을 통해 애플리케이션의 상태를 모니터링하고, 로그를 확인할 수 있다.
- 다양한 플랫폼 지원 : Java, .NET, Node.js, Python, Ruby, Go 등 다양한 언어와 프레임워크를 지원한다.
- 환경 구성 : 다양한 설정을 통해 개발, 테스트, 프로덕션 환경을 쉽게 구성할 수 있다.

## 3. Elastic Beanstalk 와 함께 사용할 수 있는 것들
Elastic Beanstalk 는 여러 AWS 서비스와 함께 통합하여 사용할 수 있다.

- RDS : 데이터베이스 서비스로 RDS 인스턴스를 연결하여 사용할 수 있다.
- S3 : 정적 파일을 저장하고 배포하는 데 S3를 사용할 수 있다.
- CloudFront : 콘텐츠 전송 네트워크(CDN) 로 CloudFront 와 함께 사용할 수 있다.
- SNS : 알림 및 메시징 서비스인 SNS 를 통해 애플리케이션 알림을 설정할 수 있다.
- CloudWatch : 애플리케이션의 성능 모니터링 및 로깅에 사용할 수 있다.

## 4. Elastic Beanstalk 는 관리 서버인가?
관리형 서비스로, 사용자가 직접 서버를 관리하는 것이 아니라 AWS 가 인프라를 관리할 수 있도록 도와주는 서비스이다. 사용자는 애플리케이션 코드와 설정을 제공하면, Elastic Beanstalk 가 자동으로 필요한 서버와 리소스를 설정하고 운영한다.

## 5. Elastic Beanstalk 환경변수 설정
Elastic Beanstalk에서 환경 변수를 설정하는 방법은 다음과 같습니다:

[application.properties, application.yml, .env 와 같은 파일을 설정할 때 사용]
- AWS Management Console에 로그인합니다.
- Elastic Beanstalk 대시보드로 이동합니다.
- 설정하고자 하는 애플리케이션을 선택합니다.
- 환경을 선택하고, 환경을 클릭하여 세부 정보 페이지로 이동합니다.
- 구성(Configuration) 버튼을 클릭합니다.
- 소프트웨어 섹션을 찾아 편집(Edit) 버튼을 클릭합니다.
- 환경 속성(Environment Properties) 섹션에서 필요한 환경 변수를 추가합니다. 변수 이름과 값을 입력합니다.
- 저장(Save) 버튼을 클릭하여 변경 사항을 적용합니다.
- 이렇게 설정한 환경 변수는 애플리케이션 코드에서 접근할 수 있습니다.