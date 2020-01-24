#! /system/bin/sh

sleep 2
# Attest method hack google pay
# stop Google Pay
/system/bin/am force-stop /data/data/com.google.android.apps.walletnfcrel
sleep 2

if [ -w /data/data/com.google.android.gms/databases/dg.db ]; then
    rm -rf /data/data/com.google.android.gms/app_dg_cache/*

    # set 777 permissions on dg.db
    chmod 777 /data/data/com.google.android.gms/databases/dg.db
    sleep 2

    sqlite3 -batch /data/data/com.google.android.gms/databases/dg.db "update main set c=0 where a like '%attest%'"
    sleep 2
    
    if [ /vendor/bin/toybox_vendor stat -c "%a" $database != "440" ]; then
        chmod 440 /data/data/com.google.android.gms/databases/dg.db
    fi
fi
