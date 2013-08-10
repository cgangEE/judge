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

int main() {
	int child=fork();
	if (child==0){
		cout<<"child"<<' '<<child<<endl;

	}
	else{
		cout<<"father"<<' '<<child<<endl;
	}
	return 0;
}
