# JPA 의 Entity 관계 매핑

## 1. JPA Entity 관계 매핑 개요
JPA 의 핵심은 RDB 의 테이블과 Java 의 객체를 매핑하는 데에 있다. 데이터베이스의 테이블 구조를 객체 모델로 변환하면서, 개발자는 데이터베이스와의 상호작용을 더 직관적이고 효율적으로 수행할 수 있다.

JPA 는 객체와 데이터베이스 간의 매핑을 정의하기 위해서 여러 애너테이션을 제공한다. JPA 에서의 관계 매핑 기본 원리는 다음과 같다.

### 1-1. 애너테이션 기반 매핑
JPA 는 @OneToOne, @OneToMany, @ManyToOne, @ManyToMany 와 같은 애너테이션을 사용해서 Entity 간의 관계를 정의한다. 이 애너테이션을 통해 매핑의 방향성과 카디널리티(두 Entity 간의 관계의 수)를 설정할 수 있다.

### 1-2. 조인 컬럼
관계를 정의할 때 외래 키와 같은 조인 컬럼을 설정할 수 있으며, 이를 통해 두 Entity 간의 연관성을 나타낸다. @JoinColumn 애너테이션을 사용해서 외래 키의 이름을 지정할 수 있다.

### 1-3. Cascade 옵션
부모 Entity 의 상태 변화가 자식 Entity 에 전파되는 방식을 설정할 수 있다. 예를 들어, 부모 Entity 가 삭제될 때 자식 Entity 도 함께 삭제되도록 만들 수 있다.

### 1-4. Fetch 전략
연관된 Entity 를 어떻게 로드할지를 결정한다. EAGER 와 LAZY 두 가지 전략을 사용해서 데이터의 로딩 방식을 조정할 수 있다. EAGER 는 즉시 로드하며, LAZY 는 필요할 때 로드한다.

## 2. 관계의 종류
관계형 데이터베이스는 방향성을 명시적으로 표현하지 않는다. 그에 따라 관계를 총 세 가지(1:1, 1:N, N:N) 로 나타낼 수 있다.

그러나 JPA 에서의 관계는 방향성을 가지고 있다는 점에서 관게형 데이터베이스의 기본적인 개념과는 약간의 다른 접근 방식을 보이며 관계의 종류가 총 네 가지로 분류된다.

- 일대일 관계 (One-to-One)
- 일대다 관계 (One-to-Many)
- 다대일 관계 (Many-to-One)
- 다대다 관계 (Many-to-Many)

## 3. 단방향 관계
단방향 관계는 한 Entity 가 다른 Entity 를 참조하지만, 반대 Entity 는 해당 Entity 를 참조하지 않는 관계를 말한다.

실제 관계형 데이터베이스는 방향을 별도로 명시하지 않기 때문에, JPA 의 단방향 관계로 테이블 간의 관계를 표현하면 객체지향 패러다임과 관계형 데이터베이스 패러다임 간의 불일치가 발생하게 된다.

만약 단방향 관계를 사용해서 데이터베이스의 쿼리 성능을 개선하려는 목적이 아니라면, 단방향 관계는 사용하지 않는 것이 기능 면에서 더 좋다고 할 수 있다.

## 4. 양방향 관계
양방향 관계는 두 Entity 가 서로를 참조하는 관계를 의미한다. 이러한 관계는 개체 간의 상호작용을 보다 직관적으로 표현할 수 있으며, 양쪽에서 서로의 데이터를 쉽게 접근할 수 있다.

동시에, 양방향 관계를 맺어 줌으로써 객체지향 언어의 객체와 데이터베이스의 테이블 간의 패러다임 불일치 현상을 해결할 수도 있다.

### 4-1. 양방향 일대일 관계
양방향 일대일 관계는 두 Entity 가 서로를 참조하는 경우이다. 예를 들어, User 와 Profile 간의 관계에서 User 는 Profile 을 참조하고, Profile 도 User 를 참조한다.

```java
@Entity
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    @OneToOne(mappedBy = "user") // Profile에서의 user 필드에 의해 매핑
    private Profile profile;
}
```

```java
@Entity
public class Profile {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String bio;

    @OneToOne
    @JoinColumn(name = "user_id") // 외래 키
    private User user;
}
```

주의해야 할 것이, 이렇게 하면 Profile 이라는 테이블에서는 User 테이블의 PK 를 "user_id"라는 이름으로 가지게 된다. 외래키의 이름을 꼭 원래 테이블의 PK 이름으로 가질 필요는 없기 때문에 가능한 구조이기는 하다.

하지만, 이미 만들어진 테이블에서 FK 의 이름이 user_id 가 아니라면 프로그램이 정상적으로 작동하지 않을 수도 있으니 주의하자.

또한, mappedBy 옵션과 @JoinColumn 에 대해서도 생각해야 한다. 관계의 주체인(외래 키를 가지고 있는) 쪽에서 @JoinColumn 애너테이션을 사용하고, 그렇지 않은 쪽에서는 mappedBy 옵션을 사용한다.

### 4-2. 양방향 일대다 관계
양방향 일대다 관계는 한 Entity 가 여러 개의 다른 Entity 를 참조하고, 다른 Entity 도 부모 Entity 를 참조하는 경우이다. 예를 들어, Customer 와 Order 간의 관계에서 Customer 는 여러 개의 Order 를 가지고, 각 Order 는 Customer 를 참조할 수 있다.

```java
@Entity
public class Customer {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    @OneToMany(mappedBy = "customer") // Order에서의 customer 필드에 의해 매핑
    private List<Order> orders;
}
```

```java
@Entity
public class Order {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String product;

    @ManyToOne
    @JoinColumn(name = "customer_id") // 외래 키
    private Customer customer; // Customer를 참조
}
```

다대일 관계에서 자식 엔티티가 부모 엔티티를 참조할 때, 꼭 List<>를 써야 하는 건 아니라고 한다. Set<>, Map<> 을 사용해도 된다고 하니 알아만 두자.

### 4-3. 양방향 다대일 관계
위 4-2. 양방향 일대다 관계에서 관계의 주인만 바뀌면 된다고 한다. mappedBy 를 가지고 있는 테이블과 @JoinColumn 을 가지고 있는 테이블만 바뀌면 된다고 한다.

### 4-4. 양방향 다대다 관계
양방향 다대다 관계는 여러 개의 Entity 가 서로 여러 개의 관계를 가지며, 서로를 참조하는 경우이다. 예를 들어 Student 와 Course 간의 관계에서 한 학생이 여러 과목을 수강할 수 있고, 한 과목에 여러 학생이 등록할 수 있다.

```java
@Entity
public class Student {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    @OneToMany(mappedBy = "student")
    private List<StudentCourse> studentCourses = new ArrayList<>();
}
```

```java
@Entity
public class Course {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String title;

    @OneToMany(mappedBy = "course")
    private List<StudentCourse> studentCourses = new ArrayList<>();
}
```

```java
@Entity
public class StudentCourse {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "student_id") // 외래 키
    private Student student;

    @ManyToOne
    @JoinColumn(name = "course_id") // 외래 키
    private Course course;

    // 추가 속성 (예: 등록일 등)
    private LocalDateTime enrollmentDate;
}
```

관계의 주인이 중간 테이블에 있는 예시였다.

## 5. Cascade 옵션
### 5-1. CascadeType.PERSIST
부모 엔티티를 저장할 때, 관련된 자식 엔티티도 함께 저장한다. 즉, 부모 엔티티가 EntityManager에 의해 persist될 경우, 자식 엔티티도 자동으로 persist됩니다. 이 옵션은 부모와 자식 간의 생명 주기를 연관 지을 때 유용합니다.

### 5-2. CascadeType.MERGE

### 5-3. CascadeType.REMOVE

### 5-4. CascadeType.ALL

### 5-5. CascadeType.DETACH

## 6. Fetch 전략
### 6-1. FetchType.EAGER
### 6-2. FetchType.LAZY
### 6-3. Fetch 전략의 성능 영향

## 7. 관계 매핑 예제
### 7-1. 실습: 일대일 관계 구현
### 7-2. 실습: 일대다 관계 구현
### 7-3. 실습: 다대다 관계 구현

## 8. Entity 관계 매핑의 모범 사례
### 8-1. 관계 설계 시 고려사항
### 8-2. 성능 최적화 전략
### 8-3. 일반적인 오류 및 문제 해결

## 9. 결론 및 추가 자료
### 9.1. JPA 관계 매핑의 중요성 요약
### 9.2. 참고 자료 및 문서