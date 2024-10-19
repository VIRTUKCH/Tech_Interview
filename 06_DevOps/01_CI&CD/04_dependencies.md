# 의존성 (dependency)

## 1. 의존성이란 무엇인가?
의존성은 소프트웨어 개발에서 특정 코드나 라이브러리가 정상적으로 작동하기 위해 필요한 외부 라이브러리나 모듈을 의미한다.

예를 들어, Java 애플리케이션이 특정 기능을 구현하기 위해 Spring Framework 또는 Apache Commons 와 같은 라이브러리를 사용할 때, 이 라이브러리들이 의존성으로 간주된다.

## 2. Gradle 은 이러한 의존성을 어떻게 관리하는가?
빌드 도구가 의존성을 추가하면, 해당 라이브러리는 네트워크를 통해 프로젝트에 다운로드되고, 이를 프로젝트에 포함한다고 한다.

아래는 그 과정이다.

### 2-1. 의존성 선언
개발자는 build.gradle 파일에서 필요한 라이브러리를 의존성으로 선언한다. 예를 들어, Gradle 에서는 다음과 같이 작성할 수 있다.
```groovy
dependencies {
    implementation 'org.springframework.boot:spring-boot-starter-web'
}
```

### 2-2. 네트워크 요청
빌드 도구는 선언된 의존성을 해결하기 위해 지정된 저장소 (Maven 중앙 저장소 등)에 네트워크 요청을 보낸다. 이 요청은 필요한 라이브러리의 메타데이터와 버전 정보를 포함한다.

### 2-3. 라이브러리 다운로드
- 저장소에서 요청한 라이브러리를 찾으면, 빌드 도구는 해당 라이브러리 파일(JAR 파일 등)을 다운로드한다. 이 파일은 로컬 캐시에 저장된다.
- Gradle 은 기본적으로 ~/.gradle/caches 디렉터리에 캐시를 저장하여, 동일한 라이브러리를 다시 다운로드할 필요가 없도록 한다.

### 2-4. 프로젝트에 포함
- 다운로드 된 라이브러리는 프로젝트의 클래스 경로에 추가되어 컴파일 및 실행 시 사용될 수 있다. Gradle 은 의존성을 컴파일 및 런타임 클래스 경로에 자동으로 추가한다.
- 이 과정에서 Gradle 은 의존성 간의 충돌이나 전이적 의존성을 관리하여, 필요한 모든 라이브러리가 올바르게 설정되도록 한다.

> 전이적 의존성(Transitive Dependency)이란?
전이적 의존성은 특정 라이브러리가 다른 라이브러리에 의존하고 있는 경우, 그 의존성을 자동으로 포함하는 것을 의미한다.

- A 라이브러리: 프로젝트에서 직접 사용하는 라이브러리.
- B 라이브러리: A 라이브러리가 의존하는 라이브러리.
- C 라이브러리: B 라이브러리가 의존하는 라이브러리.

이런 상황이라고 하면 A 를 프로젝트에 추가하면 Gradle 또는 Maven 은 B 와 C 를 자동으로 다운로드하고, 프로젝트의 의존성 그래프에 포함시킨다.

빌드 도구는 이러한 전이적 의존성도 관리하는데, 여러 라이브러리가 동일한 전이적 의존성을 포함하고 있을 때, 버전 충돌이 발생하는 것을 특정 규칙에 따라 어떤 버전을 사용할지 해결한다.

Gradle 에서는 명령어를 통해 전체 의존성 그래프를 확인할 수 있다. 아래는 사진 예시이다. 기본적으로 permission 이 허용되지 않기 때문에 chmod 를 통해 바꿔 주어야 한다.
![의존성 관리 커맨드](../../99_img/gradlew_dependencies.png)

## 3. 의존성의 종류
Gradle 에서는 여러 종류의 의존성을 제공하며, 각 의존성의 사용 목적에 따라 다르다.

### 3-1. implementation
- 설명 : 이 의존성은 컴파일 타임과 런타임에 모두 필요하지만, 다른 모듈에서는 이 의존성을 참조할 수 없다.
- 용도 : 라이브러리가 다른 모듈에 영향을 미치지 않도록 할 때 사용한다.
- 예시 : 
```groovy
implementation 'org.springframework.boot:spring-boot-starter-web'
```

implementation 을 사용하면 해당 모듈이 사용하는 특정 라이브러리의 API 나 구현 세부 사항이 다른 모듈에서 접근할 수 없다.
다시 말해, 다른 모듈은 이 라이브러리에 직접 의존하지 않기 때문에, 라이브러리가 변경되더라도 다른 모듈에 영향을 주지 않는다는 것이다.

### 3-2. api
- 설명 : 이 의존성은 컴파일 타임과 런타임에 모두 필요하며, 다른 모듈에서도 이 의존성을 사용할 수 있다.
- 용도 : 라이브러리를 다른 모듈에서도 사용할 수 있도록 할 때 사용한다.
- 예시 : 
```groovy
dependencies {
    api 'org.apache.commons:commons-lang3:3.12.0'
}
```

지금까지 프로젝트 하면서 api 타입의 의존성을 써 본 적은 없다. 'org.apache.commons:commons-lang3:3.12.0' 의존성은 유틸리티 메서드를 import 할 수 있는 의존성이라고 한다. 알아만 두자.

### 3-3. runtimeOnly
- 설명 : 런타임에만 필요하며, 컴파일 타임에는 필요하지 않다.
- 용도 : 데이터베이스 드라이버와 같이 런타임에만 필요한 라이브러리에 사용한다.
- 예시 :
```groovy
dependencies {
    runtimeOnly 'mysql:mysql-connector-java:8.0.25'
}
```

데이터베이스 드라이버가 애플리케이션의 코드에서 직접 사용되면, implementation 으로 선언할 수 있으며, 이 경우 컴파일 타임에도 필요하게 된다.

```java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DatabaseExample {
    private static final String URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "myuser";
    private static final String PASSWORD = "mypassword";

    public static void main(String[] args) {
        try {
            // MySQL JDBC 드라이버 로드
            Class.forName("com.mysql.cj.jdbc.Driver"); // 이러면 컴파일 시점에 필요함.

            // 데이터베이스 연결
            try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD)) {
                System.out.println("데이터베이스에 연결되었습니다.");

                // 쿼리 실행
                String query = "SELECT * FROM my_table";
                try (PreparedStatement preparedStatement = connection.prepareStatement(query);
                     ResultSet resultSet = preparedStatement.executeQuery()) {

                    while (resultSet.next()) {
                        // 결과 처리
                        System.out.println("데이터: " + resultSet.getString("column_name"));
                    }
                }
            }
        } catch (ClassNotFoundException e) {
            System.err.println("MySQL 드라이버를 찾을 수 없습니다.");
        } catch (SQLException e) {
            System.err.println("SQL 예외 발생: " + e.getMessage());
        }
    }
}
```

### 3-4. compileOnly
- 설명 : 이 의존성은 컴파일 시에는 필요하지만, 런타임에는 필요하지 않은 라이브러리이다. 주로 애플리케이션의 API 를 작성할 때 사용한다.
- 용도 : 라이브러리의 API 를 컴파일할 때는 필요하지만, 실제로 애플리케이션이 실행될 때는 해당 라이브러리를 포함하지 않도록 할 때 사용한다.
- 예시 :
```groovy
dependencies {
    compileOnly 'org.projectlombok:lombok:1.18.24'
    annotationProcessor 'org.projectlombok:lombok:1.18.24'  // 어노테이션 프로세서를 사용하기 위해 추가
}
```

애플리케이션이 실제로 실행될 때는 Lombok 이 생성된 코드가 포함된다. 예를 들어 @Getter 애너테이션을 사용하면 해당 멤버 변수에 대해서 모두 Getter 를 만든다.
그러므로 런타임에 Lombok 라이브러리가 필요하지 않다. 따라서, lombok 은 compileOnly 로 설정하는 것이 일반적이다.

### 3-5. testImplementation
- 설명 : 이 의존성은 테스트 코드에서 사용되는 라이브러리로, 테스트 컴파일 시와 런타임 시 모두 필요하다.
- 용도 : 주로 JUnit, Mockito 와 같은 테스트 프레임워크 및 라이브러리를 추가할 때 사용된다.
- 예시 :
```groovy
dependencies {
    testImplementation 'org.junit.jupiter:junit-jupiter:5.8.2' // JUnit 5
    testImplementation 'org.mockito:mockito-core:4.0.0' // Mockito
}
```

### 3-6. testRuntimeOnly
- 설명 : 이 의존성을 테스트 실행 시에만 필요하며, 테스트 컴파일 시에는 필요하지 않다.
- 용도 : 특정 테스트를 실행하기 위해 필요한 라이브러리나 도구를 추가할 때 사용한다. 예를 들어, 특정 테스트를 위해 Mock 서버 또는 특정 프로토콜의 클라이언트를 필요로 할 수 있다.
- 예시 :
```groovy
dependencies {
    testRuntimeOnly 'org.testcontainers:junit-jupiter:1.16.0' // TestContainers
}
```