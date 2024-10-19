# Task

## 1. build.gradle 의 task 섹션
build.gradle 파일의 task 섹션은 Gradle 빌드 프로세스에서 특정 작업을 정의하는 데 사용된다.

Gradle 을 사용해서 빌드를 수행할 때 보통 아래와 같이 명령어를 사용한다.
```bash
./gradlew build

./gradlew clean build

./gradlew test

./gradlew <task-name>
```

보통 위와 같이 gradle 명령어를 입력해서 수행하는 작업이 task 라고 하면 되겠다.

## 2. task 추가하기
### 2-1. 기본 작업 바꾸기
- clean : 이전 빌드 결과물을 삭제하는 기본 작업
```groovy
tasks.register('clean') {
    doLast {
        delete fileTree(dir: 'build', include: '**/*')
        println 'Cleaned build directory.'
    }
}
```

위에서 clean 이라는 작업을 정의한 것이다. Gradle 에서는 기본적으로 제공하는 clean 작업이 이미 존재한다. 따라서, 사용자 정의로 추가한 clean 작업이 기존의 기본 clean 작업과 충돌하게 된다. 이 경우, 사용자 정의 작업이 기본 작업을 덮어쓰게 된다.

### 2-2. 사용자 정의 작업
```groovy
tasks.register('deploy') {
    doLast {
        copy {
            from 'build/libs/myapp.jar'
            into '/path/to/deploy'
        }
        println 'Application deployed!'
    }
}
```

### 2-3. 사용자 정의 작업
```groovy
tasks.register('customTask') {
    // 작업 설명 설정
    description = 'This is a custom task that demonstrates multiple features.'

    // 작업을 특정 그룹에 할당
    group = 'Custom Tasks'

    // 입력 및 출력 정의
    inputs.file('input.txt')
    outputs.file('output.txt')

    // 작업이 실행되기 전에 수행할 작업
    doFirst {
        println 'Starting custom task...'
    }

    // 조건부 실행
    onlyIf { file('input.txt').exists() }

    // 작업이 실행된 후에 수행할 작업
    doLast {
        // 파일 처리 로직 예시
        println 'Processing input file...'
        // (여기에 파일 처리 코드를 추가)
        println 'Output generated at output.txt'
    }

    // 다른 작업에 의존성 설정
    dependsOn 'anotherTask'

    // 현재 작업이 종료된 후 실행될 작업 설정
    finalizedBy 'cleanup'
}

// 다른 작업 예시
tasks.register('anotherTask') {
    doLast {
        println 'Another task executed.'
    }
}

// 정리 작업 정의
tasks.register('cleanup') {
    doLast {
        println 'Cleanup task executed after customTask.'
    }
}
```

Gradle 을 사용해서 빌드할 때 Task 또한 커스터마이징해서 사용하면 좋겠다.