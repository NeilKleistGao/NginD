include="include \"class_info.h\"" # the include command
content="    ClassInfo::getInstance()->sign(\"Object\", []() -> Object* {return new Object();});" # call the sign method in static function

for file in $(find ../ -name "*\.h");
do
  class_name=$(grep -e "// @reflection" "${file}" -A 1 | grep -oP "class .*?[ \{\:]") # get all class with @reflection comment
  class_name="${class_name: 6: ${#class_name} - 7}"
  class_name=${class_name// /}
  if [ "$class_name" != "" ] && [ "$class_name" != "Object" ];then
    include=${include}"\n#include \""${file: 3}"\""
    content=${content}"\n    ClassInfo::getInstance()->sign(\"${class_name}\", []() -> Object* {return new ${class_name}();});"
  fi
done

# add to the file
sed -e '/^#include/d' -e '/^    ClassInfo/d' -i ../kernel/utils/reflection_injector.h
tnum=$(grep //@include ../kernel/utils/reflection_injector.h -n|cut -f1 -d:)
sed -i "${tnum}a\#${include}" ../kernel/utils/reflection_injector.h
tnum=$(grep //@sign ../kernel/utils/reflection_injector.h -n|cut -f1 -d:)
sed -i "${tnum}a\ ${content: 1}" ../kernel/utils/reflection_injector.h