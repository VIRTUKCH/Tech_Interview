# application.properties

## 1. application.properties 파일이란?
application.properties 파일은 Spring Boot 애플리케이션의 설정을 정의하는 파일이다. 키-값 쌍의 형태로 다양한 설정을 저장하며, 애플리케이션의 동작 방식을 조정한다.

기본적으로 src/main/resources 디렉터리에 위치하며, 여러 환경에 따라 다른 설정 파일을 사용할 수 있다.

## 2. application.properties 로 설정할 수 있는 것들
application.properties 파일을 통해 다음과 같은 다양한 설정을 할 수 있다.
```
- 서버 설정: 포트, 컨텍스트 경로 등
- 데이터베이스 설정: 데이터 소스, JPA 설정 등
- 로깅 설정: 로그 레벨, 로그 파일 경로 등
- 보안 설정: Spring Security의 사용자 정보
- CORS 설정: Cross-Origin Resource Sharing 정책
- 파일 업로드 설정: 최대 파일 크기 등
- 국제화 설정: 지원할 언어 및 지역 설정
- Thymeleaf 설정: 템플릿 경로 및 파일 형식 설정
- Actuator 설정: 애플리케이션 모니터링 관련 설정
```

## 3. application.properties 파일로 값을 저장하는 방법
application.properties 파일에서 값을 Java 클래스에서 가져오는 방법을 여러 가지가 있다. 일반적으로 Spring @Value 애너테이션을 사용하는 것이다.

이 방법을 통해 문자열 값을 손쉽게 주입 받을 수 있다. 또한, Spring 의 @ConfigurationProperties 를 사용하여 여러 속성을 그룹화하여 가져오는 방법도 있다.

### 3-1. @Value 애너테이션 사용하기
@Value 애너테이션을 사용하면 특정 프로퍼티 값을 간단하게 주입 받을 수 있다.
```properties
app.name=My Application
app.version=1.0.0
```

```java
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class MyAppConfig {

    @Value("${app.name}")
    private String appName;

    @Value("${app.version}")
    private String appVersion;

    public String getAppName() {
        return appName;
    }

    public String getAppVersion() {
        return appVersion;
    }
}
```

### 3-2. @ConfigurationProperties 사용하기
@ConfigurationProperties 애너테이션을 사용하면 여러 프로퍼티를 그룹화하여 가져올 수 있다. 이 방법은 특히 많은 설정이 있을 때 유용하다.

```properties
app.name=My Application
app.version=1.0.0
app.description=This is a sample application
```

```java
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@ConfigurationProperties(prefix = "app")
public class AppConfig {

    private String name;
    private String version;
    private String description;

    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }
}
```

## 4. profile
Spring Boot에서는 여러 환경(예: 개발, 테스트, 프로덕션)에 대해 각각 다른 설정을 사용할 수 있도록 프로파일을 지원한다.

서버를 개발하다 보면 배포하기 이전에 개발 및 테스트 용으로 정상적으로 통신하는 과정이 있기 마련이다.

예를 들면 JPA 를 사용해서 ddl-auto: create 속성을 이용해서 값이 저장되는 형태를 확인해 나가면서 테이블을 빠르게 만들어 나갈 수 있다. 하지만, 실제 배포된 이후 ddl-auto: none 으로 바꿔 주어야 실수로 DB 의 row 를 모두 날리는 일을 방지할 수 있다.

Profile 은 그럴 때 사용하면 좋다.

### 4-1. application.properties 에서 Profile 바꾸기
프로파일을 사용하면 특정 환경에 맞는 설정 파일을 적용할 수 있다. 기본적으로 application-{profile}.properties 형식의 파일을 생성하여 사용할 수 있다.

예를 들어, application-dev.properties 파일을 생성하여 개발 환경 설정을 정의할 수 있습니다. 활성화할 프로파일은 다음과 같이 설정합니다:
```properties
spring.profiles.active=dev
```

### 4-2. 특정 클래스나 Bean 이 특정 Profile 에서만 활성화되도록 설정하기
뿐만 아니라, Spring Boot 에서는 특정 클래스나 Bean 이 특정 프로파일에서만 활성화되도록 설정할 수 있다. 이를 위해 @Profile 애너테이션을 사용할 수 있다.

이 애너테이션을 클래스나 메서드에 적용하면, 지정한 프로파일이 활성화되었을 때 해당 Bean 이 생성된다.

### 4-3. @Profile 애너테이션 사용법

#### 4-3-1. 클래스에 적용하기
```java
import org.springframework.context.annotation.Profile;
import org.springframework.stereotype.Component;

@Profile("dev")
@Component
public class DevService {
    public void execute() {
        System.out.println("Development Service Executed");
    }
}
```
위의 예시에서는 DevService 클래스는 dev Profile 이 활성화될 때만 Bean 으로 생성된다.

#### 4-3-2. 메서드에 적용하기
Bean 메서드에 @Profile 애너테이션을 적용할 수도 있다.
```java
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;

@Configuration
public class AppConfig {

    @Bean
    @Profile("test")
    public TestService testService() {
        return new TestService();
    }
}
```
위의 예시에서는 testService() 메서드는 test Profile 이 활성화될 때만 호출되어 Bean 을 생성한다.

프로파일을 활성화하는 방법에는 application.properties 에서 값을 변경하는 방법도 있지만, 커맨드라인의 인수로 넘기는 방법도 있고, 환경변수를 통해 변경하는 방법도 있다.

```bash
java -jar myapp.jar --spring.profiles.active=dev
```

## 5. Thymeleaf
Thymeleaf는 Spring Boot에서 주로 사용되는 템플릿 엔진이다. application.properties 파일을 통해 Thymeleaf의 설정을 정의할 수 있다.

```properties
spring.thymeleaf.prefix=classpath:/templates/
spring.thymeleaf.suffix=.html
spring.thymeleaf.mode=HTML
```

이 설정은 Thymeleaf가 템플릿 파일을 찾는 경로와 파일 형식을 정의한다.

> 템플릿 엔진이란?
Template Engine 은 동적 웹 페이지를 생성하는 데 사용되는 소프트웨어 도구이다. 주로 HTML 페이지와 같은 템플릿에 데이터를 삽입하여 최종 사용자에게 보여 줄 컨텐츠를 생성하는 역할을 한다.<br>
템플릿 엔진은 서버 사이드(서버가 클라이언트의 요청에 따라 데이터를 처리하기 때문에 서버의 메모리를 사용)에서 작동하며, 보통 웹 프레임워크와 함께 사용된다.<br>
클라이언트 사이드에서도 사용할 수 있다. JavaScript 기반의 템플릿 엔진(Handlebars, Mustache 등) 은 클라이언트에서 동적으로 HTML 을 생성하는 데 사용된다.