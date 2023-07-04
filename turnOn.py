from pymodbus.client import ModbusTcpClient as ModbusClient

client = ModbusClient('192.168.1.11', 502)
connection = client.connect()
request = client.write_coil(0, 1) #covert to float
client.close()