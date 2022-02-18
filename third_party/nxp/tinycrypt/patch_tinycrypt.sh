#!/bin/bash

if [[ ! -d $PW_PROJECT_ROOT ]]; then
    echo "PW_PROJECT_ROOT is not set, run activate.sh script"
    exit 1
fi

convert_to_dos() {

    [[ $(file -b - <$1) != *"CRLF"* ]] && unix2dos "$1"
}

SOURCE=${BASH_SOURCE[0]}
SOURCE_DIR=$(cd "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)

echo "$SOURCE_DIR"

# Mbedtls header files

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/check_config.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_check_config_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/config.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_config_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/oid.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_oid_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/pk.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_pk_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/pk_internal.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_pk_internal_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/platform.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_platform_h.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/mbedtls/platform_util.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_platform_util_h.patch"

# Mbedtls source files

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/oid.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_oid_c.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/pk.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_pk_c.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/pkparse.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_pkparse_c.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/pkwrite.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_pkwrite_c.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/platform_util.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_platform_util_c.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/library/x509_crt.c
patch --binary -d "$PW_PROJECT_ROOT"/third_party/mbedtls/repo -p1 <"$SOURCE_DIR/fixes/mbedtls_x509_crt_c.patch"

# Openthead

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/openthread/repo/src/core/crypto/ecdsa.cpp
patch --binary -d "$PW_PROJECT_ROOT"/third_party/openthread/repo -p1 <"$SOURCE_DIR/fixes/openthread_ecdsa_cpp.patch"

#convert_to_dos "$PW_PROJECT_ROOT"/third_party/openthread/repo/third_party/mbedtls/mbedtls-config.h
patch --binary -d "$PW_PROJECT_ROOT"/third_party/openthread/repo -p1 <"$SOURCE_DIR/fixes/openthread_mbedtls-config_h.patch"

# Tinycrypt changes

cp -r "$SOURCE_DIR"/new_files/tinycrypt_h "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/include/tinycrypt
cp -r "$SOURCE_DIR"/new_files/tinycrypt_c "$PW_PROJECT_ROOT"/third_party/mbedtls/repo/tinycrypt

echo "Tinycrypt changes done."
exit 0
