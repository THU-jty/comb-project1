#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<windows.h>
using namespace std;
typedef long long ll;

ll jie[25];
int n, c[100];

void init()
{
    jie[0] = 1;
    for( int i = 1; i <= 20; i ++ ){
        jie[i] = jie[i-1]*1LL*i;
    }
}

int b[25];

int increasing_nxt_permutation( int *a )
{
    int i, j;
    int b[25];
    /*get increasing mid number*/
    for( i = 1; i <= n; i ++ ){
        int cnt = 0;
        for( j = i+1; j <= n; j ++ ){
            if( a[j] < a[i] ) cnt ++;
        }
        b[ a[i] ] = cnt;
    }

    /*plus 1*/
    b[2] ++;
    for( i = 2; i <= n; i ++ ){
        if( b[i] >= i ){
            if( i == n ) return 1;
            b[i+1] ++;
            b[i] = 0;
        }
        else break;
    }
    for( i = 1; i <= n; i ++ ) a[i] = 0;

    /* transfer to permutation */
    for( i = n; i >= 2; i -- ){
        int tmp = 0;
        for( j = n; j >= 1; j -- ){
            if( a[j] == 0 ){
                tmp ++;
            }
            if( tmp == b[i]+1 ){
                break;
            }
        }
        a[j] = i;
    }
    for( i = 1; i <= n; i ++ ){
        if( a[i] == 0 ){
            a[i] = 1;
            break;
        }
    }
    return 0;
}


int decreasing_nxt_permutation( int *a )
{
    int i, j;
    int b[25];
    /*get increasing mid number*/
    for( i = 1; i <= n; i ++ ){
        int cnt = 0;
        for( j = i+1; j <= n; j ++ ){
            if( a[j] < a[i] ) cnt ++;
        }
        b[ a[i] ] = cnt;
    }

    /*plus 1*/
    b[n] ++;
    for( i = n; i >= 2; i -- ){
        if( b[i] >= i ){
            if( i == 2 ) return 1;
            b[i-1] ++;
            b[i] = 0;
        }
        else break;
    }
    for( i = 1; i <= n; i ++ ) a[i] = 0;

    /* transfer to permutation */
    for( i = n; i >= 2; i -- ){
        int tmp = 0;
        for( j = n; j >= 1; j -- ){
            if( a[j] == 0 ){
                tmp ++;
            }
            if( tmp == b[i]+1 ){
                break;
            }
        }
        a[j] = i;
    }
    for( i = 1; i <= n; i ++ ){
        if( a[i] == 0 ){
            a[i] = 1;
            break;
        }
    }
    return 0;
}

int main()
{
    int i, j;
    ll cnt = 1;
    scanf("%d", &n);
    init();
    for( i = 1; i <= n; i ++ ) c[i] = i;
    DWORD s, t;
    s = GetTickCount();
    while(1){
        //if( !increasing_nxt_permutation( c ) ){
        if( !decreasing_nxt_permutation( c ) ){
            //for( i = 1; i <= n; i ++ ) printf("%d ", c[i]); puts("");
            cnt ++;
        }
        else break;
    }
    t = GetTickCount();
    printf("%lld consume time %dms\n", cnt, t-s);
}
