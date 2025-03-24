# ft232r_cbus
Customized version of example code from 
[LibFTDI](https://www.intra2net.com/en/developer/libftdi/repository.php)

ft232r_cbus is an interactive terminal program to control cbus pins[0-3]
  
### SEQUENCES: 
`Note: CBus[3]=BOOT0,  Cbus[2]=RST is pre-invert of uC-nRst, CBus[1,0] as inputs)`

| Seq | Value | BOOT-0 | RST  | Enter BootLoader Mode                  |
|-----|-------|--------|------|----------------------------------------|
| 1   | 0xCC  | High   | High | BootLoader-Mode in Reset               |
| 2   | 0xC8  | High   | Low  | Bootloader-Mode RUN                    |
| 3   | 0x00  | Low    | Low  | Release                                |

| Seq | Value | BOOT-0 | RST  | Run Normal Mode                        |
|-----|-------|--------|------|----------------------------------------|
| 1   | 0xC4  | Low    | High | Normal-Mode in Reset                   |
| 2   | 0xC0  | Low    | Low  | Normal-Mode RUN (pins driven)          |
| 3   | 0x00  | Low    | Low  | Release (Reset-PullUp, Boot0-pullDown) |

##Build
### Linux
```bash
cd ~/ft232r_cbus && make
```
### MacOs & CLion (debug on Linux)
- Ensure Tools and libraries are installed
```bash
sudo apt-get install cmake
sudo apt-get install libftdi1-dev
```
In CLion - Open PRoject folder and select CMakeLists.txt as the CMake file

CLion - Settings / Build,Execution,Deployment / Toolchains
- Add a new "Remote Host" toolchain
- Set the "Credentials" to your Remote Linux machine (SSH connection)

CLion - Settings / Build,Execution,Deployment / CMake
- Switch to the Toolchain: to the new "Remote Host" selection

CLion - Tools / CMake / Reset Cache and Reload Project
Build the project

To Change the deploy/build folder on the remote machine. (instead of /tmp/)
- Open RemoteHost viewer
- Select remote linux ssh connection
- edit settings / RootPath: to `/home/lvt/ft232r_cbus`
- edit settings / Mapping: to `/`
