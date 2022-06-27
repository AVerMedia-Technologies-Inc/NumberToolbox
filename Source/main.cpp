#include "PackageStudioService.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString port = 0;
    QString context = "";
    QString event = "";
    QString info = "";

    for(int i = 0; i < argc; ++i)
    {
        if(strncmp(argv[i], "-port", sizeof(argv+i)) == 0)
        {
            ++i;
            port = QString(argv[i]);

        }
        else if(strncmp(argv[i], "-packageUUID", sizeof(argv+i)) == 0)
        {
            ++i;
            context = QString(argv[i]);
        }
        else if(strncmp(argv[i], "-registerEvent", sizeof(argv+i)) == 0)
        {
            ++i;
            event = QString(argv[i]);
        }
        else if(strncmp(argv[i], "-info", sizeof(argv+i)) == 0)
        {
            ++i;
            info = QString(argv[i]);
        }
    }

    PackageStudioService package(port, context, event, info);
    return a.exec();
}
