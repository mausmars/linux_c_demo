//
// Created by Admin on 2021/6/22.
//

#ifndef LINUXC_DEMO_INTERFACE_H
#define LINUXC_DEMO_INTERFACE_H

enum ClassType {
    ClassType_Father = 1,
    ClassType_Child = 2,
};

typedef struct FatherCls Father;
typedef struct ChildCls Child;

typedef struct FatherCls {
    int age;
    string name;

    void (*funA)(Father *father);

    void (*funB)(Father *father);
} Father;

typedef struct ChildCls {
    Father *super;

    void (*funA)(Child *child);

    void (*funB)(Child *child);
} Child;

void funFatherA(Father *father) {
    printf("funFatherA age=%d \n", father->age);
}

void funFatherB(Father *father) {
    printf("funFatherB age=%d \n", father->age);
}

void funChildA(Child *child) {
    printf("funChildA age=%d \n", child->super->age);
}

void funChildB(Child *child) {
    printf("funChildB age=%d \n", child->super->age);
}

char* factoryObj(enum ClassType type) {
    char* obj;
    switch (type) {
        case ClassType_Father: {
            Father *o = (Father *) cover_malloc(sizeof(Father));
            o->age = 1;
            o->funA = funFatherA;
            o->funB = funFatherB;
            obj = o;
            break;
        }
        case ClassType_Child: {
            Father *super = (Father *) cover_malloc(sizeof(Father));
            super->age = 1;
            super->funA = funFatherA;
            super->funB = funFatherB;

            Child *o = (Child *) cover_malloc(sizeof(Child));
            o->super = super;
            o->funA = funChildA;
            o->funB = funChildB;
            obj = o;
            break;
        }
    }
    return obj;
}

void interfaceTest() {
    Father *father = factoryObj(ClassType_Father);
    father->funA(father);
    father->funB(father);

    Child *child = factoryObj(ClassType_Child);
    child->funA(child);
    child->funB(child);
}

#endif //LINUXC_DEMO_INTERFACE_H
