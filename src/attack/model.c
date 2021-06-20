#include "model.h"

extern string etherTypeToStr(int etherType) {
    char *et = "";
    switch (etherType) {
        case 0x0800:
            et = "ETHERTYPE_IPv4";
            break;
        case 0x86DD:
            et = "ETHERTYPE_IPv6";
            break;
        case 0x0806:
            et = "ETHERTYPE_ARP";
            break;
        case 0x0835:
            et = "ETHERTYPE_RARP";
            break;
        case 0x22F3:
            et = "ETHERTYPE_TRILL";
            break;
        case 0x22F4:
            et = "ETHERTYPE_L2_ISIS";
            break;
        case 0x8100:
            et = "ETHERTYPE_8021Q_TAG";
            break;
        case 0x86FF:
            et = "ETHERTYPE_NEXT_HOP_FORWARDING";
            break;
        case 0x8808:
            et = "ETHERTYPE_FLOW_CONTROL";
            break;
        case 0x88A8:
            et = "ETHERTYPE_8021ad_S_TAG";
            break;
        case 0x8847:
            et = "ETHERTYPE_MPLS_UNICAST";
            break;
        case 0x8848:
            et = "ETHERTYPE_MPLS_MULTICAST";
            break;
        default:
            et = "Other!";
            printf("Other! 0x%2x \n", etherType);
            break;
    }
    return et;
}

//-----------------------------------------------------
extern ArpMap *createArpMap() {
    return cover_malloc(sizeof(ArpMap));
}

extern void freeArpMap(ArpMap *arpMap) {
    if (arpMap->ip != NULL) {
        cover_free(arpMap->ip);
    }
    if (arpMap->mac != NULL) {
        cover_free(arpMap->mac);
    }
    cover_free(arpMap);
}

//-----------------------------------------------------
extern Array *createArray(int size) {
    Array *a = cover_malloc(sizeof(Array));
    a->size = size;
    a->node = cover_malloc(size * sizeof(Node));
    return a;
}

extern void *getArrayByIndex(Array *array, int index) {
    return array->node[index].obj;
}









