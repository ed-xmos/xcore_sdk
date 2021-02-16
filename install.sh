#!/bin/bash
set -e

if [ -z ${XMOS_AIOT_SDK_PATH} ]; then
	echo "XMOS_AIOT_SDK_PATH must be set before running this script."
else
    AI_TOOLS_DIR=${XMOS_AIOT_SDK_PATH}/tools/ai_tools

    echo "*****************************"
    echo "* Updating tools submodules *"
    echo "*****************************"
    (cd ${AI_TOOLS_DIR}; git submodule update --init) 

    echo "****************************"
    echo "* Building libtflite2xcore *"
    echo "****************************"
    LIB_FLEXBUFFERS_DIR=${AI_TOOLS_DIR}/utils/lib_flexbuffers
    (cd ${LIB_FLEXBUFFERS_DIR}; rm -rf build) 
    (cd ${LIB_FLEXBUFFERS_DIR}; mkdir -p build) 
    (cd ${LIB_FLEXBUFFERS_DIR}/build; cmake ../ ; make install) 

    ADF_DIR=${XMOS_AIOT_SDK_PATH}/modules/adf

    echo "*******************************"
    echo "* Building xcore_interpreters *"
    echo "******************************"
    XCORE_INTERPRETERS_DIR=${ADF_DIR}/xcore_interpreters/python_bindings
    (cd ${XCORE_INTERPRETERS_DIR}; rm -rf build) 
    (cd ${XCORE_INTERPRETERS_DIR}; mkdir -p build) 
    (cd ${XCORE_INTERPRETERS_DIR}/build; cmake ../ ; make install) 

    echo "**********************************"
    echo "* Installing Python requirements *"
    echo "**********************************"
    (pip install -r requirements.txt)

    echo "**************************************"
    echo "* Updating PATH environment variable *"
    echo "**************************************"
    MODEL_RUNNER_GENERATOR_PATH="${XMOS_AIOT_SDK_PATH}/modules/adf/tools/generate"
    export PATH="${MODEL_RUNNER_GENERATOR_PATH}:${PATH}"
fi