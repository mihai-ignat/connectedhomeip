/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

// THIS FILE IS GENERATED BY ZAP

#include <app-common/zap-generated/callback.h>
#include <app-common/zap-generated/cluster-id.h>
#include <lib/support/Span.h>
#include <protocols/interaction_model/Constants.h>

using namespace chip;

// Cluster Init Functions
void emberAfClusterInitCallback(EndpointId endpoint, ClusterId clusterId)
{
    switch (clusterId)
    {
     case ZCL_ADMINISTRATOR_COMMISSIONING_CLUSTER_ID :
        emberAfAdministratorCommissioningClusterInitCallback(endpoint);
        break;
     case ZCL_BASIC_CLUSTER_ID :
        emberAfBasicClusterInitCallback(endpoint);
        break;
     case ZCL_DESCRIPTOR_CLUSTER_ID :
        emberAfDescriptorClusterInitCallback(endpoint);
        break;
     case ZCL_DIAGNOSTIC_LOGS_CLUSTER_ID :
        emberAfDiagnosticLogsClusterInitCallback(endpoint);
        break;
     case ZCL_ETHERNET_NETWORK_DIAGNOSTICS_CLUSTER_ID :
        emberAfEthernetNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
     case ZCL_FIXED_LABEL_CLUSTER_ID :
        emberAfFixedLabelClusterInitCallback(endpoint);
        break;
     case ZCL_FLOW_MEASUREMENT_CLUSTER_ID :
        emberAfFlowMeasurementClusterInitCallback(endpoint);
        break;
     case ZCL_GENERAL_COMMISSIONING_CLUSTER_ID :
        emberAfGeneralCommissioningClusterInitCallback(endpoint);
        break;
     case ZCL_GENERAL_DIAGNOSTICS_CLUSTER_ID :
        emberAfGeneralDiagnosticsClusterInitCallback(endpoint);
        break;
     case ZCL_LEVEL_CONTROL_CLUSTER_ID :
        emberAfLevelControlClusterInitCallback(endpoint);
        break;
     case ZCL_LOCALIZATION_CONFIGURATION_CLUSTER_ID :
        emberAfLocalizationConfigurationClusterInitCallback(endpoint);
        break;
     case ZCL_NETWORK_COMMISSIONING_CLUSTER_ID :
        emberAfNetworkCommissioningClusterInitCallback(endpoint);
        break;
     case ZCL_ON_OFF_CLUSTER_ID :
        emberAfOnOffClusterInitCallback(endpoint);
        break;
     case ZCL_OPERATIONAL_CREDENTIALS_CLUSTER_ID :
        emberAfOperationalCredentialsClusterInitCallback(endpoint);
        break;
     case ZCL_PRESSURE_MEASUREMENT_CLUSTER_ID :
        emberAfPressureMeasurementClusterInitCallback(endpoint);
        break;
     case ZCL_PUMP_CONFIG_CONTROL_CLUSTER_ID :
        emberAfPumpConfigurationAndControlClusterInitCallback(endpoint);
        break;
     case ZCL_SOFTWARE_DIAGNOSTICS_CLUSTER_ID :
        emberAfSoftwareDiagnosticsClusterInitCallback(endpoint);
        break;
     case ZCL_TEMP_MEASUREMENT_CLUSTER_ID :
        emberAfTemperatureMeasurementClusterInitCallback(endpoint);
        break;
     case ZCL_THREAD_NETWORK_DIAGNOSTICS_CLUSTER_ID :
        emberAfThreadNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
     case ZCL_TIME_FORMAT_LOCALIZATION_CLUSTER_ID :
        emberAfTimeFormatLocalizationClusterInitCallback(endpoint);
        break;
     case ZCL_USER_LABEL_CLUSTER_ID :
        emberAfUserLabelClusterInitCallback(endpoint);
        break;
     case ZCL_WIFI_NETWORK_DIAGNOSTICS_CLUSTER_ID :
        emberAfWiFiNetworkDiagnosticsClusterInitCallback(endpoint);
        break;
    default:
        // Unrecognized cluster ID
        break;
    }
}

void __attribute__((weak)) emberAfAdministratorCommissioningClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfBasicClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfDescriptorClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfDiagnosticLogsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfEthernetNetworkDiagnosticsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfFixedLabelClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfFlowMeasurementClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfGeneralCommissioningClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfGeneralDiagnosticsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfLevelControlClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfLocalizationConfigurationClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfNetworkCommissioningClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfOnOffClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfOperationalCredentialsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfPressureMeasurementClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfPumpConfigurationAndControlClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfSoftwareDiagnosticsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfTemperatureMeasurementClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfThreadNetworkDiagnosticsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfTimeFormatLocalizationClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfUserLabelClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfWiFiNetworkDiagnosticsClusterInitCallback(EndpointId endpoint)
{
    // To prevent warning
    (void) endpoint;
}

//
// Non-Cluster Related Callbacks
//

void __attribute__((weak)) emberAfAddToCurrentAppTasksCallback(EmberAfApplicationTask tasks) {}

void __attribute__((weak)) emberAfRemoveFromCurrentAppTasksCallback(EmberAfApplicationTask tasks) {}

EmberAfAttributeWritePermission __attribute__((weak)) emberAfAllowNetworkWriteAttributeCallback(
    EndpointId endpoint, ClusterId clusterId,
                                                                          AttributeId attributeId, uint8_t mask,
                                                                          uint8_t * value, uint8_t type)
{
    return EMBER_ZCL_ATTRIBUTE_WRITE_PERMISSION_ALLOW_WRITE_NORMAL; // Default
}

bool __attribute__((weak)) emberAfAttributeReadAccessCallback(
    EndpointId endpoint, ClusterId clusterId, AttributeId attributeId)
{
    return true;
}

bool __attribute__((weak)) emberAfAttributeWriteAccessCallback(
    EndpointId endpoint, ClusterId clusterId, AttributeId attributeId)
{
    return true;
}

bool __attribute__((weak)) emberAfDefaultResponseCallback(
    ClusterId clusterId, CommandId commandId, EmberAfStatus status)
{
    return false;
}

bool __attribute__((weak)) emberAfPreMessageSendCallback(
    EmberAfMessageStruct * messageStruct, EmberStatus * status)
{
    return false;
}

bool __attribute__((weak)) emberAfMessageSentCallback(
    const MessageSendDestination & destination,
    EmberApsFrame * apsFrame, uint16_t msgLen, uint8_t * message,
    EmberStatus status)
{
    return false;
}

EmberAfStatus __attribute__((weak)) emberAfExternalAttributeReadCallback(
    EndpointId endpoint, ClusterId clusterId,
                                                   EmberAfAttributeMetadata * attributeMetadata,
                                                   uint8_t * buffer, uint16_t maxReadLength)
{
    return EMBER_ZCL_STATUS_FAILURE;
}

EmberAfStatus __attribute__((weak)) emberAfExternalAttributeWriteCallback(
    EndpointId endpoint, ClusterId clusterId,
                                                    EmberAfAttributeMetadata * attributeMetadata,
                                                    uint8_t * buffer)
{
    return EMBER_ZCL_STATUS_FAILURE;
}

uint32_t __attribute__((weak)) emberAfGetCurrentTimeCallback()
{
    return 0;
}

bool __attribute__((weak)) emberAfGetEndpointInfoCallback(
    EndpointId endpoint, uint8_t * returnNetworkIndex,
    EmberAfEndpointInfoStruct * returnEndpointInfo)
{
    return false;
}

void __attribute__((weak)) emberAfRegistrationAbortCallback() {}

EmberStatus __attribute__((weak)) emberAfInterpanSendMessageCallback(
    EmberAfInterpanHeader * header, uint16_t messageLength, uint8_t * message)
{
    return EMBER_LIBRARY_NOT_PRESENT;
}

bool __attribute__((weak)) emberAfStartMoveCallback()
{
    return false;
}

chip::Protocols::InteractionModel::Status __attribute__((weak)) MatterPreAttributeChangeCallback(
    const chip::app::ConcreteAttributePath & attributePath,
    uint8_t mask, uint8_t type, uint16_t size, uint8_t * value)
{
    return chip::Protocols::InteractionModel::Status::Success;
}

void __attribute__((weak)) MatterPostAttributeChangeCallback(
    const chip::app::ConcreteAttributePath & attributePath,
    uint8_t mask, uint8_t type, uint16_t size, uint8_t * value)
{
}
