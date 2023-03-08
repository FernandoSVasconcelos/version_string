#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION_SIZE 8

void getGnssVersion (__uint8_t *version);
void getBLEVersion (__uint8_t *version);
void printVersion (__uint8_t *version);
void getRDIVersion(__uint8_t *ble_version, __uint8_t *gnss_version);

void printVersion (__uint8_t *version){
    for(int i=0; i<VERSION_SIZE; i++) printf("0x%.02x ", *version++);
    printf("\n");
}

void getGnssVersion (__uint8_t *version){
    for(int i=0; i<VERSION_SIZE; i++) *version++ = 0x02+i;
}

void getBLEVersion (__uint8_t *version){
    for(int i=0; i<VERSION_SIZE; i++) *version++ = 0x04+i;
}


void getRDIVersion(__uint8_t *ble_version, __uint8_t *gnss_version){
    __uint8_t buffer[32], *rdi_version = buffer;

    for(int i=0; i<VERSION_SIZE; i++) *rdi_version++ = *ble_version++;
    for(int i=0; i<VERSION_SIZE; i++) *rdi_version++ = *gnss_version++;

    rdi_version = buffer;
    printf("RDI Version > ");
    for(int i=0; i<VERSION_SIZE*2; i++) printf("0x%.02x ", *rdi_version++);

    printf("\n"); 
    rdi_version = buffer;
    for(int i=0; i<VERSION_SIZE*2; i++) printf("Char = %c\n", '0' + *rdi_version++);

}

void main(void){

    __uint8_t gnss_vrs[8];
    __uint8_t ble_vrs [8];

    getGnssVersion(gnss_vrs);
    printf("GNSS Version > ");
    printVersion(gnss_vrs);

    getBLEVersion(ble_vrs);
    printf("ble Version > ");
    printVersion(ble_vrs);

    getRDIVersion(ble_vrs, gnss_vrs);
    
}

