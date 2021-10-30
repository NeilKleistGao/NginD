read -p "World Name: " world_name
echo "
{
    \"world-name\": \"{{world_name}}\",
    \"background-color\": \"#000000FF\",
    \"camera\": {
      \"x\": 512,
      \"y\": 384
    },
    \"children\": [
    ],
    \"components\": [
    ]
}
" >> "../resources/config/worlds/${world_name}.json"
sed -i "s/{{world_name}}/${world_name}/g" "../resources/config/worlds/${world_name}.json"