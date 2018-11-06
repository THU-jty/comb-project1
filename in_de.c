#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<windows.h>
using namespace std;
typedef long long ll;

ll jie[25];
int n, c[100], b[25], vis[25], id[25];

void init()
{
    jie[0] = 1;
    for( int i = 1; i <= 20; i ++ ){
        jie[i] = jie[i-1]*1LL*i;
    }
    memset( b, 0, sizeof(b) );
    memset( vis, 0, sizeof(vis) );
}

int increasing_nxt_permutation( int *a )
{
    int i, j;

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
    int tmp = 0, p = n;
    for( i = n; i >= 2; i -- ){
        if( i == n || b[i] < b[i+1] ){
            tmp = 0;
            p = n;
        }
        while( 1 ){
            if( a[p] == 0 ) tmp ++;
            if( tmp == b[i]+1 ) break;
            p --;
        }
        a[p] = i;
        tmp --;
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
    int tmp = 0, p = n;
    for( i = n; i >= 2; i -- ){
        if( i == n || b[i] < b[i+1] ){
            tmp = 0;
            p = n;
        }
        while( 1 ){
            if( a[p] == 0 ) tmp ++;
            if( tmp == b[i]+1 ) break;
            p --;
        }
        a[p] = i;
        tmp --;
    }
    for( i = 1; i <= n; i ++ ){
        if( a[i] == 0 ){
            a[i] = 1;
            break;
        }
    }
    return 0;
}

void dfs( int nw, ll* cnt )
{
    if( nw == n+1 ){
        (*cnt) ++;
        return ;
    }
    for( int i = 1; i <= n; i ++ ){
        if( vis[i] ) continue;
        vis[i] = 1;
        id[nw] = i;
        dfs( nw+1, cnt );
        vis[i] = 0;
    }
}

int main()
{
    int i, j, x;
    ll cnt = 1;
    printf("enter n and x:\n1 decreasing\n2 increasing\n3 recusive\n");
    scanf("%d%d", &n, &x);
    init();
    for( i = 1; i <= n; i ++ ) c[i] = i;
    DWORD s, t;
    s = GetTickCount();
    if( x == 0 ){
        while(1){
            //if( !increasing_nxt_permutation( c ) ){
            if( !decreasing_nxt_permutation( c ) ){
                //for( i = 1; i <= n; i ++ ) printf("%d ", c[i]); puts("");
                cnt ++;
            }
            else break;
        }
    }
    else if( x == 1 ){
        while(1){
            if( !increasing_nxt_permutation( c ) ){
                //for( i = 1; i <= n; i ++ ) printf("%d ", c[i]); puts("");
                cnt ++;
            }
            else break;
        }
    }
    else{
        cnt = 0;
        dfs( 1, &cnt );
    }
    t = GetTickCount();
    printf("%lld consume time %dms\n", cnt, t-s);
}
