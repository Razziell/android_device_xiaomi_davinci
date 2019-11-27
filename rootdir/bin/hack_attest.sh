#! /system/bin/sh

sleep 120
# Attest method hack google pay
if [ -w /data/data/com.google.android.gms/databases/dg.db ]; then
    rm -rf /data/data/com.google.android.gms/app_dg_cache/*
    sqlite3 -batch /data/data/com.google.android.gms/databases/android_pay "update Wallets set fails_attestation='0'"
    sqlite3 -batch /data/data/com.google.android.gms/databases/dg.db "update main set c=0 where a like '%attest%'"
    if [ /vendor/bin/toybox_vendor stat -c "%a" $database != "440" ]; then
        chmod 440 /data/data/com.google.android.gms/databases/dg.db
    fi
fi
