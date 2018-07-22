#ifndef WOL
#define WOL




uint8_t charToUint(const char c) 
{
    //subtracting char '0' will give the number
    uint8_t num = c - '0';

    //means that it is 'A-F' and 7 should be 
    //subtracted to get the correct number
    //could also add if statements to check if 'a-f'
    if (num > 9)
        return num - 7;

    return num;
}

uint8_t* parseStr(const char* str) 
{
    uint8_t* arr = (uint8_t*) malloc(6);

    for (int i = 0; i < 17; i+=3) {
        uint8_t temp = 0;
        temp += 16 * charToUint(str[i]);
        temp += charToUint(str[i+1]);

        arr[i / 3] = temp;
    }

    return arr;
}

uint8_t* createPacket(const uint8_t* mac) 
{
    /**
     * mac address has an implied size of 6, we dont need
     * to pass its size
     * 
     * 6 + (6 * 16) = 102
     * 6 for 0xFF 6 times
     * MAC address is added 16 times
     * it is 6 in length
     * total array size of 102
     */
    uint8_t* magicPacket = (uint8_t*) malloc(sizeof(uint8_t) * 102);
    
    for (int i = 0; i < 6; i++)
        magicPacket[i] = 0xFF;

    for (int i = 1; i < 17; i++)
        memcpy(&magicPacket[i * 6], mac, 6);
    

    return magicPacket;
}

void sendPacket(const char* macAddr)
{
    uint8_t* magicPacket = createPacket(parseStr(macAddr));

    #if DEBUG
    printf("\n");
    for (int i = 0; i < 102; i++)
        printf("%d ", magicPacket[i]);
    printf("\n\n");
    #endif
    
    //socket(PF_ROUTE, SOCK_RAW, IPPROTO_UDP)
    int opened = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    testSuccess(opened);

    int permission = 1;
    int successOpt = setsockopt(opened, SOL_SOCKET, SO_BROADCAST, &permission, sizeof(permission));
    testSuccess(successOpt);

    struct sockaddr_in broadcast;
    memset(&broadcast, 0, sizeof(broadcast));
    broadcast.sin_family = AF_INET;
    broadcast.sin_addr.s_addr = inet_addr("192.168.1.255"); //ip address for udp broadcast
    broadcast.sin_port = htons(WAKE_PORT); //port 9 for wake on LAN


    ERROR_CHECK;
    int a = sendto( opened, (unsigned char*)magicPacket, 102, 0, 
                  (struct sockaddr*) &broadcast, 
                  sizeof(broadcast) );

    testSuccess(a);

    ERROR_CHECK;

    printf("Sent WOL packet\n");
}
#endif /* WOL */