# NGINX

## NGINX 란
NGINX 는 고성능 웹 서버, 리버스 프록시, 로드 밸런서, 캐싱 서버, API 게이트웨이 등의 기능을 제공하는 오픈소스 소프트웨어이다.

기존의 Apache HTTP Server 보다 가볍고 성능이 뛰어나며, 비동기, 논블로킹 아키텍처를 채택하여 높은 동시 접속을 처리한다.

## NGINX 의 다양한 역할
### 1. Web Server 역할
가장 기본적인 역할로, 브라우저(클라이언트) 의 요청을 받아 HTML, CSS, JavaScript 등의 정적 파일을 제공하는 역할을 수행한다.

Apache 와 같은 웹 서버도 있지만, Nginx 는 성능이 뛰어나고 가벼워서 많으 서비스에서 기본 웹 서버로 사용된다.

백엔드 서버(Spring, Django, Node.js 등) 앞단에서 정적 파일을 제공하는 역할을 맡기 위해 사용될 수 있다.

```nginx
server {
    listen 80;
    server_name example.com;

    location / {
        root /var/www/html;
        index index.html;
    }
}
```
-> 클라이언트가 http://example.com:80 에 접근하면 /var/www/html/index.html 을 응답하도록 만든다.

### 2. Reverse Proxy 역할
Nginx 는 리버스 프록시로 동작하여 클라이언트의 요청을 백엔드 서버(Spring, Django 등) 로 전달하는 역할을 수행할 수 있다.

백엔드 서버를 직접 노출하지 않고, Nginx 를 거쳐 요청을 전달하므로 보안, 로드밸런싱, 성능 최적화에 유리하다.

```nginx
server {
    listen 80;
    server_name api.example.com;

    location / {
        proxy_pass http://backend_server:5000;  # Django, Spring 같은 백엔드 서버로 요청 전달
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
```
-> 클라이언트가 api.example.com:80 에 요청하면, Nginx 가 이를 백엔드 서버(5000 번 포트) 로 전달한다.

- 백엔드 서버가 클라이언트의 요청을 직접 받지 않기 때문에 보안성이 증가한다.
- 여러 백엔드 서버가 있을 경우 로드 밸런싱을 적용할 수도 있다.

### 3. Load Balancer 역할
대규모 서비스에서는 하나의 백엔드 서버가 모든 요청을 처리하면 성능 문제가 발생할 수 있다.

Nginx 는 여러 개의 백엔드 서버를 연결하고, 트래픽을 분산(로드 밸런싱) 하는 역할을 수행할 수 있다.

```nginx
upstream backend_servers {
    server backend1.example.com;
    server backend2.example.com;
}

server {
    listen 80;
    server_name example.com;

    location / {
        proxy_pass http://backend_servers;
    }
}
```
-> 클라이언트 요청을 받을 때, 백엔드 서버 두 개에 요청을 분산하여 처리하는 방식이다.

-> 로드 밸런싱 방식은 Round Robin(RR), Least Connections, IP Hash 등 여러 가지를 지원한다.

### 4. Static File 서빙
백엔드 서버(Spring, Django) 는 동적 요청 처리에 집중하고, 정적 파일(이미지, CSS, JS 등)은 Nginx 가 대신 제공하면 성능 최적화가 가능하다.

예를 들어, Django 는 STATICFILES_DIRS 를 지정하여 Nginx 가 정적 파일을 제공하도록 설정할 수 있다.

```nginx
server {
    listen 80;
    server_name static.example.com;

    location /static/ {
        root /var/www/static;
    }
}
```
-> /static/ 경로로 요청이 들어오면 /var/www/static 디렉토리에서 정적 파일을 제공.

### 5. SSL/TLS 인증서 적용
Nginx 는 Let's Encrypt 같은 무료 SSL 인증서를 적용해서 HTTPS 를 활성화할 수 있다.

HTTPS 를 사용하면 보안이 강화되고, HTTP/2, HSTS 등의 추가적인 보안 기능을 활용할 수 있다.

```nginx
server {
    listen 443 ssl;
    server_name example.com;

    ssl_certificate /etc/letsencrypt/live/example.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/example.com/privkey.pem;

    location / {
        proxy_pass http://backend_server;
    }
}
```
→ Let's Encrypt 인증서를 사용하여 https://example.com 도메인을 SSL/TLS로 보호.

### 6. Gzip 압축을 통한 성능 최적화
- Nginx는 Gzip 압축을 통해 HTTP 응답 크기를 줄이고, 네트워크 트래픽을 최적화할 수 있음.
- 압축된 데이터는 클라이언트에서 해제되므로, 속도가 빨라지고 성능이 개선됨.

```nginx
server {
    listen 80;
    server_name example.com;

    gzip on;
    gzip_types text/plain text/css application/json application/javascript;
}
```
-> 텍스트, CSS, JSON, JavaScript 파일을 Gzip 압축하여 전송.

### 7. API Gateway 역할
마이크로서비스 아키텍처(MSA)에서는 여러 개의 백엔드 서비스가 존재할 수 있다. Nginx는 API Gateway 역할을 수행하면서, 여러 개의 서비스로 들어오는 요청을 적절히 분배할 수 있다.

```nginx
server {
    listen 80;
    server_name api.example.com;

    location /users/ {
        proxy_pass http://user-service:8000;
    }

    location /orders/ {
        proxy_pass http://order-service:9000;
    }
}
```
-> /users/ 요청은 유저 서비스, /orders/ 요청은 주문 서비스로 전달.

## 결론
- ✔ Nginx는 단순한 웹 서버가 아니라, 리버스 프록시, 로드 밸런서, API Gateway 등의 역할을 - 수행할 수 있음.
- ✔ 백엔드 개발자는 Nginx를 활용하여 보안 강화, 트래픽 관리, 로드 밸런싱을 최적화할 수 있음.
- ✔ 마이크로서비스 환경에서 API Gateway 역할을 수행하면서, 여러 개의 서비스 간 트래픽을 - 효율적으로 제어할 수 있음.