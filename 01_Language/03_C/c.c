#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// 데이터 저장을 위한 구조체
struct MemoryStruct {
    char *memory;
    size_t size;
};

// 콜백 함수: API 응답 데이터를 처리
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, struct MemoryStruct *userp) {
    size_t realsize = size * nmemb;
    userp->memory = realloc(userp->memory, userp->size + realsize + 1);
    if(userp->memory == NULL) {
        printf("메모리 할당 실패\n");
        return 0;
    }
    memcpy(&(userp->memory[userp->size]), contents, realsize);
    userp->size += realsize;
    userp->memory[userp->size] = 0; // NULL로 종료
    return realsize;
}

// API 호출 및 결과 반환
long callApiWithHeader(const char* url, const char* token) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct response;

    response.memory = malloc(1); // 초기 메모리 할당
    response.size = 0; // 초기 크기

    // CURL 초기화
    curl = curl_easy_init();
    if(curl) {
        // 헤더 추가
        struct curl_slist *headers = NULL;
        char authHeader[256];
        snprintf(authHeader, sizeof(authHeader), "Authorization: Bearer %s", token);
        headers = curl_slist_append(headers, authHeader);
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // URL 설정
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // 타임아웃 설정

        // API 호출
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() 실패: %s\n", curl_easy_strerror(res));
        }

        // 헤더 해제
        curl_slist_free_all(headers);

        // CURL 종료
        curl_easy_cleanup(curl);
    }

    long sum = 0;
    if (response.memory) {
        sum = atol(response.memory); // 문자열을 long으로 변환
        free(response.memory); // 메모리 해제
    }

    return sum;
}

int main() {
    const char *url = "http://{URL}}:8080/api/v1/c-lang?a=5&b=10";
    const char *token = "your_token_here"; // 실제 토큰으로 변경

    long result = callApiWithHeader(url, token);
    printf("Result: %ld\n", result); // 결과 출력

    return 0;
}