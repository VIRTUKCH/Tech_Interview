# Micro Service Architecture (MSA)

## 1. MSA 란?
MSA 는 애플리케이션을 여러 개의 독립적으로 배포 가능한 서비스로 나누어 개발하는 소프트웨어 아키텍처이다.
각 서비스는 특정 비즈니스 기능을 수행하며, 독립적으로 개발, 배포, 확장할 수 있다.
MSA는 RESTful API 혹은 메시징 시스템을 이용해서 서로 통신한다

> 서비스 -> 특정 비즈니스 모기능이나 도메인 로직을 수행하는 독립적인 모듈. 각 서비스는 서로 다른 프레임워크, 데이터 저장소를 사용할 수 있음.

> 메시징 시스템 -> 서비스 간의 비동기 통신을 지원하는 인프라. MSA 에서 서비스 간의 데이터를 안전하고 효율적으로 전달하기 위해 사용 됨. RabbitMQ, Apache Kafka, ActiveMQ 등이 있음.

## 2. MSA 를 사용하는 이유
- 각 서비스가 독립적으로 배포되기 때문에 기술 스택이나 언어를 자유롭게 선택할 수 있다.
- 특정 서비스만 수평적으로 확장할 수 있다. 예를 들어, 상품 조회가 자주 일어난다면 상품 서비스 데이터베이스를 여러 개 두어서 확장할 수 있겠다.
- 서비스가 분리되어 있기 때문에 장애 격리가 가능해진다.

## 3. MSA 환경의 장점 및 단점 분석
- 서비스가 많아짐에 따라 관리해야 할 부분이 많아진다.
- 데이터 관리 : 데이터의 일관성을 유지하기 어려울 수 있으며, 분산 데이터베이스 설계가 필요하다.
- 운영 오버헤드 : 여러 서비스의 배포 및 모니터링을 관리해야 하기 때문에 운영이 복잡해질 수 있다.

## 4. MSA 환경을 사용할 때 주의할 만한 점
- 서비스 간 통신 : RESTful API, 메시징 시스템 등 적절한 통신 방식을 택해야 한다.
- 데이터 일관성 : 분산 트랜잭션 관리 및 데이터 일관성을 위한 패턴을 고려해야 한다.
- 모니터링 및 로깅 : 각 서비스의 상태를 모니터링하고, 로그를 중앙에서 관리하는 체계를 구축해야 한다.
- 배포 전략 : CI/CD 파이프라인을 구축해서 자동화된 배포를 관리하는 것이 중요하다.

> 분산 데이터베이스 -> 데이터베이스가 여러 서버(노드)에 걸쳐 분산된 상황을 말한다.

> 분산 트랜잭션 관리 -> 여러 데이터베이스에 걸쳐 트랜잭션을 관리하는 경우 각 데이터베이스가 독립적으로 동작하기 때문에 스레드나 프로세스에서 트랜잭션을 관리하게 되면, 트랜잭션의 일관성을 유지하기가 어렵다. 이런 문제를 해결하기 위해 2PC (Two-Phase Commit) 프로토콜이나 트랜잭션 관련 라이브러리를 사용하여 문제를 해결할 수 있다.

> 데이터베이스의 수평 분할 (Sharding) -> 데이터를 여러 파티션으로 나누어 각 파티션이 전체 데이터의 일부를 저장하는 방식이다. 예를 들어, 사용자 데이터베이스를 지역 별로 나누거나, 사용자 ID 의 범위에 따라 나눌 수 있다.

> 데이터베이스의 수직 분할 (Vertical Partitioning) -> 데이터베이스의 열(column)을 기준으로 나눈다. 특정 열이 자주 사용되거나 대량의 데이터를 포함하고 있을 때 유용하다. 수직 분할은 데이터의 열을 기준으로 나누어 하나의 데이터베이스 내에서 관리하는 방식이다.

> 모니터링 -> 여러 개의 서버를 동시에 작동시키는 MSA 환경의 경우, 각 애플리케이션의 건강 상태를 확인하는 것이 중요할 수 있고, 이런 상태나 성능 등을 조회를 쉽게 하기 위해 Spring Boot Actuator 혹은 Micrometer 와 같은 의존성을 사용한다.

> 로깅 -> 여러 개의 서버를 나눠서 처리하는 MSA 환경에서는 한 곳에서 여러 개의 서비스에서 발생하는 로그를 적절하게 확인하는 것이 중요하겠다. ELK 스택이나 Fluentd 를 사용하면 여러 개의 서비스에서 발생하는 로그를 한 곳에서 모아서 확인할 수 있다.

> CI/CD 파이프라인 -> CI/CD 프로세스를 실제로 구현하기 위한 자동화된 작업 흐름이다. (Git Push -> Build -> Test -> Deployment)

## 5. 관련 구현체
- Spring Cloud : 마이크로서비스를 구축하기 위한 다양한 도구와 라이브러리를 제공한다.

## 6. 그 외 정보
- 마이크로서비스 아키텍처에서 자주 사용되는 패턴으로는 API Gateway, Circuit Breaker, Service Discovery, CQRS 등이 있다.

> API Gateway : 클라이언트와 여러 마이크로서비스 간의 중간 역할을 하는 컴포넌트이다. 클라이언트 요청을 받아 적절한 서비스로 라우팅하고, 여러 기능을 제공하여 클라이언트와 서비스 간의 통신을 관리한다. (Spring Cloud Gateway 등)

> Circuit Breaker : 마이크로서비스 아키텍처에서 서비스의 위치를 자동으로 찾고 관리하는 메커니즘이다. 서비스가 동적으로 생성되고 삭제될 수 있기 때문에, 이를 효율적으로 관리하기 위해 사용된다. (Spring-Cloud-Starter-Circuitbreaker-resilience4j 등)

> Service Discovery : 마이크로서비스 아키텍처에서 서비스의 위치(주소, 포트)를 자동으로 찾고 관리하는 메커니즘이다. 서비스가 동적으로 생성되고 삭제될 수 있기 때문에, 이를 효율적으로 관리하기 위해 사용된다.

> CQRS : command 와 query 의 책임을 분리하는 아키텍처 패턴이다. 시스템의 읽기 및 쓰기 작업을 분리하여 각 작업을 최적화하고, 성능과 확장성을 향상시키는 데에 도움을 준다.