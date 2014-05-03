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
	LIM.rlim_cur = 1;
	LIM.rlim_max = LIM.rlim_cur;
	setrlimit(RLIMIT_CPU, &LIM);

	execlp("java", "java", "Main",  (char*)0);
}

void judge(pid_t pid){
	int status;
	struct user_regs_struct reg;
	struct rusage ruse;
	while (1){
		wait4(pid, &status, 0, &ruse);

		if (WIFEXITED(status)){
		   	puts("FUCK IT's OK!");
			break;
		}

		int exitcode = WEXITSTATUS(status);
		cout<<exitcode<<endl;
		if (exitcode == SIGXCPU){
			puts("FUCK It's be killed!");
			break;
		}

		if (WIFSIGNALED(status)){
			int sig = WTERMSIG(status);
			if (sig==SIGXCPU || sig==SIGKILL) {
				puts("May TLE!");
				break;
			}
		}
	}
}

int main(){
	system("javac Main.java");
	pid_t pid = fork();
	if (pid==0)
		run();
	else{
		judge(pid);
	}
	return 0;
}
