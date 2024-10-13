# @RequestMapping

## 1. @RequestMapping 애너테이션이 하는 일
@RequestMapping 애너테이션은 Spring MVC에서 HTTP 요청을 처리하는 메서드와 URL 경로를 매핑하는 데 사용된다.
이 애너테이션을 통해 특정 URL 패턴에 대한 요청을 처리할 컨트롤러 메서드를 정의할 수 있다.

<주요 기능>
- HTTP 메서드 매핑: GET, POST, PUT, DELETE 등 HTTP 메서드를 지정할 수 있다.
- URL 경로 매핑: 특정 URL 경로를 지정하여 해당 경로로 들어오는 요청을 처리할 수 있다.
- 요청 매개변수: 특정 요청 매개변수에 따라 메서드를 선택적으로 호출할 수 있다.
- 헤더 정보: 요청의 특정 헤더에 따라 메서드를 매핑할 수 있다.
- 소비 및 생산 타입: 요청 본문의 타입(예: JSON, XML) 및 응답의 타입을 지정할 수 있다.

<예시>
```java
@RestController
@RequestMapping("/api/users")
public class UserController {

    @GetMapping("/{id}")
    public User getUser(@PathVariable String id) {
        // 사용자 정보 반환
    }

    @PostMapping
    public User createUser(@RequestBody User user) {
        // 사용자 생성
    }
}
```

## 2. 구체적인 내부 동작 원리

### 2-1. 핸들러 매핑
Spring MVC는 애플리케이션이 시작될 때 모든 컨트롤러 클래스를 스캔하여 @RequestMapping이 붙은 메서드와 해당 URL 경로를 매핑한다.

### 2-2. 요청 수신
클라이언트가 HTTP 요청을 보내면, DispatcherServlet이 이를 수신한다.

### 2-3. 적절한 핸들러 찾기
DispatcherServlet은 요청 URL과 HTTP 메서드를 기반으로 적절한 핸들러(메서드)를 찾기 위해 핸들러 매핑을 사용한다.

### 2-4. 핸들러 호출
매핑된 핸들러가 발견되면, 해당 메서드가 호출되어 요청을 처리한다.

### 2-5. 응답 반환
핸들러 메서드는 처리 결과를 반환하며, 이 결과는 클라이언트에게 응답으로 전송된다.

### 2-6. 예시 내부 흐름
클라이언트가 /api/users/1로 GET 요청을 보내면, DispatcherServlet이 이를 수신하고, UserController의 getUser 메서드를 찾아 호출한다.

이와 같은 방식으로 @RequestMapping 애너테이션을 통해 HTTP 요청이 특정 메서드에 매핑되고, 요청 처리가 이루어진다.