#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from davinci device
$(call inherit-product, device/xiaomi/davinci/device.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

TARGET_BOOT_ANIMATION_RES := 1080

# FOD
TARGET_HAS_FOD := true

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := lineage_davinci
PRODUCT_DEVICE := davinci
PRODUCT_BRAND := Xiaomi
PRODUCT_MANUFACTURER := Xiaomi

PLATFORM_SECURITY_PATCH_OVERRIDE := 2020-07-01

BUILD_FINGERPRINT := "Xiaomi/davinci/davinci:10/QKQ1.190825.002/V12.0.3.0.QFJMIXM:user/release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="davinci-user 10 QKQ1.190825.002 V12.0.3.0.QFJMIXM release-keys" \
    PRODUCT_NAME="davinci"
