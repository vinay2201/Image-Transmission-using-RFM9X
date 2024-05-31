import os
import serial
import time

# Path to the image file
file_path = '/home/pi/Downloads/image1.jpg'

# Read the file in binary mode
with open(file_path, 'rb') as file:
    file_data = file.read()
print("File loaded successfully.")
print(file_data)

# Get the size of the file in bytes
file_size = len(file_data)
print(f"File size: {file_size} bytes")

# Constants for transmission
chunk_size = 64  # The maximum data chunk size in bytes (adjust as needed)
start_marker = '<START>'  # Example sequence for start marker, now as a string
end_marker = '<END>'  # Example sequence for end marker, now as a string
eot_marker = '<EOT>'  # Example sequence for End of Transmission, now as a string

ser = serial.Serial('/dev/ttyACM1', 9600)
time.sleep(2)  # Wait for the connection to establish
print("Serial connection established.")

# Function to divide the file data into chunks and add markers
def get_chunks(data, size):
    chunks = []
    # Adjust size to account for markers
    adjusted_size = size - len(start_marker.encode()) - len(end_marker.encode())
    for i in range(0, len(data), adjusted_size):
        chunk = data[i:i + adjusted_size]
        marked_chunk = start_marker + chunk.hex() + end_marker  # Convert chunk to hex and wrap with markers
        chunks.append(marked_chunk)
    return chunks

# Split the file data into marked chunks
marked_chunks = get_chunks(file_data, chunk_size)

# Send each marked chunk over serial
total_start_time = time.time()
for index, chunk in enumerate(marked_chunks):
    print(f"Chunk {index + 1}/{len(marked_chunks)} content: {chunk}")  # Print the chunk content
    ser.write(chunk.encode())  # Convert string to bytes before sending
    print(f"Sent chunk {index + 1}/{len(marked_chunks)}")
    #time.sleep(0.5)  # Optional: Adjust sleep time based on receiver's capability

time.sleep(2)

# Send End of Transmission marker
print(f"Sending EOT marker: {eot_marker}")
ser.write(eot_marker.encode())
print("End of Transmission marker sent.")

# Close the serial connection
ser.close()

# Calculate total transmission time
total_end_time = time.time()
print(f"All chunks sent. Total transmission time: {total_end_time - total_start_time:.3f} seconds.")
