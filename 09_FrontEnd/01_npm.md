# npm

## 1. npm 이란
Node Package Manager 의 약자로, Node.js 를 위한 패키지 관리 도구이다. npm 은 JavaScript 라이브러리 및 패키지를 쉽게 설치하고 관리할 수 있도록 도와준다. Vue.js 와 같은 프레임워크 라이브러리를 사용하는 데 있어서 매우 유용하다.

## 2. 주요 기능

### 2-1. 패키지 설치
다양한 라이브러리와 패키지를 쉽게 설치할 수 있다. 예를 들어, 특정 라이브러리를 설치하려면 다음과 같은 명령어를 사용한다.
```bash
npm install package-name
```

### 2-2. 패키지 관리
설치된 패키지의 버전 관리 및 업데이트가 가능하다. 특정 패키지를 업데이트하려면 다음과 같은 명령어를 사용한다.
```bash
npm update package-name
```

### 2-3. 프로젝트 의존성 관리
프로젝트에 필요한 모든 패키지를 package.json 파일에 기록하여 프로젝트를 다른개발자와 공유할 때 필요한 패키지를 자동으로 설치할 수 있다.

### 2-4. 스크립트 실행
package.json 파일에 정의된 스크림트를 이용하여 빌드, 테스트, 실행 등의 작업을 간편하게 수행할 수 있다.
```bash
npm run script-name
```

### npm 사용 예제

#### 1. 패키지 설치
```bash
npm install axios
```

#### 2. 프로젝트 생성
```bash
npm init
```

#### 3. 패키지 제거
```bash
npm uninstall package-name
```