#!/bin/bash

echo "Change build mode..."
sed -i "s/static constexpr short CURRENT_MODE = MODE_DEBUG;/static constexpr short CURRENT_MODE = MODE_RELEASE;/g" "../kernel/settings.h"
sed -i "s/if (0)/if (1)/g" "../CMakeLists.txt"
cd ..

if  [ ! -d "build" ]; then
  mkdir "build"
fi

cmake --build cmake-build-debug --target all -- -j6
make

for file in `find ./build/resources -name "*.lua"`
do
    echo "encrypt ${file}..."
    `build/crypto ${file} ${file: 0:${#file} - 4}".lsm"`
    rm ${file}
done

for file in `find ./build/resources -name "*.json"`
do
    echo "encrypt ${file}..."
    `build/crypto ${file} ${file: 0:${#file} - 5}".cson"`
    rm ${file}
done

for file in `find ./build/resources -name "*.png"`
do
    echo "compress ${file}..."
    `build/compress ${file} ${file: 0:${#file} - 4}".cng"`
    rm ${file}
done

for file in `find ./build/resources -name "*.jpg"`
do
    echo "compress ${file}..."
    `build/compress ${file} ${file: 0:${#file} - 4}".cpg"`
    rm ${file}
done

for file in `find ./build/resources -name "*.vs"`
do
    echo "encrypt ${file}..."
    `build/crypto ${file} ${file: 0:${#file} - 3}".cs"`
    rm ${file}
done

for file in `find ./build/resources -name "*.frag"`
do
    echo "encrypt ${file}..."
    `build/crypto ${file} ${file: 0:${#file} - 5}".crag"`
    rm ${file}
done

for file in `find ./build/resources -name "*.ini"`
do
    echo "encrypt ${file}..."
    `build/crypto ${file} ${file: 0:${#file} - 4}".cini"`
    rm ${file}
done

rm "build/crypto"
rm "build/compress"

cd tools
sed -i "s/if (1)/if (0)/g" "../CMakeLists.txt"
sed -i "s/static constexpr short CURRENT_MODE = MODE_RELEASE;/static constexpr short CURRENT_MODE = MODE_DEBUG;/g" "../kernel/settings.h"