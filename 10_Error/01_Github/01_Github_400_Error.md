# 에러 로그

fatal: the remote end hung up unexpectedly

# 원인

한 파일의 크기가 ~Mb 정도 되어서, 

# 해결 방법

해당 파일이 .pdf 형식이라서 -> .png 형식으로 바꿨음

```shell
git config --global http.postBuffer 52428800
```
위와 같이 입력해서 한 파일의 크기가 최대 50MB 까지 가능하도록 하는 방법도 있음.