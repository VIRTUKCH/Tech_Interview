# build.gradle

## 1. 플러그인 섹션
```groovy
// 플러그인 섹션: 빌드에 필요한 플러그인을 선언합니다.
plugins {
    // Spring Boot 플러그인: Spring Boot 애플리케이션을 쉽게 만들고 관리합니다.
    id 'org.springframework.boot' version '3.0.0' 
    // Spring 의존성 관리 플러그인: 의존성을 관리하기 위한 플러그인입니다.
    id 'io.spring.dependency-management' version '1.0.11.RELEASE' 
    // Java 플러그인: Java 프로젝트를 위한 기본 플러그인입니다.
    id 'java' 
}
```
일반적으로 컴퓨터 공학에서 "플러그인"이라는 용어는 특정 소프트웨어 또는 시스템의 기능을 확장하거나 추가하기 위해 외부 모듈이나 컴포넌트를 사용하는 것을 의미한다.

빌드 도구에서 플러그인은 특정 작업을 추가하기 위해 사용하는 모듈이란다. 플러그인을 통해 프로젝트의 빌드 프로세스를 확장하고, 다양한 작업을 자동화할 수 있다.

플러그인은 빌드 프로세스를 관리하는 도구이고, 의존성은 애플리케이션의 기능을 구현하는 데에 필요한 외부 코드라는 것이 둘의 차이점이다.

## 2. 프로젝트 속성
```groovy
// 프로젝트 속성: 그룹 ID, 버전, 사용할 Java 버전 등을 설정합니다.
group = 'com.example' // 그룹 ID
version = '1.0.0' // 프로젝트 버전
sourceCompatibility = '17' // 사용할 Java 버전
```
- group : 프로젝트의 그룹 ID 이다. 일반적으로 회사나 조직의 도메인 이름을 반전하여 사용한다. 예를 들어, com.example 는 example.com 도메인에 해당하는 조직의 프로젝트를 나타낸다. Maven 중앙 저장소와 같은 레파지토리에서 아티팩트를 고유하게 식별하는 데에 사용된다.
- version : 프로젝트의 버전을 말한다. 버전 관리는 아티팩트의 변경 사항을 추적하고, 사용자에게 어떤 버전이 최신인지 알리는 데 도움을 준다.
- sourceCompatibility : 컴파일러에게 어떤 Java 버전의 문법을 지원할지 알려준다.

## 3. 저장소 섹션
```groovy
// 저장소 섹션: 의존성을 다운로드할 저장소를 정의합니다.
repositories {
    mavenCentral() // Maven 중앙 저장소를 사용합니다.
}
```
- repositories 블록 : 프로젝트에서 사용할 의존성을 다운로드할 저장소를 설정한다. Gradle 은 이들 저장소에서 필요한 라이브러리와 플러그인을 검색한다.

- mavenCentral() : Maven 중앙 저장소를 사용하겠따는 설정이다. Maven 중앙 저장소는 Java 라이브러리의 가장 큰 저장소 중 하나로, 전 세계의 많은 오픈 소스 프로젝트가 이곳에 배포된다. jcenter, jitpack.io(GitHub 에서 관리) 등이 있다.

## 4. 의존성 섹션
```groovy
// 의존성 섹션: 프로젝트에서 사용할 라이브러리를 정의합니다.
dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web' // Spring Web 의존성
    implementation 'org.springframework.boot:spring-boot-starter-data-jpa' // Spring Data JPA 의존성
    runtimeOnly 'com.h2database:h2' // H2 데이터베이스 런타임 의존성
    testImplementation 'org.springframework.boot:spring-boot-starter-test' // 테스트 의존성
}
```
의존성 섹션은 Gradle 빌드 스크립트에서 프로젝트에서 사용할 라이브러리와 모듈을 정의하는 부분이다. 이 섹션을 통해 필요한 외부 라이브러리를 명시하고, 이를 프로젝트에 통합하여 사용할 수 있다.

의존성에 대해서는 다음 글에서 자세히 정리한다.

## 5. 태스크 섹션
```groovy
// 태스크 섹션: 사용자 정의 태스크를 정의합니다.
tasks.named('test') {
    useJUnitPlatform() // JUnit 플랫폼을 사용하여 테스트를 실행합니다.
}
```
태스크 섹션은 Gradle 빌드 스크립트에서 특정 작업을 구성하는 부분이다. Gradle 에서 태스크는 빌드 프로세스의 기본 단위로, 코드 컴파일, 테스트 실행, 패키징 등 다양한 작업을 수행할 수 있다.

- 태스크 : Gradle 에서 태스크는 특정 작업을 수행하는 단위이다. 각 태스크는 특정한 작업을 의미하며, Gradle 은 이러한 태스크를 순차적으로 실행하여 전체 빌드 프로세스를 관리한다.
- 빌드 프로세스 : 태스크는 빌드 프로세스를 구성하는 핵심 요소로, 어떤 작업을 언제 수행할지를 정의한다.

## 6. 사용자 정의 태스크 예시
```groovy
// 사용자 정의 태스크 예시: "hello"라는 이름의 태스크를 정의합니다.
task hello {
    doLast {
        // 이 태스크가 실행될 때 출력할 메시지입니다.
        println 'Hello, Gradle!' 
    }
}
```

## 7. 전체 파일
```groovy
// 플러그인 섹션: 빌드에 필요한 플러그인을 선언합니다.
plugins {
    // Spring Boot 플러그인: Spring Boot 애플리케이션을 쉽게 만들고 관리합니다.
    id 'org.springframework.boot' version '3.0.0' 
    // Spring 의존성 관리 플러그인: 의존성을 관리하기 위한 플러그인입니다.
    id 'io.spring.dependency-management' version '1.0.11.RELEASE' 
    // Java 플러그인: Java 프로젝트를 위한 기본 플러그인입니다.
    id 'java' 
}

// 프로젝트 속성: 그룹 ID, 버전, 사용할 Java 버전 등을 설정합니다.
group = 'com.example' // 그룹 ID
version = '1.0.0' // 프로젝트 버전
sourceCompatibility = '17' // 사용할 Java 버전

// 저장소 섹션: 의존성을 다운로드할 저장소를 정의합니다.
repositories {
    mavenCentral() // Maven 중앙 저장소를 사용합니다.
}

// 의존성 섹션: 프로젝트에서 사용할 라이브러리를 정의합니다.
dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web' // Spring Web 의존성
    implementation 'org.springframework.boot:spring-boot-starter-data-jpa' // Spring Data JPA 의존성
    runtimeOnly 'com.h2database:h2' // H2 데이터베이스 런타임 의존성
    testImplementation 'org.springframework.boot:spring-boot-starter-test' // 테스트 의존성
}

// 태스크 섹션: 사용자 정의 태스크를 정의합니다.
tasks.named('test') {
    useJUnitPlatform() // JUnit 플랫폼을 사용하여 테스트를 실행합니다.
}

// 사용자 정의 태스크 예시: "hello"라는 이름의 태스크를 정의합니다.
task hello {
    doLast {
        // 이 태스크가 실행될 때 출력할 메시지입니다.
        println 'Hello, Gradle!' 
    }
}
```