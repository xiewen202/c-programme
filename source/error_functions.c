#include <stdarg.h>
#include "common.h"

static void terminate(Boolean useExit3)
{
	char *s;
	s = getenv("EF_DUMPCORE");
	if(s != NULL && *S != '\n')
		abort();
	else if(useExit3)
		exit(EXIT_FAILURE);
	else
		_exit(EXIT_FAILURE);
}

static void outputError(Boolean useErr,int err,Boolean flushStdout,const char *format,va_list ap)
{
#define BUF_SIZE 500
	char buf[BUF_SIZE],userMsg[BUF_SIZE],errText[BUF_SIZE];
	vsnprintf(userMsg,BUF_SIZE,format,ap);
	if(useErr)
		snprintf(errText,BUF_SIZE,"[%s %s]",(err > 0 && err <= MAX_ENAME)?ENAME[ERR]:"?unknown?",strerror(err));
	else
		snprintf(errText,BUF_SIZE,":");

	snprintf(errText,BUF_SIZE,"ERROR%s %s\n",errText,userMsg);

	if(flushStdout)
		fflush(stdout);
	fputs(buf,stderr);
	fflush(stderr);
}

void errMsg(const char *format,...)
{
	va_list argList;
	int saveErrno;

	savedErrno = errno;
	va_start(argList,format);
	outputError(TRUE,errno,TRUE,format,arglist);
	va_end(argList);

	errno = saveErrno;
}

void errExit(const char *format,...)
{
	va_list argList;

	va_start(argList,format);
	outputError(TRUE,errno,TRUE,format,arglist);
	va_end(argList);

	terminate(TRUE);
}

void err_exit(const char *format,...)
{
	va_list argList;

	va_start(argList,format);
	outputError(TRUE,errno,FALSE,format,arglist);
	va_end(argList);

	terminate(FALSE);
}

void errExitEn(int errnum,const char *format,...)
{
        va_list argList;

        va_start(argList,format);
        outputError(TRUE,errnum,TRUE,format,arglist);
        va_end(argList);

        terminate(TRUE);
}

void fatal(const char *format,...)
{
        va_list argList;

        va_start(argList,format);
        outputError(FALSE,errno,TRUE,format,arglist);
        va_end(argList);

        terminate(TRUE);
}

void usageErr(const char *format,...)
{
        va_list argList;

	fflush(stdout);
	fprintf(stderr,"usageErr:");

        va_start(argList,format);
        vfprintf(stderr,format,argList);
        va_end(argList);

	fflush(stderr);
        exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format,...)
{
        va_list argList;

	fflush(stdout);
	fprintf(stderr,"cmdLineErr: ");
        va_start(argList,format);
        vfprintf(stderr,format,argList);
        va_end(argList);

        fflush(stderr);
	exit(EXIT_FAILURE);
}
