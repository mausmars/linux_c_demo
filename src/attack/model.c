#include "model.h"

extern string etherTypeToStr(int etherType) {
    char *et = "";
    switch (etherType) {
        case ETHERTYPE_IPv4:
            et = "ETHERTYPE_IPv4";
            break;
        case ETHERTYPE_IPv6:
            et = "ETHERTYPE_IPv6";
            break;
        case ETHERTYPE_ARP:
            et = "ETHERTYPE_ARP";
            break;
        case ETHERTYPE_RARP:
            et = "ETHERTYPE_RARP";
            break;
        case ETHERTYPE_TRILL:
            et = "ETHERTYPE_TRILL";
            break;
        case ETHERTYPE_L2_ISIS:
            et = "ETHERTYPE_L2_ISIS";
            break;
        case ETHERTYPE_8021Q_TAG:
            et = "ETHERTYPE_8021Q_TAG";
            break;
        case ETHERTYPE_NEXT_HOP_FORWARDING:
            et = "ETHERTYPE_NEXT_HOP_FORWARDING";
            break;
        case ETHERTYPE_FLOW_CONTROL:
            et = "ETHERTYPE_FLOW_CONTROL";
            break;
        case ETHERTYPE_8021ad_S_TAG:
            et = "ETHERTYPE_8021ad_S_TAG";
            break;
        case ETHERTYPE_MPLS_UNICAST:
            et = "ETHERTYPE_MPLS_UNICAST";
            break;
        case ETHERTYPE_MPLS_MULTICAST:
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
