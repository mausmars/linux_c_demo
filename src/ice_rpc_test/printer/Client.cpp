#include <Ice/Ice.h>
#include <Printer.h>
#include <stdexcept>

using namespace std;
using namespace Demo;

int
main(int argc, char *argv[]) {
    try {
        Ice::CommunicatorHolder ich(argc, argv);
        // x.x.x.x 是服务端的ip
        std::string conn = std::string("SimplePrinter") + ":tcp -h 127.0.0.1 -p 10000";
        auto base = ich->stringToProxy(conn);
        //auto base = ich->stringToProxy("SimplePrinter:default -p 10000");
        auto printer = Ice::checkedCast<PrinterPrx>(base);
        if (!printer) {
            throw std::runtime_error("Invalid proxy");
        }

        printer->printString("Hello World!");
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}