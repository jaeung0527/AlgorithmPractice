/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>

using namespace std;

struct Node{
    int parent = -1;
    int left = 0, right = 0, level = 0;
    Node(){};
};

Node tree[10001];

void init()
{
    for(int i = 0; i < 10001; i++)
        tree[i] = Node(); 
}

void setLevel(int n, int prev)
{
    tree[n].level = prev + 1;
    if(tree[n].left) setLevel(tree[n].left, prev + 1);
    if(tree[n].right) setLevel(tree[n].right, prev + 1);
}

int subTree(int n)
{
    if(tree[n].left)
    {
        if(tree[n].right)
            return subTree(tree[n].left) + subTree(tree[n].right) + 1;
        else
            return subTree(tree[n].left) + 1;
    }
    return 1;
}

int LCA(int n1, int n2)
{
    if(tree[n1].level < tree[n2].level)
    {
        int tmp = n1;
        n1 = n2;
        n2 = tmp;
    }
    while(tree[n1].level > tree[n2].level)
        n1 = tree[n1].parent;

    while(n1 != n2)
    {
        n1 = tree[n1].parent;
        n2 = tree[n2].parent;
    }
    return n1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();
        int V, E, n1, n2;
        cin >> V >> E >> n1 >> n2;
        while(E--)
        {
            int parent, child;
            cin >> parent >> child;

            if(!tree[parent].left) tree[parent].left = child;
            else tree[parent].right = child;
            tree[child].parent = parent; 
        }
        setLevel(1, 0);
        int ans = LCA(n1, n2);
		cout << "#" << test_case << ' ' << ans << ' ' << subTree(ans) << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}