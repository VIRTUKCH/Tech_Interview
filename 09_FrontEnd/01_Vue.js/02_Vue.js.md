# Vue.js

## 1. Vue.js 란?
Vue.js 는 UI 와 싱글 페이지 애플리케이션 (SPA) 를 구축하기 위한 프로그레시브 자바스크립트 프레임워크이다.

## 2. SPA 란?
SPA 는 Single Page Application 의 약자로, 단일 페이지 애플리케이션을 의미한다. SPA 는 웹 애플리케이션의 한 형태로, 사용자가 페이지를 이동할 때 전체 페이지를 새로고침하지 않고, 필요한 데이터와 콘텐츠만을 동적으로 로드하여 표시한다.

예를 들면 Netflix 는 다양한 영화와 TV 프로그램을 탐색할 수 있지만, 카테고리 변경이나 콘텐츠 선택 시 페이지가 새로 고쳐지지 않는다.

SPA 는 URL 이 변경되더라도 전체 페이지가 새로 로드되지 않는데, SPA 는 처음으로 로드될 때 필요한 모든 HTML, CSS, JavaScript 파일을 한 번에 가져오기 때문이다. 이후 사용자가 애플리케이션 내에서 상호작용할 때, 페이지 전체를 새로 로드하는 대신 필요한 데이터만 서버에서 요청하고, 그 데이터를 기반으로 현재 페이지의 내용을 업데이트한다.

## 3. MPA 란?
MPA 의 반댓말은 전통적인 웹 애플리케이션에서는 Multi-Page Application (MPA) 방식을 사용한다. MPA 는 각 페이지가 독립적으로 존재하며, 사용자가 페이지를 로드할 때마다 전체 페이지를 새로 로드한다.

예를 들면, 뉴스 웹사이트에서 각 뉴스 기사는 별도의 페이지로 구성되며, 사용자가 기사를 클릭하면 새로운 페이지가 로드된다. 또한, 모든 페이지는 다른 URL로 구성되어 있으며 서버는 그에 맞는 페이지를 반환하고 브라우저는 해당 페이지를 로드한다.