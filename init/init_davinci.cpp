/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.
   Copyright (C) 2016 The CyanogenMod Project.
   Copyright (C) 2019 The LineageOS Project.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fstream>
#include <unistd.h>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;
    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}
void property_override_dual(char const system_prop[],
    char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void load_davinciglobal() {
    property_override_dual("ro.product.model", "ro.vendor.product.model", "Mi 9T");
    property_override("ro.build.product", "davinci");
    property_override_dual("ro.product.device", "ro.product.vendor.device", "davinci");
    property_override("ro.build.description", "davinci-user 10 QKQ1.190825.002 V11.0.4.0.QFJEUXM release-keys");
    property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "Xiaomi/davinci_eea/davinci:10/QKQ1.190825.002/V11.0.4.0.QFJEUXM:user/release-keys");
    property_override("ro.product.mod_device", "davinci_eea_global");
    property_override("ro.build.type", "user");
    property_override("ro.boot.verifiedbootstate", "green");
}

void load_davinciin() {
    property_override_dual("ro.product.model", "ro.vendor.product.model", "Redmi K20");
    property_override("ro.build.product", "davinciin");
    property_override_dual("ro.product.device", "ro.product.vendor.device",  "davinciin");
    property_override("ro.build.description", "davinciin-user 9 PKQ1.190302.001 V10.3.8.0.PFJINXM release-keys");
    property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "Xiaomi/davinciin/davinciin:9/PKQ1.190302.001/V10.3.8.0.PFJINXM:user/release-keys");
    property_override("ro.product.mod_device", "davinciin_in_global");
}

void load_davinci() {
    property_override_dual("ro.product.model", "ro.vendor.product.model", "Redmi K20");
    property_override("ro.build.product", "davinci");
    property_override_dual("ro.product.device", "ro.product.vendor.device",  "davinci");
    property_override("ro.build.description", "davinci-user 9 PKQ1.190302.001 V10.3.15.0.PFJCNXM release-keys");
    property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "Xiaomi/davinci/davinci:9/PKQ1.190302.001/V10.3.15.0.PFJCNXM:user/release-keys");
}

void vendor_load_properties()
{
    std::ifstream fin;
    std::string buf;

    fin.open("/proc/cmdline");
    while (std::getline(fin, buf, ' '))
        if (buf.find("androidboot.hwc") != std::string::npos)
            break;
    fin.close();

    if (buf.find("CN") != std::string::npos) {
        load_davinci();
    } else if (buf.find("INDIA") != std::string::npos) {
        load_davinciin();
    } else if (buf.find("GLOBAL") != std::string::npos) {
        load_davinciglobal();
    }
}
