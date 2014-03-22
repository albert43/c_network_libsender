#include "libsender.h"

#define SEND_SAMPLE_DATA    "{\"category\":\"database\",\"function\":\"openDb\",\"input\":{\"location\":{\"host\":\"127.0.0.1\",\"path\":\"/englab/management\"},\"name\":\"englab\"},\"session_id\":\"12345\"}"
int main(void)
{
    SEND_RET        Ret;
    struct SEND_S   stSend;
    
    Ret = Send_Open(&stSend, NULL);
    if (Ret != SEND_RET_SUCCESS)
        printf ("Send_Open() failure. Ret = %d\n", Ret);
    
    Ret = Send_SendbyAddr(&stSend, "192.168.0.103", 14000, 
                    SEND_SAMPLE_DATA, 
                    strlen(SEND_SAMPLE_DATA));
    if (Ret != SEND_RET_SUCCESS)
        printf ("Send_SendbyAddr() failure. Ret = %d\n", Ret);
    
    return 0;
}
