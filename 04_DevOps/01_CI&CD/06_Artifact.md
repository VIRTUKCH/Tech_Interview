# Artifact

## 1. Artifact 란?
Artifact 는 소프트웨어 개발에서 생성된 결과물 또는 산출물을 의미한다. 이는 코드, 라이브러리, 실행 가능한 파일 등 다양한 형태로 존재할 수 있으며, 보통 빌드 프로세스를 통해 생성된다.

예를 들어, Java 애플리케이션은 JAR 파일이나 WAR 파일이 대표적인 Artifact 가 된다. 이러한 Artifact 란 배포, 테스트, 배포 자동화 등의 과정에서 사용된다.

## 2. JAR (Java ARchive)
JAR 는 Java 애플리케이션을 패키징하는 파일 형식으로, 여러 개의 클래스 파일, 메타데이터, 리소스 파일 등을 하나의 파일로 묶어 배포할 수 있게 해준다.

JAR 파일은 ZIP 형식으로 압축되어 있으며, META-INF 디렉터리와 MANIFAST.MF 파일을 포함한다. 이 파일은 JAR 의 메타데이터를 정의하고, 애플리케이션의 시작 클래스를 지정할 수 있다.

JAR 파일은 Java 애플리케이션을 배포하거나 라이브러리로 사용할 때 주로 사용한다.
```cmd
java -jar myapp.jar
```

## 3. WAR (Web Application Archieve)
WAR 는 웹 애플리케이션을 패키징하는 파일 형식으로, JSP 파일, 서블릿, HTML 파일, 이미지와 같은 웹 리소스를 포함한다.

WAR 파일은 JAR 파일과 유사하게 ZIP 형식으로 압축되어 있으며, WEB-INF 디렉터리와 web.xml 파일을 포함한다.

WAR 파일은 Java EE 기반의 웹 애플리케이션을 배포할 때 사용되며, 웹 서버나 애플리케이션 서버에 배포하여 실행할 수 있다. 예를 들어, Apache Tomcat 과 같은 서버에서 WAR 파일을 배포한다.

---

결론 : JAR 파일은 자바 애플리케이션을 패키징하는 파일 형식이고, WAR 파일은 웹 애플리케이션을 패키징하는 파일 형식이다. Spring Boot 는 웹 애플리케이션을 패키징하긴 하지만, 빌드 후에 JAR 파일을 내보내며, 필요에 따라 WAR 파일로도 패키징할 수 있는 옵션을 제공한다.

WAR 파일은 JAVA EE 기반의 웹 애플리케이션을 배포할 때 사용되며, 웹 서버나 애플리케이션 서버에 배포하여 실행할 수 있다. 예를 들어, Apache Tomcat 과 같은 서버에서 WAR 파일을 배포한다.

---

## 4. Docker Images
Docker 이미지란 애플리케이션과 그 실행해 필요한 모든 종속성, 라이브러리, 설정 파일 등을 포함한 경량화된 실행 환경이다.

Docker 이미지는 여러 개의 레이어로 구성되며, 각 레이어는 파일 시스템의 변경 사항을 나타낸다. Dockerfile 을 통해 이미지를 정의하고 생성할 수 있다.

Docker 이미지는 컨테이너화된 애플리케이션을 배포하고 실행하기 위해 사용된다. Docker 컨테이너는 이미지를 기반으로 실행되며, 개발 환경과 프로덕션 환경을 일관되게 유지할 수 있다.

## Spring Boot 로 만든 백엔드 환경을 Docker 이미지에 포함할 때, 어떤 파일이 들어갈까?

### 1. Jar 파일
Jar 파일은 애플리케이션의 코드, 종속성 및 리소스를 포함하고 있다.

### 2. Dockerfile
Docker 이미지를 생성하기 위한 명세 파일이다. 이 파일에는 이미지의 기반 이미지, 복사할 파일, 실행할 명령어 등이 포함된다.
```dockerfile
# OpenJDK 11 JRE의 경량화된 버전을 기반 이미지로 사용합니다.
FROM openjdk:11-jre-slim

# 빌드된 JAR 파일을 컨테이너의 /app 디렉토리에 복사합니다.
COPY target/myapp.jar /app/myapp.jar

# 컨테이너가 시작될 때 실행할 명령어를 정의합니다.
# java -jar 명령어를 사용하여 복사한 JAR 파일을 실행합니다.
ENTRYPOINT ["java", "-jar", "/app/myapp.jar"]
```

### 3. 애플리케이션 설정 파일
Spring Boot 애플리케이션의 설정 파일이 포함될 수 있다. 일반적으로 application.properties 또는 application.yml 파일이 이에 해당한다.

### 4. 종속성
Maven 또는 Gradle 을 통해 관리되는 외부 라이브러리와 종속성이 포함된다. 이러한 종속성은 JAR 파일에 이미 패키징되어 있을 수 있다.

### 5. 환경 변수 및 설정
Docker 컨테이너에서 애플리케이션의 동작을 제어하기 위한 환경 변수 설정이 필요할 수 있다. 이 정보는 Dockerfile 이나 Docker Compose 파일에서 설정할 수 있다.
```yaml
environment:
  SPRING_DATASOURCE_URL: jdbc:mysql://db:3306/mydb
  SPRING_DATASOURCE_USERNAME: user
  SPRING_DATASOURCE_PASSWORD: password
```

## ZIP
ZIP 형식은 여러 파일을 압축하여 하나의 파일로 만드는 포맷이다. JAR 파일도 ZIP 형식으로 압축된 파일이다. ZIP 파일은 다양한 파일 형식을 포함할 수 있으며, 주로 파일 전송이나 저장 공간 절약을 위해 사용된다.

## MANIFEST.MF
MANIFEST.MF 파일은 JAR 파일 내에 META-INF 디렉터리에 위치하며, JAR 파일의 메타데이터를 정의한다. 이 파일에는 메인 클래스, 버전 정보, 저작권 등이 포함될 수 있다.

## META-INF
META-INF 디렉터리는 JAR 파일이나 WAR 파일 내에서 메타 데이터를 포함하는 디렉터리이다. 이 디렉터리에는 MANIFEST.MF 파일을 포함하며, 애플리케이션에 대한 정보를 제공한다.

## web.xml
web.xml 파일은 WAR 파일 내의 WEB-INF 디렉터리에 위치하며, 웹 애플리케이션의 설정을 정의한다. 이 파일에는 서블릿, 필터, 리스너 등의 매핑과 설정이 포함되어 있다. Java EE 기반의 웹 애플리케이션에서 주로 사용된다.