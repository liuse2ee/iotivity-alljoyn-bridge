//******************************************************************
//
// Copyright 2016 Intel Corporation All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "octypes.h"
#include <inttypes.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/AboutObjectDescription.h>
#include <stdint.h>
#include <vector>

/** Protocol independent indentifier.*/
#define OC_RSRVD_PROTOCOL_INDEPENDENT_ID "piid"

/** Device software version.*/
#define OC_RSRVD_SOFTWARE_VERSION        "sv"

/** Device manufacture name. */
#define OC_RSRVD_DEVICE_MFG_NAME         "dmn"

/** Device model number.*/
#define OC_RSRVD_DEVICE_MODEL_NUM        "dmno"

/** To represent secure mode resource type.*/
#define OC_RSRVD_RESOURCE_TYPE_SECURE_MODE "oic.r.securemode"

#define LOG_ERR         3
#define LOG_INFO        6

void LogWriteln(
    const char *file,
    const char *function,
    int32_t line,
    int8_t severity,
    const char *fmt,
    ...
);

#define LOG(severity, fmt, ...)                                         \
    LogWriteln(__FILE__, __FUNCTION__, __LINE__, severity, fmt, ##__VA_ARGS__)

extern std::string gRD;

void DeriveUniqueId(OCUUIdentity *id, const char *deviceId, uint8_t *appId, size_t n);

const char *GetServerInstanceIDString();
OCStackResult SetPlatformAndDeviceInfo(ajn::AboutObjectDescription &objectDescription,
        ajn::AboutData &aboutData);
OCStackResult StartPresence();
OCStackResult StopPresence();

OCStackResult RDPublish();

OCStackResult CreateResource(const char *uri, const char *typeName, const char *interfaceName,
        OCEntityHandler entityHandler, void *callbackParam,
        uint8_t properties);
OCStackResult DestroyResource(const char *uri);
OCStackResult AddResourceType(const char *uri, const char *typeName);
OCStackResult AddInterface(const char *uri, const char *interfaceName);
OCStackResult DoResponse(OCEntityHandlerResponse *response);

OCStackResult DoResource(OCDoHandle *handle,
        OCMethod method,
        const char *uri,
        const OCDevAddr *destination,
        OCPayload *payload,
        OCCallbackData *cbData,
        OCHeaderOption *options,
        uint8_t numOptions);
OCStackResult DoResource(OCDoHandle *handle,
        OCMethod method,
        const char *uri,
        const std::vector<OCDevAddr> &destinations,
        OCPayload *payload,
        OCCallbackData *cbData,
        OCHeaderOption *options,
        uint8_t numOptions);
OCStackResult Cancel(OCDoHandle handle, OCQualityOfService qos);

OCStackResult NotifyListOfObservers(const char *uri,
        OCObservationId  *obsIdList,
        uint8_t numberOfIds,
        OCRepPayload *payload);

#endif // __PLUGIN_H__
