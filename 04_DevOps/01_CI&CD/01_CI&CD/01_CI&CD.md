# CI/CD

![CI/CD 파이프라인](../../99_img/CI_CD_PipeLine.png)

## 1. CI/CD 란?
CI/CD 는 지속적 통합(Continous Integration)과 지속적 배포(Continous Development)의 약자로, 소프트웨어 개발 프로세스를 자동화하고 효율적으로 관리하기 위한 방법론이다.
- CI 는 개발자들이 코드 변경 사항을 자주 통합하고, 자동화된 테스트를 통해 품질을 보장하는 것을 목표로 하며,
- CD 는 이러한 통합된 코드를 자동으로 프로덕션 환경에 배포하는 과정을 의미한다.

## 2. CI/CD 를 해두면 좋은 점
구체적인 상황을 가정해 보자.
- Thymeleaf 를 사용하는 웹 프론트 서버
- 백엔드 서버를 배포해야 하는 상황을
- AWS(Cloud Service) 를 사용해서 특정 컴퓨터에 의존하지 않게 만드는 중.

보통 아래와 같은 절차를 밟는다.
```
1. Build (Gradle 을 이용해서 Compile -> Test -> Artifact 생성)
2. Artifact(.JAR) 파일 Cloud 환경으로 옮기기
3. Cloud 실행하기
```

CI/CD 를 통해서 파이프라인을 미리 만들어 두면,
위와 같은 과정을 Git 의 특정 브랜치에 push 하는 것만으로도 대체할 수 있다.

## 3. 파이프 라인이란 무엇인가?
파이프라인이란 소프트웨어 개발 주기의 모든 단계를 자동화하여 연속적으로 실행하는 흐름을 말한다.
일반적으로 CI/CD 에서 파이프라인이라고 하면, 개발 이후 배포까지의 흐름을 이야기한다.

> 다음은 CI/CD 과정에서 파이프라인의 과정을 순차적으로 나타낸 것이다.
```
- 소스 코드 관리 : 코드가 저장소에 푸시 될 때마다 파이프라인이 트리거된다.
- 빌드 (Build) : 소스 코드를 컴파일하고, 필요한 의존성을 설치하여 실행 가능한 애플리케이션을 생성한다.
- 테스트 (Test) : 자동화된 테스트를 실행하여 코드의 품질과 기능을 검증한다.
- 배포 (Deploy) : 테스트가 성공적으로 완료된 후, 애플리케이션을 프로덕트 환경에 배포한다.
- 모니터링 (Monitoring) : 배포 후 애플리케이션의 성능 및 오류를 모니터링하여 문제가 발생할 경우 신속하게 대응한다.
```

> 프로덕트 환경이란?
```
프로덕트 환경(Production Environment) 은 소프트웨어나 애플리케이션이 실제 사용자에게 제공되는 운영 환경을 의미한다. "프로덕트 환경에 올린다" 라고 하면, 실제로 사용자가 접근하기 쉽게 사용할 수 있는 웹이나 PlayStore 에 올리는 상황을 생각하면 되겠다.
```

## 4. GitHub Action 과 같은 CI/CD 툴은 뭘 해주는가
GitHub Action 은 GitHub 에서 제공하는 CI/CD 플랫폼으로, 소프트웨어 개발 워크플로우를 자동화할 수 있는 기능을 제공한다.

예를 들어, 특정 브랜치에 코드 푸시 혹은 풀 리퀘스트가 요청되는 순간에 -> 이전에 정의해 주었던 자동으로 실행되는 작업을 실행시킬 수 있다.

> 주요 기능
```
- 워크플로우 자동화 : 특정 이벤트 (코드 푸시, 풀 리퀘스트 등) 에 따라 자동으로 실행되는 작업을 정의할 수 있다.
- 커스터마이징 가능한 작업 : 다양한 작업 (빌드, 테스트, 배포 등) 을 정의하고, 필요한 경우 다른 GitHub Action 이나 사용자 정의 스크립트를 사용할 수 있따.
- YALM 파일 기반 설정 : 워크플로우는 YAML 파일로 정의되며, 이 파일을 통해 각 단계와 조건을 세밀하게 조정할 수 있다.
- 다양한 플랫폼 지원 : Linux, macOS, Windows 등 다양한 운영체제에서 작업을 실행할 수 있다.
- 패키지 및 도구 통합 : Docker 컨테이너, Node.js, Java, Python 등 다양한 언어와 도구를 지원하며, 필요에 따라 외부 서비스와도 통합할 수 있다.
- 시크릿 관리 : API 키나 비밀번호와 같은 민감한 정보를 안전하게 관리할 수 있는 기능이 제공된다.
```

## 5. 그렇다면 내가 GitAction 에 주어야 할 정보는 뭐가 있을까?
- 워크플로우 정의 : YAML 파일로 CI/CD 프로세스를 정의해야 한다.
- 트리거 설정 : 어떤 이벤트에서 워크플로우가 실행될지를 설정한다.
- 작업 정의 : 빌드, 테스트, 배포 등의 단계에서 수행할 작업을 정의한다.
- 환경 변수 및 시크릿 : 필요한 API 키나 비밀번호 등을 안전하게 관리하기 위해 환경 변수나 시크릿으로 정의한다.

## 6. Spring Boot, AWS, Docker, SSH 등을 사용하는 개발자가 작성한 yaml 파일의 예시 3가지

1. Spring Boot 애플리케이션 빌드 및 테스트 정의하는 YAML 파일
```CI.yml
name: CI  # 워크플로우의 이름

on:
  push:  # 특정 이벤트로 워크플로우를 트리거
    branches:
      - main  # main 브랜치에 푸시될 때 실행

jobs:
  build:  # 빌드 작업 정의
    runs-on: ubuntu-latest  # 작업이 실행될 환경 설정

    steps:  # 작업의 단계 목록
      - name: Checkout code  # 코드 체크아웃 단계
        uses: actions/checkout@v2  # GitHub Actions의 체크아웃 액션 사용

      - name: Set up JDK  # JDK 설정 단계
        uses: actions/setup-java@v2  # Java 환경을 설정하는 액션 사용
        with:
          java-version: '11'  # 사용할 JDK 버전

      - name: Build with Gradle  # Gradle 빌드 단계
        run: ./gradlew build  # Gradle을 사용하여 프로젝트 빌드

      - name: Run tests  # 테스트 실행 단계
        run: ./gradlew test  # Gradle을 사용하여 테스트 실행
```

### 1. runs-on: ubuntu-latest 는 어떤 환경을 말하는 걸까?
여기서 ubuntu-latest 는 GitHub Action 에서 제공하는 최신 버전의 Ubuntu 운영 체제를 의미한다.
즉, 이 설정은 빌드 및 테스트 작업이 Ubuntu 환경에서 실행된다는 것을 나타낸다.

- GitHub Actions 는 작업을 실행하기 위해 Virtual Machine 을 생성한다.
- 해당 VM 은 Ubuntu 최신 버전을 기반으로 한다.
- 다양한 개발 도구와 라이브라리가 사전 설치되어 있다.
- 각 작업은 독립된 VM 에서 실행되기 때문에, 다른 작업이나 레포지토리에 영향을 주지 않는다.

### 2. actions/checkout@v2, actions/setup-java@v2 와 같은 디렉터리는 어디에 있는 디렉터리인가?
디렉터리가 아니고, 사용자가 만들지 않아도 되는, GitHub 의 서버에서 제공되는 "액션"이라는 것이다.
[actions/checkout@v2](https://github.com/actions/checkout)와 [actions/setup-java@v2](https://github.com/actions/setup-java)는 GitHub 에서 제공하는 공식 액션을 참조한다.

- 이 액션들은 GitHub 의 Marketplace 에서 호스팅된다.
- 사용자 정의 액션과는 다르게 별도의 디렉터리 구조가 필요하지 않다.
- GitHub 서버에서 API 호출 형식으로 제공되므로, 단순히 액션의 이름과 버전을 지정하기만 하면 된다.

### 3. 액션이 뭘까?
액션(Action)은 GitHub Actions에서 특정 작업을 수행하는 모듈이다. 재사용 가능한 코드 블록으로, 특정 기능을 수행하도록 설계되었다. 액션은 CI/CD 워크플로우의 일부로 사용되어, 다양한 자동화 작업을 수행할 수 있다.

예를 들어, [actions/setup-java@v2](https://github.com/actions/setup-java) 는 GitHub 가 Java 코드를 Run 할 수 있도록 환경을 조성하는 등의 역할을 한다.

액션의 역할

```
코드 체크아웃: actions/checkout을 사용하여 GitHub 리포지토리의 코드를 가져온다.
빌드: 소스 코드를 빌드하여 실행 가능한 패키지를 생성한다.
테스트: 자동화된 테스트를 실행하여 코드의 품질을 검증한다.
배포: 애플리케이션을 특정 환경에 배포한다.
```

액션은 GitHub의 Marketplace에서 찾을 수 있으며, 사용자 정의 액션을 만들어 사용할 수도 있다.

액션의 종류
```
Docker 기반 액션: Docker 컨테이너에서 실행되며, 복잡한 환경을 쉽게 설정할 수 있다.
JavaScript 액션: Node.js로 작성된 액션으로, 빠른 실행 속도를 가지고 있다.
Composite 액션: 여러 작업을 조합하여 하나의 액션으로 사용할 수 있다.
```

### 4. 작업하는 레파지토리가 여러 개라면 각 레파지토리마다 CI/CD 파이프라인 로직을 별도로 추가해 주어야 하는가?
그렇다. 각 레파지토리는 독립적인 프로젝트이기 때문에, 각 프로젝트의 요구 사항에 맞는 CI/CD 설정을 정의해야 한다.

다만, 여러 레파지토리에서 공통된 로직이나 설정이 있다면, 이를 템플릿으로 만들어 재사용하거나, 스크립트를 외부 저장소에 두고 필요한 레파지토리에서 호출할 수 있다.

2. Docker를 사용한 애플리케이션 배포
```Docker.yml
name: Docker Build and Push

on:
  push:
    branches:
      - main

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v2

      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v1  # Buildx를 설정하는 액션 사용

      - name: Build Docker image
        run: docker build -t myapp:latest .  # Docker 이미지를 빌드

      - name: Log in to Docker Hub
        run: echo "${{ secrets.DOCKER_PASSWORD }}" | docker login -u "${{ secrets.DOCKER_USERNAME }}" --password-stdin  # Docker Hub에 로그인

      - name: Push Docker image
        run: docker push myapp:latest  # Docker 이미지를 Docker Hub에 푸시
```
아직은 Docker를 잘 몰라서, Docker 를 다루는 쪽에서 다시 한 번 다루겠다.

3. AWS EC2에 SSH를 통해 배포
```Deploy_to_AWS.yml
name: Deploy to AWS  # 워크플로우의 이름

on:
  push:  # 특정 이벤트로 워크플로우를 트리거
    branches:
      - main  # main 브랜치에 푸시될 때 실행

jobs:
  deploy:  # 배포 작업 정의
    runs-on: ubuntu-latest  # 작업이 실행될 환경 설정

    steps:  # 작업의 단계 목록
      - name: Checkout code  # 코드 체크아웃 단계
        uses: actions/checkout@v2  # GitHub Actions의 체크아웃 액션 사용

      - name: Deploy to EC2  # EC2 배포 단계
        env:  # 환경 변수 설정
          HOST: ${{ secrets.EC2_HOST }}  # EC2 호스트 주소 (GitHub Secrets에서 가져옴)
          USER: ${{ secrets.EC2_USER }}  # EC2 사용자 이름 (GitHub Secrets에서 가져옴)
          KEY: ${{ secrets.EC2_SSH_KEY }}  # EC2 SSH 키 (GitHub Secrets에서 가져옴)
        run: |
          echo "$KEY" > ec2_key.pem  # SSH 키를 파일로 저장
          chmod 600 ec2_key.pem  # 파일 권한 변경
          ssh -i ec2_key.pem $USER@$HOST 'bash -s' < ./deploy_script.sh  # EC2에 SSH로 접속하여 배포 스크립트 실행
```
아직은 AWS 를 잘 몰라서, AWS 를 다루는 쪽에서 다시 한 번 알아 보겠다.

## 7. CI/CD 와 관련하여 알아 두면 좋은 점들
```
- 버전 관리: 코드 변경 사항을 잘 관리하는 것이 중요하다.
- 자동화의 중요성: 가능한 많은 과정을 자동화하여 효율성을 높이는 것이 좋다.
- 모니터링 및 알림: CI/CD 파이프라인의 상태를 모니터링하고, 실패 시 알림을 설정하는 것이 필요하다.
- 팀 문화: CI/CD를 성공적으로 도입하기 위해서는 팀의 문화와 프로세스도 함께 고려해야 한다.
```