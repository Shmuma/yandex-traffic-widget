#ifndef __LOG_H__
#define __LOG_H__


class Log
{
private:
    QFile *f;

    Log ();
    void initFile ();

public:
    static Log* instance ();

    void add (const QString &line);

    void disable ();
    void enable ();
};


#endif // __LOG_H__
