/*
 * Copyright (C) 2019-2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "FingerprintInscreenService"

#include "FingerprintInscreen.h"

#include <android-base/logging.h>
#include <fstream>
#include <cmath>

#define FINGERPRINT_ERROR_VENDOR 8

#define COMMAND_NIT 10
#define PARAM_NIT_630_FOD 1
#define PARAM_NIT_NONE 0

#define DIM_LAYER_PATH "/sys/devices/platform/soc/ae00000.qcom,mdss_mdp/drm/card0/card0-DSI-1/dim_layer_enable"

#define DC_DIMMING_PATH "/sys/devices/platform/soc/soc:qcom,dsi-display/ea_enable"

#define DISPPARAM_PATH "/sys/devices/platform/soc/ae00000.qcom,mdss_mdp/drm/card0/card0-DSI-1/disp_param"
#define DISPPARAM_HBM_FOD_ON "0x20000"
#define DISPPARAM_HBM_FOD_OFF "0xE0000"

#define Touch_Fod_Enable 10
#define Touch_Aod_Enable 11

#define FOD_SENSOR_X 455
#define FOD_SENSOR_Y 1931
#define FOD_SENSOR_SIZE 190

namespace vendor {
namespace lineage {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_1 {
namespace implementation {

int dc_dimming;

template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

FingerprintInscreen::FingerprintInscreen() {
    this->mFodCircleVisible = false;
    TouchFeatureService = ITouchFeature::getService();
    xiaomiFingerprintService = IXiaomiFingerprint::getService();
}

Return<int32_t> FingerprintInscreen::getPositionX() {
    return FOD_SENSOR_X;
}

Return<int32_t> FingerprintInscreen::getPositionY() {
    return FOD_SENSOR_Y;
}

Return<int32_t> FingerprintInscreen::getSize() {
    return FOD_SENSOR_SIZE;
}

Return<void> FingerprintInscreen::onStartEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::switchHbm(bool enabled) {
    if (enabled) {
        set(DISPPARAM_PATH, DISPPARAM_HBM_FOD_ON);
    } else {
        set(DISPPARAM_PATH, DISPPARAM_HBM_FOD_OFF);
    }
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    set(DIM_LAYER_PATH, 1);
    TouchFeatureService->setTouchMode(Touch_Fod_Enable, 1);
    xiaomiFingerprintService->extCmd(COMMAND_NIT, PARAM_NIT_630_FOD);
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    TouchFeatureService->setTouchMode(Touch_Fod_Enable, 100);
    xiaomiFingerprintService->extCmd(COMMAND_NIT, PARAM_NIT_NONE);
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    set(DIM_LAYER_PATH, 1);
    this->mFodCircleVisible = true;
    dc_dimming = get(DC_DIMMING_PATH, 0);
    set(DC_DIMMING_PATH, 0);
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    if (mFodCircleVisible) {
        set(DC_DIMMING_PATH, dc_dimming);
    }
    set(DIM_LAYER_PATH, 0);
    TouchFeatureService->resetTouchMode(Touch_Fod_Enable);
    xiaomiFingerprintService->extCmd(COMMAND_NIT, PARAM_NIT_NONE);
    this->mFodCircleVisible = false;
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t acquiredInfo, int32_t vendorCode) {
    LOG(ERROR) << "acquiredInfo: " << acquiredInfo << ", vendorCode: " << vendorCode << "\n";
    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t error, int32_t vendorCode) {
    LOG(ERROR) << "error: " << error << ", vendorCode: " << vendorCode << "\n";
    return error == FINGERPRINT_ERROR_VENDOR && vendorCode == 6;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t brightness) {
    float alpha;
    int realBrightness = brightness * 2047 / 255;

    if (realBrightness > 500) {
        alpha = 1.0 - pow(realBrightness / 2047.0 * 430.0 / 600.0, 0.455);
    } else {
        alpha = 1.0 - pow(realBrightness / 1680.0, 0.455);
    }

    return 255 * alpha;
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
    return false;
}

Return<void> FingerprintInscreen::setCallback(const sp<IFingerprintInscreenCallback>&) {
    return Void();
}

}  // namespace implementation
}  // namespace V1_1
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace lineage
}  // namespace vendor
