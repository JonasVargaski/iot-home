import React from 'react'
import { ThemeProvider } from 'styled-components/native'
import theme from './theme'

export function GlobalStyleProvider({ children }) {
  return <ThemeProvider theme={theme}>{children}</ThemeProvider>
}
