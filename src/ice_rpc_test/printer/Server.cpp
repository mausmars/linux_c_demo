
#include <Ice/Ice.h>
#include <Printer.h>

using namespace std;
using namespace Demo;

class PrinterI : public Printer {
public:
    virtual void printString(string s, const Ice::Current &) override;
};

void
PrinterI::printString(string s, const Ice::Current &) {
    cout << s << endl;
}

int
main(int argc, char *argv[]) {
    try {
        Ice::CommunicatorHolder ich(argc, argv);
        //  没有指定ip, 表示接受任何ip的请求
        auto adapter = ich->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "tcp -p 10000");
        auto servant = make_shared<PrinterI>();
        adapter->add(servant, Ice::stringToIdentity("SimplePrinter"));
        adapter->activate();
        ich->waitForShutdown();
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}