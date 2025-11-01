#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=install -B build

pushd build
make -j$(nproc) install
popd

ln -sf build/compile_commands.json
