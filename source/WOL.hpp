/**
 * easyWOL
 * 
 * Wake on LAN packet sender
 * 
 * Alex Brachet-Mialot
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <functional>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Version3.cpp"

//#include "ConfigFileParser.cpp"

#define DEBUG 1

#ifdef DEBUG
    #include <errno.h>
    #define ERROR_CHECK printf("errno: %d\n", errno)
#else
    #define ERROR_CHECK
#endif

void testSuccess(int a)
{
    #if DEBUG
    a < 0 ? 
    printf("Unsuccesfull\n") :
    printf("Successfull.  given int: %d\n", a);
    #endif
}

#define WAKE_PORT 9

#include "WOL.cpp"


////////////////////////////////////////////////////
//                                                //
//                 DEBUG / TESTING                //
//                                                //
////////////////////////////////////////////////////
#define TEST 1

#ifdef TEST

    #define MY_MAC "2C:FD:A1:5A:16:E0" //Desktop at moms
    #define UBUNTU_LAP "BC:EE:7B:20:E4:B9"
    #define DAD_PC "40:8D:5C:90:FA:03"

    /**
     * Possible UDP broadcast IP's
     * Will change program to dynamically find them later
     */ 
    #define UDP_BCAST_1 "192.168.1.255"
    #define UDP_BCAST_2 "192.168.2.255"
    #define UDP_BCAST_3 "192.168.10.255"
    #define UDP_BCAST_4 "255.255.255.255"

#endif




/**
 * <b> TODO </b>
 * Dynamically find UDP broadcast IP
 * For finding sys calls to dynamically find UDP broadcast IP
 * sudo dtruss ./ifconfig
 * 
 */ 

/**
 * @brief used for Hexadecimal to uint conversion
 * @todo only accepts capital letters
 *       throw error when converstion doesnt return 0-16
 *         meaning invalid MAC address given
 * 
 * @params (char c) takes one char '0-9' or 'A-F'
 * 
 * @returns uint8_t
 */ 
uint8_t charToUint(const char);

/**
 * @brief takes MAC address as string and returns
 *        int representation in an array. Used
 *        for sending the magic packet
 * 
 * @todo pottentially parse MAC to ensure some accuracy, 
 * 
 * @params (char* str) MAC address in human readable string form
 * 
 * @returns array of size 6 of the MAC address
 */
uint8_t* parseStr(const char*);

/**
 * @brief not needed, just calls parseStr()
 * 
 * @todo get rid of it? unless it can be where MAC testing can happen.
 *       valid address format verification can happen in config file creation though
 * 
 * @calls parseStr()
 * @returns uint8_t of parseStr()
 */ 
uint8_t* createMAC(const char*);

/**
 * @brief constructs WOL "Magic Packet"
 *        prefaces with 6 x 0xFF
 *        adds MAC address array from parseStr() 16 times
 * 
 * @params (uint8_t* mac) MAC address aray from parseStr()
 * 
 * @returns uint8_t array of size 102 to be sent 
 */
uint8_t* createPacket(const uint8_t*);


void sendPacket(const char* macAddr);