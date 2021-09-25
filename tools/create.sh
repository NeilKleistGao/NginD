read -p "Project Name: " project_name
read -p "Project Directory: " directory

path="${directory}/${project_name}"

if [ ! -d "$path" ]; then
mkdir $path
else
echo "The Path ${path} has existed."
exit
fi

echo "Copying source code..."
cp -R "../cmake" "${path}/cmake"
cp -R "../extern" "${path}/extern"
cp -R "../include" "${path}/include"
cp -R "../kernel" "${path}/kernel"
mkdir "${path}/lib"
cp -R "../lib/linux" "${path}/lib/linux"
cp -R "../plugin" "${path}/plugin"

echo "Copying resources..."
mkdir "${path}/resources"
mkdir "${path}/resources/config"
mkdir "${path}/resources/config/animations"
cp -R "../resources/config/components" "${path}/resources/config/components"
mkdir "${path}/resources/config/prefabs"
mkdir "${path}/resources/config/programs"
cp "../resources/config/programs/sprite.json" "${path}/resources/config/programs/sprite.json"
cp "../resources/config/programs/text.json" "${path}/resources/config/programs/text.json"
mkdir "${path}/resources/config/worlds"
cp "../resources/config/worlds/template.json" "${path}/resources/config/worlds/welcome.json"
cp "../resources/config/global_settings.json" "${path}/resources/config/global_settings.json"
mkdir "${path}/resources/effect"
mkdir "${path}/resources/fonts"
cp "../resources/fonts/manaspc.ttf" "${path}/resources/fonts/manaspc.ttf"
mkdir "${path}/resources/images"
cp "../resources/images/dice.png" "${path}/resources/images/dice.png"
mkdir "${path}/resources/music"
mkdir "${path}/resources/script"
cp -R "../resources/script/kernel" "${path}/resources/script/kernel"
mkdir "${path}/resources/shaders"
cp "../resources/shaders/sprite.vs" "${path}/resources/shaders/sprite.vs"
cp "../resources/shaders/sprite.frag" "${path}/resources/shaders/sprite.frag"
cp "../resources/shaders/text.vs" "${path}/resources/shaders/text.vs"
cp "../resources/shaders/text.frag" "${path}/resources/shaders/text.frag"
mkdir "${path}/resources/text"

echo "Copying tools..."
cp -R "../tools" "${path}/tools"
cp "../CMakeLists.txt" "${path}/CMakeLists.txt"
cp "../main.cc" "${path}/main.cc"

sed -i "s/NginD/${project_name}/g" "${path}/CMakeLists.txt"

echo "Create ${project_name} at ${path}."