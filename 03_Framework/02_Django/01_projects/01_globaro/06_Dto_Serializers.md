ㅈ# Dto 와 Serializer

## 1. Spring 의 Dto (Data Transfer Object)
Dto 란 계층 간 데이터를 주고 받기 위해 사용하는 객체이다. 주로 Controller <-> Service <-> Repository 사이에서 데이터를 전달하는 데 사용된다. Dto 는 데이터를 단순이 운반하는 역할만 수행하며, 비즈니스 로직을 포함하지 않는다.

## 2. Dto 의 역할

### 2-1. 데이터 캡슐화
요청 데이터를 캡슐화하여 Controller 에서 Service 로 전달하거나, Service 결과를 응답 데이터로 변환한다.

### 2-2. 계층 간 독립성 유지
Entity 를 직접 노출하지 않고 Dto 를 사용하여 시스템 계층 간 의존성을 줄인다.

### 2-3. 필드 매핑 및 데이터 변환
엔티티와 동일하지 않은 데이터 구조를 만들 수 있어서, API 요청/응답 형식에 맞는 데이터를 전달한다.

[Spring 에서의 Dto 사용]
```java
// DTO 클래스 정의
public class UserDto {
    private String name;
    private int age;

    // Getter와 Setter
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }
}

// Controller에서 DTO 사용
@RestController
@RequestMapping("/users")
public class UserController {
    
    @PostMapping
    public ResponseEntity<String> createUser(@RequestBody UserDto userDto) {
        // 요청 데이터를 처리
        System.out.println("Name: " + userDto.getName());
        System.out.println("Age: " + userDto.getAge());
        return ResponseEntity.ok("User created");
    }
}
```

Spring 에서의 Dto 는 Entity 와 직접 매핑해야 한다. 또한, 엔티티와 API 요청 및 응답 구조를 분리하기 때문에 설계를 깔끔하게 할 수 있다.

## 3. Django 의 Serializer

Serializer 는 데이터를 직렬화하거나 역직렬화하는 도구이다. 주로 Django REST Framework(DRF) 에서 사용되며, 데이터 구조를 JSON, XML 등과 같은 포맷으로 변환하거나, 클라이언트로부터 받은 데이터를 Python 객체로 반환한다.

## 4. Serializer 의 역할

### 4-1. 데이터 직렬화
Python 객체 (모델, 딕셔너리 등) 를 JSON, XML 형식으로 변환한다.

### 4-2. 역직렬화 및 유효성 검사
클라이언트에서 요청한 데이터를 역직렬화하며, 데이터가 유효한지 검사한다.

### 4-3. 모델 매핑핑
모델 데이터를 자동으로 매핑하여 요청과 응답에 사용할 수 있다.

[예시: Django에서 Serializer 사용]
```python
# Serializer 정의
from rest_framework import serializers

class UserSerializer(serializers.Serializer):
    name = serializers.CharField(max_length=100)
    age = serializers.IntegerField()

# 데이터 직렬화
user_data = {"name": "Alice", "age": 30}
serializer = UserSerializer(data=user_data)

if serializer.is_valid():
    print(serializer.validated_data)  # {'name': 'Alice', 'age': 30}
else:
    print(serializer.errors)
```

## 5. ModelSerializer
Django 의 ModelSerializer 는 모델과 직결된 Serializer 로, 모델 필드에 맞게 자동으로 직렬화기를 생성한다.
```python
from rest_framework import serializers
from myapp.models import User

class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = '__all__'0
```