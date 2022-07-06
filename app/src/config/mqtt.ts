import Paho from 'paho-mqtt'

const config = {
  host: 'broker.mqttdashboard.com',
  port: 8000,
  path: '/mqtt',
  clientId: 'expo-rn-client-id@unique',
}

export const client = new Paho.Client(config.host, config.port, config.path, config.clientId)
