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

- **Remote Signal Pin (from Board 2 - Gate Control Pin)**: Connected to pin `REMOTE_SIGNAL_PIN (4)`.

- **Lock Down Pin (from Board 2)**: Connected to pin `LOCK_DOWN_PIN (2)`.

- NB: all negative (-ve/GND) wires are connected to GND.

> For detailed connections, refer to the [**Circuit Diagram**](../RSC-circuit-diagram.jpg).

## RFID Access Cards

The access cards, defined in the code, are used for controlling valid access. Make sure to update the `residentCards` array with the appropriate RFID card IDs.

## Remote Control Functionality

**Gate Control**: The remote facilitates the opening and closing of the gate. When the appropriate button is pressed, it triggers the gate control pin from board 2 `controlgate (4)` which then sends a signal to board 1 `REMOTE_SIGNAL_PIN (4)`, ensuring seamless access.

**Lockdown Mode Activation**:  The remote is equipped with a unique functionality — activating a lockdown mode. When the appropriate button is pressed, it triggers the gate lockdown pin from board 2 `gateLockdownPin (5)` which then sends a signal to board 1 `LOCK_DOWN_PIN (2)` to activate the lockdown mode. During lockdown, access card functionality is temporarily disabled, preventing entry using RFID access cards. In this mode, the gate can only be operated using the remote, adding an extra layer of security. Once the security concern is resolved, the lockdown can be lifted. After lifting the lockdown, RFID access cards regain their functionality, and gate control returns to normal, allowing both remote and access cards for operation.

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
    <li><a href="mailto:patnet84@gmail.com">e-mail</a></li>
    </ul>
</details>
