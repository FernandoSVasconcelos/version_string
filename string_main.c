#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_SIZE   32
#define HEADER_SIZE    4
#define END_SIZE       1
#define SYSTEM_MODULES 9 /* PBOOT SBOOT SAM BLE GNSS GUI RTP RTP-SBOOT RTP-PBOOT */
#define RDI_LEN (VERSION_SIZE * SYSTEM_MODULES)


typedef __uint8_t version_t[VERSION_SIZE];
void getGnssVersion (version_t version);
void getBLEVersion  (version_t version);
void getRDIVersion(version_t ble_version, version_t gnss_version, char *rdivrs);

void getGnssVersion (version_t version){
    for(int i=0; i<sizeof(version_t); i++) version[i] = '0' + i%10;
    // printf("GNSS Version > %s\r\n", &version[0]);
}

void getBLEVersion (version_t version){
    for(int i=0; i<sizeof(version_t); i++) version[i] = 'a' + i%26;
    // printf("BLE Version > %s\r\n", &version[0]);
}


void getRDIVersion(version_t ble_version, version_t gnss_version, char *rdivrs){
    char ble_header[HEADER_SIZE] = {'B', 'L', 'E', '-'};
    char gnss_header[HEADER_SIZE] = {'G', 'N', 'S', '-'};
    char end_char = ';';

    memcpy(rdivrs, ble_header, HEADER_SIZE);
    memcpy(rdivrs + HEADER_SIZE, ble_version, sizeof(version_t));
    memcpy(rdivrs + HEADER_SIZE + VERSION_SIZE, &end_char, END_SIZE);

    memcpy(rdivrs + HEADER_SIZE + END_SIZE + VERSION_SIZE, gnss_header, HEADER_SIZE);
    memcpy(rdivrs + HEADER_SIZE*2 + END_SIZE + VERSION_SIZE, gnss_version, VERSION_SIZE);
    memcpy(rdivrs + HEADER_SIZE*2 + END_SIZE + VERSION_SIZE*2, &end_char, END_SIZE);

    printf("RDI Version > %s\r\n", &rdivrs[0]);
    
}

void main(void){

    version_t gnss_vrs;
    version_t ble_vrs;
    char rdi_vrs[RDI_LEN] = {0};

    getGnssVersion(gnss_vrs);
    getBLEVersion(ble_vrs);

    getRDIVersion(ble_vrs, gnss_vrs, rdi_vrs);
    
}

