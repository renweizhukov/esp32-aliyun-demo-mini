#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

COMPONENT_ADD_INCLUDEDIRS := include/guider include/mqtt include/packages/LITE-log include/packages/LITE-utils include/sdk-impl include/system include/utils/digest include/utils/misc

COMPONENT_SRCDIRS := src src/iotkit-embedded/src/guider src/iotkit-embedded/src/mqtt src/iotkit-embedded/src/mqtt/MQTTPacket src/iotkit-embedded/src/packages/LITE-log src/iotkit-embedded/src/packages/LITE-utils src/iotkit-embedded/src/sdk-impl src/iotkit-embedded/src/system src/iotkit-embedded/src/utils/digest src/iotkit-embedded/src/utils/misc src/platform/os/esp32 src/platform/ssl/mbedtls
