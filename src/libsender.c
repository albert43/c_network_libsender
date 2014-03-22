#include "libsender.h"

SEND_RET Send_Open(struct SEND_S *pstSend, struct SEND_ATTR_S *pstAttr)
{
    if (pstSend == NULL)
        return SEND_RET_ERR_PARAM;
    
    if (pstAttr)
        memcpy (&pstSend->stAttr, pstAttr, sizeof(struct SEND_ATTR_S));
        
    return SEND_RET_SUCCESS;
}
SEND_RET Send_SendbySocket(struct SEND_S *pstSend, 
                           int iSocket,
                           char *pData,
                           unsigned long ulDataLen)
{
    if (pstSend == NULL)
        return SEND_RET_ERR_PARAM;
    
    if ((pData == NULL) || (ulDataLen == 0))
        return SEND_RET_ERR_PARAM;
    
    if (iSocket == -1)
        return SEND_RET_ERR_PARAM;
    
    if (send(pstSend->iSocket, pData, (size_t)ulDataLen, 0) != ulDataLen)
    {
        DEBUG_PRINTF("%s(): %d, errno: %d\n", __FUNCTION__, __LINE__, errno);
        perror("Send_SendbyAddr");
        closesocket(pstSend->iSocket);
        return SEND_RET_ERR_SOCKET_SEND;
    }
    
    return SEND_RET_SUCCESS;
}

SEND_RET Send_SendbyAddr(struct SEND_S *pstSend, 
                         char *pszDestAddr, unsigned long ulDestPort,
                         char *pData, unsigned long ulDataLen,
                         BOOL bCloseSocket)
{
    int     iRet;
    struct sockaddr_in     stSockAddr;
    
    if (pstSend == NULL)
        return SEND_RET_ERR_PARAM;
    
    if ((pszDestAddr == NULL) || (ulDestPort == 0))
        return SEND_RET_ERR_PARAM;
    
    if ((pData == NULL) || (ulDataLen == 0))
        return SEND_RET_ERR_PARAM;
    
    //  Create socket
    pstSend->iSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (pstSend->iSocket == -1)
        return SEND_RET_ERR_SOCKET;
    
    //  Transfer IP address and port to struct sockaddr.
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_addr.s_addr = inet_addr(pszDestAddr);
    stSockAddr.sin_port = htons(ulDestPort);
    
    if (connect(pstSend->iSocket, (struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)) == -1)
        return SEND_RET_ERR_SOCKET_CONNECT;

    if ((iRet = send(pstSend->iSocket, pData, (size_t)ulDataLen, 0)) != ulDataLen)
    {
        DEBUG_PRINTF("%s(): %d, errno: %d\n", __FUNCTION__, __LINE__, errno);
        perror("Send_SendbyAddr");
        closesocket(pstSend->iSocket);
        return SEND_RET_ERR_SOCKET_SEND;
    }
    
    if (bCloseSocket == TRUE)
        closesocket(pstSend->iSocket);

    return SEND_RET_SUCCESS;
}
