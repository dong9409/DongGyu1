#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define INF int(1e9)
using namespace std;

struct Set { //각 지점의 번호, 무게, 좌표값 저장하는 구조체
	int h = 0, w = 0, x = 0, y = 0;
	bool visit = 0;
};

int N, startweight = 1, minprice = INF; //시작무게는 1로 둔다(드론무게), 최소값을 무한대로 설정

Set *point[21];	// 구조체 Set의 배열, 최대 20이므로 21을 두고 0은 쓰지 않는다.

bool sorting_h(Set *a, Set *b) {
	return a->h < b->h ? true : false; // 번호순대로 소팅, 오름차순.
}

bool sorting_w(Set *a, Set *b) {
	return a->w > b->w ? true : false; // 무게순대로 소팅, 내림차순(무거운 짐 부터 내리기 위해)
}

void inputdata() {
	FILE* inp = fopen("drone.inp", "r");
	fscanf(inp, "%d", &N);
	for (int i = 1; i <= N; i++) {
		point[i] = new Set;
		fscanf(inp, "%d", &point[i]->h);
		fscanf(inp, "%d", &point[i]->w);
		fscanf(inp, "%d", &point[i]->x);
		fscanf(inp, "%d", &point[i]->y);
		startweight += point[i]->w; // 총 무게 계산( 시작무게 1이므로 총 무게가 20이면 21로 설정됨, 짐을 다 내리고 돌아올때를 위해)
	}

	fclose(inp);
	sort(point + 1, point + N + 1, sorting_h); // 번호순대로 소팅
	sort(point + 2, point + N + 1, sorting_w); // h가 2부터 무게순대로 소팅(시작은 무조건 1이므로)
}

void outputdata() {
	FILE* out = fopen("drone.out", "w");
	fprintf(out, "%d", minprice);
	//printf("%d\n", minprice);
	fclose(out);
	return;
}

void delivery(int index, int price, int depth) {
	int current_price;
	if (depth == 1) {
		current_price = price + (abs(point[index]->x - point[1]->x) + abs(point[index]->y - point[1]->y));
		minprice = current_price < minprice ? current_price : minprice;
		return;
	}
	startweight = startweight - point[index]->w; // 총 무게에서 방문한 곳의 무게를 뺌 (마지막일때는 무게가 1이남음)
	point[index]->visit = 1; // 방문 표시
	for (int i = 2; i <= N; i++) {
		if (point[i]->visit != 1) {
			current_price = price + startweight * (abs(point[index]->x - point[i]->x) + abs(point[index]->y - point[i]->y));
			if (minprice > current_price) {
				delivery(i, current_price, depth - 1);
			}
		}
	}
	point[index]->visit = 0; // 리턴전에 방문표시를 지워줌.
	startweight = startweight + point[index]->w; // 리턴전에 무게를 다시 더해줌.
	return;
}

int main() {
	//clock_t start, end;
	//start = clock();
	inputdata();
	delivery(1, 0, N);
	outputdata();
	//end = clock();
	//cout << (double)(end - start) / CLOCKS_PER_SEC;
	return 0;
}