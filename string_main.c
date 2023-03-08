#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getGnssVersion (__uint8_t *version);
void getBLEVersion (__uint8_t *version);
void printVersion (__uint8_t *version);
void getRDIVersion(__uint8_t *ble_version, __uint8_t *gnss_version);

void main(void){
    __uint8_t *gnss_version;
    gnss_version = malloc(sizeof(__uint8_t) * 1);
    __uint8_t *ble_version;
    ble_version = malloc(sizeof(__uint8_t) * 1);

    getGnssVersion(gnss_version);
    printf("GNSS Version > ");
    printVersion(gnss_version);

    getBLEVersion(ble_version);
    printf("ble Version > ");
    printVersion(ble_version);

    getRDIVersion(ble_version, gnss_version);
    
}

void printVersion (__uint8_t *version){
    for(int i=0; i<sizeof(version); i++){
        printf("0x%.02x ", version[i]);
    }
    printf("\n");
}

void getGnssVersion (__uint8_t *version){
    for(int i=0; i<sizeof(version); i++){
        *(version+i) = 0x02+i;
    }
}

void getBLEVersion (__uint8_t *version){
    for(int i=0; i<sizeof(version); i++){
        *(version+i) = 0x04+i;
    }
}


void getRDIVersion(__uint8_t *ble_version, __uint8_t *gnss_version){
    __uint8_t *rdi_version;
    char existing[100];
    size_t len = strlen(existing);

    rdi_version = malloc(sizeof(__uint8_t) * 20);

    for(int i=0; i<sizeof(ble_version); i++){
        *(rdi_version+i) = *(ble_version+i);
    }
    int j=0;
    for(int i=sizeof(ble_version); i<(sizeof(gnss_version) + sizeof(ble_version)); i++){
        *(rdi_version+i) = *(gnss_version+j);
        j++;
    }
    *(rdi_version + (sizeof(rdi_version)*2)) = 0xFE;
    printf("RDI Version > ");
    for(int i=0; i<(sizeof(rdi_version)*2)+1; i++){
        printf("0x%.02x ", rdi_version[i]);
    }
    printf("\n");

    sprintf(existing + len , "%X", (unsigned) *(rdi_version+1)); 
    puts(existing);

}