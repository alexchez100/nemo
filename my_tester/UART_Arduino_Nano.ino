
void setup() 
{
  Serial.begin(115200, SERIAL_8E2); // 8 bits - data, 2 - stop bits, None - parity
  // Serial.setTimeout(1);

  pinMode(LED_BUILTIN, OUTPUT);
}

void blink_led (int n_msec) // функция мигания светодиодом
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(n_msec);
  digitalWrite(LED_BUILTIN, LOW); 
  delay(n_msec);
}

int8_t UART_read_byte(void) // нормальная функция чтения (проблемы со скоростями)
{
  while(1)
  {
    if (Serial.available() > 0) // проверка буфера, есть ли что там
      return (Serial.read());
  }
}

void UART_write_byte(int8_t data) // нормальная функция записи (проблемы со скоростями)
{
  Serial.write(data);
  Serial.flush(); // ожидание пока все уйдет
}



int8_t data_r[100]; // переменная Чтения
int8_t data_w[100]; // переменная Отправки

void loop() 
{
  while (1)
  {
    /// чтение данных /// 
    data_r[0] = UART_read_byte();
    data_r[1] = UART_read_byte();
    data_r[2] = UART_read_byte();
    int len = 0;
    len = data_r[1]*256 + data_r[2];
    int i = 0;
    while (i < len)
    {
      data_r[i+3] = UART_read_byte();
      i++;
    }

    /// запись данных ///  
    if (data_r[0] == (int8_t)0xAA) // 0xAA   0x0000  ->  0xBB 0x0000
    {
      UART_write_byte(0xBB); UART_write_byte(0x00); UART_write_byte(0x00);
      continue;
    }

    if (data_r[0] == (int8_t)0x65) // 0x65 0x0002 0x11 0x12  ->  0x65 0x0002 0xA1 0xA2
    {
      UART_write_byte(0x65); UART_write_byte(0x00); UART_write_byte(0x02); UART_write_byte(0xA1); UART_write_byte(0xA2);
      continue;
    }

    if (data_r[0] == (int8_t)0x66) // 0x66 0x0003 0x21 0x22 0x23  ->  0x66 0x0003 0xB1 0xB2 0xB3
    {
      UART_write_byte(0x66); UART_write_byte(0x00); UART_write_byte(0x03); UART_write_byte(0xB1); UART_write_byte(0xB2); UART_write_byte(0xB3);
      continue;
    }

    if (data_r[0] == (int8_t)0x67) // 0x67 0x0001 0x31  ->  0x67 0x0001 0xC1
    {
      UART_write_byte(0x67); UART_write_byte(0x00); UART_write_byte(0x01); UART_write_byte(0xC1);
      continue;
    }

    if (data_r[0] == (int8_t)0xCC) // 0xCC 0x0002 0x01 0x02  ->  0xCC 0x0002 0xA1 0xA2
    {
      UART_write_byte(0xCC); UART_write_byte(0x00); UART_write_byte(0x02); UART_write_byte(0x01); UART_write_byte(0x02);
      continue;
    }

    if (data_r[0] == (int8_t)0xDD) // 0xDD 0x0001 0x01  ->  0xDD 0x0003 0x01 0x02 0x03
    {
      UART_write_byte(0xDD); UART_write_byte(0x00); UART_write_byte(0x03); UART_write_byte(0x01); UART_write_byte(0x02); UART_write_byte(0x03);
      continue; 
    }

    if (data_r[0] == (int8_t)0xFF) // 0xFF 0x0003 0x01 0x02 0x03  ->  0xFF 0x0001 0x01
    {
      UART_write_byte(0xFF); UART_write_byte(0x00); UART_write_byte(0x01); UART_write_byte(0x01);
      continue;
    }
    
    UART_write_byte(0xEE); // error
  }
  
  
  //delay(200);                       
                 
}
