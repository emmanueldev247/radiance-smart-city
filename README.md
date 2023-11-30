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
   - Our Web App (demo) is live at [Radiance Smart City Web App](https://radiancesmartcity.free.nf).

## Code Structure

The project consists of three boards, each with its specific functionality:

### Board 1: Security System

- [**Directory**](./Board1_RFID_SecuritySystem): `Board1_SecuritySystem`
- [**Code File**](./Board1_RFID_SecuritySystem/Board1_SecuritySystem.ino): `Board1_SecuritySystem.ino`
- [**Documentation**](./Board1_RFID_SecuritySystem/README.md): `README.md`


### Board 2: Energy Control and Emergency Alerts

- [**Directory**](./Board2_EnergyEmergency): `Board2_EnergyEmergency`
- [**Code File**](./Board2_EnergyEmergency/Board2_EnergyEmergency.ino): `Board2_EnergyEmergency.ino`
- [**Documentation**](./Board2_EnergyEmergency/Board2_EnergyEmergency/README.md): `README.md`

### Board 3: Smart Bridge and Emergency Communication

- [**Directory**](./Board3_SmartBridge_SMS): `Board3_SmartBridge_SMS`
- [**Code File**](./Board3_SmartBridge_SMS/Board3_SmartBridge_SMS.ino): `Board3_SmartBridge_SMS.ino`
- [**Documentation**](./BBoard3_SmartBridge_SMS/README.md): `README.md`

Feel free to explore the documentation for each board to understand their features, use cases, and implementation details. If you have any questions or need further assistance, don't hesitate to reach out. Happy exploring!

## How to Use

1. Clone the repository: `git clone https://github.com/emmanueldev247/Radiance-Smart-City.git`
2. Ensure the required libraries (e.g., MFRC522, Servo, IRremote) are installed.
3. Follow the instructions in each board's README for uploading the respective code and setting up the connections.


## Contributing

Contribute to the improvement of Radiance Smart City by creating issues, suggesting new features, or opening pull requests.

> Enjoy building a smarter and safer city with Radiance Smart City!

## Authors

<details>
    <summary>Emmanuel Ademola</summary>
    <ul>
    <li><a href="https://www.github.com/emmanueldev247">Github</a></li>
    <li><a href="https://www.twitter.com/emmanueldev247">Twitter</a></li>
    <li><a href="mailto:mailemmydee@gmail.com">e-mail</a></li>
    </ul>
</details>
<details>
    <summary>Emeka Amah</summary>
    <ul>
    <li><a href="patnet84@gmail.com">e-mail</a></li>
    </ul>
</details>
