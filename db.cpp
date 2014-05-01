//	0 id
//	1 pid
//	2 title
//	3 tlimit
//	4 mlimit
//	5 desp
//	6 input
//	7 output
//	8 sinput
//	9 soutput
//	10 source
//	11 date

//	0 id
//	1 code
//	2 date
//	3 uid
//	4 status
//	5 info
//	6 pid
//	7 lang

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "mysql.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/user.h>

using namespace std;
typedef vector<int> vi;
typedef map<int,int> mii;
typedef long long ll;
template <class T> void checkmax(T &t, T x){if (x > t) t = x;}
template <class T> void checkmin(T &t, T x){if (x < t) t = x;}
template <class T> void _checkmax(T &t, T x){if (t == -1 || x > t) t = x;}
template <class T> void _checkmin(T &t, T x){if (t == -1 || x < t) t = x;}
#define INF (INT_MAX/10)
#define SQR(x) ((x)*(x))
#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define iter(v) __typeof((v).begin())
#define foreach(it, v) for (iter(v) it = (v).begin(); it != (v).end(); it++)
#define clr(ar,val) memset(ar, val, sizeof(ar))
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define mid(x, y) ((x+y)/2)
#define vp vector<P>
#define itr iterator

#define host "localhost"
#define user "root"
#define pwd "Alical"
#define dbase "fzroj"


#define S 100000

int i,j,k,m,n,l;
MYSQL *conn;
char s[S+10], t[S+10];

bool init(){
	conn = mysql_init(NULL);
	if (!conn){
		puts("FT!"); 
		return false;
	}

	conn = mysql_real_connect(conn, host, user, pwd, dbase, 0, NULL, 0);
	if (conn){
		puts("OK!");
		mysql_query(conn, "SET NAMES 'UFT8'");
		mysql_query(conn, "SET CHARACTER SET UFT8");
		return true;
	}
	else puts("Failed!");
	return false;
}


void done(){
	mysql_close(conn);
}

void gao(){
	char *s =(char*) "select id, name, pwd, email, motto, date from user";
	mysql_query(conn, s);
	MYSQL_RES * result = mysql_store_result(conn);

	freopen("user.db", "w", stdout);

	while (MYSQL_ROW row = mysql_fetch_row(result)){
		rep(i, 6)
			puts(row[i]), puts("fuck up, it should be seperate");
	}


	char *t =(char *) "select id, pid, uid, code, lang, status, time, memory, date from code";
	mysql_query(conn, t);
	MYSQL_RES * result2 = mysql_store_result(conn);

	freopen("code.db", "w", stdout);

	while (MYSQL_ROW row = mysql_fetch_row(result2)){
		rep(i, 9){
			if (row[i])
				puts(row[i]); 
			puts("fuck up, it should be seperate");
		}
	}

}

char st[9][S+10], ss[S*10+10];

void add(char *s, char *t){
	if (strlen(s)) s[strlen(s)]='\n';
	int m=strlen(s), n=strlen(t);
	rep(i, n) s[m+i]=t[i];
	rep(i, n){
		if (t[i]=='\'')
			s[m++]='\\';
		s[m++]=t[i];
	}
}

void getInUser(){
	freopen("user.db", "r", stdin);
	freopen("/dev/tty", "w", stdout);
	while (1){
		clr(st, 0);
		rep(i, 6){
			if (gets(s)==NULL) return;
			while (strcmp(s, "fuck up, it should be seperate")!=0){
				add(st[i], s);
				gets(s);
			}
		}
		clr(ss, 0);
		sprintf(ss, "insert into user(uid, uname, upwd, uemail, umotto, udate) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')", st[0], st[1], st[2], st[3], st[4], st[5]);
		mysql_query(conn, ss);
	}
}

void getInCode(){
	freopen("code.db", "r", stdin);
	freopen("/dev/tty", "w", stdout);
	while (1){
		clr(st, 0);
		rep(i, 9){
			if (gets(s)==NULL) return;
			while (strcmp(s, "fuck up, it should be seperate")!=0){
				add(st[i], s);
				gets(s);
			}
		}
		clr(ss, 0);
		sprintf(ss, "insert into code VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", st[0], st[1], st[2],
				st[3], st[4], st[5], st[6], st[7], st[8]);
		mysql_query(conn, ss);
	}
}

int main(){
	if (init()){
	//	gao();
//		getInUser();
		getInCode();
		done();
	}
	return 0;
}

