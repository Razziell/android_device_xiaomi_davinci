#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from sm6150-common
-include device/xiaomi/sm6150-common/BoardConfigCommon.mk

DEVICE_PATH := device/xiaomi/davinci

# Kernel
BOARD_KERNEL_BASE := 0x00000000
BOARD_RAMDISK_OFFSET := 0x02000000
TARGET_KERNEL_SOURCE := kernel/xiaomi/davinci
TARGET_KERNEL_CONFIG := vendor/davinci_user_defconfig
TARGET_KERNEL_CROSS_COMPILE_PREFIX := aarch64-linux-android-
TARGET_KERNEL_VERSION := 4.14

# Platform
TARGET_BOARD_PLATFORM_GPU := qcom-adreno618

# HIDL
DEVICE_MANIFEST_FILE += $(DEVICE_PATH)/manifest.xml

# NFC
TARGET_USES_NQ_NFC := true

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 134217728
BOARD_DTBOIMG_PARTITION_SIZE := 33554432
BOARD_VENDORIMAGE_PARTITION_SIZE := 1610612736

# Power
TARGET_TAP_TO_WAKE_EVENT_NODE := "/dev/input/event2"

# Sepolicy
BOARD_SEPOLICY_DIRS += $(DEVICE_PATH)/sepolicy/vendor

# Vendor init
TARGET_INIT_VENDOR_LIB := libinit_davinci
TARGET_RECOVERY_DEVICE_MODULES := libinit_davinci

# Inherit from the proprietary version
-include vendor/xiaomi/davinci/BoardConfigVendor.mk
