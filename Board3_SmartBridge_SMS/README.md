# Board 3: Smart Bridge Control and Emergency Communication

Board 3 is responsible for the control of the smart bridge in case of flooding, it also manages emergency communication (call & SMS) in response to fire & flood incidents.

## Connections

- **Servo Motors for Bridge Control**:
  - Servo 1: Connected to pin `servoPin (5)`.
  - Servo 2: Connected to pin `servoPin2 (6)`.

- **Fire Signal In (from Board 2 - Fire Sigal Out)**: Connected to pin `fireInPin (10)`.
- **Flood Signal In (from Board 2 - Flood Signal Out)**: Connected to pin `in (9)`.

- **Emergency Communication**:
  - SIM900 TX: Connected to pin `7`.
  - SIM900 RX: Connected to pin `8`.
  - Buzzer (for emergency alarm): Connected to pin `alarmBuzzerPin (11)`.

- NB: all negative (-ve/GND) wires are connected to GND.

> For detailed connections, refer to the [**Circuit Diagram**](../radiance-smart-city-circuit-diagram.jpg).

## Smart Bridge Control

- The servos control the bridge's position.
  - **Bridge Up Position**: `BRIDGE_UP_POSITION (70)`.
  - **Bridge Down Position**: `BRIDGE_DOWN_POSITION (0)`.

## Fire and Water Emergency Communication

- **Fire Detection**:
  - Fire Signal In: Connected to pin `fireInPin (10)`.
  - Automatic emergency call and SMS alert are triggered in case of fire.
- **Water Level Detection**:
  - Flood Signal In: Connected to pin `waterInPin (9)`.
  - Automatic emergency call and SMS alert are triggered in case of rising water levels.

## Usage

1. Adjust configurations in the code if necessary.
2. Upload the [**Board3_SmartBridge_SMS.ino**](./Board3_SmartBridge_SMS.ino) code to your Arduino board.
3. Connect the components as specified in the connections section.
4. Power on the system and test the smart bridge control and emergency communication systems.

> Refer to the [code file](./Board3_SmartBridge_SMS.ino) for detailed comments and configuration instructions.

## Contributing

Contribute to the improvement of the smart bridge and emergency communication by creating issues, suggesting new features, or opening pull requests.


## Authors

<details>
    <summary>Emmanuel Ademola</summary>
    <ul>
    <li><a href="https://www.github.com/emmanueldev247">Github</a></li>
    <li><a href="https://www.twitter.com/emmanueldev247">Twitter</a></li>
    <li><a href="mailto:mailemmydee@gmail.com">E-mail</a></li>
    <li><a href="https://emmanueldev247.publicvm.com">Portfolio</a></li>
    </ul>
</details>
<details>
    <summary>Emeka Amah</summary>
    <ul>
    <li><a href="mailto:patnet84@gmail.com">E-mail</a></li>
    </ul>
</details>
