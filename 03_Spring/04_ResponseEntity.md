# ResponseEntity<>
다른 팀원들과 프로젝트를 함께 하다 보면, ResponseEntity 를 사용하는 모습을 자주 볼 수 있었다. 응답의 형태롤 정하기 위해서 사용하는 것 같아 보이는데, 내부적으로 어떻게 작동하는지, 그리고 어떻게 사용하면 좋을지에 대해 고민해 보면 좋을 것 같아서 글을 정리해 보게 되었다.

## 1. ResponseEntity 란? 
ResponseEntity 는 Spring Framework 에서 HTTP 응답을 표현하는 클래스이다.
이 클래스는 응답 본문(body), HTTP 상태 코드, HTTP 헤더를 포함할 수 있으며, RESTful 웹 서비스에서 클라이언트에게 반환할 응답을 보다 세밀하게 조정할 수 있습니다.
다시 말해서, 응답의 형태를 내가 원하는대로 커스터마이징 하기 위해서 사용하는 것이라고 생각하면 되겠다.

## 2. ResponseEntity 의 내부 동작 구조
ResponseEntity 는 HttpEntity 를 상속 받는다.

```java
public class ResponseEntity<T> extends HttpEntity<T>
```

그리고 HttpEntity<> 는 다음과 같은 멤버 변수를 가지고 있다.

```java
public class HttpEntity<T> {

	private final HttpHeaders headers;

	@Nullable
	private final T body;
}
```

기본적으로 HttpHeaders 를 가지고 있고, Body 또한 가지고 있다.

```java
package org.springframework.http;

public class ResponseEntity<T> extends HttpEntity<T> {

    private final HttpStatusCode status;

    public ResponseEntity(HttpStatusCode status) {
        this((Object) null, (MultiValueMap) null, status);
    }

    public ResponseEntity(@Nullable T body, HttpStatusCode status) {
        this(body, (MultiValueMap) null, status);
    }
    
    // 이 뒤에도 약 200 줄이 넘는 코드가 있다.
}
```

이건 ResponseEntity<> 의 내부 구조인데, HttpEntity 를 상속 받으면서 멤버 상수로 HttpStatusCode 를 가지고 있는 것을 볼 수 있다.

어려워 보일 수 있지만, 내부적으로 HttpStatusCode 를 가지고 있는, 응답을 위한 하나의 클래스라고 보면 되겠다.

### 결론적으로, ResponseEntity<> 는 HttpStatusCode, HttpHeaders, Body(Generics 형식) 을 담을 수 있다.

## 3. 그래서 어떻게 사용할 건가
결과적으로 ResponseEntity<> 는 HttpStatusCode, HttpHeaders, Body(Generics 형식) 을 담아서 일관적인 형태로 표현하기 위해 사용하는 것이라고 할 수 있다.

그렇다면, 이제 ResponseEntity<> 를 일반적으로 사용하는 여러 가지 형태에 대해서 알아 보자.

### 3-1. 단순 응답
```java
 @GetMapping("/greeting")
public ResponseEntity<String> getGreeting() {
    return ResponseEntity.ok("Hello, World!"); // 200 OK 응답
}
```
- HttpStatusCode 를 사용했는가? (O)
- HttpHeaders 를 적극적으로 활용했는가? (X)
- Body(Generics 형식) 에 유용한 정보가 들어 있는가? (X)

가장 기본적으로 ResponseEntity 를 사용하는 예시라고 볼 수 있다.
접근한 이후에는 내부적인 에러가 있더라도 무조건 200 상태 코드와 Hello World 라는 내용을 Body 에 반환한다.

### 3-2. 상태 코드와 함께 본문을 반환
```java
@PostMapping("/create")
public ResponseEntity<Item> createItem(@RequestBody Item newItem) {
    Item createdItem = itemService.create(newItem);
    return ResponseEntity.status(HttpStatus.CREATED).body(createdItem); // 201 Created 응답
}
```
- HttpStatusCode 를 사용했는가? (O)
- HttpHeaders 를 적극적으로 활용했는가? (X)
- Body(Generics 형식) 에 유용한 정보가 들어 있는가? (O)

일반적으로 사용하는 ResponseEntity 의 예시라고 볼 수 있다.
POST 요청을 통해 자원을 생성하고, 적절한 HttpStatusCode 와 생성된 Entity 를 반환하면서 생성된 자원에 대한 정보도 같이 넘긴다.

### 3-3. 예외 처리와 함께 사용
```java
@Getter
@Setter
public class ErrorResponseDto {
    private String message;
    private int errorCode;
    private LocalDateTime timestamp;
}

@ExceptionHandler(ItemNotFoundException.class)
public ResponseEntity<ErrorResponseDto> handleItemNotFound(ItemNotFoundException ex) {
    ErrorResponseDto errorResponse = new ErrorResponseDto();
    errorResponse.setMessage(ex.getMessage());
    errorResponse.setErrorCode(404); // 사용자 정의 에러 코드
    errorResponse.setTimestamp(LocalDateTime.now());
    return ResponseEntity.status(HttpStatus.NOT_FOUND).body(errorResponse); // 404 Not Found 응답
}
```
- HttpStatusCode 를 사용했는가? (O)
- HttpHeaders 를 적극적으로 활용했는가? (X)
- Body(Generics 형식) 에 유용한 정보가 들어 있는가? (O)

예외가 발생했을 때, 일정한 형태의 응답을 반환하기 위한 ExceptionHandler 의 코드 일부이다.
ErrorResponseDto 라는 하나의 Dto 클래스를 만들어서, 에러에 대한 정보를 추가적으로 담는 모습을 볼 수 있다.

---

## 4. ResponseEntity 의 헤더를 사용하는 방법? 

```java
@GetMapping("/items")
public ResponseEntity<List<Item>> getItems() {
    List<Item> items = itemService.getAllItems();
    
    HttpHeaders headers = new HttpHeaders();
    headers.set("X-Custom-Header", "Value");
    headers.setContentType(MediaType.APPLICATION_JSON);
    
    return ResponseEntity.ok()
                         .headers(headers)
                         .body(items);
}
```

헤더를 적극적으로 사용하는 것은 잘 보지 못했다. 하지만, 위와 같이 사용하면 헤더도 잘 사용할 수 있지 않을까 싶다.
예를 들면 쿠키 같은 것들을 생각해 볼 수 있겠다. HTTP 헤더에 쿠키를 설정할 수 있지만, ResponseEntity 자체에 쿠키를 직접적으로 담는 기능은 없기 때문이다.

## 5. 그 외 추가적으로 알아 두면 좋을 내용
- 제네릭 타입: ResponseEntity<T> 에서 T는 응답 본문의 타입을 지정하여 타입 안전성을 보장한다.
- 빌더 패턴: ResponseEntity 는 빌더 패턴을 지원하여, 다양한 설정을 직관적으로 할 수 있다.
- 전역 예외 처리: 전역 예외 처리기와 함께 사용하면, 예외 상황에 대한 일관된 응답을 제공할 수 있다.
- HTTP 메서드에 따른 응답: GET, POST, PUT, DELETE 등의 HTTP 메서드에 따라 적절한 응답 형식을 설정할 수 있다.