/*******************************************************************************

    dbgmsg.h - Interface file for debug log facility

    -----------------------------------------------------------------------
    
    Copyright 2018 Paul Alexander

    Redistribution and use in source and binary forms, with or without modi-
    fication, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, 
       this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright 
       notice, this list of conditions and the following disclaimer in the 
       documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its con-
       tributors may be used to endorse or promote products derived from this 
       software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CON-
    SEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTI-
    TUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTER-
    RUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
    OF SUCH DAMAGE.
    
*******************************************************************************/

#ifndef DBGMSG_H

#define DBGMSG_H

/*******************************************************************************
*                                                                              *
*                           Additional header files                            *
*                                                                              *
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*******************************************************************************
*                                                                              *
*                           Function declarations                              *
*                                                                              *
*******************************************************************************/

/*******************************************************************************

    dbgmsg_open_file() - Open log file for concurrent writing.
    
    Return 0 on success, -1 on failure.
    
*******************************************************************************/

int dbgmsg_open_file(const char* file_spec);

/*******************************************************************************

    dbgmsg_open_conn() - Open network connection to log recorder server.
    
    Return 0 on success, -1 on failure.
    
*******************************************************************************/

int dbgmsg_open_conn(const char* server_spec);  

/*******************************************************************************

    dbgmsg_printf() - Write log entry using printf style formatting
    
    Description
    ===========
    
    Write a single log entry of the form:
    
        <utc-time> <host-name>:<program-name>[pid:tid] <message>
        
    where:
   
        <utc-time>     = system UTC time in nanosecond precision, returned
                         by clock_gettime() vDSO library function
        
        <host-name>    = value returned by gethostname() library function
        
        <program-name> = value stored in the process-wide global variable
                         program_invocation_short_name
                         
        pid            = Process ID assigned to main thread of program, re-
                         turned by getpid() library function
                         
        tid            = Process ID assigned to calling thread, returned by
                         SYS_gettid system call
                         
        <message>      = text produced by feeding format and its following 
                         arguments to the vsnprintf() library function, and
                         appending a newline character
    
*******************************************************************************/

void dbgmsg_printf(const char* format, ...);

/*******************************************************************************

    DBGMSG_PRINTF() - 
    
    Convenience macro which conditionally generates log entry
    
    Description
    ===========
    
    If the preprocessor identifier DBGMSG is defined, invoke dbgmsg_printf(),
    but supply __FILE__, __LINE__, and __FUNCTION__ as additional initial
    arguments to be printed.
    
*******************************************************************************/

#ifdef DBGMSG
#define DBGMSG_PRINTF(format, ...) \
dbgmsg_printf("%s:%d:%s() " format,__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__)
#else
#define DBGMSG_PRINTF(format, ...)
#endif // DBGMSG


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DBGMSG_H


