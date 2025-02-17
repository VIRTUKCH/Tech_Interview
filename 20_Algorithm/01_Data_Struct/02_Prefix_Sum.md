# Prefix Sum (구간합)

## 1. 기본 개념
- 배열의 특정 구간의 합을 빠르게 구하는 방법.
- 매번 for 문을 통해 구하면 O(N), Prefix Sum 을 사용하면 O(1)
- 주로 누적 합(Prefix Sum) 배열을 활용해서 계산.
- **[중요] 배열을 N+1 의 크기로 할당해야 실수하지 않음**

## 2. Prefix Sum (누적합) 알고리즘
```java
int[] A = {2, 3, 7, 1, 8, 5};
int N = A.length;
int[] S = new int[N + 1]; // 누적합 배열

// 누적합 계산
for (int i = 1; i <= N; i++) {
    S[i] = S[i - 1] + A[i - 1]; // S 배열은 1부터 시작, A 배열은 0부터 시작
}
```

## 3. 구간합 계산 (Range Sum Query)
```java
int L = 2, R = 5;
int rangeSum = S[R] - S[L - 1]; // O(1) 연산
System.out.println(rangeSum); // 21
```

### 관련 문제
[백준 - 구간 합 구하기 4](https://www.acmicpc.net/problem/11659)

### 문제 풀이
N+1 개의 공간을 할당했다면 훨씬 더 쉽게 풀 수 있었을 것.

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Iterator;
import java.util.StringTokenizer;

import javax.imageio.metadata.IIOMetadataFormatImpl;

// Run Shortcut => Shift + Command + Function + F11
public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = 0, M = 0;
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		
		long[] arrayValue = new long[N];
		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < arrayValue.length; i++) {
			arrayValue[i] = Long.parseLong(st.nextToken());
		}
		
		long[] sumArrayValue = new long[N];
		for (int i = 0; i < sumArrayValue.length; i++) {
			if(i>0) {
				sumArrayValue[i] = arrayValue[i] + sumArrayValue[i-1];
			} else {
				sumArrayValue[i] = arrayValue[i];
			}
		}
		
		int a = 0, b = 0;
		// 1. 여러 번 받아
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			a = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			if(a == 1) {
				System.out.println(sumArrayValue[b-1]);
			} else {
				System.out.println(sumArrayValue[b-1] - sumArrayValue[a-2]);
			}
		}
	}
}
```

## 4. 2차원 구간합 계산

### 2D Prefix Sum 공식
(x1, y1) ~ (x2, y2) = (S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1])

### 관련 문제
[백준 - 구간 합 구하기 5](https://www.acmicpc.net/problem/11660)

### 문제 풀이
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

// Run Shortcut => Shift + Command + Function + F11
public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int N = 0, M = 0;
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken()); // 표의 정사각형 한 크기
		M = Integer.parseInt(st.nextToken()); // 입력의 개수

		
		// 1. 계산하기 편하게 한 변의 크기가 N+1 인 정사각형을 하나 만들자.
		int[][] squareArray = new int[N+1][];
		for (int i = 0; i < squareArray.length; i++) {
			squareArray[i] = new int[N+1];
		}
		
		// 2. 초기화하자.
		for (int i = 1; i < squareArray.length; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 1; j < squareArray.length; j++) {
				squareArray[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
//		 3. 테스트 출력
//		for (int i = 0; i < squareArray.length; i++) {
//			System.out.println(Arrays.toString(squareArray[i]));
//		}
		
		// 4. 누적합을 가지고 있는 배열을 생성
		int[][] S = new int[N+1][];
		for (int i = 0; i < S.length; i++) {
			S[i] = new int[N+1];
		}
		
		for (int i = 1; i < S.length; i++) {
			for (int j = 1; j < S.length; j++) { // 현재 칸은 S[i][j]
				S[i][j] = S[i][j-1] + S[i-1][j] - S[i-1][j-1] + squareArray[i][j];
			}
		}
		
//		// 6. 테스트 출력
//		for (int i = 0; i < squareArray.length; i++) {
//			System.out.println(Arrays.toString(S[i]));
//		}
		
		// 7. 이제 빼면 됨
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			x1 = Integer.parseInt(st.nextToken());
			y1 = Integer.parseInt(st.nextToken());
			x2 = Integer.parseInt(st.nextToken());
			y2 = Integer.parseInt(st.nextToken());
			System.out.println((S[x2][y2] - S[x1-1][y2] - S[x2][y1-1] + S[x1-1][y1-1]));
		}
	}
}
```

## 5. [백준] 나머지 합(10986번)
[백준 - 구간 합 구하기 5](https://www.acmicpc.net/problem/10986)
- 수학적인 풀이를 요구하는 문제 중 하나였다.
- 자료형의 중요성에 대해 제대로 깨닫게 되었다.
- 풀이 자체도 쉽지 않았다. 나중에 여유가 되면 풀어 보자.