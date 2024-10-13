# JPQL (Java Persistence Query Language)

## 1. JPQL 이란?
JPQL 이란 JPA 에서 사용하는 객체지향 쿼리 언어로, 데이터베이스의 테이블이 아닌 JPA Entity (Java 객체) 를 대상으로 쿼리를 작성한다.

JPQL은 SQL과 유사한 구문을 사용하지만, 실제 데이터베이스의 구조보다는 객체 모델에 기반하여 쿼리를 작성한다. 이를 통해 객체 간의 관계를 명확하게 표현할 수 있다.

<예시>
```java
import jakarta.persistence.*;
import java.util.List;

@Entity
@Table(name = "members")
public class Member {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String name;

    @OneToMany(mappedBy = "member")
    private List<Coin> coins;

    // getters and setters
}
```

```java
@Entity
@Table(name = "coins")
public class Coin {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long amount;

    @ManyToOne
    @JoinColumn(name = "member_id")
    private Member member;

    // getters and setters
}
```
```java
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface CoinRepository extends JpaRepository<Coin, Long> {

    @Query("SELECT c FROM Coin c WHERE c.member.id = :memberId")
    List<Coin> findCoinsByMemberId(@Param("memberId") Long memberId);
}
```
위와 같은 상황이라고 할 때, JPQL 로 코드를 짜면 아래와 같다.
```java
@Query("SELECT c FROM Coin c WHERE c.member.id = :memberId")
```
SQL 로 코드를 짜면 아래와 같다.
```sql
SELECT * FROM coins WHERE member_id = :memberId;
```
쿼리 메시지는 거의 같다. 하지만, JPQL 은 Entity 를 기반으로 하며, JPA 는 Coin 과 Member 간의 관계를 직접적으로 이용한다. 객체 속성인 member.id 를 통해 회원 정보를 조회한다.

반면, 테이블 기반 SQL 쿼리는 coins 테이블에서 직접 member_id 컬럼을 이용하여 데이터를 조회한다. '객체 간의 관계가 외래 키를 통해서만 표현되기 때문에' 객체지향적인 접근 방식이 아니라고 하는 것 같다.

### 개인적인 생각
JPQL 에 대해서 깊이 있게 배워 보고, 사용하는 예시를 자주 보지는 않았다. 하지만 JPA 가 Entity 를 만들어 내고, JPQL 은 JPA 가 제공하는 Entity 를 이용하는 것일 뿐이지, JPQL 이 무언가 대단한 역할을 하는 것 같지는 않다. (내가 객체지향에 대해 잘 몰라서 쉽게 얘기하는 것일 수도 있다.)

JPQL 은 특정 데이터베이스에 종속되지 않기 때문에, 데이터베이스를 변경하더라도 쿼리를 쉽게 수정할 수 있다는 말 정도는 공감이 된다.

데이터베이스의 한 row 와 자바 객체 간의 패러다임을 완전히 극복한다는 개념적인 부분이 JPQL 을 학습하는 데에 있어서 가장 중요한 부분이 아닐까 생각해 본다.

## 2. 언제 사용하면 좋을까?
데이터베이스의 한 row 가 아닌 Entity 를 기준으로 데이터를 매핑하기 때문에, 객체지향적인 방식으로 데이터를 처리하고자 할 때 사용하면 좋다고 한다.

JPQL 은 특히 복잡한 데이터 모델을 다룰 때 유용하며, 객체와 속성의 관계를 쉽게 쿼리할 수 있도록 도와준단다. Native Query 와의 차이는 JPQL 이 객체 지향적이라는 점으로, 데이터베이스 의존성을 줄이고, 코드의 가독성을 높이는 데에 기여한다는 정도인 것 같다.

## 3. JPARepository 에서의 사용, @Query
Spring Data JPA 를 사용하면 JPARepository 에서 메서드 이름을 통해 쿼리를 자동으로 생성할 수 있지만, 복잡한 경우에는 @Query 애너테이션을 사용해서 명시적으로 정의해야 한다.

이 때 @Query 애너테이션을 사용해서 JPQL 을 사용할 수 있다.

## 4. @Param
@Param 애너테이션은 쿼리에서 명명된 매개변수를 정의하는 데에 사용된다. 이 애너테이션을 사용하면 쿼리 내에서 사용하는 매개변수와 메서드의 매개변수를 연결할 수 있다. (@PathVariable 같은 느낌)

@Param 애너테이션은 주로 JPQL 과 함께 사용되지만, Native Query 에서도 사용해도 된다.

JPARepository 에서 @Query 애너테이션을 작성했다는 건, Spring Data JPA 가 메서드 이름을 통해 자동으로 생성해주는 쿼리로는 감당이 불가능한 상황이라고 생각한다. 그에 따라 @Query 애너테이션을 사용하면 @Param 애너테이션은 반쯤 필수인 것 같다.

#### @Param 애너테이션을 사용한 예시(JQPL)
```java
@Query("SELECT c FROM Coin c WHERE c.memberId = :memberId")
List<Coin> findByMemberId(@Param("memberId") Long memberId);
```

## 5. 요약
- JPQL 은 JPA 에서 객체 지향적으로 데이터를 쿼리하는 언어로, SQL과 유사하지만 엔티티 중심의 접근 방식을 제공한다.
- Spring Data JPA와 통합하여 유용하게 사용할 수 있으며, @Query 애너테이션을 통해 복잡한 쿼리를 명시적으로 작성할 수 있다.
- JPQL은 객체 지향 프로그래밍의 장점을 살려 데이터 처리의 유연성을 높이고, 데이터베이스 독립성을 제공한다.