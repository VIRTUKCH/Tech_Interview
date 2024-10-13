# Spring MVC

## 1. Spring MVC 란?
Spring MVC 란, Spring Framework 의 웹 애플리케이션 개발을 위한 모듈로, Model-View-Controller 패턴을 기반으로 한 웹 프레임워크이다. Spring MVC 는 웹 애플리케이션에서 요청과 응답을 처리하고, 비즈니스 로직을 분리하여 개발할 수 있도록 도와준다.

만약, Spring Boot 를 사용해서 백엔드를 구성하고, 프론트엔드를 React 로 운영하는 경우, 전통적인 Spring MVC 패턴을 사용한다고 보기는 어렵단다. RESTful API 패턴을 사용한다고 보는 게 더 합리적이란다.

서버 사이드 렌더링 방식을 사용하면 전통적인 Spring MVC 패턴이라고 할 수 있지만, 클라이언트 사이드 렌더링 방식을 사용하면 전통적인 Spring MVC 패턴이라고 보기 어렵다고 한다.

> 서버 사이드 렌더링 (Servier-Side Rendering, SSR) 이란?</br>
서버 사이드 렌더링은 서버가 클라이언트의 요청에 따라 필요한 데이터를 처리하고, 그 데이터를 기반으로 HTML 페이지를 생성한 후 클라이언트에게 전달하는 방식이다.

> 클라이언트 사이드 렌더링 (Client-Side Rendering, CSR) 이란?<br>
클라이언트 사이드 렌더링은 웹 애플리케이션의 UI 와 콘텐츠가 브라우저 JavaScript 를 통해 동적으로 생성되는 방식이다. 초기 페이지 로드 시 최소한의 HTML 만 서버에서 제공하고, 나머지 컨텐츠는 클라이언트 측에서 API 호출 등을 통해 가져와서 렌더링한다.


## 2. 구성 요소
### 2-1. Model
애플리케이션의 데이터 및 비즈니스 로직을 나타낸다. 데이터베이스와의 상호작용을 통해 데이터를 가져오고, 처리하는 역할을 한다.

### 2-2. View
사용자에게 정보를 표시하는 부분으로, JSP, Thymeleaf, HTML 등 다양한 템플릿을 사용할 수 있다.

### 2-3. Controller
사용자의 요청을 처리하고, Model 과 View 를 연결하는 역할을 한다. 클라이언트의 요청을 받고, 적절한 비즈니스 로직을 수행한 후, 결과를 View 에 전달한다.

## 3. 핵심 기능
### 3-1. 요청 매핑
클라이언트의 요청을 처리하기 위한 매핑 기능을 제공한다.
```java
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/users")
public class UserController {

    @GetMapping("/{id}")
    public String getUser(@PathVariable String id) {
        // 사용자 ID에 따라 사용자 정보를 반환하는 로직
        return "User ID: " + id;
    }

    @PostMapping
    public String createUser(@RequestBody String userName) {
        // 사용자 생성 로직
        return "User created: " + userName;
    }
}
```
- @RestController : @Controller + @ResponseBody
- @ResponseBody : 메서드의 반환 값을 HTTP 응답 본문으로 직접 사용하도록 함 (JSON 변환) => Body 로 응답하라.
- @RequestMapping : HTTP 요청을 특정 메서드에 매핑
- @GetMapping : @RequestMapping(method = RequestMethod.GET)의 간편한 단축형
- @PostMapping : @RequestMapping(method = RequestMethod.POST)의 간편한 단축형
- @PathVariable : URL 경로의 변수를 메서드 매개변수로 주입받기 위한 애너테이션
- @RequestBody : HTTP 요청 본문을 메서드 매개변수로 주입받기 위한 애너테이션 => Body 를 가져와라

### 3-2. 데이터 바인딩
: 요청 파라미터를 DTO 객체로 매핑하여 쉽게 사용할 수 있도록 한다.
```java
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/users")
public class UserController {

    @PostMapping
    public String createUser(@RequestBody UserDTO userDTO) {
        return "User created: " + userDTO.getName();
    }
}
```

```java
// DTO 클래스
class UserDTO {
    private String name;

    // Getter와 Setter
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
```

### 3-3. 유효성 검사
: Bean Validation API를 사용하여 입력 데이터의 유효성을 검사할 수 있다.
```java
import javax.validation.constraints.Email;
import javax.validation.constraints.NotBlank;

public class UserDTO {
    @NotBlank(message = "이름은 필수입니다.")
    private String name;

    @Email(message = "유효한 이메일 주소를 입력하세요.")
    @NotBlank(message = "이메일은 필수입니다.")
    private String email;

    // getters and setters
}
```

```java
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/users")
public class UserController {

    @PostMapping
    public String createUser(@Valid @RequestBody User user) {
        // 유효성 검사를 통과한 사용자 처리
        return "사용자 생성 성공: " + user.getName();
    }
}
```

@NotBlank, @Email 은 javax.validation.constraints 패키지에 속해 있고, @Valid 애너테이션은 org.springframework.validation.annotation.Validated 패키지에 속해 있지만, Spring 과 Hibernate Validator 를 통해 호환된다고 한다.

### 3-4. 예외 처리
: 전역 예외 처리 기능을 제공하여, 일관된 방식으로 예외를 처리할 수 있다. @ControllerAdvice와 @ExceptionHandler를 사용한다.

```java
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;

@ControllerAdvice(assignableTypes = UserController.class)
public class UserExceptionHandler {

    @ExceptionHandler(UserNotFoundException.class)
    public ResponseEntity<String> handleUserNotFoundException(UserNotFoundException e) {
        return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
    }
}
```

```java
@RestController
@RequestMapping("/users")
public class UserController {

    @GetMapping("/{id}")
    public User getUser(@PathVariable String id) {
        if (id.equals("0")) {
            throw new RuntimeException("사용자를 찾을 수 없습니다.");
        }
        return new User("John Doe", "john@example.com");
    }
}
```

@ControllerAdvice 를 사용하면 전역적으로 예외를 처리할 수 있다. 특정 컨트롤러와 관련된 예외만 처리하려면 (assignableTypes = UserController.class) 를 붙여서 사용할 수도 있다.

@ExceptionHandler 를 사용하면 특정 예외를 처리할 수 있다. 지정된 예외가 발생할 때 호출된다.

위와 같이 GlobalExceptionHandler 를 사용하여 전역적으로 예외를 처리할 수 있는 로직 또한 Spring MVC 의 기능 중 하나이다.

## 4. 특징
- 유연성: Spring MVC는 Thymeleaf 와 같은 다양한 뷰 기술을 지원하며, XML 또는 Java 기반의 설정을 통해 유연하게 구성할 수 있습니다.
- RESTful 지원: RESTful 웹 서비스 개발을 위한 기능을 제공하여, JSON, XML 등의 형식으로 데이터를 송수신할 수 있다. @RestController 애넝테이션 또한 Spring MVC 의 일부이다.
- 테스트 용이성: Spring MVC는 테스트를 용이하게 해주는 다양한 도구와 기능을 제공한다. MockMvc를 사용하여 컨트롤러의 테스트를 쉽게 수행할 수 있다.

## 5. Spring Boot 와의 관계
Spring Boot는 Spring MVC를 기반으로 한 애플리케이션 개발을 더욱 간편하게 해주는 프레임워크입니다. Spring Boot를 사용하면 Spring MVC 설정을 최소화하고, 자동 설정 기능을 통해 빠르게 웹 애플리케이션을 개발할 수 있습니다.

Spring MVC는 웹 애플리케이션을 개발하기 위한 강력하고 유연한 프레임워크로, Model-View-Controller 패턴을 통해 애플리케이션의 구조를 명확히 하고, 유지 보수성을 높이는 데 기여합니다. RESTful API 개발을 포함한 다양한 웹 애플리케이션을 쉽게 구현할 수 있도록 지원합니다. 추가적인 질문이나 도움이 필요하시면 언제든지 말씀해 주세요!

