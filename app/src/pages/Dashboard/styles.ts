import styled from 'styled-components/native'

export const Container = styled.View`
  flex: 1;
  align-items: center;
  justify-content: center;
  background: ${({ theme }) => theme.pallete.primary};
`

export const Button = styled.TouchableOpacity<{ active: Boolean }>`
  background-color: ${({ active }) => (active ? '#3bd33b' : '#e1e1e1')};
  padding: 15px 80px;
  border-radius: 4px;
  margin: 10px;
`
