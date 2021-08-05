printer工程

server:
g++ --std=c++11 -I. -DICE_CPP11_MAPPING -c Printer.cpp Server.cpp
g++ --std=c++11 -o Server Printer.o Server.o -lIce++11 -lpthread

client:
g++ --std=c++11 -I. -DICE_CPP11_MAPPING -c Printer.cpp Client.cpp
g++ --std=c++11 -o Client Printer.o Client.o -lIce++11 -lpthread

-----------------------------------
hello工程
slice2cpp Hello.ice

server
g++ --std=c++11 -I. -DICE_CPP11_MAPPING -c Server.cpp Hello.cpp HelloI.cpp
g++ --std=c++11 -o Server HelloI.o Hello.o Server.o -lIce++11 -lpthread

client
g++ --std=c++11 -I. -DICE_CPP11_MAPPING -c Hello.cpp Client.cpp
g++ --std=c++11 -o Client Hello.o Client.o -lIce++11 -lpthread

跑步起来，还有问题。。。。
-----------------------------------
