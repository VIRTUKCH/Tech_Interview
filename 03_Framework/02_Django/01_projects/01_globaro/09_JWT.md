# JWT (Json Web Token)

## JWT 란?
JWT(Json Web Token) 은 인증과 정보 교환을 위해 사용하는 토큰 기반 인증 방식이다. 사용자의 로그인과 관련된 정보 및 권한을 포함한 토큰을 생성하여 클라이언트 측에 제공하고, 클라이언트는 이 토큰을 이용해 서버와 상태를 유지하지 않고(stateless) 인증 요청을 수행할 수 있다.

JWT 는 암호화된 서명(Signature)을 포함하여, 변조를 방지할 수 있으며, 웹, 모바일, API 서버 간의 인증 방식으로 널리 사용된다. 특히, 앱을 재시작하거나 네트워크가 자주 변경될 수 있는 안드로이드와 같은 환경에서 더욱 환영받기도 한다.

## 왜 안드로이드 환경에서 JWT 가 Cookie & Session 기반의 인증보다 더 좋을까?
'안드로이드 환경이기 때문에' JWT 기반의 인증 방식이 Cookie & Session 기반의 인증 방식보다 더 나을 이유는 하나도 없다.

JWT가 Cookie & Session 기반 인증보다 유리한 이유는, 플랫폼(Android, iOS, Web)이 아니라 "서버 부하, 확장성, 인증 방식의 차이"에 있다.

- ✔ 플랫폼(Android, iOS, Web)에 따라 JWT가 더 유리한 것은 아님.
- ✔ 세션 기반 인증도 모바일에서 충분히 사용할 수 있다.
- ✔ JWT가 유리한 이유는, 서버가 세션을 유지하지 않아도 되기 때문이지, 모바일 환경 때문이 아니다.
- ✔ 세션 기반 인증에서도 쿠키를 적절히 관리하면 모바일에서도 문제없이 사용 가능하다.
- ✔ JWT는 DB 서버와의 연결 비용을 줄이고, API 서버 확장성을 높이는 것이 장점이다.
- 🚫 "안드로이드이기 때문에 JWT가 더 낫다" → ❌ 틀린 표현
- ✅ "JWT는 서버 확장성과 API 요청의 독립성을 높이기 때문에 유리할 수 있다" → ⭕ 올바른 표현
- 👉 즉, 인증 방식의 선택은 안드로이드, iOS 같은 플랫폼 때문이 아니라, 서버 구조와 확장성, 트래픽 처리 방식에 따라 결정해야 한다. 🚀

## stateless 방식을 지원한다는 의미
Stateless(무상태) 방식이란, 서버가 클라이언트의 인증 상태(Session)를 저장하지 않고, 매 요청마다 클라이언트가 자신의 인증 정보를 함께 전송하는 방식을 의미한다.
즉, 서버는 클라이언트의 로그인 상태를 기억할 필요 없이, 매 요청에서 받은 JWT를 검증하여 인증을 수행한다.

✔ 장점:
- 서버 부담 감소 (세션 저장소 불필요)
- 로드 밸런싱이 쉬워지고, API 서버 확장성 증가
- 마이크로서비스 아키텍처에서 유리

✔ 단점:
- 클라이언트가 토큰을 관리해야 함
- 토큰 탈취 시 보안 이슈 발생 가능

## JWT 의 구조
JWT는 3개의 부분으로 구성되며, Header.Payload.Signature 형태로 나타난다.

1️⃣ Header (헤더)
```json
{
  "alg": "HS256",
  "typ": "JWT"
}
```
alg: 사용할 암호화 알고리즘 (예: HS256, RS256)
typ: 토큰 타입 (JWT)

2️⃣ Payload (페이로드)
```json
{
  "user_id": 123,
  "exp": 1707168000
}
```
user_id: 사용자 식별자
exp: 토큰 만료 시간(Unix Timestamp)

3️⃣ Signature (서명)
```scss
HMACSHA256(base64UrlEncode(header) + "." + base64UrlEncode(payload), secret_key)
```
서명을 통해 JWT의 무결성을 보장함

## JWT 가 정보를 담는 방식
JWT는 **클레임(Claim)**이라는 데이터 구조를 사용하여 정보를 저장한다.

✅ 등록된 클레임 (Registered Claims)
- 표준적으로 사용되는 필드
- exp: 만료 시간
- iat: 발급 시간
- sub: 사용자 ID

✅ 공개 클레임 (Public Claims)
- 이메일, 역할(role) 등 공개적으로 정의할 수 있는 데이터

✅ 비공개 클레임 (Private Claims)
- 서비스 내부에서만 사용하는 커스텀 데이터

⚠️ 주의: JWT는 암호화되지 않으므로 민감한 정보(비밀번호, 카드번호 등)를 저장하면 안 된다.

## JWT 를 통해 사용자를 식별하는 방식
- 1️⃣ 클라이언트가 로그인하여 **JWT(Access Token)**를 발급받음
- 2️⃣ 이후 모든 요청에서 Authorization: Bearer <JWT> 헤더를 포함하여 전송
- 3️⃣ 서버에서 JWT의 서명을 검증하고 사용자를 인증

## Cookie & Session 을 통해 사용자를 식별하는 방식
- 1️⃣ 로그인하면 session_id를 생성하고 서버가 이를 저장
- 2️⃣ 클라이언트는 Set-Cookie를 통해 받은 세션 ID를 쿠키에 저장
- 3️⃣ 이후 요청에서 Cookie: session_id=ABC123을 포함하여 전송
- 4️⃣ 서버가 session_id를 확인하여 사용자를 인증

✔ 쿠키는 웹 브라우저에서 자동 관리되므로 편리함

✔ 모바일에서는 쿠키를 직접 저장해야 하므로 불편할 수 있음

## JWT 의 장단점과 주의할 점

✅ 장점
- Stateless 방식으로 서버 부담 감소
- 로드 밸런싱과 API 확장성이 뛰어남
- 마이크로서비스 아키텍처에 적합

❌ 단점
- 토큰 탈취 시 보안 위험 (XSS 공격, 탈취된 토큰 사용 가능)
- 서버에서 강제 로그아웃이 어려움 (Blacklist 관리 필요)
- 토큰 크기가 커서 네트워크 트래픽 증가 가능

🚨 보안 조치
- JWT는 HttpOnly & Secure 쿠키에 저장해야 안전함
- Access Token은 만료 시간을 짧게 설정하고, Refresh Token을 사용하여 갱신해야 함
- 탈취된 토큰을 차단할 수 있도록 Refresh Token 블랙리스트 관리 필요
- 블랙리스트의 크기가 커지면 Session 기반의 방식과 다를 것이 없기는 함. (JWT 의 딜레마)

## 회원가입, 로그인, 로그아웃 시의 서버의 대응
- ✔ 회원가입 → 사용자 정보를 저장하고, 필요시 이메일 인증
- ✔ 로그인 → 사용자 확인 후 Access Token + Refresh Token 발급
- ✔ 로그아웃 → 클라이언트에서 토큰 삭제, Refresh Token 폐기

## 토큰 유효성 확인 및 예외 처리
- 1️⃣ 유효한 토큰인지 검증 (exp, iat)
- 2️⃣ 서명 검증 (secret key)
- 3️⃣ 위변조 확인

## Access Token 과 Refresh Token
- ✔ Access Token → 짧은 수명의 JWT (5~30분)
- ✔ Refresh Token → 새로운 Access Token을 발급하는 용도로 사용 (DB 저장 필요)

## 로그인 상태에서 비밀번호를 변경한다면 백엔드 로직은 어떻게 짜야 할까
- 1️⃣ 기존 비밀번호 확인
- 2️⃣ 새 비밀번호로 업데이트
- 3️⃣ 기존 Refresh Token 폐기 (전체 로그아웃 효과)

## 이메일을 통해 받은 링크로 비밀번호를 재설정한다면 백엔드 로직은 어떻게 짜야 할까
- 1️⃣ 사용자가 reset-password 요청하면 이메일 전송
- 2️⃣ 이메일의 링크를 클릭하면 reset-password-confirm API에서 비밀번호 변경

## 토큰 유효성을 확인하고, 만료된 토큰이라면 새로운 토큰을 발급하는 것을 하나의 API 에 할당하는 것은, 단일 책임의 원칙에 위배되는 걸까?
**단일 책임 원칙(SRP)**을 지키려면 토큰 검증 API와 Refresh Token API를 분리하는 것이 좋다.

## 아래처럼 분리하는 건 좋은 설계일까?
- 회원가입 (POST /members/)
- 로그인 (POST /auth/login/)
- 로그아웃 (DELETE /auth/logout/)
- 토큰 유효성 확인 (GET /auth/me/)
- Refresh Token 발급 (PUT /auth/token/)
- 로그인 상태에서 비밀번호 변경 (PUT /members/:id/password/)
- 비밀번호 잊은 채로 이메일 통해 재설정 링크 받는 API (POST /auth/reset-password/)
- 재설정 링크 클릭해서 비밀번호 변경하는 로직 (POST /auth/reset-password-confirm/)

👍 좋은 설계
- RESTful 원칙을 따름
- 역할이 명확하게 분리됨
- 유지보수하기 쉬움

## 추가적으로 고려하거나 추가해야 할 로직이 있을까?
- ✔ 2FA (Two-Factor Authentication) 추가
- ✔ Refresh Token 블랙리스트 관리
- ✔ OAuth 2.0 연동 (Google, Kakao 로그인 지원)
- ✔ IP, User-Agent 기반의 추가적인 보안 검증