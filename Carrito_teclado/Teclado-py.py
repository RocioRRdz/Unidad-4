from pynput import keyboard as kb
import serial

ser = serial.Serial('COM7', 9600)  # Reemplaza 'COM7' con el número de puerto de tu módulo HC05

def pulsar(tecla):
	if hasattr(tecla, 'char') and tecla.char in ['w', 's', 'a', 'd', 'x']:
		#print('Se ha pulsado la tecla: ' + tecla.char)
		#ser.write(tecla.char.encode())
		teclas = tecla.char.upper()
		print('Se ha pulsado la tecla: ' + teclas)
		ser.write(teclas.encode())

	elif tecla in [kb.Key.up, kb.Key.down, kb.Key.left, kb.Key.right]:
		print('Se ha pulsado la tecla: ' + tecla.name)

		if tecla == kb.Key.up:
			ser.write('W'.encode())
		elif tecla == kb.Key.down:
			ser.write('S'.encode())
		elif tecla == kb.Key.left:
			ser.write('A'.encode())
		elif tecla == kb.Key.right:
			ser.write('D'.encode())

	elif tecla == kb.Key.esc:
		print('Salir del programa')
		return False

with kb.Listener(pulsar) as escuchador:
	escuchador.join()
