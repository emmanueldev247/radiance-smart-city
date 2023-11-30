# Radiance Smart City

Welcome to the Radiance Smart City project repository. This real estate solution integrates cutting-edge technology to enhance security, energy efficiency, and emergency response systems.

## Features

### 1. Security

- **Boom Barrier System**: A sophisticated security measure using RFID technology. Access is granted only to valid cardholders, and the boom barrier can be controlled by security personnels using remotes.

### 2. Energy Savings

- **Street Light Control**:
  - **Automatic Mode (Default)**: LDR sensors ensure that street lights are turned on only in darkness.
  - **Manual Mode**: Remote control allows manual control of street lights.

### 3. Emergency Response

- **Fire and Flood Alarms**:
  - **Detection**: Sensors identify fire and flood incidents.
  - **Notification**: Immediate alarms and notifications through SMS and calls to the designated emergency agency.

### 4. Smart Bridge

- **Flood Response**: In case of a flood, the bridge is automatically raised using servo motors to a safe level.

### 5. Project Web App

- **A Comprehensive Community Hub**.
   - Order groceries, generate visitor codes, and report incidents seamlessly.
   - Contact security, report crimes, or emergencies for a safer and more connected community.
   - Our Web App is live at [Radiance Smart City Web App](https://radiancesmartcity.free.nf).

## Code Structure

The project consists of three boards, each with its specific functionality:

### Board 1: Security System

- **Directory**: `Board1_SecuritySystem`
- [**Directory**](./Board1_RFID_SecuritySystem/): `Board1_SecuritySystem`
- [**Code File**](./Board1_RFID_SecuritySystem/Board1_SecuritySystem.ino): `Board1_SecuritySystem.ino`
- [**Documentation**](./Board1_RFID_SecuritySystem/README.md): `README.md`


### Board 2: Energy Control and Emergency Alerts

- **Directory**: `Board2_EnergyEmergency`
- **Code File**: `Board2_EnergyEmergency.ino`

### Board 3: Smart Bridge and Emergency Communication

- **Directory**: `Board3_SmartBridge_SMS`
- **Code File**: `Board3_SmartBridge_SMS.ino`

Feel free to explore the documentation for each board to understand their features, use cases, and implementation details. If you have any questions or need further assistance, don't hesitate to reach out. Happy exploring!

## Board-Specific READMEs

2. [Board 2 - Energy Savings and Alarms](./Board2_EnergySavings_Alarms/README.md)
3. [Board 3 - Smart Bridge Control and Emergency Communication](./Board3_SmartBridge_SMS/README.md)

## How to Use

1. Clone the repository: `git clone https://github.com/your-username/Radiance-Smart-City-2.0.git`
2. Upload the respective code files to each Arduino board.
3. Ensure the required libraries (e.g., MFRC522, Servo, IRremote) are installed.

## Board-specific Instructions

- **Board 1**: Connect RFID, LEDs, and Servo as per the defined pins.
- **Board 2**: Connect IR receiver, LDR, and LEDs as specified.
- **Board 3**: Connect Servos, flame, and water sensors according to the defined pins.

Refer to the individual code files for detailed comments and configuration instructions.

## Contributing

Feel free to contribute to the project by creating issues, submitting feature requests, or opening pull requests.

Enjoy building a smarter and safer city with Radiance Smart City 2.0!

