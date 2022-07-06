import React from 'react'
import { GlobalStyleProvider } from './global/styles/Provider'
import { Dashboard } from './pages/Dashboard'

export default function App() {
  return (
    <GlobalStyleProvider>
      <Dashboard />
    </GlobalStyleProvider>
  )
}
