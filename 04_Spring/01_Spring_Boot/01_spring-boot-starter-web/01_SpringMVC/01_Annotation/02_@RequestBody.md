# @RequestBody

## 1. @RequestBody 애너테이션이란?
@RequestBody 애너테이션은 HTTP 요청의 본문 (Body)을 Java 객체로 변환할 때 사용하는 Spring MVC 의 기능이다. JSON 또는 XML 형식의 데이터를 DTO(Data Transfer Object) 로 매핑하는 데에 사용한다.

<주요 기능>
- 데이터 변환 : 클라이언트로부터 전달 받은 JSON 혹은 XML 데이터를 Java 객체로 자동 변환시킨다. 이를 통해 복잡한 파싱 작업을 생략할 수 있다.

- RESTful API 개발 : RESTful 웹 서비스에서 클라이언트가 전송한 데이터를 쉽게 처리할 수 있도록 도와 준다.

- 유효성 검사 : DTO 에 유효성 검증 애너테이션을 적용해서, 요청 데이터의 유효성을 검증할 수 있다.

```java
@RestController
@RequestMapping("/api/users")
public class UserController {

    @PostMapping
    public User createUser(@Valid @RequestBody UserDto userDto) {
        // userDto 객체는 JSON 데이터로부터 자동으로 변환됨
        return userDto;
    }
}
```

> Q. 클라이언트가 입력한 값을 JSON 혹은 XML 로 변환시켜주는 것은 누가 하는 일일까?</br></br>
클라이언트가 입력한 값을 JSON 혹은 XML로 변환하는 작업은 메시지 변환기(Message Converter)에 의해 수행된다.</br>
Spring MVC에서는 기본적으로 Jackson 라이브러리를 사용하여 JSON 변환을 처리한다. XML 변환의 경우, JAXB 또는 Jackson XML 모듈을 사용할 수 있다.</br>
요청의 Content-Type 헤더에 따라 적절한 변환기가 선택되어 데이터 변환이 이루어지게 된다.

> Q. 응답을 JSON 이 아닌 XML 로 하려면 어떻게 해야 할까?</br></br>
응답을 JSON이 아닌 XML로 하려면 Spring Boot에서 XML 변환기 의존성을 추가해야 한다.</br>
의존성을 추가한 뒤, HTTP 응답의 Accept 헤더를 설정하고, 컨트롤러 메서드에서 XML 을 반환하면 된다.</br>
또한, 클라이언트에서 Accept 헤더에 application/xml 을 포함해야 한다고 명시해야 한다.


```java
@GetMapping(value = "/{id}", produces = MediaType.APPLICATION_XML_VALUE)
public User getUser(@PathVariable String id) {
    // User 객체를 XML로 반환
    return userService.findUserById(id);
}
```

## 2. @RequestBody 애너테이션이 없다면?
@RequestBody 애너테이션 없이 DTO를 파라미터로 받으면, Spring MVC는 요청 본문을 읽지 않는다.
그에 따라 DTO의 모든 멤버 변수는 null 값으로 초기화된다.
다시 말해서, 본문의 데이터는 모두 전달되지 않는다.

## 3. 구체적인 내부 동작 원리

### 3-1. DispatcherServlet 수신
클라이언트가 HTTP 요청을 보내면, Spring 의 DispatcherServlet 이 이를 수신한다.

### 3-2. Handler 메서드 선택
요청 URL 과 HTTP 메서드에 기반하여 적절한 컨트롤러 메서드를 찾는다.

### 3-3. HTTP 요청 본문 읽기
선택된 핸들러 메서드의 파라미터에 @RequestBody 애너테이션이 있으면 본문을 읽는다. 다시 말해서, @RequestBody 애너테이션이 없으면 본문을 읽지 않는다.

### 3-4. 메시지 변환기 사용
Spring 은 등록된 메시지 변환기를 사용해서 요청 본문을 Java 객체로 변환한다. 기본적으로 JSON 데이터는 Jackson 라이브러리를 통해 변환된다.

이는 spring-boot-starter-web 의존성에 포함되어 있으며, Jackson 라이브러리는 메시지 컨버터를 가지고 있다. 기본적으로 MappingJackson2HttpMessageConverter 가 사용되며, 이를 통해 JSON 데이터의 직렬화와 역직렬화 작업이 이루어진다.

### 3-5. DTO 객체 전달
변환된 DTO 객체가 메서드의 파라미터를 통해 전달 된다.

### 3-6. 응답 반환
핸들러 메서드가 처리한 결과를 클라이언트에게 응답으로 반환한다.