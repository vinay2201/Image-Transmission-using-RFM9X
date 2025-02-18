# 📡 Wireless Image Transmission using RFM9X & Serial Communication

This project enables **wireless image transmission** using **LoRa-based RFM9X modules and Serial Communication**. The system facilitates **sending and receiving images** between a Raspberry Pi and an Arduino over **serial communication**, ensuring efficient and reliable data transfer.

---

## 📌 **Project Overview**
Wireless data transmission is essential for **IoT, remote monitoring, and embedded systems**. This project focuses on:
- **Encoding and transmitting image data** from the sender device.
- **Receiving and reconstructing the image** at the receiver end.
- **Using RFM9X (LoRa) or serial communication** to transfer images efficiently.
- **Handling data chunks, markers, and file integrity verification**.

---

## ✅ **Key Features**
✔ **Wireless Image Transmission** using **RFM9X or Serial Communication**.  
✔ **Data Chunking & Reconstruction** to ensure **accurate image recovery**.  
✔ **Efficient Data Transfer** with **start, end, and transmission markers**.  
✔ **Cross-Platform Compatibility**: Works on **Raspberry Pi, Arduino, and PC**.  
✔ **Error Handling & Data Integrity Checks** during transmission.  

---

## 🛠 **Installation & Setup**
### **1️⃣ Clone the Repository**
```bash
git clone https://github.com/vinay2201/Image-Transmission-using-RFM9X.git
cd Image-Transmission-using-RFM9X
```

### **2️⃣ Install Required Dependencies**
```bash
pip install pyserial

```

Ensure that Arduino IDE is installed for flashing the .ino files onto an Arduino board.

### 3️⃣ **Upload Arduino Code**
- Flash sender_image_arduino.ino onto the Arduino Sender.
- Flash receiver_image_arduino.ino onto the Arduino Receiver.

### 4️⃣ **Run Python Scripts for Serial Communication**
On the Sender Side (Raspberry Pi)
```bash
python Sender_image.py

```
On the Receiver Side (PC/Arduino)

```bash
python receiver_image.py
```

### 📊 **How the Transmission Works**
Image Encoding & Chunking

- The sender script reads an image file and encodes it into a hexadecimal format.
- The data is split into smaller chunks for reliable transmission.
- Each chunk is marked with start (<START>) and end (<END>) markers.

Serial Transmission via RFM9X

- The encoded data chunks are sent via serial communication or LoRa.
- An End of Transmission (<EOT>) marker is added to signal completion.

Receiving & Image Reconstruction

- The receiver collects incoming data chunks and reconstructs the original image.
- The received data is converted back to binary format and saved as an image file.

### 📄 **License**
This project is licensed under the MIT License
