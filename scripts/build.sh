#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=install -DBUILD_EXAMPLES=ON -B build

pushd build
make -j$(nproc) install
popd

ln -sf build/compile_commands.json
