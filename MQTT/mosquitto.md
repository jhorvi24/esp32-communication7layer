# Mosquitto on Ubuntu

    sudo apt update
    sudo apt install mosquitto mosquitto-clients
    sudo systemctl start mosquitto
    sudo systemctl enable mosquitto

## Configure the file /etc/mosquitto/mosquitto.conf

    allow_anonymous true #allow connection without authentication 
    listener 1883 #allow connection from every ip

## Test using MQTT Explorer

## Test using  a client publisher

    mosquitto_pub -h ip-address -p 1883 -t "test/topic" -m "Hello from MQTT client"

#Test using a client subscriber

    mosquitto_sub -h your_server_ip -t test/topic
