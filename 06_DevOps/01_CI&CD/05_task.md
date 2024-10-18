# Task

## 1. 

[코드 분석]
```
1. tasks.named('test')
- 설명 : tasks.named('test')는 Gradle 의 기본 태스크 중 하나인 test 태스크를 참조한다. test 태스크는 프로젝트의 테스트 코드를 실행하는 데 사용된다.
- 용도 : 이 구문을 통해 Gradle 의 기존 태스크에 접근하고, 해당 태스크의 동작을 수정할 수 있다.

2. { useJUnitPlatform() }
- 설명 : 이 블록 내에서 useJUnitPlatform() 메서드를 호출하여 JUnit 플랫폼을 사용하여 테스트를 실행하도록 설정한다. JUnit 플랫폼은 JUnit 5 의 테스트 실행 엔진으로, 다양한 테스트 프레임워크와 호환된다.
- 용도 : 이 설정을 통해 Gradle 은 JUnit 5 를 사용하여 테스트를 실행하며, JUnit 5 의 다양한 기능 (동적 테스트, 태그 기능 등)을 활용할 수 있다.
```

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