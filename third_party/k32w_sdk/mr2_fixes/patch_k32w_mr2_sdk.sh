#!/bin/bash

if [[ ! -v K32W061_SDK_ROOT ]]; then
    echo "K32W061_SDK_ROOT is not set"
    exit 1
fi

cp -r chip                 $K32W061_SDK_ROOT/boards/k32w061dk6/wireless_examples/hybrid/ble_ot/
cp PWR.c                   $K32W061_SDK_ROOT/middleware/wireless/framework/LowPower/Source/k32w061dk6/
cp controller_interface.h  $K32W061_SDK_ROOT/middleware/wireless/ble_controller/interface/
cp Messaging.h             $K32W061_SDK_ROOT/middleware/wireless/framework/Messaging/Interface/
cp ble_conn_manager.h      $K32W061_SDK_ROOT/middleware/wireless/bluetooth/application/common/
cp GenericList.h           $K32W061_SDK_ROOT/middleware/wireless/framework/Lists/
cp pin_mux.c               $K32W061_SDK_ROOT/boards/k32w061dk6/wireless_examples/openthread/enablement/

echo "K32W MR2 patched"
exit 0
