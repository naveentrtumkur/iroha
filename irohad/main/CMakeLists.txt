# Copyright 2017 Soramitsu Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(server_runner server_runner.cpp)
target_link_libraries(server_runner
    torii_service
    logger
    endpoint
    schema
    )

add_library(genesis_block_server
    genesis_block_server/genesis_block_server.cpp
    genesis_block_server/genesis_block_processor.cpp
    impl/raw_block_insertion.cpp
    )
target_link_libraries(genesis_block_server
    ametsuchi
    model
    timer
    endpoint
    optional
    logger
    )

add_library(application
    application.cpp
    impl/ordering_init.cpp
    impl/consensus_init.cpp
    )
target_link_libraries(application
    logger
    gtest
    gmock
    yac
    server_runner
    model
    ametsuchi
    networking
    ordering_service
    chain_validator
    hash
    stateless_validator
    stateful_validator
    processors
    crypto
    simulator
    )

add_executable(irohad irohad.cpp)
target_link_libraries(irohad
    application
    genesis_block_server
    ametsuchi
    gflags
    rapidjson
    config
    )
