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
	write(STDOUT_FILENO, tmp, strlen(tmp));
	free(tmp);
}

