#include <QtCore>

#include "log.hpp"


// --------------------------------------------------
// Log
// --------------------------------------------------
static Log *_log;


Log* Log::instance ()
{
    if (!_log)
        _log = new Log;

    return _log;
}


Log::Log ()
    : f (0)
{
    enable ();
}


void Log::initFile ()
{
    f = new QFile ("/tmp/yandex-traffic-widget.log");

    if (!f->open (QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly)) {
        delete f;
        f = NULL;
    }
}


void Log::enable ()
{
    if (f)
        return;

    initFile ();
}


void Log::disable ()
{
    f->close ();
    delete f;
    f = NULL;
}


void Log::add (const QString &line)
{
    if (!f)
        return;

    // Build timestamp
    QString ts = QDateTime::currentDateTime ().toString ("dd:MM:yy hh.mm.ss.zzz: ");

    f->write (ts.toUtf8 ());
    f->write (line.toUtf8 ());
    f->write ("\n");
    f->flush ();
}
