#!/usr/bin/env bash

#
#    Copyright (c) 2021 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

set -e

# Build script for K32W examples GitHub workflow.

source "$(dirname "$0")/../../scripts/activate.sh"

set -x
env

./third_party/k32w_sdk/mr2_fixes/patch_k32w_mr2_sdk.sh
gn gen --root="$1" "$2" --args="k32w_sdk_root=\"${K32W061_SDK_ROOT}\" is_debug=true"
ninja -C "$2"
$K32W061_SDK_ROOT/tools/imagetool/sign_images.sh "$2"
