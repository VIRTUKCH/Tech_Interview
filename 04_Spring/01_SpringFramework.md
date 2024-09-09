# Spring Framework

## 1. Spring 이란?
Spring 은 자바 플랫폼을 위한 오픈 소스 애플리케이션 프레임워크로, 엔터프라이즈 애플리케이션의 개발을 간소화하고 효율적으로 만들기 위해 설계되었다.

```
엔터프라이즈 애플리케이션이란?
대규모 조직의 비즈니스 요구를 충족하기 위해 설계된 복잡한 소프트웨어 시스템으로,
주로 여러 사용자가 동시에 사용하고 다양한 기능을 제공하는 애플리케이션.
```

Spring 은 다양한 모듈로 구성되어 있으며, 객체 지향 프로그래밍의 원칙을 기반으로 하여 유연하고 확장 가능한 애플리케이션 아키텍처를 제공한다.

## 2. Spring Framework 란?
Spring Framework 는 Spring 의 핵심 모듈로, 의존성 주입(Dependency Injection)과 AOP(Aspect-Oriented Programming)를 지원하여 애플리케이션의 구성 요소 간의 결합도를 낮추고, 테스트 용이성을 높인다.

예를 들어, 사용자 서비스(UserService)가 데이터베이스 접근을 위해 사용자 리포지토리(UserRepository)에 의존한다고 가정해보자.
```java
@Service
public class UserService {
   private final UserRepository userRepository;
   
    // 의존성 주입
   @AutoWired
    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }
    
    public User getUserById(Long id) {
        return userRepository.findById(id);
    }
}
```
위 코드에서 UserService 는 UserRepository 의 인스턴스를 생성자에서 주입받는다. 이렇게 하면 UserService 는 UserRepository 에 직접 의존하지 않게 되어, 테스트 시 Mock 객체를 쉽게 사용할 수 있다.

DI 를 사용하지 않아도 구현할 수 있는 내용이다. 하지만, UserService 내부에서 직접 UserRepository 의 인스턴스를 생성하면, 특정 구현체에 의존하게 되어 결합도가 높아진다. 아래 예시를 보자.

```java
public class UserService {
    private final UserRepository userRepository = new UserRepositoryImpl(); // DI 미사용

    public User getUserById(Long id) {
        return userRepository.findById(id);
    }
}
```

## 3. Spring Framework 의 장점
- **의존성 주입**: 객체 간의 관계를 외부에서 주입하여 결합도를 낮추고, 코드의 재사용성을 높입니다.
- **모듈화**: 다양한 모듈을 제공하여, 필요한 기능만 선택적으로 사용할 수 있습니다. (Spring Data, Spring Security 등)
- **테스트 용이성**: 의존성 주입 덕분에 단위 테스트가 용이하며, 목 객체(Mock Object)를 활용한 테스트가 가능합니다.
- **AOP 지원**: 관심사 분리를 통해 코드의 가독성과 유지보수성을 향상시킵니다.
