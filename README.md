# HogReborns

HogReborns is an ambitious project aimed at creating an immersive and customizable multiplayer experience for an environment based on **Hogwarts Legacy**. This project combines client scripts (via **UE4SS**) with a server built using the **ENet** networking library.

---

## Key Features

- **Dynamic Connection/Disconnection**: Enable or disable multiplayer mode directly in-game with a configurable key.
- **Ping Display**: View your latency in real-time directly on the user interface.
- **Custom Server**: Efficient connection management and player synchronization with a backend written in C++.
- **Scalable Client Scripts**: Harness the power of Lua via UE4SS to enhance gameplay.

---

## Prerequisites

### **Tools and Dependencies**

- **Visual Studio 2019 or 2022** (with the C++ development module)
- **CMake** (to compile the ENet library)
- **Required Libraries**:
  - [ENet](https://github.com/lsalzman/enet)
  - `Ws2_32.lib` and `Winmm.lib` (included with the Windows SDK)

### **Required Files**

- UE4SS: To inject Lua scripts into the game client.
- Custom configuration files for UE4SS and ENet (available in this repository).

---

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/HogReborns.git
   ```

2. Compile the **ENet** library:

   ```bash
   cd enet-master
   cmake .
   cmake --build .
   ```

   This will generate the `enet.lib` file in the `Debug` or `Release` directory.

3. Configure your environment:

   - Place the compiled files (server and client scripts) in their corresponding directories.
   - Ensure that **UE4SS** is properly installed along with the Lua files from this project.

4. Start the server:

   ```bash
   ./HogRebornsServer.exe
   ```

5. Launch the client and press the configured key (`Insert` by default) to activate multiplayer mode.

---

## Usage

### **In-Game Controls**

- **Enable/Disable Multiplayer**: Press `Insert`.
- **Ping Display**: Shown in the top-right corner of the screen once connected to the server.

### **Customization**

- Modify the Lua files to adjust client behavior.
- Change the server port or connection settings in the main configuration file.

---

## Contribution

Contributions are welcome! Here's how you can help:

1. Fork this repository.
2. Create a branch for your changes:
   ```bash
   git checkout -b my-new-feature
   ```
3. Make your changes and submit a Pull Request.

---

## Support

If you have questions or encounter issues, open an **Issue** on this repository or contact me directly.

---

## License

This project is licensed under the **MIT** License. See the [LICENSE](LICENSE) file for details. 

