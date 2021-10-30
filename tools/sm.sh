read -p "State Machine Name: " sm_name
read -p "Directory: " sm_path
echo "
{{sm_name}} = class(\"{{sm_name}}\")

function {{sm_name}}:ctor()
end

function {{sm_name}}:enter()
  self.move(\"Idle\")
end

function {{sm_name}}:updateIdle()
end

function {{sm_name}}:exit()
end" >> "../resources/script/${sm_path}/${sm_name}.lua"

sed -i "s/{{sm_name}}/${sm_name}/g" "../resources/script/${sm_path}/${sm_name}.lua"