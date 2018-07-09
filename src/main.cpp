#include "arenatracker.h"
#include <QMessageBox>

#ifdef ASM_CRASH_REPORT
#include "asmCrashReport.h"
#endif

int main(int argc, char *argv[])
{
    ArenaTracker arenaTracker(argc, argv);
#ifdef ASM_CRASH_REPORT
    qDebug("--- asmCrashReport started ---");
    asmCrashReport::setSignalHandler(QString(), [] (const QString &inFileName, bool inSuccess) {
      QString  message;
      if (inSuccess) {
         message = QStringLiteral("Sorry, %1 has crashed. A log file was written to:\n\n%2\n\n"
                                  "Please email this to support@example.com." )
                 .arg(QCoreApplication::applicationName(), inFileName);
      } else {
         message = QStringLiteral("Sorry, %1 has crashed and we could not write a log file to:\n\n%2\n\n"
                                  "Please contact support@example.com." )
                 .arg(QCoreApplication::applicationName(), inFileName);
      }
      QMessageBox::critical(nullptr, QObject::tr("%1 Crashed").arg(QCoreApplication::applicationName()), message);
   });
#endif
    return arenaTracker.run();
}
