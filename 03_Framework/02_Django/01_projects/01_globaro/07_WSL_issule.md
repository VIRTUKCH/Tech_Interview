# WSL Issue

## 1. 상황에 대한 설명
나는 WSL2 에서 /mnt/c/... 내에 디렉터리를 새로 만들어서 사용하고 있었다. Windows 파일 탐색기로 해당 내용들에 대한 접근이 가능하기 때문에, 나는 그렇게 하는 게 가장 적절하다고 생각했다.

## 2. 문제 인식
```bash
npm start
```
절대 별 명령어가 아님에도 불구하고, npm 을 써서 서버를 시작하는데 10초 이상이 걸렸다. 보통 길어 봐야 2초 이내에 끝나야 할 작업이기 때문에, 분명히 문제였다. 조금 검색해 본 결과, WSL 에 해당 문제점이 있다는 것을 알게 되었다.

## 3. 지연의 원인 원인
WSL2는 Windows 파일 시스템(`/mnt/c/...`)에 접근할 때 네트워크 파일 공유 방식(SMB 유사 프로토콜)을 사용한다. 이로 인해 파일 읽기/쓰기 속도가 느려질 수 있다.

WSL은 Windows에서 Linux 커널을 가상화해 실행하는 환경이다. WSL2는 Windows 파일 시스템에 네트워크를 통해 접근하며, 이를 통해 두 운영 체제 간의 파일 시스템 차이를 처리한다.

React 프로젝트는 `node_modules` 디렉터리에 필요한 의존성 라이브러리 파일을 저장한다. `npm start` 명령어 실행 시, Webpack Dev Server는 이 디렉터리에서 수천 개의 파일을 읽고, 변경 사항을 감지하며 빌드를 수행한다.

```bash
npm start
```

위 명령어는 파일 전체를 스캔하며 변경 사항을 감지하는 작업인 Webpack Dev Server 를 수행한다.

Windows 와 WSL 이 서로 파일을 접근하려 할 때는 밀리초 단위의 대기 시간이 발생하고, 파일 수가 수천 개에 달하기 때문에 10초 이상의 지연이 발생했던 것이다.

## 4. 지연이 WSL 내부에서는 더 빠른 이유
WSL 의 /home 경로에서는 Linux 가 원래 사용하는 파일 시스템 (ext4) 을 사용한다. 그에 따라 네트워크에 의존하지 않고, 그에 따라 네트워크 병목을 피할 수 있게 된다.

## 5. 해결 방법
프로젝트를 WSL 내부로 이동시켜 해결했다. /mnt/c 대신에 Linux 파일 시스템을 사용하는 /home/... 에서 실행한 것이다.

## 6. 결론
WSL2 와 Windows 파일 시스템 간의 파일 I/O 병목이 주요 원인이었던 것이다.

프로젝트를 WSL 내부로 이동시킨 이후에는 2초 이내로 빌드가 가능해졌다. 지연 시간이 대폭 감소한 것이다.