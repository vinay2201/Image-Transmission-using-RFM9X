import serial
import time

# Setup the serial connection
serial_port = '/dev/ttyACM0'  # Adjust as per your setup
baud_rate = 9600  # Must match Arduino's baud rate

# Open the serial port
ser = serial.Serial(serial_port, baud_rate, timeout=1)
time.sleep(2)  # Allow time for the connection to establish

print("Listening for messages from Arduino...")

full_data = bytearray()  # Use bytearray to accumulate binary data

try:
    while True:
        # Read data from serial port
        data = ser.readline()  # Reads a line from the serial port
        if data:
            try:
                # Try decoding as UTF-8
                decoded_data = data.decode('utf-8').strip()
                print("Decoded UTF-8 data:", decoded_data)
                full_data.extend(data.strip())  # Append the raw data to full_data
            except UnicodeDecodeError:
                print("Received non-UTF-8 data:", data)
                full_data.extend(data)  # Append the raw data to full_data
except KeyboardInterrupt:
    print("Program interrupted. Exiting...")
    # Convert full_data to a string for display if necessary, or handle as binary
    print("Full data received:")
    try:
        reconstruct_data = full_data.decode('utf-8')  # Attempt to decode the full data as UTF-8
        hex_conversion = bytes.fromhex(reconstruct_data)
        print(reconstruct_data)  # Print the decoded UTF-8 data
        print('hex conversion')
        print(hex_conversion)
        with open('reconstructed1_image.jpg', 'wb') as file:
            file.write(hex_conversion)  # Write the binary data to a file
        print('done and dusted')
    except UnicodeDecodeError:
        print(full_data)  # If not decodable, display as bytes
finally:
    ser.close()  # Ensure the serial port is closed on exit
    print("Serial connection closed.")
