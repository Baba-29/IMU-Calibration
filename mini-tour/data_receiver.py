import serial.tools.list_ports

ports = list(serial.tools.list_ports.comports())
serialInst = serial.Serial()

portList = []

for port in ports:
    portList.append(str(port))
    print(str(port))

val = input("Select port : COM")

for x in range(len(portList)):
    if portList[x].startswith("COM" + str(val)):
        print(portList[x])

serialInst.baudrate = 115200
serialInst.port = "COM" + str(val)
serialInst.open()

while True:
    if serialInst.in_waiting > 0:
        packet = serialInst.readline()
        print(packet.decode("utf-8"))
