#!/bin/bash
choice=3
name_file="*_test.c"

echo -e "Hello! Please, tell me what do yo need to make?\n"
#==============selct accions ===========================
while [[ ! $choice == 0  &&  ! $choice == 1 ]]; do
    echo -e "0 . Without Valgrind"
    echo -e "1 . With    Valgrind\n"
    read -p "prompt >  " choice; #lo primero se guarda en choice, lo segundo e name_file como str, y lo que le sigue se ignora
    echo -e "------------------------------------------\n"
done
#========================================================


#==============selct File ===========================
echo -e "-------------Select File---------------------------\n"

ls tests/*.c | sed -E "s/^tests\/(.*)\_test.c$/\1/"

echo -e "\nWhich file do you want?"
read -p "prompt >>>" name_file _;
echo -e "-------------------------------------------\n"
#==============================================
cd ./tests/
#==================Ejecución total, si no hay name_file ========================
if [ -z ${name_file} ]; then 
    echo -e "Name File is not avaible, so it, i testing all\n"
    #Se ejecuta todo COn valgrind
    if [ ${choice} == 0 ]; then 
        make run_all
        exit
    fi
    #Se ejecuta todo sin Valgrind
    if [ ${choice} == 1 ]; then 
        make runv_all
        exit
    fi
    echo -e "Ready. Good Bye!!\n"
    exit
fi
#=================================================================================

#============================Ejecucion del file indicado ===========================================
#Sin valgrind
if [ ${choice} == 0 ]; then 
    make run_${name_file}
fi
#Con valgrind
if [ ${choice} == 1 ]; then 
    make v${name_file}
fi
echo -e "Ready. Good Bye!!\n"
exit

#echo -e "su eleccion fue ${choice} y su archivo es : ${name_file}\n";

#Pequeño comentario para los profesores que corrijan este script.
#La idea es que el makefile principal tenga un comando que ejecute el presente
#script, a su vez, éste hace referencia a un makefile contenido en el directorio tests