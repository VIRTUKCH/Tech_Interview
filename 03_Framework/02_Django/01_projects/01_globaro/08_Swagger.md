# API 명세서 만들기

## 1. Swagger 란?
Swagger는 REST API의 구조를 자동으로 문서화하고, 인터페이스를 테스트하며, 개발자 간의 커뮤니케이션을 원활하게 하는 오픈소스 프레임워크이다.
Django REST Framework에서는 drf-yasg 패키지를 사용하여 Swagger 문서를 생성할 수 있다.

## 2. Swagger 만드는 방법

### 2-1. drf-yasg 설치
```bash
pip install drf-yasg
```

설치 후 settings.py에서 INSTALLED_APPS에 추가한다.
```python
INSTALLED_APPS = [
    ...
    'drf_yasg',
]
```

### 2-2. urls.py 에 Swagger 경로 추가
urls.py 파일에 Swagger 관련 경로를 추가한다.
```python
from django.urls import path, re_path
from rest_framework import permissions
from drf_yasg.views import get_schema_view
from drf_yasg import openapi

schema_view = get_schema_view(
    openapi.Info(
        title="My API",
        default_version='v1',
        description="API 문서",
        terms_of_service="https://www.example.com/terms/",
        contact=openapi.Contact(email="contact@example.com"),
        license=openapi.License(name="BSD License"),
    ),
    public=True,
    permission_classes=(permissions.AllowAny,),
)

urlpatterns = [
    path('swagger/', schema_view.with_ui('swagger', cache_timeout=0), name='schema-swagger-ui'),
    path('redoc/', schema_view.with_ui('redoc', cache_timeout=0), name='schema-redoc'),
    re_path(r'^swagger(?P<format>\.json|\.yaml)$', schema_view.without_ui(cache_timeout=0), name='schema-json'),
]
```

### 2-3. API 뷰에 Swagger 주석 추가
views.py에서 swagger_auto_schema를 사용하여 API 문서에 추가적인 설명을 넣을 수 있다.

```python
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from drf_yasg.utils import swagger_auto_schema
from drf_yasg import openapi

class ExampleView(APIView):
    """
    예제 API
    """

    @swagger_auto_schema(
        operation_summary="데이터 조회",
        operation_description="이 API는 예제 데이터를 반환합니다.",
        responses={
            200: openapi.Response(
                description="성공적인 응답",
                schema=openapi.Schema(
                    type=openapi.TYPE_OBJECT,
                    properties={
                        "message": openapi.Schema(type=openapi.TYPE_STRING, description="응답 메시지")
                    }
                )
            )
        }
    )
    def get(self, request):
        return Response({"message": "Hello, Swagger!"}, status=status.HTTP_200_OK)
```

## 3. 어디에서 확인할까
Django 서버를 실행한 후 브라우저에서 아래 URL로 접속하면 Swagger 문서를 확인할 수 있다.

Swagger UI: http://localhost:8000/swagger/

ReDoc 문서: http://localhost:8000/redoc/

JSON 문서: http://localhost:8000/swagger.json

## 4. URL 을 바꿀 수 있을까
urls.py에서 path('swagger/', ...) 부분을 변경하면 Swagger 문서의 URL을 원하는 대로 변경할 수 있다.
예를 들어 /api-docs/로 바꾸고 싶다면:
```python
path('api-docs/', schema_view.with_ui('swagger', cache_timeout=0), name='schema-swagger-ui')
```