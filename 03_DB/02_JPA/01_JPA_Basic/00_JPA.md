# JPA (Java Persistence API)

## 1. JPA 란?
JPA (Java Persistence API)는 자바에서 객체와 관계형 데이터베이스 간의 매핑을 관리하는 API 이다. 이를 통해 데이터베이스 작업을 객체지향적으로 수행할 수 있다.

JPA 는 객체지향 프로그래밍 개념을 데이터베이스에 적용해서, 객체를 데이터베이스의 테이블과 매핑한다. 이를 통해 개발자는 데이터베이스를 객체로 다룰 수 있게 된다.

결론적으로, JPA 는 RDB 의 테이블과 Java 의 객체를 매핑하는 ORM(Object-Relational Mapping) API(Application Programming Interface) 라고 할 수 있다

> API 란? </br>
-> 다양한 소프트웨어 애플리케이션이 서로 정보를 교환하고 기능을 호출할 수 있도록 해주는 인터페이스다. 정의된 인터페이스가 있고, 기능을 제공하며, 표준화를 거쳤고, 추상화된 요소가 있다면 그것을 API(Application Programming Interface)라고 볼 수 있다.
</br></br>
JPA는 자바에서 '객체'와 관계형 데이터베이스 간의 매핑을 정의하는 규약을 제공하는 API 이다. 개발자가 데이터베이스와 상호작용할 때 따르는 일관된 인터페이스를 의미한다.
</br></br>
JPA 의 구현체에는 Hibernate, EclipseLink 등이 있지만, 이들 모두 JPA 의 인터페이스를 구현하고 있다. 추상화인 것이다. 즉, JPA 를 통해 개발자는 특정 구현체에 의존하지 않고, 표준화된 방법으로 데이터베이스 작업을 수행할 수 있다.

## 2. JPA 의 역사와 발전
JPA 는 2006 년에 공식 발표되어 자바 EE 5(Enterprise Edition) 의 일부로 포함되며, 데이터 지속성 관리의 표준으로 자리 잡았다. 여러 어플리케이션 서버에서 지원되며, 자바 개발자들이 데이터베이스와 쉽게 상호작용할 수 있도록 한다.

> 애플리케이션 서버란? </br>
-> 애플리케이션 서버는 데이터베이스와 상호작용하고, 비즈니스 로직을 실행하여 클라이언트 요청에 대한 결과를 생성한다. Spring Boot Starter Web 의존성에 내장되어 있는 Apache Tomacat 을 예로 들 수 있다.

JPA의 구현체로 여러가지가 있는데, 가장 널리 사용되는 Hibernate 부터 시작해서 EclipseLink, OpenJPA 등이 있다. 또한, Spring Data JPA를 통해 쉽게 사용할 수 있도록 지원하며, Repository 패턴으로 CRUD 작업을 간소화한다.

## 3. JPA 와 JDBC 의 연관성
JDBC 는 Java 에서 데이터베이스에 접근하기 위한 기본 API 이다. SQL 쿼리를 직접 작성하고 실행하여 데이터베이스와 상호작용한다.

JDBC는 저수준 API 로, 데이터베이스와의 세부적인 상호작용을 직접 관리해야 한다. 반면에, JPA 는 ORM 기술을 통해 객체와 데이터베이스 간의 매핑을 자동으로 관리하기 때문에, 개발자가 데이터베이스 세부사항을 신경 쓰지 않아도 된다.


<JDBC를 이용한 자바 코드 예시>
```java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class JdbcExample {
    private static final String URL = "jdbc:mysql://localhost:3306/mydb"; // 데이터베이스 URL
    private static final String USER = "your_username"; // 데이터베이스 사용자명
    private static final String PASSWORD = "your_password"; // 데이터베이스 비밀번호

    public static void main(String[] args) {
        // 데이터 삽입
        insertUser("John Doe", "john.doe@example.com");

        // 데이터 조회
        fetchUsers();
    }

    // 사용자 삽입 메서드
    private static void insertUser(String name, String email) {
        String insertSQL = "INSERT INTO users (name, email) VALUES (?, ?)";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {
            
            pstmt.setString(1, name);
            pstmt.setString(2, email);
            int rowsAffected = pstmt.executeUpdate();
            System.out.println("Inserted " + rowsAffected + " row(s) into the database.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // 사용자 조회 메서드
    private static void fetchUsers() {
        String selectSQL = "SELECT * FROM users";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(selectSQL);
             ResultSet rs = pstmt.executeQuery()) {
            
            while (rs.next()) {
                int id = rs.getInt("id");
                String name = rs.getString("name");
                String email = rs.getString("email");
                System.out.println("ID: " + id + ", Name: " + name + ", Email: " + email);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
```

---

> Q. JPA 의존성을 추가했는데, JDBC 의존성도 추가해야 하나?</br>
A. JPA 는 JDBC를 내부적으로 사용하기 때문에, JPA 구현체가 필요한 JDBC 드라이버를 포함하고 있다. 그러나, 특정 데이터베이스에 연결하기 위해서는 해당 데이터베이스의 JDBC 드라이버를 명시적으로 추가해야 한다. 예를 들어, MySQL 을 사용한다면 MySQL JDBC 드라이버를 추가해야 한다.

```xml
<!-- MySQL JDBC 드라이버 예제 (Maven) -->
<dependencies>
    <!-- JPA 의존성 -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-data-jpa</artifactId>
    </dependency>

    <!-- MySQL JDBC 드라이버 -->
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-j</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>
```

백엔드 환경에서 데이터베이스를 사용한다고 하면 특정 데이터베이스를 거의 무조건 지칭해야 하기 때문에, MySQL과 같이 특정 DB 를 사용하는 경우에는 두 의존성 모두 추가해야 한다고 생각하면 되겠다.

## 4. JPA와 ORM의 관계

### ORM(Object-Relational Mapping)
ORM 이란 객체 지향 프로그래밍 언어의 객체와 관계형 데이터베이스의 데이터 간의 매핑을 자동으로 처리하는 기술이다. ORM 을 사용하면 쿼리를 작성하지 않고도 객체를 데이터베이스에 저장하거나 데이터베이스에서 조회할 수 있다.

JPA는 자바에서 ORM 을 적용하기 위한 표준 인터페이스를 제공한다. JPA 를 통해 개발자는 데이터베이스 테이블을 자바 객체로 매핑하고, 객체를 통해 데이터베이스 작업을 수행할 수 있다. JPA 는 ORM 프레임워크의 일종으로, Hibernate 와 같은 구현체를 통해 실제 ORM 기능을 수행한다.

ORM 은 보통 Dynamic Query 를 지원하기 때문에, PreparedStatement와 같은 안전한 방법으로 쿼리를 처리하여 SQL Injection 과 같은 공격을 방어해 낼 수 있다는 추가적인 장점도 있다.

<JDBC 의 Prepared Statement 쿼리 예시>
```java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class JdbcPreparedStatementExample {
    private static final String URL = "jdbc:mysql://localhost:3306/mydb"; // 데이터베이스 URL
    private static final String USER = "your_username"; // 데이터베이스 사용자명
    private static final String PASSWORD = "your_password"; // 데이터베이스 비밀번호

    public static void main(String[] args) {
        // 사용자 삽입 예시
        insertUser("Jane Doe", "jane.doe@example.com");

        // 사용자 조회 예시
        fetchUserByName("Jane Doe");
    }

    // 사용자 삽입 메서드
    private static void insertUser(String name, String email) {
        String insertSQL = "INSERT INTO users (name, email) VALUES (?, ?)";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(insertSQL)) {
            
            pstmt.setString(1, name); // 첫 번째 물음표에 name 값 설정
            pstmt.setString(2, email); // 두 번째 물음표에 email 값 설정
            int rowsAffected = pstmt.executeUpdate(); // 쿼리 실행
            System.out.println("Inserted " + rowsAffected + " row(s) into the database.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // 사용자 조회 메서드
    private static void fetchUserByName(String name) {
        String selectSQL = "SELECT * FROM users WHERE name = ?";
        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement pstmt = conn.prepareStatement(selectSQL)) {
            
            pstmt.setString(1, name); // 조건에 맞는 name 값 설정
            ResultSet rs = pstmt.executeQuery(); // 쿼리 실행
            
            while (rs.next()) {
                int id = rs.getInt("id");
                String userName = rs.getString("name");
                String email = rs.getString("email");
                System.out.println("ID: " + id + ", Name: " + userName + ", Email: " + email);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
```

## 5. JPA 의 주요 개념
Entity, EntityManager, Persistence Context 등의 기본적인 개념이 있다. 다음 글에서 계속 작성하겠다.