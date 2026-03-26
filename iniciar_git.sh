#!/bin/bash
repo="https://github.com/Raao-tech/Game_Violeta_Rafael.git";
echo -e "Hola! Soy tu asistente de Pre_prog, llamame Ingit.\n";

read -p "Quien eres? responde: " name;
sleep 0.29
echo -e "Bienvenido ${name}, que quieres hacer?\n";
sleep 1
echo -e "1. iniciar mi repo desde una compu de la uni\n";
echo -e "2. iniciar mi repo desde mi compu\n";
echo -e "3. Adios Ingit\n";


play=1;
sleep 1
while [ $play -eq 1 ]; do
    read -p "Hare la opcion: " opcion;
    if [ "$opcion" == "3" ]; then
        echo -e "Marchando ${name}!!"
        sleep 1
        echo -e "Dame un chance que estoy limpiando toda nuestra conversacion"
        sleep 2.5
        clear
        sleep 1
        echo -e "Todo listo mi brother"
        sleep 1
        echo -e "Por cierto, nadie debe de enterarse de esta conversacion"
        sleep 0.5 
        echo -e "¿Capichi mi pana?"
        sleep 1.5
        echo -e "... Mas te vale"
        sleep 3
        clear
        echo -e "Dicho eso, vente cuando quieras!!"
        sleep 2
        clear
        play=0;
        exit 0;
    elif [[ ! "$opcion" =~ ^[1-2]+$ ]]; then
        echo -e "${name} Has introducido una opcion invalida.... Dios, lo que me toca vivir\n";
    else 
        echo -e "Ok ${name}! En camino...\n";
        play=0;
    fi
done

sleep 1
if [ "$opcion" == 1 ]; then
    echo -e "Antes de empezar, voy a crear un repo, se supone que has descargado esto desde un .zip"
    sleep 0.5
    read -p "¿Correcto? (responde  si, yes, s, y, todo lo demas sera un NO): " respuesta
    if [[ ! "$respuesta" =~ ^(si|yes|s|y|S|correct)$ ]]; then
        sleep 0.3
        echo -e "Pues ¿que haces aqui? Deja de joder"
        exit 0
    fi
    echo -e "Inciando repo en el directorio actual"
    git init
    git remote add origin $repo
    read -p "cual es tu USERNAME de github? : " username
    read -p "cual es tu EMAIL de github? : " email
    read -p "Cual es tu PASSWORD de github? : " password
    read -p "Cual es tu TOKEN de uni? : " token

    git config --global user.email  "$email"
    git config --global user.name  "$username"

fi




