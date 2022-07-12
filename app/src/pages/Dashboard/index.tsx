import React, { useEffect, useState } from 'react'
import { View, Text } from 'react-native'
import { client } from '../../config/mqtt'
import { Container, Button } from './styles'

interface IPinState {
  pO1: number
  pO2: number
  pO3: number
  pO4: number
  pO5: number
  pO6: number
  pO7: number
  timestamp: Number
}

const defaultPinState = { pO1: 0, pO2: 0, pO3: 0, pO4: 0, pO5: 0, pO6: 0, pO7: 0, timestamp: 0 }
const topic = 'ngkKzLHfUh@5C:CF:7F:4C:4C:1E'

export function Dashboard() {
  const [pinState, setPinState] = useState<IPinState>(() => defaultPinState)
  const [isConnected, setIsConnected] = useState(false)

  function changePin(pin: Number) {
    const state = { ...defaultPinState, ...pinState }
    state[`pO${pin}`] = !state[`pO${pin}`] ? 1 : 0
    state.timestamp = new Date().getTime()
    setPinState(state)

    const message = JSON.stringify({ action: 'syncPinState', payload: state })
    if (isConnected) client.send(topic, message, 1, true)
  }

  useEffect(() => {
    client.onConnectionLost = () => setIsConnected(false)
    client.onMessageArrived = (message) => {
      const { action, payload } = JSON.parse(message.payloadString)
      if (action === 'syncPinState')
        setPinState((old) => {
          if (payload.timestamp > old.timestamp) return payload
          return old
        })
    }

    if (!isConnected) {
      client.connect({
        reconnect: true,
        onSuccess: () => {
          setIsConnected(true)
          client.subscribe(topic, { qos: 1 })
        },
      })
    }
  }, [])

  return (
    <Container>
      <Text style={{ fontWeight: '600', color: isConnected ? '#0f0' : '#f00' }}>
        {isConnected ? 'Conectado' : 'Desconectado'}
      </Text>

      <View style={{ marginTop: 30 }}>
        <Button active={!!pinState.pO1} onPress={() => changePin(1)}>
          <Text>Relé 1</Text>
        </Button>
        <Button active={!!pinState.pO2} onPress={() => changePin(2)}>
          <Text>Relé 2</Text>
        </Button>
        <Button active={!!pinState.pO3} onPress={() => changePin(3)}>
          <Text>Relé 3</Text>
        </Button>
        <Button active={!!pinState.pO4} onPress={() => changePin(4)}>
          <Text>Relé 4</Text>
        </Button>
        <Button active={!!pinState.pO5} onPress={() => changePin(5)}>
          <Text>Relé 5</Text>
        </Button>
        <Button active={!!pinState.pO6} onPress={() => changePin(6)}>
          <Text>Relé 6</Text>
        </Button>
        <Button active={!!pinState.pO7} onPress={() => changePin(7)}>
          <Text>Relé 7</Text>
        </Button>
      </View>
    </Container>
  )
}
