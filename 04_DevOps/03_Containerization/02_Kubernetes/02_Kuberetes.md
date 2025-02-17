# Kubernetes(k8s)

## Kubernetes 란?
Kubernetes 는 컨테이너화 된 어플리케이션을 자동으로 배포, 확장, 관리하는 컨테이너 오케스트레이션(Container Orchestration) 플랫폼이다.

Google 이 내부에서 사용하던 Borg 시스템을 기반으로 개발했으며, 현재 Cloud Native Computing Foundation 에서 관리하고 있다고 한다.

Kubernetes 는 단순히 컨테이너를 실행하는 것뿐만 아니라, 컨테이너 배포 자동화, 로드 밸런싱, 스케일링, 자가 복구 기능까지 제공하여 대규모 애플리케이션 운영을 효율적으로 관리할 수 있도록 한다.

## Kubernetes 의 기능 간단히 정리
- 자동 배포, 스케일링, 서비스 디스커버리 등의 컨테이너 관리 자동화
- 컨테이너가 장애를 일으키면 자동으로 다시 실행하거나, 정상적인 노드로 옮겨서 실행 가능하다
- CPU 및 메모리 사용량에 따라 컨테이너 개수를 자동으로 조정. (오토 스케일링)
- 클라우드 또는 온프레미스 어디에서나 실행 가능

## Docker + Docker Compose or Shell Script 로 할 수 있는 일
Docker 및 Docker Compose 또는 Shell Script를 활용하면 단일 서버에서 컨테이너를 실행하고 관리하는 작업을 수행할 수 있다. 하지만 Kubernetes(k8s)처럼 클러스터링, 자동 복구, 오토스케일링 등의 고급 기능은 제공하지 않는다.

### 📌 1) 컨테이너 실행 및 관리
- docker run 명령어를 사용하여 컨테이너를 실행
- docker stop, docker start, docker restart로 컨테이너 수동 관리
- docker ps로 실행 중인 컨테이너 확인

### 📌 2) 컨테이너 환경 설정 및 구성 자동화 (Docker Compose)
- docker-compose.yml 파일을 사용하여 여러 개의 컨테이너를 한 번에 실행
- 예: 웹 애플리케이션 + 데이터베이스(MySQL, PostgreSQL) + 캐시(Redis)
- docker-compose up -d로 컨테이너 실행, docker-compose down으로 종료

### 📌 3) 네트워크 설정 및 컨테이너 간 통신
- docker network create 명령어를 사용하여 컨테이너 간 통신 설정 가능
- docker-compose.yml에서 네트워크를 정의하여 컨테이너 간 자동 연결 가능

### 📌 4) 볼륨을 활용한 데이터 지속성 유지
- docker volume create로 컨테이너 데이터를 영구적으로 저장
- docker-compose.yml에서 볼륨을 설정하여 컨테이너 재시작 후에도 데이터 유지 가능

### 📌 5) 컨테이너 빌드 자동화 (CI/CD 활용 가능)
- Dockerfile을 이용하여 이미지를 자동으로 빌드
- Shell Script로 CI/CD 파이프라인에서 자동 빌드 및 배포 수행 가능
- GitHub Actions, GitLab CI/CD와 연동하여 자동화

### 📌 6) 단일 서버에서 애플리케이션 배포 및 관리
- Docker + Shell Script를 활용하여 단일 서버에서 자동으로 컨테이너 배포 가능
- 단일 노드에서 여러 개의 애플리케이션을 실행하는 경우 유용

## k8s 만 할 수 있는 일
Kubernetes는 멀티 노드 환경에서 컨테이너를 자동으로 배포, 관리, 확장하는 기능을 제공한다. Docker + Shell Script 또는 Docker Compose로는 불가능한 대규모 컨테이너 오케스트레이션을 수행할 수 있다.

### 📌 1) 클러스터링 및 멀티 노드 컨테이너 관리
- Docker Compose는 단일 서버에서만 컨테이너를 관리하지만, Kubernetes는 여러 개의 서버(노드)로 구성된 클러스터에서 컨테이너를 관리할 - 수 있음.
- 워커 노드(Worker Node)들을 추가하면 자동으로 컨테이너를 배분하여 실행 가능.

### 📌 2) 오토스케일링(Auto Scaling)
- **HPA(Horizontal Pod Autoscaler)**를 통해 CPU/메모리 사용량에 따라 Pod 개수를 자동으로 늘리거나 줄일 수 있음.
- Docker Compose는 수동으로 컨테이너 개수를 늘려야 하지만, Kubernetes는 트래픽 증가 시 자동으로 컨테이너를 확장할 수 있음.

### 📌 3) 서비스 디스커버리 및 로드 밸런싱
- Kubernetes의 서비스(Service) 개념을 이용해 자동 로드 밸런싱 가능.
- 여러 개의 Pod(컨테이너 인스턴스) 중 하나가 다운되더라도, 나머지 Pod로 트래픽을 자동 분배하여 장애 없이 운영 가능.
- Docker Compose에는 기본적인 네트워크 설정만 가능하며, Kubernetes의 서비스 디스커버리 기능이 없음.

### 📌 4) 자가 복구(Self-Healing)
- 컨테이너가 장애로 인해 종료되면, Kubernetes가 자동으로 새로운 컨테이너를 재생성하여 유지.
- Docker Compose는 컨테이너가 종료되면 수동으로 다시 실행해야 함.

### 📌 5) 롤링 업데이트(Rolling Update) 및 롤백(Rollback)
- Kubernetes는 새로운 애플리케이션 버전을 배포할 때 무중단(Zero-downtime)으로 업데이트 가능.
- Docker Compose에서는 기존 컨테이너를 삭제하고 다시 실행해야 하므로 서비스 중단이 발생할 수 있음.
### 📌 6) 퍼시스턴트 볼륨(Persistent Volume, PV) 및 스토리지 관리
- Kubernetes는 스토리지 볼륨을 여러 Pod에서 공유할 수 있으며, 클라우드 스토리지(AWS EBS, GCP Persistent Disk)와 연동 가능.
- Docker Compose는 기본적으로 로컬 볼륨만 지원하므로, 멀티 노드 환경에서는 데이터 공유가 어려움.

### 📌 7) CI/CD와 연동하여 프로덕션 환경에서 무중단 배포
- ArgoCD, FluxCD 같은 GitOps 도구를 활용하여 Git을 기반으로 배포 자동화 가능.
- Jenkins, GitHub Actions와 Kubernetes를 연동하여 자동 배포 파이프라인 구축 가능.

### 📌 8) 클라우드 네이티브 및 멀티 클라우드 지원
- Kubernetes는 AWS EKS, GCP GKE, Azure AKS 등 클라우드 네이티브 환경에서 완벽하게 동작하도록 설계됨.
- Docker Compose는 단일 서버에서 실행되므로 클라우드 환경에서 확장성이 부족함.