import React, { useEffect, useState } from 'react'
import { View, StyleSheet, Text, TouchableOpacity } from 'react-native'
import Paho from 'paho-mqtt'
import { Container } from './styles'

interface IPinState {
  pO1: number
  pO2: number
  pO3: number
  pO4: number
  pO5: number
  pO6: number
  pO7: number
}

const defaultPinState = {
  pO1: 0,
  pO2: 0,
  pO3: 0,
  pO4: 0,
  pO5: 0,
  pO6: 0,
  pO7: 0,
}

const client = new Paho.Client('broker.mqttdashboard.com', Number(8000), '/mqtt', 'expo-rn-client-id@unique')

const connect = () => {
  client.connect({
    keepAliveInterval: 0,
    reconnect: true,
    timeout: 10,
    onSuccess: () => {
      client.subscribe('ngkKzLHfUh@5C:CF:7F:4C:4C:1E', { qos: 1 })
    },
  })
}

export function Dashboard() {
  const [lastMessage, setLastMessage] = useState('')
  const [pinState, setPinState] = useState<IPinState>(() => defaultPinState)

  function changePin(pin: Number) {
    const state = { ...defaultPinState, ...pinState }
    state[`pO${pin}`] = !state[`pO${pin}`] ? 1 : 0

    if (!client.isConnected()) connect()
    if (client.isConnected())
      client.send(
        'ngkKzLHfUh@5C:CF:7F:4C:4C:1E',
        JSON.stringify({ action: 'syncPinState', payload: { ...state } }),
        1,
        true,
      )
  }

  useEffect(() => {
    client.onMessageArrived = (message) => {
      setLastMessage(message.payloadString)

      const { action, payload } = JSON.parse(message.payloadString)
      if (action === 'syncPinState') setPinState(payload)
    }

    connect()
  }, [])

  const styles = StyleSheet.create({
    button: {
      paddingHorizontal: 70,
      paddingVertical: 14,
      margin: 6,
      backgroundColor: '#f1f1f1',
      borderRadius: 4,
    },
  })

  return (
    <Container>
      <Text style={{ fontWeight: '600', color: client.isConnected() ? '#0f0' : '#f00' }}>
        {client.isConnected() ? 'Conectado' : 'Desconectado'}
      </Text>
      <Text style={{ textAlign: 'center', margin: 5 }}>
        Último estado:
        {lastMessage}
      </Text>
      <View style={{ marginTop: 30 }}>
        <TouchableOpacity
          onPress={() => changePin(1)}
          style={[styles.button, { backgroundColor: pinState.pO1 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 1</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(2)}
          style={[styles.button, { backgroundColor: pinState.pO2 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 2</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(3)}
          style={[styles.button, { backgroundColor: pinState.pO3 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 3</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(4)}
          style={[styles.button, { backgroundColor: pinState.pO4 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 4</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(5)}
          style={[styles.button, { backgroundColor: pinState.pO5 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 5</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(6)}
          style={[styles.button, { backgroundColor: pinState.pO6 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 6</Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => changePin(7)}
          style={[styles.button, { backgroundColor: pinState.pO7 ? '#48ef1f' : '#ccc' }]}
        >
          <Text>Relé 7</Text>
        </TouchableOpacity>
      </View>
    </Container>
  )
}
