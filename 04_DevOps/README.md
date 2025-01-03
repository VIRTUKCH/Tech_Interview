# 6. DevOps_Tool

## 1. DevOps 란?
DevOps 란 Development 와 Operation 의 통합을 목표로 하는 문화나 사람, 도구 등을 포함한다.

데브옵스라는 집단은, 개발 팀과 운영 팀 간의 협업을 통해 소프트웨어 개발 주기를 단축하고, 소프트웨어 품질을 개선하고, 지속적인 배포를 가능하게 하는 것을 목표로 한다.

- 데브옵스 포지션이라고 얘기하면, 배포를 더 빠르고 안정적으로 수행할 수 있도록 돕는 사람을 말한다.
- 데브옵스 툴이라고 말하면, 배포를 더 빠르고 안정적으로 수행할 수 있게 하는 도구를 말한다.

## 2. DevOps 툴의 종류

### 2-1. 버전 관리 시스템 (VCS, Version Control System)
- Git : 분산 버전 관리 시스템으로, 코드 변경 사항을 관리한다.
- GitHub / GitLab : Git 저장소를 호스팅하고 협업 기능을 제공하는 플랫폼이다.

### 2-2. CI/CD 도구
- Jenkins : 오픈소스 자동화 서버로, 빌드와 배포를 자동화한다. 어렵지만 커스터마이징 가능하다는 특징이 있다.
- GitAction : GitHub 내에서 CI/CD 워크플로우를 자동화할 수 있는 기능으로, 코드 푸시 시 자동으로 테스트 및 배포를 수행할 수 있다.

### 2-3. 컨테이너화 도구
- Docker : 애플리케이션을 패키징하여 일관된 실행 환경을 제공한다. 이를 통해 개발, 테스트, 운영 환경에서 동일한 환경을 유지할 수 있다.
- Kubernetes : 컨테스터 오케스트레이션 도구로, 대규모 컨테이너 배포 및 관리를 자동화한다. 여러 컨테이너를 클러스트로 관리하고, 자동 스케일링 및 복구 기능을 제공한다.

### 2-4. 모니터링 및 로깅 도구
- Prometheus : 시스템 모니터링 및 경고 시스템으로, 메트릭 수집과 저장을 지원한다.
- Grafana : 다양한 데이터 소스로부터 시각화 대시보드를 생성하여 데이터를 시각적으로 표현할 수 있다.
- ELK Stack (ElasticSearch, Logstash, Kibana) : 로그 수집, 분석 및 시각화를 위한 통합 솔루션으로, 실시간 데이터를 처리하고 대시보드를 제공한다.
- Splunk : 데이터 검색 및 분석 플랫폼으로, 로그 및 이벤트 데이터를 실시간으로 분석하여 인사이트를 제공한다.

### 2-5. 구성 관리 도구 (Optional)
- Puppet : 인프라를 코드로 관리하는 도구로, 시스템의 상태를 정의하고 자동으로 관리한다.
- Ansible : IT 자동화 및 구성을 관리하는 
- Chef : 애플리케이션 배포 및 서버 구성을 자동화하는 도구로, Ruby DSL 을 사용하여 인프라를 코드로 관리한다.

### 2-6. 클라우드 서비스
- AWS : 다양한 클라우드 서비스를 제공하여 인프라를 구축하고 관리할 수 있는 플랫폼이다.
- Azure : Microsoft 의 클라우드 플랫폼으로, 다양한 개발 및 배포 도구를 제공한다.
- Google Cloud Platform (GCP) : Google 의 클라우드 서비스로, 애플리케이션 배포 및 데이터 관리에 유용하다.

### 2-7. 협업 도구 (Optional, 웹 페이지 방문 or 애플리케이션 설치 정도는 해 보자)
- Slack : 채팅 및 파일 공유 기능을 제공한다.
- Trello : 프로젝트 관리 및 작업 흐름을 시각화하는 도구로, 카드 기반의 인터페이스를 제공한다.
- Jira :  애자일 프로젝트 관리 도구로, 이슈 추적, 스프린트 계획 및 팀의 작업 관리를 지원한다.

## 3. 내가 공부하는 DevOps 의 범위
- 어떤 개념인지 설명할 수 있도록 하자.
- 왜 쓰는지 설명할 수 있도록 하자.
- 최소한 작동할 수 있게는 만들자.