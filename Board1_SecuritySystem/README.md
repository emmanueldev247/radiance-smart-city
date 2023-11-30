# Board 1: Security System

This board is responsible for implementing the security features of the Radiance Smart City project. It controls access to the estate through a sophisticated RFID-based boom barrier system and allows for manual control using remotes. Additionally, it provides visual feedback through LEDs and an audible alarm in case of unauthorized access.

## Connections

- **RFID Module**: Connected to pins `SS_PIN (10)` and `RST_PIN (9)`
  - MOSI (11)
  - MISO (12)
  - VCC (3.3v)

- **LEDs and Buzzer**:
  - Red LED: Connected to pin `RED_LED (7)`.
  - Green LED: Connected to pin `GREEN_LED (6)`.
  - Buzzer: Connected to pin `BUZZER_PIN (3)`.

- **Servo Motor (Gate)**: Connected to pin `5`.

- **Remote Signal Pin (from Board 2)**: Connected to pin `REMOTE_SIGNAL_PIN (4)`.

- **Lock Down Pin (from Board 2)**: Connected to pin `LOCK_DOWN_PIN (2)`.

- NB: all negative (-ve/GND) wires are connected to GND.

> For detailed connections, refer to the [**Circuit Diagram**](../RSC-circuit-diagram.jpg).

## RFID Access Cards

The access cards, defined in the code, are used for controlling valid access. Make sure to update the `residentCards` array with the appropriate RFID card IDs.

## Usage

1. Adjust configurations in the code if necessary, such as RFID card IDs.
2. Upload the [**Board1_SecuritySystem.ino**](./Board1_SecuritySystem.ino) code to your Arduino board.
3. Connect the components as specified in the connections section.
4. Power on the system and test the RFID access control and manual remote control features.

> Refer to the [code file](./Board1_SecuritySystem.ino) for detailed comments and configuration instructions.

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
    <li><a href="patnet84@gmail.com">e-mail</a></li>
    </ul>
</details>
