#! /system/bin/sh

sleep 2
# Attest method hack google pay
if [ -f /data/data/com.google.android.gms/databases/dg.db ]; then
    # stop Google Pay
    /system/bin/am force-stop /data/data/com.google.android.apps.walletnfcrel
    sleep 2

    rm -rf /data/data/com.google.android.gms/app_dg_cache/*
    sleep 2

    # set 777 permissions on dg.db
    /system/bin/chmod 777 /data/data/com.google.android.gms/databases/dg.db
    sleep 2

    /system/bin/sqlite3 /data/data/com.google.android.gms/databases/dg.db "update main set c='0' where a like '%attest%';"
    sleep 2

    /system/bin/chmod 440 /data/data/com.google.android.gms/databases/dg.db
fi
