# Nios II on Arduino
create nexessary library to allow Arduino IDE compile with Nios II target
Still very early development, just able to compile a hello world program. 
Major porting oc core library code needed.

Require seperate installtion of Nios II GCC toolchain.
I install ACDS 15.1 Lite

Just copy and put entire intel folder into arduino_install_dir/hardware/intel/nios2 folder, and modify platform.txt to point to nios2-elf-gcc directory
