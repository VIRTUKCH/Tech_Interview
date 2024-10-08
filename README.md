# 기술 면접 대비를 위한 레파지토리

## 1. 이 레파지토리를 만든 이유
Spring Boot, MySQL, RESTful API 등을 작동하게 만드는 데에는 문제가 없지만, 내부적으로 어떻게 돌아가는지에 대한 이해가 부족하다고 느끼게 됨.

예를 들면, JPA 의 캐싱과 같은 부분이나 RESTful API 의 정의, Thread 의 동작 원리에 대한 이해가 부족함.

위의 것들을 알아야 구현할 수 있는 것은 아니지만, 알아 두어야 더욱 효율적으로 사용할 수 있음.

동시에, 이런 기초적인 부분들을 마무리하고 CI/CD, NGINX, Kafka 와 같은 기술들도 다루어 보고, 개념 정리를 해 보고 싶었음.

공부한 과정을 기록하지 않으면 휘발된다는 개인적인 생각으로, 이러한 것들을 글과 그림으로 남겨 보고자 이 레파지토리를 만들게 되었음.

## 2. 해당 레파지토리에서 다룰 컨텐츠는 무엇인가?
- Java, Network, DB, Spring 과 같은 Backend 와 관련된 기본적인 분야
- JPA, Spring 등 기능을 제공하는 구현체가 가진 기본적인 기능 및 내부 동작 방식
- CI/CD Tool, NGINX, Kafka 와 같은 기술의 도입 배경과 제공하는 기능 및 내부 동작 방식

## 3. 목적과 내용이 합리적인가?
개발자는 필요성을 따지고 효율을 추구해야 한다고 생각함. 그에 따라, 자신이 사용하는 기술의 내부 동작까지 이해하여 해당 기술을 사용하는 이유에 대해 잘 설명할 수 있는 사람이 되어야 한다고 생각.

기술을 사용하고 요구사항을 구현하는 것을 넘어, 해당 구현체의 구체적인 동작 방식을 이해한다는 관점에서는 목적과 내용이 합리적이라고 생각함.

## 4. 구체적인 순서가 있는가?

기본적으로 Java 부터 배워 보고 싶은 마음이 있음. 그러나, 개발자의 손에는 항상 '해결해야 하는 문제'가 있어야 하고, 개발자가 당장 공부해야 하는 것은 '해결해야 하는 문제에 대한 개념'이라고 생각함.

일단은 프로젝트에서 사용하는 기술들에 대해 잘게 쪼개어 공부해 볼 예정이며, 프로젝트가 어느 정도 마무리되는 시점에는 다시 Java 로 돌아가 개인 학습을 진행할 예정.

## 5. 주의해야 할 점에는 어떤 것들이 있을까?
열정만 가지고 있다고 해서 좋은 개발자가 될 수 있는 것은 아니라고 생각함. 효율적인 공부에는 좋은 공부법이 따라야 할 것. 그러니 주변에 전문가에게 지금 하고 있는 행동이 합리적인지 항상 물어 볼 것.