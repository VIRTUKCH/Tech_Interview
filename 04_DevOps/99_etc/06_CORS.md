# CORS(Cross-Origin Resource Sharing)

## 1. CORS 란?
기본적으로 웹 브라우저는 동일 출처 정책 (Same-Origin Policy)을 따른다. 다시 말해서, 한 출처에서 로드된 웹 페이지는 자신의 리소스에만 접근해야 한다는 말이다.

일반적으로 백엔드 프로젝트를 진행하다 보면 프론트 서버와 백엔드 서버를 분리하기 나름이다. 그에 따라 웹 페이지가 다른 서버의 리소스에 접근하여 사용자에게 동적인 페이지를 보여 준다.

CORS 란 Cross Origin Resource Sharing 의 약자로, 웹 브라우저에서 보안 상의 이유로 다른 출처의 리소스에 접근할 수 있도록 허용하는 메커니즘이다.

예를 들어, https://example.com에서 로드된 웹 페이지가 https://api.example.com의 API를 호출하려고 할 때, 브라우저는 이를 차단한다. CORS 는 이러한 제한을 해결하기 위해 서버가 특정 출처의 요청을 허용할 수 있도록 설정할 수 있게 해준다.

## 2. 서버 측 설정
API 의 호출을 받는 입장에서는 어떤 IP 에 대해 요청을 허용할지, 어떤 HTTP 메서드를 허용할지, 어떤 헤더를 허용할지 등을 설정할 수 있다.

NGINX 를 사용할 수도 있고, 서버 언어와 프레임워크를 사용할 수도 있다.

나의 경우에는 NGINX 를 붙일 필요성까지는 못 느껴서 별도의 Filter 를 만들어 관리했다.

```java
package com.virtukch.dongiveupbe.security.common.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;
import org.springframework.web.filter.CorsFilter;

@Configuration
public class CorsConfig {

    @Bean
    public CorsFilter corsFilter() {
        UrlBasedCorsConfigurationSource source = new UrlBasedCorsConfigurationSource();
        CorsConfiguration config = new CorsConfiguration();
        config.setAllowCredentials(true);
        config.addAllowedOrigin("http://localhost:8080"); // 요청을 허용할 프론트엔드 URL
//        config.addAllowedOriginPattern("*"); // 모든 Pattern 에 대하여 CORS 허용
        config.addAllowedHeader("*"); // 모든 헤더 허용
        config.addAllowedMethod("*"); // 모든 HTTP 메서드 허용
        source.registerCorsConfiguration("/**", config);
        return new CorsFilter(source);
    }
}
```

어지간한 것들은 되도록이면 모두 허용하여 구현에 문제가 없게 했다.

## 3. NGINX 의 필요성
CORS 를 구현함에 있어서 NGINX 를 도입할 필요까지는 없다. 애플리케이션의 서버 코드에서 CORS 를 처리하는 것이 가능하기 때문이다.

그러나 NGINX 를 사용하면 CORS 설정을 서버와 클라이언트 간의 프록시 역할로 간편하게 할 수 있는 장점이 있다.

## 4. 추가적인 사항
- 보안 : CORS 설정을 할 때, 가능한 한 특정 출처만 허용하도록 하자.
- 디버깅 : 요청과 응답 헤더를 개발자 도구에서 확인하여 요청과 응답 헤더를 검사할 수 있다.
- 미들웨어 사용 : 클라이언트와 서버 간의 통신을 중재하는 컴포넌트인 미들웨어를 사용해서, CORS 설정을 쉽게 관리할 수 있다.