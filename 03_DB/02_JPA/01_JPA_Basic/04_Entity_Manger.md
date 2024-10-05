# Entity Manager

## 1. EntityManager 란?
EntityManager 는 JPA 에서 데이터베이스와 자바 객체 간의 상호작용을 관리하는 기본 인터페이스이다. 이 인터페이스는 영속성 컨텍스트를 통해 엔티티의 생명 주기를 관리하고, CRUD 작업을 수행하며, JPQL 및 Criteria API 를 사용하여 쿼리를 실행한다.

## 2. EntityManager 는 PersistenceContext 를 관리하는가?
EntityManager 는 영속성 컨텍스트를 관리한다. EntityManager 는 영속성 컨텍스트와 상호작용하여 엔티티를 저장하고 조회하며, 상태를 변경하는 등의 작업을 수행한다. 영속성 컨텍스트는 EntityManager 가 관리하는 엔티티 인스턴스의 집합이다.

## 3. EntityManager 의 생명주기
EntityManager 는 EntityManagerFactory 를 통해 생성된다. EntityManagerFactory 는 애플리케이션의 전체 생명 주기 동안 하나만 생성되며, EntityManagerFactory 는 여러 개의 EntityManager 인스턴스를 생성할 수 있다.

예를 들어, 웹 애플리케이션에서는 각 HTTP 요청에 대해 새로운 EntityManger 를 생성하고, 요청이 완료된 후에 해당 인스턴스를 종료하는 방식으로 사용할 수 있다.

EntityManager 는 생성된 이후 엔티티를 저장, 조회, 병합, 삭제 등 여러 작업을 메서드를 통해 할 수 있다. 메서드에 대해서는 4번에서 다룬다.

EntityManager 의 사용이 끝나면, close() 메서드를 호출하여 종료해야 한다. 이를 통해 리소스를 해제하고, 연결을 닫을 수 있다.

애플리케이션이 종료될 때, EntityManagerFactory 또한 종료해야 한다. close() 메서드를 호출하여 모든 리소스를 해제한다.

## 4. EntityManager 의 주요 메서드

### 4-1. CRUD 작업

#### 4-1-1. persist() -> Create
새로운 엔티티를 영속성 컨텍스트에 추가하고, 데이터베이스에 저장하기 위한 준비를 한다. persist 메서드를 호출한 후, 트랜잭션이 커밋되면 엔티티가 데이터베이스에 저장된다.

<예시 코드>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin();

Student student = new Student();
student.setName("John Doe");

em.persist(student); // student 엔티티를 영속성 컨텍스트에 추가
em.getTransaction().commit();
em.close();
```

#### 4-1-2. merge() -> Update
이미 존재하는 엔티티의 상태를 영속성 컨텍스트와 동기화한다. merge() 메서드를 호출하면, 주어진 엔티티의 상태가 데이터베이스에 반영된다. 만약 엔티티가 영속성 컨텍스트에 없다면, 새로운 엔티티로 간주되어 데이터베이스에 추가된다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin();

Student student = em.find(Student.class, 1L);
student.setName("Jane Doe");

em.merge(student); // 수정된 상태를 데이터베이스에 반영
em.getTransaction().commit();
em.close();
```

#### 4-1-3. remove() -> Delete
영속성 컨텍스트에서 특정 엔티티를 삭제한다. remove() 메서드가 호출되면, 해당 엔티티는 영속성 컨텍스트에서 제거되고, 트랜잭션이 커밋되면 데이터베이스에서도 삭제된다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin();

Student student = em.find(Student.class, 1L);
em.remove(student); // student 엔티티를 삭제
em.getTransaction().commit();
em.close();
```

#### 4-1-4. find() -> Read
주어진 기본 키를 사용하여 데이터베이스에서 엔티티를 조회한다. 만약 해당 엔티티가 존재하지 않으면 null을 반환한다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();

Student student = em.find(Student.class, 1L); // 기본 키로 엔티티 조회
if (student != null) {
    System.out.println(student.getName());
}
em.close();
```

### 4-2. 쿼리 실행

#### 4-2-1. createQuery() -> JPQL 을 사용해서 쿼리를 실행
createQuery() 메서드는 JPQL(Java Persistence Query Language) 를 사용하여 쿼리를 생성한다. JPQL 은 SQL 과 유사하지만, 객체지향적이며 엔티티 객체를 기준으로 쿼리를 작성할 수 있게 해준다.

이 메서드는 동적 쿼리를 작성할 때 유용하며, getResultList() 또는 getSingleResult() 메서드를 통해 결과를 가져올 수 있다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();

List<Student> students = em.createQuery("SELECT s FROM Student s", Student.class).getResultList();
for (Student student : students) {
    System.out.println(student.getName()); // 각 학생의 이름 출력
}
em.close();
```

#### 4-2-2. createNamedQuery() -> Entity 클래스에 이미 정의된 JPQL 쿼리를 실행
createNamedQuery() 메서드는 미리 정의된 JPQL 쿼리를 실행한다. Named Query 는 애플리케이션이 시작될 때 미리 컴파일되기 때문에 성능을 향상시킬 수 있다. Named Query 는 엔티티 클래스에 @NamedQuery 애너테이션을 사용하여 정의된다.

<사용 예시>
```java
@Entity
@NamedQuery(name = "Student.findAll", query = "SELECT s FROM Student s")
public class Student {
    // 필드 및 메서드 정의
}

EntityManager em = entityManagerFactory.createEntityManager();

List<Student> students = em.createNamedQuery("Student.findAll", Student.class).getResultList();
for (Student student : students) {
    System.out.println(student.getName()); // 각 학생의 이름 출력
}
em.close();
```

#### 4-2-3. createNativeQuery() -> SQL 쿼리를 직접 실행하여 데이터베이스와의 직접적인 상호작용 가능
createNativeQuery() 메서드는 SQL 쿼리를 직접 실행할 수 있게 해준다. 이 메서드는 데이터베이스에 종속적인 쿼리를 사용할 때 유용하다. SQL 쿼리를 작성하여 실행할 수 있으며, 결과는 Object[] 형태로 반환된다. 또한, 특정 엔티티 클래스로 결과를 매핑할 수도 있다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();

List<Object[]> results = em.createNativeQuery("SELECT * FROM student").getResultList();
for (Object[] result : results) {
    System.out.println(result[1]); // 엔티티의 두 번째 컬럼만 출력.
}
em.close();
```

### 4-3. 트랜잭션 관리

#### 4-3-1. getTransaction()
getTransaction() 메서드는 현재 EntityManager 에 대한 트랜잭션 객체를 반환한다. EntityManager 에게서 얻은 트랜잭션 객체를 사용해서 트랜잭션을 시작하고, 커밋하거나 롤백할 수 있다.

JPA 에서는 트랜잭션을 통해 데이터베이스 작업을 원자적으로 처리할 수 있으며, 모든 작업이 성공적으로 완료되면 커밋하고, 실패할 경우 롤백된다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin(); // 트랜잭션 시작

// 데이터베이스 작업 수행 (예: 엔티티 추가, 수정 등)

em.getTransaction().commit(); // 모든 작업을 데이터베이스에 반영
em.close();
```

#### 4-3-2. commit()와 rollback()
commit() 메서드는 현재 트랜잭션을 커밋하여, 영속성 컨텍스트에 있는 모든 변경 사항을 데이터베이스에 반영한다. 이 메서드가 호출되면, 트랜잭션 내의 모든 작업이 완료되고 데이터베이스에 저장한다.

rollback() 메서드는 현재 트랜잭션을 롤백하여, 트랜잭션 내에서 수행된 모든 작업을 취소한다. 이 메서드는 오류가 발생했거나, 작업을 취소하고 싶을 때 사용한다. 롤백 후에는 트랜잭션 내에서 변경된 사항이 모두 원래 상태로 되돌아간다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin(); // 트랜잭션 시작

try {
    // 데이터베이스 작업 수행
    // 예: 엔티티 추가, 수정 등
    
    em.getTransaction().commit(); // 커밋
} catch (Exception e) {
    em.getTransaction().rollback(); // 오류 발생 시 롤백
    e.printStackTrace(); // 오류 로그 출력
} finally {
    em.close(); // EntityManager 종료
}
```

### 4-4. 상태 관리

#### 4-4-1. clear() -> 모든 엔티티를 detached 상태로 만드는 메서드
영속성 컨텍스트의 모든 엔티티를 분리하여, 더 이상 관리하지 않도록 한다. 이 메서드를 호출하면 영속성 컨텍스트에 있는 모든 엔티티가 detached 상태로 변경된다.

이 메서드를 호출한 후 모든 엔티티는 더 이상 엔티티 매니저에 의해 관리되지 않으며, 영속성 컨텍스트의 변경 사항이 데이터베이스에 반영되지 않는다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin();

Student student = em.find(Student.class, 1L);
// 엔티티에 대한 작업 수행

em.clear(); // 모든 엔티티를 분리
// 이제 student는 detached 상태임
em.getTransaction().commit();
em.close();
```

#### 4-4-2. detach() -> 단일 엔티티를 detached 상태로 만드는 메서드
특정 엔티티를 영속성 컨텍스트에서 분리하여 detached 상태로 만든다. 이 메서드를 호출한 후 해당 엔티티는 더 이상 관리되지 않으며, 영속성 컨텍스트의 변경 사항이 데이터베이스에 반영되지 않는다.

특정 엔티티만 분리할 수 있어, 영속성 컨텍스트의 다른 엔티티는 계속해서 관리된다.

<사용 예시>
```java
EntityManager em = entityManagerFactory.createEntityManager();
em.getTransaction().begin();

Student student = em.find(Student.class, 1L);
// 엔티티에 대한 작업 수행

em.detach(student); // student를 detached 상태로 만듭니다.
em.getTransaction().commit();
em.close();
```

#### 4-4-3. refresh() -> 특정 엔티티의 상태를 데이터베이스의 현재 상태로 갱신
특정 엔티티의 상태를 데이터베이스의 현재 상태로 갱신하는 데에 사용된다.

refresh() 가 호출된 엔티티는 영속성 컨텍스트 내의 상태가 데이터베이스의 현재 상태로 덮어씌워진다. 즉, 엔티티의 필드 값은 데이터베이스에서 가져온 최신 값으로 업데이트된다.

refresh() 호출 전에 엔티티(자바 객체)의 속성이 변경되었다면, 그 변경 사항은 무시되고 데이터베이스의 값으로 대체된다. 따라서, 주의해서 사용해야 한다.