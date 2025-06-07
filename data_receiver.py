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

serialInst.baud = 115200
serialInst.port = "COM" + str(val)
serialInst.open()

accel = []

while True:
    if serialInst.in_waiting > 0:
        packet = serialInst.readline()
        accel.append(packet.decode("utf-8"))
        if packet.decode("utf-8") == "0,0,0":
            break

with open("accel.txt", "a") as f:
    for x in accel:
        f.write(x)

