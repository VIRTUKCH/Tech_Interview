# Flutter

## 1. Flutter 란?
Flutter 는 구글이 개발한 오픈 소스 UI 소프트웨어 개발 키트(SDK)로, 모바일, 웹, 데스크탑 애플리케이션을 개발할 수 있도록 지원한다.

Flutter 는 Dart 프로그래밍 언어를 사용하여 작성되며, 위젯 기반의 구성 요소를 통해 직관적이고 유연한 UI 를 구현할 수 있다.

## 2. Flutter 가 여러 플랫폼으로 배포할 수 있는 이유?
Flutter 는 다음과 같은 이유로 여러 플랫폼에서 배포가 가능하다.

### 2-1. 단일 코드베이스
Flutter 는 하나의 코드베이스로 Android, iOS, 웹, 데스크톱 애플리케이션을 모두 개발할 수 있다.

### 2-2. 네이티브 성능
Flutter 는 컴파일러를 통해 ARM 코드로 변환되어 네이티브 성능을 제공한다. 이로 인해 다양한 플랫폼에서 사용자 경험이 향상 된다.

> ARM 코드란?
> ARM 코드는 ARM 아키텍처를 기반으로 한 프로세서에서 실행되는 기계어 코드이다. Flutter 는 ARM 코드로 변환되어 모바일 기기에서 최적의 성능을 발휘한다.

### 2-3. 위젯 시스템
Flutter 의 위젯은 재사용 가능하며, 각 플랫폼의 디자인 가이드라인을 따르는 커스터마이징이 가능하다. 이를 통해 플랫폼에 맞는 UI 를 쉽게 구현할 수 있다.

> Flutter 의 위젯과 React 의 Component 의 차이점

> 구조 : Flutter 의 위젯은 모든 UI 요소를 객체로 취급하며, 상태를 관리하는 StatefulWidget 과 상태가 없는 StatelessWidget 으로 나눌 수 있다.
> 반면, React 의 Component 는 클래스형 및 함수형으로 나뉘며, 훅을 통해 상태를 관리한다.

> 렌더링 : Flutter 는 자체 렌더링 엔진을 사용하여 UI 를 그리는 반면, React 는 브라우저의 DOM 을 활용하여 UI 를 업데이트한다.
> 이로 인해 Flutter 는 플랫폼에 구애받지 않는 일관적인 UI 표현이 가능하다.

## 3. Flutter 는 어떻게 Web 으로 배포 되는가?
Flutter 는 Android Studio 내에서 Web 으로 배포할 수 있는 기능이 있다. 내부적으로 어떻게 동작하는 걸까?

### 3-1. Dart to JavaScript
Flutter 애플리케이션은 Dart 로 작성되며, 웹에 배포하기 위해 JavaScript 로 컴파일된다. 이를 통해 브라우저에서 실행할 수 있다.

### 3-2. HTTP 서버
Flutter 웹 애플리케이션은 정적 파일을 제공하기 위해 HTTP 서버를 사용할 수 있다. 이 서버는 HTML, CSS, JavaScript 파일을 클라이언트에게 전달한다.

### 3-3. Flutter Web Engine
Flutter 의 웹 엔진은 DOM 과 Canvas 를 사용하여 UI 를 렌더링한다. 이 엔진은 Flutter 의 위젯을 웹에서 효과적으로 표시할 수 있도록 도와준다.