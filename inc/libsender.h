#ifndef __AL_NETWORK_SENDER_LIB_H__
#define __AL_NETWORK_SENDER_LIB_H__

//
//  Header files.
//
//  Common
#include <stdio.h>                //  standard buffered input/output 
#include <stdlib.h>               //  standard library definitions 
#include <string.h>               //  string operations 
#include <errno.h>                //  system error numbers
#include <fcntl.h>                //  file control options
#include <time.h>                 //  time types 

//  Linux
#ifdef OS_LINUX
#include <sys/types.h>            //  data types
#include <sys/stat.h>             //  data returned by the stat() function
#include <sys/wait.h>             //  declarations for waiting
#include <pthread.h>              //  threads
#include <semaphore.h>            //  semaphores (REALTIME)
#include <dlfcn.h>                //  dynamic linking
#include <sys/ioctl.h>
#include <sys/poll.h>

#include <sys/socket.h>           //  Internet Protocol family
#include <netdb.h>                //  definitions for network database operations 
#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#endif

//  Windows
#ifdef OS_WINDOWS
#include <WinSock2.h>
#endif

//
//  Definition.
//
//  Common
#define MAX_BUF_LEN             2048
#define DEBUG_PRINTF(fmt,ARG...)		printf(fmt,##ARG)

//  Linux
#ifdef OS_LINUX
#define BOOL                    int
#define TRUE                    1
#define FALSE                   0

#define INVALID_SOCKET          -1
#define SOCKET_ERROR            -1
#define closesocket(sock)       close(sock)
#endif

//  Windows
#ifdef OS_WINDOWS
#include <WinSock2.h>
#define WSA_VERSION MAKEWORD(2, 2)  // using winsock 2.2
#endif // OS_WINDOWS

typedef enum
{
    SEND_RET_ERR_START = -100,
    SEND_RET_ERR_SYSTEM,
    SEND_RET_ERR_SOCKET,
    SEND_RET_ERR_SOCKET_INIT,
    SEND_RET_ERR_SOCKET_CONNECT,
    SEND_RET_ERR_SOCKET_SEND,
    SEND_RET_ERR_INTERNAL,
    SEND_RET_ERR_NOTFOUND,
    SEND_RET_ERR_PARAM,
    SEND_RET_ERR_PROCEDURE,
    SEND_RET_ERR_END,
    SEND_RET_SUCCESS = 0
}SEND_RET;

struct SEND_ATTR_S
{
    unsigned long       ulSendBuffSize;
};

struct SEND_S
{
    int                 iSocket;
    struct SEND_ATTR_S  stAttr;
};

SEND_RET Send_Open(struct SEND_S *pstSend, struct SEND_ATTR_S *pstAttr);

SEND_RET Send_Close(struct SEND_S *pstSend);

//  Description:
//      Send data to the destination by the given socket description.
//  i/p:
//      iSocket : The socket description. This description won't be clse after sending.
SEND_RET Send_SendbySocket(struct SEND_S *pstSend, 
                           int iSocket,
                           char *pData,
                           unsigned long ulDataLen);

//  Description:
//      Send data to the destination by the given IP and port.
//  i/p:
//      bCloseSocket    : TRUE, the socket description will be closed after sending.
//                        FALSE, the socket description will NOT be closed after sending.
SEND_RET Send_SendbyAddr(struct SEND_S *pstSend, 
                         char *pszDestAddr, unsigned long ulDestPort,
                         char *pData, unsigned long ulDataLen,
                         BOOL bCloseSocket);
#endif  //  __AL_NETWORK_SENDER_LIB_H__
