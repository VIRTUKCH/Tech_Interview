# Dependency Cache
GitHub Action 에서의 Dependency Cache 는 CI/CD 파이프라인에서 빌드 및 테스트 과정에서 사용하는 의존성(Dependency) 을 캐시하여, 다음 빌드 시 더 빠른 속도로 진행할 수 있게 해주는 기능이다.

이 기능은 빌드 시간을 단축시키고, 불필요한 네트워크 요청을 줄여준다.

## 1. 주요 기능 및 이점

### 1-1. 속도 향상
의존성을 캐시하면, 빌드 과정에서 매번 의존성을 다운로드할 필요가 없어져 빌드 시간이 크게 단축된다.

### 1-2. 네트워크 비용 절감
의존성을 다운로드하기 위한 네트워크 요청을 줄일 수 있어, 네트워크 대역폭을 절약할 수 있다.

### 1-3. 일관성 유지
동일한 의존성 버전을 사용할 수 있도록 캐시를 통해 일관성을 유지할 수 있다. 팀원 간의 환경 차이를 줄이는 데에도 도움이 된다.

### 1-4. 간편한 설정
GitHub Actions 의 캐시 액션을 사용하여 쉽게 설정할 수 있다. 특정 경로를 지정하고, 캐시 키를 정의하는 방식으로 관리한다.

## 2. 파일 설정
다음은 GitHub Actions 에서 의존성 캐시를 설정하는 예제이다.
```yml
name: CI Workflow

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

      - name: Cache Gradle packages
        uses: actions/cache@v2
        with:
          path: ~/.gradle/caches  # 캐시할 경로
          key: ${{ runner.os }}-gradle-${{ hashFiles('**/*.gradle*', '**/gradle-wrapper.properties') }}  # 캐시 키
          restore-keys: |
            ${{ runner.os }}-gradle-

      - name: Set up JDK
        uses: actions/setup-java@v2
        with:
          java-version: '17'
          distribution: 'temurin'

      - name: Build with Gradle
        run: ./gradlew build
```

## 3. 어디에 캐싱되는가?
GitHub Actions 에서의 Dependency Cache 는 GitHub 의 캐시 저장소에 저장된다. 이 저장소는 GitHub 의 인프라 내에서 관리되며, 다음과 같은 특징을 가진다.

### 3-1. 저장 위치
의존성 캐시는 GitHub 의 클라우드 인프라에 저장된다. 이는 GitHub Actions 가 실행되는 서버에서 관리되며, 각 빌드 작업이 필요할 때마다 해당 캐시를 조회하고 사용할 수 있다.

### 3-2. 캐시 키
각 캐시는 고유한 키를 사용하여 식별된다. 일반적으로 이 키는 의존성의 버전이나 해시 값을 기반으로 생성되어, 변경이 있을 때마다 새로운 캐시가 생성된다.

예를 들어, 아래의 코드에서 캐시 키는 runner.os 와 Gradle 파일의 해시값을 결합하여 생성된다.
```yml
key: ${{ runner.os }}-gradle-${{ hashFiles('**/*.gradle*', '**/gradle-wrapper.properties') }}
```

쉽게 말해서, GitHub 의 서버 측에 내 프로젝트를 위한 Dependencly Cache 가 저장된다. 의존성 파일의 해시 값이나 환경 정보(runner.os) 를 조합하여 생성된다.

> Runner 란?</br>
GitHub Actions 워크플로우를 실행하는 서버 또는 환경을 의미한다. 러너는 기본적으로 작업(Job) 을 수행하는 데 필요한 모든 자원을 제공한다.

### 3-3. 복원 및 저장
워크 플로우가 실행될 때, 지정한 캐시 키를 기반으로 GitHub 는 해당 캐시가 존재하는지 확인한다.
캐시를 사용하는 다른 프로그램과 다를 것 없이, 캐시가 존재하면 이를 복원하여 사용할 수 있다.

### 3-4. 제한 사항
GitHub Actions 의 캐시는 저장 용량과 시간에 제한이 있을 수 있다. 기본적으로 각 저장소는 5GB 의 캐시를 저장할 수 있으며, 오래된 캐시는 자동으로 삭제될 수 있다.

캐시는 특정 조건(키 변경, 저장소 변경 등) 에 따라 유효성을 잃을 수 있다. 이 경우 새로 다운로드해야 할 수 있다.