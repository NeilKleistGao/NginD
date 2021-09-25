#!/bin/bash

echo "Change build mode..."
sed -i "s/static constexpr short CURRENT_MODE = MODE_DEBUG;/static constexpr short CURRENT_MODE = MODE_RELEASE;/g" "../kernel/settings.h"
sed -i "s/# set(CMAKE_CXX_FLAGS/set(CMAKE_CXX_FLAGS/g" "../CMakeLists.txt"
cd ..

cmake --build . --target all -- -j6
make

for file in `find ./bin/resources -name "*.lua"`
do
    echo "encrypt ${file}..."
    `bin/crypto ${file} ${file: 0:${#file} - 4}".lsm"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.json"`
do
    echo "encrypt ${file}..."
    `bin/crypto ${file} ${file: 0:${#file} - 5}".cson"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.png"`
do
    echo "compress ${file}..."
    `bin/compress ${file} ${file: 0:${#file} - 4}".cng"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.jpg"`
do
    echo "compress ${file}..."
    `bin/compress ${file} ${file: 0:${#file} - 4}".cpg"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.vs"`
do
    echo "encrypt ${file}..."
    `bin/crypto ${file} ${file: 0:${#file} - 3}".cs"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.frag"`
do
    echo "encrypt ${file}..."
    `bin/crypto ${file} ${file: 0:${#file} - 5}".crag"`
    rm ${file}
done

for file in `find ./bin/resources -name "*.ini"`
do
    echo "encrypt ${file}..."
    `bin/crypto ${file} ${file: 0:${#file} - 4}".cini"`
    rm ${file}
done

rm "bin/crypto"
rm "bin/compress"

cd tools
sed -i "s/set(CMAKE_CXX_FLAGS/# set(CMAKE_CXX_FLAGS/g" "../CMakeLists.txt"
sed -i "s/static constexpr short CURRENT_MODE = MODE_RELEASE;/static constexpr short CURRENT_MODE = MODE_DEBUG;/g" "../kernel/settings.h"