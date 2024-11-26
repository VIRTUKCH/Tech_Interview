# Framework

## 1. Framework 란 무엇인가?
프레임워크란 소프트웨어 개발에서 특정한 문제를 해결하기 위해 제공되는 기본적인 구조나 틀을 의미한다. 프레임워크를 사용하면 개발자가 반복적으로 작성해야 하는 코드를 줄일 수 있고, 규칙과 패턴을 따르게 하여 일관성 있는 코드를 작성하고 팀 내에서의 협업을 원활하게 할 수 있다. (코드가 생긴 게 비슷하게 됨)

이러한 구조를 유지하여 개발자가 비즈니스 로직에 집중할 수 있도록 도와준다.

## 2. Framework 는 왜 기본적인 구조나 틀을 지키도록 강제하는가?
코드를 비슷한 형태로 개발하게 만들게 되면, 비슷한 형태가 만들어지게 된다. 같은 프레임워크를 사용하는 사람들끼리 코드가 비슷해지게 되면, 아래와 같은 이점을 얻을 수 있다.

[예시]
- 프레임워크가 권장하는 규칙을 따르다 보면, 팀원 간의 협업 시 이해도를 높이고, 유지보수를 용이하게 할 수 있다.
- 재사용 가능한 코드와 구조를 제공하기 때문에, 개발자가 새로운 기능을 추가하는 데에 소요되는 시간을 단축시킬 수 있다.
- 특정한 패턴과 관행을 따르도록 하여, 다양한 개발자가 동일한 기준으로 코드를 작성할 수 있게 한다.
- 버그 수정 및 기능 추가 시에 더 쉽게 수정할 수 있도록 한다.

## 3. 의존성 역전(Dependency Inversion) 이란?
의존성 역전 원칙(Dependency Inversion Principle, DIP) 는 소프트웨어 설계의 원칙으로, 고수준 모듈이 저수준 모듈에 의존하는 것이 아니라 추상화된 인터페이스에 의존하도록 하는 것이다.

다시 말해서, 특정 구현체가 아닌 인터페이스에 의존하게 만들도록 하는 것이다. DIP 를 지켜 코드를 작성하면, 구현체를 변경할 때 유리하게 만들 수 있다.

아래는 의존성 역전 원칙을 적용한 간단한 자바 코드 예시이다.

```java
// 추상화된 인터페이스
interface NotificationService {
    void sendNotification(String message);
}

// 저수준 모듈
class EmailService implements NotificationService {
    public void sendNotification(String message) {
        System.out.println("Sending email: " + message);
    }
}

// 다른 저수준 모듈 (SMS 서비스 예시)
class SMSService implements NotificationService {
    public void sendNotification(String message) {
        System.out.println("Sending SMS: " + message);
    }
}

// 고수준 모듈
class UserService {
    private NotificationService notificationService;

    // 의존성 주입을 통해 NotificationService를 주입받음
    public UserService(NotificationService notificationService) {
        this.notificationService = notificationService;
    }

    public void registerUser(String email) {
        // 사용자 등록 로직
        System.out.println("User registered with email: " + email);
        notificationService.sendNotification("Welcome, " + email); // 알림 전송
    }
}

// 사용 예
public class Main {
    public static void main(String[] args) {
        // EmailService를 사용한 경우
        NotificationService emailService = new EmailService();
        UserService userServiceWithEmail = new UserService(emailService);
        userServiceWithEmail.registerUser("user@example.com");

        // SMSService를 사용한 경우
        NotificationService smsService = new SMSService();
        UserService userServiceWithSMS = new UserService(smsService);
        userServiceWithSMS.registerUser("user@example.com");
    }
}
```

위 코드를 보면 UserService 에서는 Console 에 사용자의 이메일을 출력하는 로직을 볼 수 있다.

- NotificationService 라는 인터페이스 사용
- SMSService, EmailService 는 NotificationService 라는 동일한 인터페이스를 구현함.
- UserService 는 구현체를 사용하지 않고, NotificationService 라는 인터페이스를 사용.

이렇게 설계하고 사용하면, 구현체를 바꿀 때 코드의 변경이 거의 없이 변경할 수 있게 된다. 이를 통해 시스템의 구조를 더 유연하게 만들고 유지보수성을 향상시킬 수 있다.