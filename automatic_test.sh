#!/bin/bash
choice=3
name_file="*_test.c"

echo -e "Hello! Please, tell me what do yo need to make?\n"
while [[ ! $choice == 0  &&  ! $choice == 1 ]]; do
    echo -e "0 . Without Valgrind"
    echo -e "1 . With    Valgrind\n"
    echo -e "Format of the input:   <your choice> <name_test_file_without_extension>\n"
    read -p "prompt >  " choice name_file _; #lo primero se guarda en choice, lo segundo e name_file como str, y lo que le sigue se ignora
done
cd ./tests/
make run_${name_file}
echo -e "su eleccion fue ${choice} y su archivo es : ${name_file}\n";
