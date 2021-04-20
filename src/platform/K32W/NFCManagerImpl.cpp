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

#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <platform/NFCManager.h>

#include <support/CodeUtils.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>
#include <support/CHIPPlatformMemory.h>

namespace chip {
namespace DeviceLayer {

NFCManagerImpl NFCManagerImpl::sInstance;

CHIP_ERROR NFCManagerImpl::_Init()
{
	ntagDriverHandleInstance = NTAG_InitDevice((NTAG_ID_T)0, I2C2);
	assert(ntagDriverHandleInstance);

    return CHIP_NO_ERROR;
}

CHIP_ERROR NFCManagerImpl::_StartTagEmulation(const char * payload, size_t payloadLength)
{
	sInstance.smartPoster.headerNdef    = NFC_NDEF_RECORD_HEADER_SMART_POSTER;
	sInstance.smartPoster.lenRecordType = NFC_NDEF_RECORD_TYPE_LEN;
	sInstance.smartPoster.lenPayload    = payloadLength + sizeof(sInstance.smartPoster.uriCode);
	sInstance.smartPoster.recordName    = NFC_NDEF_RECORD_NAME;
	sInstance.smartPoster.uriCode       = NFC_NDEF_URI_CODE;

	if(payloadLength > NFC_NDEF_MAX_PAYLOAD_LEN)
	{
		return CHIP_ERROR_INTERNAL;
	}
	else
	{
		memcpy(sInstance.smartPoster.uri, payload, payloadLength);
	}

    if (AppNtagInitEepromSmartPoster() != E_APP_NTAG_NO_ERROR)
    {
    	return CHIP_ERROR_INTERNAL;
    }
    else
    {
    	sInstance.mIsStarted = TRUE;
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR NFCManagerImpl::_StopTagEmulation()
{

	/* zero all the fields except  within the NfcSmartPosterNdef_t structure */
	sInstance.smartPoster.headerNdef    = 0x00;
	sInstance.smartPoster.lenRecordType = 0x00;
	sInstance.smartPoster.lenPayload    = 0;
	sInstance.smartPoster.recordName    = '\0';
	sInstance.smartPoster.uriCode       = 0x00;

	eAppNtagError ntagErr = E_APP_NTAG_NO_ERROR;
	ntagErr = AppNtagEepromWriteSmartPoster();
	if (ntagErr != E_APP_NTAG_NO_ERROR)
	{
		return CHIP_ERROR_INTERNAL;
	}

	/* call driver function to close ntagDriverHandleInstance */
	NTAG_CloseDevice(sInstance.ntagDriverHandleInstance);

	return CHIP_NO_ERROR;
}

NFCManagerImpl::eAppNtagError NFCManagerImpl::AppNtagInitEepromSmartPoster(void)
{
    eAppNtagError ntagErr = E_APP_NTAG_NO_ERROR;
    uint8_t byte0 = 0;
    uint8_t i = 0;
    bool_t i2cAddrFound = FALSE;

    do
    {
        HAL_I2C_InitDevice(HAL_I2C_INIT_DEFAULT, kCLOCK_Fro32M, I2C2);

        /* Try to access the device at default I2C address */
        if (NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, 0, &byte0, sizeof(byte0)))
        {
            /* Try now with the 0x02 I2C address */
            NTAG_SetNtagI2cAddress(sInstance.ntagDriverHandleInstance, 0x2);
            if (!NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, 0, &byte0, sizeof(byte0)))
            {
                i2cAddrFound = TRUE;
            }
            else
            {
                /* Loop to try to find a valid i2c address */
                for (i = 0; i < 0xFF; i++)
                {
                    if (i == 2 || i == 0x55) /* Skip default and 0x02 I2C address */
                    {
                        continue;
                    }

                    NTAG_SetNtagI2cAddress(sInstance.ntagDriverHandleInstance, i);
                    if (!NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, 0, &byte0, sizeof(byte0)))
                    {
                        i2cAddrFound = TRUE;
                        break;
                    }
                }
            }

            if (!i2cAddrFound)
            {
                ntagErr = E_APP_NTAG_READ_ERROR;
                break;
            }
        }

            ntagErr = AppNtagEepromWriteSmartPoster();

    } while (0);

    /* Stop I2C */
    HAL_I2C_CloseDevice(I2C2);

    return ntagErr;
}

bool NFCManagerImpl::AppNtagSmartPosterEepromWrite(void)
{
    bool wasWritten = FALSE;


    /* DORU, EU ACUM MI-AM DAT SEAMA. LEN PAYLOAD E ZERO CAND VREM SA DAM WRITE DE ZERO PESTE TOT, DECI NU POT SA CALCULEZ NDEFSIZE..
     * DECI NU E OK MOMENTAN */

    uint32_t ndefSize = sizeof(sInstance.smartPoster.headerNdef) + sizeof(sInstance.smartPoster.lenRecordType) +
    		sizeof(sInstance.smartPoster.lenPayload) + sizeof(sInstance.smartPoster.recordName) +
			sizeof(sInstance.smartPoster.uri);

    //uint32_t ndefSize = sizeof(sInstance.smartPoster);

    uint32_t addrToWrite = NTAG_I2C_BLOCK_SIZE;
    uint8_t buf[4];
    memset(buf, 0, sizeof(buf));
    uint8_t terminatorTLV;
    if(sInstance.smartPoster.lenPayload == 0)
    {
    	terminatorTLV =  0x00;
    }
    else
    {
    	terminatorTLV = 0xFE;
    }

    do
    {
        if (ndefSize < 0xFF)
        {
        	if(sInstance.smartPoster.lenPayload > 0)
        	{
        		buf[0] = 0x3;
        		buf[1] = ndefSize;
        	}
            if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, addrToWrite, buf, 2))
            {
                break;
            }

            addrToWrite += 2;
        }
        else if (ndefSize <= 0xFFFF)
        {
        	if(sInstance.smartPoster.lenPayload > 0)
        	{
        		buf[0] = 0x3;
				buf[1] = 0xFF;
				buf[2] = (uint8_t) (ndefSize & 0x0000FF00) >> 8;
				buf[3] = (uint8_t)(ndefSize & 0x000000FF);
        	}

            if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, addrToWrite, buf, 4))
            {
                break;
            }

            addrToWrite += 4;
        }

        if(sInstance.smartPoster.lenPayload == 0)
        {
        	memset((uint8_t *)(&sInstance.smartPoster), 0, ndefSize);
        }
        if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, addrToWrite, (uint8_t *)(&sInstance.smartPoster), ndefSize))
        {
            break;
        }

        addrToWrite += ndefSize;

        if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, addrToWrite, &terminatorTLV, 1))
        {
            break;
        }

        wasWritten = TRUE;
    } while (0);

    return wasWritten;
}

bool NFCManagerImpl::AppNtagIsEepromSmartPosterConfigured(eAppNtagError *pNtagError)
{
	bool isConfigured = FALSE;
	uint32_t addrToRead = NTAG_I2C_BLOCK_SIZE;
	uint8_t buf[4];
	uint16_t smartPosterNdefSize = ApNtagSmartPosterGetSize();

	if (!NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, addrToRead, buf, sizeof(buf)))
	{
		*pNtagError = E_APP_NTAG_NO_ERROR;

		if (smartPosterNdefSize < 0xFF)
		{
			isConfigured = (buf[1] == smartPosterNdefSize);
		}
		else
		{
			isConfigured = (buf[1] == 0xff &&
					  buf[2] == (uint8_t) ((smartPosterNdefSize & 0x0000FF00) >> 8) &&
					  buf[3] == (uint8_t)(smartPosterNdefSize & 0x000000FF));
		}
	}
	else
	{
		*pNtagError = E_APP_NTAG_READ_ERROR;
	}

	return isConfigured;
}

NFCManagerImpl::eAppNtagError NFCManagerImpl::AppNtagEepromWriteSmartPoster(void)
{
    eAppNtagError ntagErr = E_APP_NTAG_NO_ERROR;

    do
    {
        /* Unlock write access */
        ntagErr = AppNtagUnlockWriteAccess();
        if (ntagErr != E_APP_NTAG_NO_ERROR)
        {
            break;
        }

        /* Write the smart poster value */
        if (!AppNtagSmartPosterEepromWrite())
        {
            ntagErr = E_APP_NTAG_WRITE_ERROR;
            break;
        }

        /* Lock write access */
        ntagErr = AppNtagLockWriteAccess();
    } while(0);

    return ntagErr;
}

uint16_t NFCManagerImpl::ApNtagSmartPosterGetSize()
{
    return sizeof(sInstance.smartPoster);
}

NFCManagerImpl::eAppNtagError NFCManagerImpl::AppNtagLockWriteAccess(void)
{
    eAppNtagError ntagErr = E_APP_NTAG_NO_ERROR;

    uint8_t bytes[NTAG_I2C_BLOCK_SIZE];
    FLib_MemSet(bytes, 0x0, sizeof(bytes));

    do
    {
        /* Try to read the block 0 */
        if (NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, 0, bytes, sizeof(bytes)))
        {
            ntagErr = E_APP_NTAG_READ_ERROR;
            break;
        }

        /* Set the Capability Container (CC) */
        bytes[3] = 0xE1; /* Indicates that NDEF data is present inside the tag */
        bytes[4] = 0x10; /* Indicates to support the version 1.0 */
        bytes[5] = 0xE9; /* Indicates 1864 bytes of memory size assigned to the data area */
        bytes[6] = 0x0F; /* Indicates read only access granted */

        if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, 0, bytes, sizeof(bytes)))
        {
            ntagErr = E_APP_NTAG_WRITE_ERROR;
        }
    } while (0);

    return ntagErr;
}

NFCManagerImpl::eAppNtagError NFCManagerImpl::AppNtagUnlockWriteAccess(void)
{
    eAppNtagError ntagErr = E_APP_NTAG_NO_ERROR;

    uint8_t bytes[NTAG_I2C_BLOCK_SIZE];
    FLib_MemSet(bytes, 0x0, sizeof(bytes));

    do
    {
        /* Try to read the block 0 */
        if (NTAG_ReadBytes(sInstance.ntagDriverHandleInstance, 0, bytes, sizeof(bytes)))
        {
            ntagErr = E_APP_NTAG_READ_ERROR;
            break;
        }

        /* Set the Capability Container (CC) */
        bytes[12] = 0xE1; /* Indicates that NDEF data is present inside the tag */
        bytes[13] = 0x10; /* Indicates to support the version 1.0 */
        bytes[14] = 0xE9; /* Indicates 1864 bytes of memory size assigned to the data area */
        bytes[15] = 0x00; /* Indicates read and write access granted without any security */

        if (NTAG_WriteBytes(sInstance.ntagDriverHandleInstance, 0, bytes, sizeof(bytes)))
        {
            ntagErr = E_APP_NTAG_WRITE_ERROR;
        }

    } while (0);

    return ntagErr;
}

} // namespace DeviceLayer
} // namespace chip
