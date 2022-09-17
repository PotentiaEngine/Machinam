cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
move .\build\compile_commands.json .\compile_commands.json
