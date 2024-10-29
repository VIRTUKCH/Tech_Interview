# AOP (Aspect-Oriented Programming)

## 1. AOP 란?
AOP 는 관점 지향 프로그래밍(Aspect-Oriented Programming)의 약자로, 소프트웨어 개발에서 공통 관심사를 모듈화하는 방법론이다.

AOP 는 코드의 주요 비즈니스 로직과 공통적으로 적용되는 기능(로깅, 보안, 트랜잭션 관리 등)을 분리하여, 코드의 가독성과 유지보수성을 높이는 데 도움을 준다.

## 2. AOP 는 왜 사용하나?

예를 들어, 모든 서비스에 대해서 하나의 메서드가 수행될 때, 함수의 이름과 함수가 완성되는 데에 걸리는 시간을 알고 싶다고 하자.

이런 경우에 AOP 를 사용하지 않으면 모든 서비스 클래스에 대해서 로그를 출력하는 코드를 모두 작성해야 한다.

아래 예시를 보자.

```java
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class LoggingAspect {
    private static final Logger logger = LoggerFactory.getLogger(LoggingAspect.class);
    
    @Around("execution(* com.example.service.*.*(..))")
    public Object logExecutionTime(ProceedingJoinPoint joinPoint) throws Throwable {
        long startTime = System.currentTimeMillis();
        
        // 메서드 실행
        Object proceed = joinPoint.proceed();

        long endTime = System.currentTimeMillis();
        logger.info("Method " + joinPoint.getSignature() + " executed in " + (endTime - startTime) + "ms");

        return proceed;
    }
}
```

이렇게 로그를 출력하기 위한 클래스를 하나 만들어 두기만 하면,

일일히 모든 메서드에 로그를 출력하는 메서드와 같은 로직을 추가하지 않아도 모든 서비스 메서드에 대해서 로그를 출력할 수 있다.

## 3. AOP 를 조금 더 활용하는 방법

AOP 를 이용해서 로그를 출력하는 로직을 구현하고, 클래스를 만들었다고 하자.

그러나, 어떤 메서드는 INFO 레벨로 로그를 출력하고 어떤 메서드는 WARN 레벨로 로그를 출력하고 싶을 수도 있다.

또한, 어떤 메서드에 대해서는 아예 로그를 출력하고 싶지 않을 수도 있다.

그런 경우에는 아래 코드와 같이 구현해 볼 수 있다.

```java
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface LogLevel {
    String value();
}
```
```java
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.aspectj.lang.reflect.MethodSignature;

@Aspect
public class LoggingAspect {

    private static final Logger logger = LoggerFactory.getLogger(LoggingAspect.class);

    @Around("@annotation(LogLevel)")
    public Object logExecution(ProceedingJoinPoint joinPoint) throws Throwable {
        MethodSignature signature = (MethodSignature) joinPoint.getSignature();
        LogLevel logLevelAnnotation = signature.getMethod().getAnnotation(LogLevel.class);

        // LogLevel 애너테이션이 없으면 로그를 출력하지 않음
        if (logLevelAnnotation == null) {
            return joinPoint.proceed();
        }

        String level = logLevelAnnotation.value();

        if ("DEBUG".equals(level)) {
            logger.debug("Entering method: " + joinPoint.getSignature());
        } else {
            logger.info("Entering method: " + joinPoint.getSignature());
        }

        Object proceed = joinPoint.proceed();

        if ("DEBUG".equals(level)) {
            logger.debug("Exiting method: " + joinPoint.getSignature());
        } else {
            logger.info("Exiting method: " + joinPoint.getSignature());
        }

        return proceed;
    }
}
```

```java
import org.springframework.stereotype.Service;

@Service
public class ExampleService {

    @LogLevel("DEBUG")
    public void debugMethod() {
        // 메서드 로직
    }

    @LogLevel("INFO")
    public void infoMethod() {
        // 메서드 로직
    }
    
    public void doNotPrintLog() {
        // 메서드 로직
    }
}
```

위의 경우에는 서비스의 메서드를 구현하고 나서, @LogLevel 애너테이션을 사용하여 로그의 출력 여부를 결정할 수 있다.

또한, @LogLevel 애너테이션을 사용하지 않으면 로그를 출력하지 않게 하도록 할 수도 있다.

## 4. AOP 는 왜 SpringFramework 에서 강조되는가?
Spring 은 "경량화"와 "유연성"을 중시하는 프레임워크로, AOP 는 이러한 철학과 잘 맞다고 한다. Spring 은 개발자가 비즈니스 로직에 집중할 수 있도록 공통 기능을 모듈화하는 데 AOP 를 적극 활용한다.

또한, Spring Framework 은 IoC(제어의 역전)와 DI(의존성 주입)와 같은 다른 기능들과 AOP 를 자연스럽게 통합한다. 이로 인해 애플리케이션 전반에서 AOP 를 쉽게 적용할 수 있다.



## 5. 그 외 알아 두면 좋을 것들
- AOP 를 이용해서 트랜잭션 관리, 메서드 접근 제어를 통한 보안 정책, 성능 모니터링, 예외 처리(예외 발생 시 로그 추가 or 특정 로직 수행) 등이 가능하다.
- Spring AOP 는 프록시 기반으로 동작하며, AspectJ 는 컴파일 타임 또는 로드 타임에 바이트코드를 조작하는 방식으로 더 많은 기능을 지원한다. (차이를 알아 두면 좋다)
- 순서: 여러 개의 AOP 가 적용될 경우, 실행 순서가 중요하며, @Order 애너테이션을 이용해서 해결해 볼 수 있다.