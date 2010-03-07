#include <stdio.h>
#include <QtCore>

#include <regions.hpp>


int main()
{
    RegionsTable table;
    const RegionInfo *ri;

    ri = table.lookup ("1");
    if (ri)
        printf ("Region 1 is %s\n", ri->name ().toUtf8 ().constData ());
    else
        printf ("Region 1 is not found\n");

    return 0;
}

