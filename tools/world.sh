read -p "World Name: " world_name
cp "../resources/config/worlds/template.json" "../resources/config/worlds/${world_name}.json"
sed -i "s/{{world_name}}/${world_name}/g" "../resources/config/worlds/${world_name}.json"