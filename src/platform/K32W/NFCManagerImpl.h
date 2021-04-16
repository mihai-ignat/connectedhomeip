/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      Platform-specific NFCManager implementation for NXP K32W.
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include "ntag_driver.h"

namespace chip {
namespace DeviceLayer {

class NFCManagerImpl final : public NFCManager
{
    friend class NFCManager;

private:
    // ===== Members that implement the NFCManager internal interface.

    CHIP_ERROR _Init();
    CHIP_ERROR _StartTagEmulation(const char * payload, size_t payloadLength);
    CHIP_ERROR _StopTagEmulation();
    bool _IsTagEmulationStarted() const { return mIsStarted; };

    // ===== Members for internal use by this class.

    constexpr static uint8_t kNdefBufferSize = 128;

    uint8_t mNdefBuffer[kNdefBufferSize];
    bool mIsStarted;

    // ===== Members for internal use by the following friends.

    friend NFCManager & NFCMgr();
    friend NFCManagerImpl & NFCMgrImpl();

    typedef enum
    {
        E_APP_NTAG_NO_ERROR,
        E_APP_NTAG_I2C_ERROR,
        E_APP_NTAG_READ_ERROR,
        E_APP_NTAG_WRITE_ERROR
    } eAppNtagError;

    typedef PACKED_STRUCT
    {
        uint8_t headerNdef;
        uint8_t lenRecordType;
        uint8_t lenPayload;
        uint8_t recordName;
        uint8_t uriCode;
        uint8_t uri[19];
    } NfcSmartPosterNdef_t;

    static eAppNtagError AppNtagInitEepromSmartPoster(void);
    static bool          AppNtagIsEepromSmartPosterConfigured(eAppNtagError *pNtagError);
    static bool          AppNtagSmartPosterEepromWrite(NTAG_HANDLE_T ntagHandleInstance);
    static eAppNtagError AppNtagEepromWriteSmartPoster(void);
    static eAppNtagError AppNtagLockWriteAccess(void);
    static eAppNtagError AppNtagUnlockWriteAccess(void);
    static uint16_t      ApNtagSmartPosterGetSize();

    NfcSmartPosterNdef_t smartPoster;
    static NFCManagerImpl sInstance;
    NTAG_HANDLE_T ntagDriverHandleInstance;
};

inline NFCManager & NFCMgr()
{
    return NFCManagerImpl::sInstance;
}

inline NFCManagerImpl & NFCMgrImpl()
{
    return NFCManagerImpl::sInstance;
}

} // namespace DeviceLayer
} // namespace chip
