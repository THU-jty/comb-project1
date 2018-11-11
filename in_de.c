#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<windows.h>
using namespace std;
typedef long long ll;

ll jie[25], qe = 0;
int n, c[100], b[25], vis[25], id[25];
int tree[100];
ll tag[100];

void init()
{
    jie[0] = 1;
    for( int i = 1; i <= 20; i ++ ){
        jie[i] = jie[i-1]*1LL*i;
    }
    memset( b, 0, sizeof(b) );
    memset( vis, 0, sizeof(vis) );
    memset( tag, 0, sizeof(tag) );
    memset( tree, 0, sizeof(tree) );
}

void build( int L, int R, int x )
{
    if( L == R ){
        tree[x] = 1;
        return ;
    }
    int mid = (L+R)>>1;
    build( L, mid, x<<1 );
    build( mid+1, R, x<<1|1 );
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

int query( int val, int L, int R, int x )
{
    if( L == R )
        return L;
    int mid = (L+R)>>1;
    if( tree[x<<1|1] >= val ) return query( val, mid+1, R, x<<1|1 );
    else return query( val-tree[x<<1|1], L, mid, x<<1 );
}

void update( int pos, int L, int R, int x )
{
    if( L == R && pos == L ){
        tree[x] = 0;
        return ;
    }
    int mid = (L+R)>>1;
    if( pos <= mid ) update( pos, L, mid, x<<1 );
    else update( pos, mid+1, R, x<<1|1 );
    tree[x] = tree[x<<1] + tree[x<<1|1];
}

int increasing_nxt_permutation( int *a )
{
    int i, j;
    qe ++;
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
    //int tmp = 0, p = n;
    build( 1, n, 1 );
    for( i = n; i >= 2; i -- ){
        int tmp = query( b[i]+1, 1, n, 1 );
        a[tmp] = i;
        update( tmp, 1, n, 1 );
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
    ll mask = ( 1LL<<50 )-2;
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
        //mask ^= ( 1<<p );
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
    printf("enter n and x:\n0 decreasing\n1 increasing\n2 recusive\n");
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


/* 找到了需要更新的节点位置 */
if x为叶子节点 & x代表的点的下标 == pos
	val[x] = 0
	return
/* 若更新点在当前区间的左子区间 */
if pos 属于 l[x]
	return update( pos, l[x] )
/* 若更新点在当前区间的右子区间 */
else
	return update( pos, r[x] )
/* 更新完单个节点后进行线段树的merge操作，递归更新所有之前访问的节点 */
val[x] = val[ l[x] ] + val[ r[x] ]





