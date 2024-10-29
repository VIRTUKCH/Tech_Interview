# Alarm
GitHub Actions 를 사용해서 알람을 보낼 수도 있다. Discord, Slack, 이메일 등이 알람을 지원한다.

## 1. 디스코드로 알람 보내기

### 1-1. Discord 에서 웹훅 설정
- Discord 서버에서 "서버 설정" > "통합" > "웹훅"을 선택하여 새로운 웹훅을 생성합니다.
- 생성된 웹훅 URL을 복사합니다.

### 1-2. GitHub Secrets 에 웹훅 URL 추가
GitHub 리포지토리의 "Settings" > "Secrets"에서 DISCORD_WEBHOOK_URL이라는 이름으로 저장합니다.

### 1-3. 워크플로우 파일 작성
```yml
name: Send Discord Alarm

on:
  push:
    branches:
      - main

jobs:
  notify:
    runs-on: ubuntu-latest

    steps:
      - name: Send alarm to Discord
        run: |
          curl -X POST -H 'Content-type: application/json' --data '{
            "content": "새로운 코드가 main 브랜치에 푸시되었습니다!"
          }' ${{ secrets.DISCORD_WEBHOOK_URL }}
```