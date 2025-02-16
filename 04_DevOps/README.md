# DevOps

## 1. DevOps 란?
DevOps(데브옵스)는 Development(개발) + Operation(운영) 의 합성어로, 개발팀과 운영팀 간의 협업을 원활하게 하여 소프트웨어를 더 빠르고 안정적으로 배포하는 것을 목표로 하는 문화이자 실천 방식이다.

여기서 말하는 운영은 전통적으로 시스템 관리자, IT 인프라 담당자, SRE(Site Reliablity Engineer) 등의 비개발자가 주로 담당하는 영역이었지만, DevOps 가 도입되면서 개발자도 운영에 더 깊이 관여하게 되었다. 일부 개발자도 운영에 참여하였지만, DevOps 이전에는 역할이 확실히 분리되어 있었다.

2000년대 초반까지만 해도, 개발팀과 운영팀이 철저하게 분리되어 있었다. 운영 관련 작업은 개발자가 직접 하지 않는 경우가 많았다.

예를 들어, 개발자는 코드만 작성하고 시스템 관리자나 IT 엔지니어가 서버에 올리고 실행하는 등의 방식을 따랐다. 또한, 시스템 관리자가 서버 셋업, 네트워크 설정, 데이터베이스 운영 등을 직접 담당했다. 클라우드 이전에는 서버 증설도 운영팀이 직접 하드웨어 주문 및 설치하는 과정이 필요했다.

## 2. 데브옵스 엔지니어가 하는 일
DevOps 엔지니어는 개발과 운영의 경계를 허물고, 소프트웨어 배포 및 인프라 운영을 자동화하여 서비스의 안정성과 효율성을 극대화하는 역할을 한다.

- CI/CD 구축 및 자동화
- 인프라 및 클라우드 관리
- 컨테이너 및 오케스트레이션 관리
- 모니터링 및 로깅
- 보안 및 접근 제어
- 배포 및 운영 자동화
- 개발팀과 운영팀의 협업 지원

## 3. 백엔드 개발자의 DevOps
백엔드 개발자가 DevOps 를 공부할 때는 백엔드 서비스의 배포 및 운영에 필요한 핵심 개념을 익히는 것이 중요하다. 전체적인 DevOps 역할을 수행하는 것이 아니라, 배포 자동화와 인프라 운영에 대한 이해를 높이고 개발 생산성을 향상시키는 것을 목표로 한다.

1️⃣ CI/CD 구축 및 자동화
2️⃣ 인프라 및 클라우드 기초
3️⃣ 컨테이너 및 배포 환경
4️⃣ 모니터링 및 로깅
5️⃣ 배포 및 운영 자동화

### 3-1. CI/CD 구축 및 자동화
✅ 개념
- CI/CD란 무엇인가? (Continuous Integration & Continuous Deployment)
- 배포 자동화의 필요성 및 배포 전략 (블루/그린, 카나리아 배포)
🔹 주요 도구
- Jenkins: 오픈소스 자동화 서버, 복잡하지만 강력한 커스터마이징 가능
- GitHub Actions: GitHub 내에서 CI/CD 자동화 가능, 설정이 쉬움
- GitLab CI/CD: GitLab과 통합된 CI/CD 솔루션


### 3-2. 인프라 및 클라우드 기초
✅ 개념
- 온프레미스 vs 클라우드 vs 서버리스 비교
- 네트워크 기초 (로드밸런서, DNS, VPC)
- Infrastructure as Code(IaC) 개념 및 적용
🔹 주요 도구
- AWS (EC2, S3, RDS, Lambda, IAM)
- Azure (Azure Functions, Virtual Machines, Blob Storage)
- Google Cloud Platform (GCP) (Compute Engine, Cloud Run, BigQuery)
- Terraform: 인프라를 코드로 관리 (IaC)

### 3-3. 컨테이너 및 배포 환경
✅ 개념
- 컨테이너란 무엇인가? (가상머신과의 차이점)
- 컨테이너 기반 배포의 장점
- 오케스트레이션 개념 및 Kubernetes 필요성
🔹 주요 도구
- Docker: 컨테이너화된 애플리케이션 실행 환경 제공
- Docker Compose: 여러 컨테이너를 로컬 환경에서 손쉽게 구성
- Kubernetes(K8s): 컨테이너 오케스트레이션 도구, 자동화된 배포 및 스케일링 제공
- Helm: Kubernetes 애플리케이션을 패키징 및 배포

### 3-4. 모니터링 및 로깅
✅ 개념
- 모니터링과 로깅의 차이점
- 서비스 및 인프라 모니터링의 필요성
- 장애 감지 및 대응 자동화
🔹 주요 도구
- Prometheus: 메트릭 기반 시스템 모니터링 및 경고 설정
- Grafana: 대시보드를 통한 데이터 시각화
- ELK Stack (ElasticSearch, Logstash, Kibana): 로그 수집, 분석 및 검색을 위한 통합 솔루션
- Splunk: 실시간 로그 분석 및 보안 이벤트 감지

### 3-5. 배포 및 운영 자동화
✅ 개념
- Nginx, Gunicorn, uWSGI를 활용한 백엔드 배포
- 무중단 배포 전략 (Rolling Update, Blue/Green)
- Auto Scaling 및 장애 감지 자동화
🔹 주요 도구
- Nginx: 리버스 프록시 및 로드밸런서
- Gunicorn: Python 기반 백엔드 서버 실행
- Kubernetes: 컨테이너 기반 자동 확장 및 복구
- AWS Lambda, Google Cloud Functions: 서버리스 배포 방식

## 4. 내가 목표해야 하는 수준
- 운영팀 없이 개발자가 직접 배포하고 관리할 수 있을 정도의 DevOps 역량을 갖추는 것이 목표!
- DevOps 엔지니어 수준까지 깊게 공부할 필요는 없지만, CI/CD, Docker/K8s, 클라우드 기본 개념 정도는 필수
- 실제 개발과 연결되는 DevOps 개념만 익혀서 실무에서 효율적으로 활용할 수 있도록 학습