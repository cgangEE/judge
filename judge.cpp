//	0 id"", 
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

int ptime=2, pmem=3;


int cid=0, pid=1, uid=2, ctext=3, clang=4, cstatus=5, cctime=6, cmem=7, cdate=8;

char names[][30]={"Main.c", "Main.cpp", "Main.java"};
char comps[][30]={"gcc Main.c -o Main", "g++ Main.cpp -o Main", "javac Main.java"};
char fName[30];
FILE *file;

void save(MYSQL_ROW row){
	memcpy(fName, names[row[clang][0]-'0'], 30);
	file = fopen(fName, "w");
	fputs(row[ctext], file);
	fclose(file);
}

#define PD 0
#define CE 1
#define TLE 2
#define AC 3
#define WA 4
#define RE 5
#define PE 6

void update_sql(int ACflg, MYSQL_ROW row){
	sprintf(s, "UPDATE code SET cstatus = '%d' WHERE cid='%s'", ACflg, row[cid]);
	mysql_query(conn, s);
}

bool comp(MYSQL_ROW row){
	if (system(comps[g(row[clang])])==0) return true;
	update_sql(CE, row);
	return false;
}

void run(int id, int lang, int time, int memory){
	freopen("data.in", "r", stdin);
	freopen("user.out", "w", stdout);

	struct rlimit LIM;

	if (lang==2) LIM.rlim_cur = time * 3;
	else LIM.rlim_cur = time;

	LIM.rlim_max = LIM.rlim_cur;
	setrlimit(RLIMIT_CPU, &LIM);

	LIM.rlim_cur = memory * 1024 * 1024 * 3 / 2;
	LIM.rlim_max = memory * 1024 * 1024 * 2;
	if (lang<=1) setrlimit(RLIMIT_AS, &LIM);

	if (lang<=1) execl("./Main", "", (char*)NULL);
	else execlp("java", "java", "Main", (char*)NULL);

	exit(0);
}

int judge(pid_t pidApp){
	int status, sig, exitcode, ACflg=AC;
	struct user_regs_struct reg;
	struct rusage ruse;

	while (1)
	{
		wait4(pidApp, &status, 0, &ruse);


		exitcode = WEXITSTATUS(status);

		if (exitcode == SIGXCPU){
			ACflg = TLE;
			break;
		}

		if (exitcode!=0){
			ACflg = RE;
			break;
		}

		if (WIFEXITED(status)) break;

		if (WIFSIGNALED(status)){
			sig = WTERMSIG(status);
			switch (sig){

				case SIGCHLD:
				case SIGALRM:
					alarm(0);
				case SIGKILL:
				case SIGXCPU:
					ACflg = TLE;
					break;
				default:
					ACflg = RE;
			}
			cout<<(strsignal(sig))<<endl;
			break;
		}
	}
	return ACflg;
}

int judge_solution(){
	int ret = AC;
	FILE *f1, *f2;
	f1 = fopen("data.out", "r");
	f2 = fopen("user.out", "r");
	if (!f1 || !f2) return RE;
	for(;;){
		char c1=fgetc(f1), c2=fgetc(f2);
		while ((isspace(c1) || isspace(c2))){
			if (c1 != c2){
				if ((c1=='\r' && c2=='\n')) c1=fgetc(f1);
				else if ((c1=='\n' && c2=='\r')) c2=fgetc(f2);
				else if (c1==EOF){
					do c2=fgetc(f2) ;
					while (isspace(c2));
					break;
				}
				else if (c2==EOF){
					do c1=fgetc(f1); while (isspace(c1));
					break;
				}
				else return PE;
			}
			if (isspace(c1)) c1 = fgetc(f1);
			if (isspace(c2)) c2 = fgetc(f2);
		}
		if (c1==EOF && c2==EOF) return AC;
		if (c1 != c2) return WA;
	}
}

void gao(MYSQL_ROW row){
	pid_t pidApp = fork();
	if (pidApp == 0){
		sprintf(s, "SELECT * FROM problem WHERE pid = %s ", row[pid]);
		mysql_query(conn, s);
		MYSQL_RES * result = mysql_store_result(conn);
		MYSQL_ROW row2 = mysql_fetch_row(result);
		run(g(row[cid]), g(row[clang]), g(row2[ptime]), g(row2[pmem]));
	}
	else{
		int ACflg = judge(pidApp);
		if (ACflg==AC) 
			ACflg = judge_solution();
		update_sql(ACflg, row);
	}
}

void indir(int pid){
	sprintf(proHome, "%s/%d", judgeHome, pid);
	chdir(proHome);
}

void gao(){
	mysql_query(conn, "SELECT * FROM code WHERE cstatus = 0 ORDER BY cdate");
	MYSQL_RES * result = mysql_store_result(conn);

	while (MYSQL_ROW row = mysql_fetch_row(result)){
		indir(g(row[pid]));
		save(row);
		if (!comp(row)) continue;
		gao(row);
	}
}

void done(){
	mysql_close(conn);
}

int main(){
	if (init()){
		for(;;){
			gao();
			sleep(1);
		}
		done();
	}
	return 0;
}

