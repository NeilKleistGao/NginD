include="include \"class_info.h\"\n"
content=""

for file in $(find ../ -name "*\.h");
do
  class_name=$(grep -e "@reflection" "${file}" -A 1 | grep "class .*[ \{\:]" -o)
  class_name="${class_name: 6: ${#class_name} - 7}"
  class_name=${class_name// /}
  echo "sign ${class_name}"
  if [ "$class_name" != "" ];then
    include=${include}"#include \""${file: 3}"\"\n"
    content=${content}"    ClassInfo::getInstance()->sign(\"${class_name}\", []() -> Object* {return new ${class_name}();});\n"
  fi
done

sed -e '/^#include/d' -e '/^    ClassInfo/d' -i ../kernel/utils/reflection_register.h
tnum=$(grep //@include ../kernel/utils/reflection_register.h -n|cut -f1 -d:)
echo "${tnum}"
sed -i "${tnum}a\#${include}" ../kernel/utils/reflection_register.h
tnum=$(grep //@sign ../kernel/utils/reflection_register.h -n|cut -f1 -d:)
echo "${tnum}"
sed -i "${tnum}a\ ${content: 1}" ../kernel/utils/reflection_register.h