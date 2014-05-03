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
	execl("./judge", "",  (char*)0);
	exit(0);
}

void gao(){
	pid_t pid = fork();
	if (pid==0) run();

	int status;
	struct user_regs_struct reg;
	struct rusage ruse;
	wait4(pid, &status, 0, &ruse);
	gao();
}

int main(){
	gao();
	return 0;
}

