#include <iostream>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/user.h>

using namespace std;

#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define clr(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define sz(a) ((int)(a).size())

void run(){
	struct rlimit LIM;

	LIM.rlim_cur = 3600;
	LIM.rlim_max = LIM.rlim_cur;
	setrlimit(RLIMIT_CPU, &LIM);

	execl("./judge", "",  (char*)0);
	exit(0);
}

void gao(){
	rep(i, 1000000){
		pid_t pid = fork();
		if (pid==0) run();
		sleep(3600);
	}
}

int main(){
	gao();
	return 0;
}

