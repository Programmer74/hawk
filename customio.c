#include "customio.h"

void printstr(char* s) {
	write(STDOUT_FILENO, s, strlen(s));
}
void printstr_err(char* s) {
	write(STDERR_FILENO, s, strlen(s));
}

void printint(int x) {
	char* tmp = (char*)calloc(50, sizeof(char));
	sprintf(tmp, "%d", x);
	write(STDOUT_FILENO, tmp, strlen(tmp));
	free(tmp);
}

void printint_err(int x) {
	char* tmp = (char*)calloc(50, sizeof(char));
	sprintf(tmp, "%d", x);
	write(STDERR_FILENO, tmp, strlen(tmp));
	free(tmp);
}

void printdouble(double x) {
	char* tmp = (char*)calloc(50, sizeof(char));
	sprintf(tmp, "%lf", x);
	int n = 1;
	int i = 0;
	for (i = strlen(tmp) - 1; i >= 0; i--) {
		//write(STDOUT_FILENO, &tmp[i], 1);
		//printf(">%c", tmp[i]);
		if (tmp[i] == '.') break;
		if (tmp[i] != '0') {
			i++;
			break;
		}
		
	}
	//exit(0);
	write(STDOUT_FILENO, tmp, i);
	free(tmp);
}

