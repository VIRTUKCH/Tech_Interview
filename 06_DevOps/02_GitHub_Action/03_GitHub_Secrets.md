# GitHub Secrets
GitHub Action 을 사용해서 CI/CD 파이프라인을 구성하기 위해서는, 애플리케이션이 동작하기 위해 필요한 정보를 모두 넘겨주어야 한다. 그러나 데이터베이스의 URL 이나 USERNAME, PASSWORD 와 같은 민감한 정보는 github 에 올리기 어렵다.

GitHub Secrets 를 사용하면 민감한 정보를 안전하게 저장하고 CI/CD 워크플로우에서 사용할 수 있다. 아래는 GitHub Secrets 를 설정하는 구체적인 방법이다.

## 1. 해당 Repository 로 이동 > Settings 탭 > 클릭 > Secrets and variables 선택 > New repository secret 클릭

## 2. 비밀 정보 입력
- Name 필드: 비밀 정보를 참조할 이름을 입력한다. (예: DB_URL, DB_USERNAME, DB_PASSWORD 등)
- Value 필드: 해당 비밀 정보의 값을 입력한다.
- Add secret 버튼을 클릭하여 비밀 정보를 저장한다.

## 3. 워크플로우 파일에서 GitHub Secrets 를 참조.
${{ secrets.<SECRET_NAME> }} 형식을 사용하면 된다.
```yaml
name: CI Workflow

on:
  push:
    branches:
      - main

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v2

      - name: Set up JDK
        uses: actions/setup-java@v2
        with:
          java-version: '17'
          distribution: 'adopt'

      - name: Build with Gradle
        env:
          DB_URL: ${{ secrets.DB_URL }}
          DB_USERNAME: ${{ secrets.DB_USERNAME }}
          DB_PASSWORD: ${{ secrets.DB_PASSWORD }}
        run: ./gradlew build
```