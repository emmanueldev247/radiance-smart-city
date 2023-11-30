# Board 2: Energy Management and Environmental Monitoring

This board focuses on energy efficiency and environmental monitoring within the Radiance Smart City project. It manages street lighting based on ambient light conditions, allows manual control via remote, and monitors fire and flood situations.

## Connections

- **IR Receiver**: Connected to pins `6`.
- **LDR (Light Dependent Resistor)**: Connected to pin `A0`.
- **Water Level Sensor**: Connected to pin `A1`.
- **Street Light LEDs**: Connected to pin `SLledPin (8)`.
- **Gate Control Pin (from Board 1 - Remote Signal Pin)**: Connected to pin `controlgate (4)`.
- **Alarm System, LEDs and Buzzer**:
  - **Fire Alarm**:
    - Fire Sensor: Connected to pin `flameInPin (7)`.
    - Fire Red LED: Connected to pin `fireRedLedPin (13)`. Indicates fire detection.
    - Fire Green LED: Connected to pin `fireGreenLedPin (12)`. Indicates no fire.
    - Water Level Sensor: Connected to pin `waterInPin (A1)`.
  - **Water Alarm**:
    - Water Red LED: Connected to pin `waterRedLedPin (3)`. Indicates rising water levels.
    - Water Green LED: Connected to pin `waterGreenLedPin (2)`. Indicates safe water levels.
  - Buzzer: Connected to pin `alarmBuzzerPin (11)`.
- NB: all negative (-ve/GND) wires are connected to GND.

## LDR (Light Dependent Resistor) Mode and Remote Control

- LDR Mode: The street lights are controlled based on ambient light conditions using the LDR sensor.
- Remote Control: The IR remote allows manual control of street lights and gate (lockdown & open/close)


## Fire and Water Alarm System Operation
- Fire Alarm System: The fire sensor constantly monitor the environment for potential fire incidents.
- Water Alarm System: The water level sensor actively gauges water levels.
- Both systems, integrates visual indicators to signal detection, ensuring a visual distinction. In conjunction with the visual indicators, an alarm is employed to provide an audible alert during critical situations.

> For detailed connections, refer to the [**Circuit Diagram**](../RSC-circuit-diagram.jpg).

## Usage

1. Adjust configurations in the code if necessary.
2. Upload the [**Board2_EnergyManagement.ino**](./Board2_EnergyManagement.ino) code to your Arduino board.
3. Connect the components as specified in the connections section.
4. Power on the system and test the LDR-based street light control, remote functions, and fire/water alarm systems.

> Refer to the [code file](./Board2_EnergyManagement.ino) for detailed comments and configuration instructions.

## Contributing

Feel free to contribute to the enhancement of the security system by creating issues, submitting feature requests, or opening pull requests.

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
    <li><a href="mailto:patnet84@gmail.com">e-mail</a></li>
    </ul>
</details>
