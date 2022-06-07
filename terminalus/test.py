import serial
import time

arduino = serial.Serial(port='COM3', baudrate=115200, bytesize=8, parity=serial.PARITY_EVEN, stopbits=serial.STOPBITS_TWO, timeout=.1) #, rtscts=False, dsrdtr=True)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    arduino.reset_input_buffer()
    #time.sleep(0.05)
    #bytesToRead = arduino.inWaiting()
    #while (bytesToRead == 0):
        #bytesToRead = arduino.inWaiting()
    #print (bytesToRead)
    #arduino.rts = False
    #arduino.dtr = False
    #data = arduino.read(bytesToRead)
    data = arduino.read(1)
    return data


while True:
    num = input("Enter a number: ")

    value = write_read(num)
    print(type(value))
    print(value)