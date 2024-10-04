# Entity : JPA 에서 데이터베이스의 테이블에 매핑되는 자바 객체.

## 1. Entity 란?
JPA의 핵심 기능은 데이터베이스의 테이블과 Java 의 객체를 매핑하는 것이다. Entity 란, JPA 에서 데이터베이스의 테이블에 매핑되는 자바 객체를 의미한다.

각 Entity 인스턴스는 데이터베이스의 한 행(row) 을 나타내며, Entity 를 통해 객체지향적으로 데이터베이스와 상호작용할 수 있다.

## 2. Entity 클래스 정의

기본적으로 다음과 같은 구조를 가진다. 클래스는 @Entity 어노테이션으로 표시되며, 각 필드는 데이터베이스의 컬럼에 매핑된다.

### 2-1. Entity 클래스의 기본 구조

```java
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity
@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class User {
    @Id // 기본 키를 나타냅니다.
    @GeneratedValue(strategy = GenerationType.IDENTITY) // 기본 키의 생성 전략을 정의합니다.
    private Long id;
    private String name;
    private String email;
}
```

> javax.persistence.Entity 와 jakarta.persistence.Entity 의 차이는? </br>
javax.persistence: JPA 2.x 이전 버전에서 사용, Java EE의 일환. </br>
jakarta.persistence: JPA 3.0 이상에서 사용, Jakarta EE로의 전환 후 새롭게 정의된 패키지.

### 2-2. @Entity 애너테이션
@Entity 어노테이션은 해당 클래스가 JPA Entity 임을 나타낸다. 이 어노테이션이 붙은 클래스는 JPA에 의해 관리되며, 데이터베이스의 테이블과 매핑된다.

### 2-3. 기본 키 정의
Entity 에서 키본 키는 @Id 애너테이션으로 정의한다. 기본 키는 각 Entity 인스턴스를 고유하게 식별하는 역할을 하며 @GeneratedValue 를 사용해서 기본 키의 생성 전략을 정의할 수 있다.

#### Id 의 @GeneratedValue 의 종류 </br>
- AUTO : JPA 구현체가 자동으로 전략을 선택.
- IDENTITY : 데이터베이스의 자동 증가 기능 사용.
- SEQUENCE : 데이터베이스의 시퀀스를 사용.
- TABLE : 별도의 테이블을 사용하여 키 생성.

### 2-4. 필드 매핑
Entity의 필드는 데이터베이스의 컬럼에 매핑된다. JPA 는 기본적으로 필드 이름과 매칭되는 컬럼을 생성하지만, @Column 애너테이션을 사용하면 매핑을 세부적으로 조정할 수 있다.
```java
import javax.persistence.Column;

@Column(name = "user_name", nullable = false, length = 50) // 컬럼 이름, null 허용 여부 및 길이 설정
private String name;

@Column(name = "user_email", unique = true) // 이메일은 유일해야 함
private String email;
```

@Column 애너테이션에는 아래와 같은 것들이 포함될 수 있다.
- name: 컬럼 이름
- nullable: NULL 허용 여부
- unique: 유일성 여부
- length: 최대 길이
- precision: 전체 자릿수 (BigDecimal 타입에 사용)
- scale: 소수점 아래 자릿수 (BigDecimal 타입에 사용)
- columnDefinition: SQL 정의 ("TEXT" 라고 적으면 TEXT 타입으로 정의)
- insertable: INSERT 포함 여부 (INSERT 쿼리에 포함되는지 여부를 지정)
- updatable: UPDATE 포함 여부 (UPDATE 쿼리에 포함되는지 여부를 지정)