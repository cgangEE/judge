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

#define CE 1

#define S 1000

int i,j,k,m,n,l;
MYSQL *conn;
char s[S+10], t[S+10];
char judgeHome[100], proHome[100];

bool init(){
	if (NULL==getcwd(judgeHome, 100)){
		puts("GET Judge Home Failed!"); return false;
	}

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

void display(){
		sprintf(s, "SELECT * FROM problem"); 
		mysql_query(conn, s);
		MYSQL_RES * result = mysql_store_result(conn);

		int i=0;
		while(MYSQL_FIELD *fd = mysql_fetch_field(result)){
		cout<<i<<' '<<fd->name<<endl;
			i++;
	}
}

int g(char *s){
	int ret=0;
	rep(i, strlen(s)) ret=ret*10+s[i]-'0';
	return ret;
}
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

int tlimit=3;
int mlimit=4;

//	0 id
//	1 code
//	2 date
//	3 uid
//	4 status
//	5 info
//	6 pid
//	7 lang

int id=0;
int code=1;
int date=2;
int pid=6;
int lang=7;

char names[][30]={"Main.c", "Main.cpp", "Main.java"};
char comps[][30]={"gcc Main.c -o Main", "g++ Main.cpp -o Main", "javac Main.java"};
char fName[30];
FILE *file;

void save(MYSQL_ROW row){
	memcpy(fName, names[row[lang][0]-'0'], 30);
	file = fopen(fName, "w");
	fputs(row[code], file);
	fclose(file);
}

bool comp(MYSQL_ROW row){
	if (system(comps[g(row[lang])])==0) return true;
	sprintf(s, "UPDATE code SET status = '%d', date ='%s' WHERE id='%s'", CE, row[date], row[id]);
	mysql_query(conn, s);
	return false;
}

void runApp(int id, int lang, int time, int memory){
	cout<<id<<' '<<lang<<' '<<time<<' '<<memory<<endl;
	freopen("data.in", "r", stdin);
	freopen("user.out", "w", stdout);

	struct rlimit LIM;
	LIM.rlim_cur = time;
	LIM.rlim_max = LIM.rlim_cur;
	setrlimit(RLIMIT_CPU, &LIM);

	execl("./Main", "", (char*)NULL);
	exit(0);
}

void run(MYSQL_ROW row){
	pid_t pidApp = fork();
	if (pidApp == 0){
		sprintf(s, "SELECT * FROM problem WHERE pid = %s ", row[pid]);
		mysql_query(conn, s);
		MYSQL_RES * result = mysql_store_result(conn);
		MYSQL_ROW row2 = mysql_fetch_row(result);
		runApp(g(row[id]), g(row[lang]), g(row2[tlimit]), g(row2[mlimit]));
	}
	else{
	}
}

void indir(int pid){
	sprintf(proHome, "%s/%d", judgeHome, pid);
	chdir(proHome);
}

void gao(){
	mysql_query(conn, "SELECT * FROM code WHERE status = 0 ORDER BY date");
	MYSQL_RES * result = mysql_store_result(conn);

	while (MYSQL_ROW row = mysql_fetch_row(result)){
		indir(g(row[pid]));
		save(row);
		if (!comp(row)) continue;
		run(row);
	}
}

void done(){
	mysql_close(conn);
}

int main(){
	if (init()){
		repf(i, 1, 3){
			gao();
			sleep(1);
		}
		done();
	}
	return 0;
}
