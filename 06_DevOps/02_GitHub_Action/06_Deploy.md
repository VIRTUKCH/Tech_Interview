# Deployment
배포(Deployment) 는 소프트웨어 개발 및 운영 과정에서 중요한 단계로, 개발이 완료된 애플리케이션이나 서비스를 실제 환경에 배포하는 과정을 의미한다. 배포는 여러 방식으로 이루어질 수 있으며, 다양한 전략과 도구가 사용된다.

## 1. CD 를 통한 배포 자동화
CI/CD 툴에서는 대부분 배포를 지원하며, GitHub Action 또한 배포를 지원한다.

## 2. 배포 도구
- Docker : 컨테이너화 된 애플리케이션을 배포하는 데 유용하다.
- Kubernetes : 컨테이너 오케스트레이션 플랫폼으로, 대규모 애플리케이션의 배포와 관리를 자동화한다.
- Terraform : 인프라를 코드로 관리하여, 배포 환경을 쉽게 설정하고 관리할 수 있다.
- GitHub Actions : CI/CD 파이프라인을 구축하여 자동화된 배포를 지원한다.

## 3. 어디에 배포할 것인가?
배포할 환경은 여러 가지가 있으며, 각 환경에 따라 적합한 배포 전략을 선택해야 한다. 일반적인 배포 환경은 다음과 같다.
- 클라우드 서비스 : AWS, Google Cloud, Azure 와 같은 클라우드 제공 업체를 통해 배포할 수 있다. 이들 서비스는 인프라 제공과 관리, 스케일링 등을 지원한다.
- 온프레미스 서버 : 기업 내부의 물리적 서버에 애플리케이션을 배포하는 방식이다.
- PaaS(Platform as a Service) : Heroku, Google App Engine 과 같은 플랫폼에서 제공하는 서비스로, 애플리케이션 배포를 간편하게 할 수 있다.

## 4. Docker 를 사용하여 배포하는 구체적인 방법
Docker 를 사용하면 Docker Image 라는 것을 만들 수 있는데, 이를 통해 애플리케이션의 실행을 간단하게 관리할 수 있다.

Docker Image 는 애플리케이션과 그 실행에 필요한 모든 종속성을 포함하는 템플릿이다. 이를 통해 애플리케이션을 컨테이너화하고, 환경에 구애받지 않고 일관된 실행 환경을 제공한다.

Docker 는 기본적으로 리눅스 기반의 컨테이너를 사용하기 때문에, Shell 과 밀접한 관련이 있다. Docker 컨테이너 내에서 애플리케이션을 실행할 때 Shell 을 통해 명령을 실행하거나 스크립트를 사용할 수 있다.

Shell Script 는 애플리케이션의 실행 및 관리에 필요한 명령어를 모아 놓은 스크립트 파일로, Dockerfile 내에서도 Shell 명령어를 사용할 수 있다. 예를 들어, Dockerfile 에서 RUN 명령어를 사용해 Shell 명령어를 실행할 수 있다.

### 구체적인 절차
### 4-1. Dockerfile 작성
Dockerfile 은 Docker 이미지를 생성하기 위한 스크립트이다. 이 파일에 애플리케이션을 설정하고 실행하는 데 필요한 모든 명령어를 정의한다.
```dockerfile
# OpenJDK 17 버전의 슬림 이미지를 기반으로 설정합니다.
FROM openjdk:17-jdk-slim

# 호스트 시스템의 target/myapp.jar 파일을 컨테이너의 /app/myapp.jar 위치로 복사합니다.
COPY target/myapp.jar /app/myapp.jar

# 컨테이너가 시작될 때 실행할 명령어를 설정합니다.
# 이 경우, Java 애플리케이션을 실행합니다.
ENTRYPOINT ["java", "-jar", "/app/myapp.jar"]
```

### 4-2. 컨테이너 관리
Docker 를 사용하면 컨테이너를 쉽게 생성, 시작, 중지 및 삭제할 수 있다. 이를 통해 애플리케이션의 실행을 간편하게 관리할 수 있다.

## 5. GitHub Action 을 통해 배포를 자동화하는 방법
GitHub Actions 를 사용하면 코드 변경 시 자동으로 애플리케이션을 빌드하고 배포할 수 있다. CI/CD 파이프라인을 쉽게 설정할 수 있어, 개발자가 수동으로 배포할 필요가 줄어든다.

### 5-1. GitHub Actions 워크플로우 설정
.github/workflows 디렉터리 밑에 yml 파일을 하나 생성한다.
```yml
name: Deploy to Production

on:
  push:
    branches:
      - main  # main 브랜치에 푸시될 때 트리거

jobs:
  deploy:
    runs-on: ubuntu-latest  # 사용할 운영 체제

    steps:
      - name: Checkout code
        uses: actions/checkout@v2  # 코드 체크아웃

      - name: Set up JDK
        uses: actions/setup-java@v2
        with:
          java-version: '17'  # JDK 버전 설정

      - name: Build with Gradle
        run: ./gradlew build  # Gradle로 빌드

      - name: Deploy to server
        run: ssh user@your-server "docker pull your-image:latest && docker run -d -p 8080:8080 your-image:latest"
        env:
          SSH_PRIVATE_KEY: ${{ secrets.SSH_PRIVATE_KEY }}  # SSH 키를 GitHub Secrets에서 가져오기
```
위에서는 민감한 정보를 보호하기 위해 SSH 와 같은 비밀 정보를 GitHub Secrets 에 저장했다. 이미 다룬 내용이기 때문에 넘어 가겠다.

## 6. SSH 를 사용한 로컬 배포
SSH(Secure Shell) 는 원격 서버에 안전하게 접속하고 명령을 실행할 수 있도록 해주는 프로토콜이다. SSH 를 사용하면 암호화된 연결을 통해 원격 시스템에 접근할 수 있어, 보안성이 높다.

SSH 를 통해 원격 서버에 안전하게 접속하기 위해서는 SSH 키를 생성하고, 공개 키를 원격 서버의 ~/.ssh/authorized_keys 파일에 추가해야 한다.

또한, GitHub 레파지토리의 Secrets 에 SSH 키를 저장해서 워크플로우에서 안전하게 사용할 수 있도록 해야 한단다.

이후 SSH 를 통해 원격 서버에 접속하고, 애플리케이션을 배포하는 명령어를 실행하는 스크립트를 작성하면 된다.

아래는 예시다.

```yml
name: Deploy to Server

on:
  push:
    branches:
      - dev  # dev 브랜치에 푸시될 때 트리거

jobs:
  deploy:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v2

      - name: Set up SSH
        run: |
          mkdir -p ~/.ssh
          echo "${{ secrets.SSH_PRIVATE_KEY }}" > ~/.ssh/id_rsa
          chmod 600 ~/.ssh/id_rsa

      - name: Deploy to server
        run: ssh user@your-server "cd /path/to/app && ./deploy.sh"
```

## 7. 마무리
현재 남는 컴퓨터가 있어 그 컴퓨터를 배포 컴퓨터로 사용할 예정이다. 해당 컴퓨터에 SSH 를 설정하고 GitHub Actions 와 연결할 생각이다.

그런데 아무래도 Shell, SSH 에 대한 이해가 부족해서 그 부분부터 다루고 넘어가야 할 것 같다.

03_shell 디레겉리에서 shell 에 대한 개념을 정리한다.