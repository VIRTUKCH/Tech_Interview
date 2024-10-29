# Web RTC (Web Real-Time Communication)

## 1. 실시간 비디오 스트리밍이란?

실시간 비디오 스트리밍은 사용자가 콘텐츠를 생성하여 다른 사용자에게 실시간으로 전송하는 기술이다.
이 과정에서 지연이 최소화되어야 하며, 사용자 간의 즉각적인 상호작용이 가능하게 한다.
주로 화상 회의, 라이브 방송, 게임 스트리밍 등에서 된다.

또한, 실시간 비디오 스트리밍은 비디오 데이터와 오디오 데이터를 모두 지속적으로 보내주어야 한다.
비디오는 연속적인 이미지로 구성되고, 오디오는 연속적인 소리로 구성된다.

그리고 이러한 비디오 데이터와 오디오 데이터를 실시간으로 보내기 위해서는 이미지 데이터와 오디오 데이터를 동기화하고, 인코딩까지 해주어야 한다.
(인코딩은 데이터를 압축하여 대역폭을 효율적으로 사용하도록 도와준다.)

## 2. HTTP 를 이용해서 실시간 비디오 스트리밍을 할 순 없을까?

HTTP 프로토콜을 이용한 비디오 스트리밍은 일반적으로 버퍼링을 포함한 방식으로 동작하게 된다.
다시 말해서, 클라이언트가 비디오를 전체적으로 다운로드한 뒤에 재생을 시작해야 한다는 말이다.

다만, HTTP Live Streaming(HLS)나 Dynamic Adaptive Streaming over HTTP(DASH)와 같은 기술을 사용하면
비디오를 작은 조각으로 나누어 클라이언트가 이 조각들을 순차적으로 다운로드하며 재생할 수 있다.
그러나, 이 경우에도 어느 정도의 버퍼링이 필요합니다.

### HTTP 프로토콜을 사용한 비디오 스트리밍이 버퍼링을 포함한 방식으로 동작하는 이유?
HTTP 프로토콜을 사용한 비디오 스트리밍이 버퍼링을 포함한 방식으로 동작하는 이유는 여러 가지가 있다.
그 중 하나는 HTTP 가 기본적으로 일회성 통신 방식이라는 점이다.

HTTP 는 요청-응답 모델로 작동하며, 클라이언트가 서버에 요청을 보내면 서버가 응답을 반환하는 구조이다.
이로 인해 지속적인 연결이 어렵고, 실시간 데이터 전송에 적합하지 않다.

실시간 비디오 스트리밍을 원한다면, 이미지를 지속적으로 보내기 위해 반복적으로 API 를 호출해야 할 거다.
이 경우 HTTP 연결을 지속적으로 열고 닫아야 하므로, 실시간 스트리밍에 부적합하다고 할 수 있다.

HTTP/1.1에서는 Keep-Alive 기능을 통해 연결을 유지할 수 있지만, 실시간 스트리밍에는 여전히 한계가 있다.
HTTP/2와 같은 더 발전된 프로토콜이 더 나은 성능을 제공할 수 있지만, P2P 통신 방식보다는 실시간 상호작용에 적합하지 않다.

결론적으로, HTTP Live Streaming(HLS)이나 Dynamic Adaptive Streaming over HTTP(DASH) 같은 기술이 존재하지만,
이들 역시 일정한 지연이 발생하며, 사용자가 즉각적인 상호작용을 요구하는 경우에는 적합하지 않다.

## 3. Socket 을 이용해서 실시간 비디오 스트리밍을 할 순 없을까?

Socket 은 네트워크를 통해 데이터를 송수신하는 기본적인 인터페이스로 (HTTP 프로토콜 보다 더 낮은 단계로 구현 됨) TCP 나 UDP 와 같은 전송 프로토콜을 사용하여 지속적인 연결을 유지할 수 있다.
HTTP 의 일회성 요청-응답 모델과는 달리, 클라이언트와 서버 간에 지속적으로 데이터를 주고받을 수 있는 구조인 것이다.

Socket 은 UDP 전송 프로토콜을 사용할 수 있으면서 + 지속적인 연결을 유지할 수 있기 때문에 실시간 비디오 스트리밍에 있어서 HTTP 보다는 더 나은 성능을 보일 것이다.

하지만 Socket 또한 그다지 나은 성능을 보이지 못하는 것이, 


## 4. Web RTC 가 실시간 비디오 스트리밍에 좋은 이유

## 5. Web RTC 를 사용하는 방법

(0) 도커 이미지 다운로드
https://github.com/epicgames/PixelStreamingInfrastructure/pkgs/container/pixel-streaming-sfu

(1) github 에서 다운로드
https://github.com/EpicGamesExt/PixelStreamingInfrastructure

(2) root 디렉터리의 docker-compose.yml 파일 수정
```docker-compose.yml
version: '3.8'

services:
  pixel-streaming-sfu:
    image: ghcr.io/epicgames/pixel-streaming-sfu:5.4
    environment:
      - SIGNALLING_URL=ws://localhost:5678
    network_mode: "host"
```

(3) root 디렉터리의 config.json 파일 수정 (송신자와 수신자의 port 번호 수정)
```config.json
{
    "log_folder": "logs",
    "log_level_console": "info",
    "log_level_file": "info",
    "streamer_port": "5678",    // 송출하는 사람 포트
    "player_port": "6789",      // 들으려는 사람 포트
    "sfu_port": "8889",         // sfu 포트
    "serve": true,
    "http_root": "D:\\PixelStreamingInfrastructure\\SignallingWebServer\\www",
    "homepage": "player.html",
    "https": false,
    "https_port": 443,
    "ssl_key_path": "certificates/client-key.pem",
    "ssl_cert_path": "certificates/client-cert.pem",
    "https_redirect": true,
    "rest_api": false,
    "peer_options": "",
    "log_config": true,
    "stdin": false,
    "console_messages": "verbose"
}
```

(4) sfu 서버 열기
```shell
docker compose up
```
docker-compose.yml 파일을 찾아서 자동으로 찾아서 컨테이너 실행.

(5) 포트포워딩

(6) start_with.stun 파일 실행

* 윈도우의 경우
```shell
.\SignallingWebServer\platform_scripts\cmd\start.bat
```

* 맥, 리눅스의 경우
```shell
./SignallingWebServer/platform_scripts/bash/start.sh
```

(7) localhost:수신자포트 로 들어가서 수신 잘 되는지 확인